#include "../include/Server.h"

using namespace std;

Server::Server()
{
    this->loadUserData(userDataPath);

    this->listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->listenfd == -1) {
        perror("Error");
        exit(1);
    }
    int enable = 1;
    if (setsockopt(this->listenfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    bzero(&this->servAddr, sizeof(this->servAddr));
    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->servAddr.sin_port = htons(SERVER_PORT);

    if (bind(this->listenfd, (const sockaddr*)&this->servAddr, sizeof(this->servAddr))) {
        perror("Error");
        exit(1);
    }

    if (listen(this->listenfd, 10)) {
        perror("Error! Cannot listen!");
        exit(1);
    }
    cout << "Server Started!\n";
}

Server::~Server()
{
    for (auto user : this->listUser) {
        delete user;
    }
    this->listUser.clear();
}

void Server::run()
{
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    signal(SIGCHLD, sig_chld);
    int connfd;

    while (1) {
        // Accept request
        connfd = accept(this->listenfd, (sockaddr*)&clientAddr, &clientAddrLen);
        if (connfd < 0) {
            perror("Error");
            exit(1);
        }
        this->pid = fork();
        cout << "Pid" << this->pid << endl;
        if (this->pid == 0) {
            close(this->listenfd);
            printf("You got a connection from port %d\n", ntohs(clientAddr.sin_port));
            User *clientUser = nullptr;
            while (1) {
                this->rcvFromClient(connfd, clientAddr);
                switch (getCode(this->buff)) {
                case RQ_REGISTER:
                    this->rq_register();
                    this->sendToClient(connfd, clientAddr);
                    break;
                
                case RQ_LOGIN:
                    this->rq_login(&clientAddr, clientUser);
                    this->sendToClient(connfd, clientAddr);
                    break;

                case RQ_LOGOUT:
                    this->rq_logout(clientUser);
                    this->sendToClient(connfd, clientAddr);
                    break;

                case RQ_CREATE_ROOM:
                    this->rq_createRoom(clientUser);
                    this->sendToClient(connfd, clientAddr);
                    break;
                default:
                    break;
                }
            }
            close(connfd);
            exit(0);
        }

        close(connfd);
    }
    close(this->listenfd);
}

void Server::loadUserData(string path)
{
    ifstream ReadFile(path);
    string line;
    string delimiter = " ";

    while (getline(ReadFile, line)) {
        string username = line.substr(0, line.find(delimiter));
        string password = line.substr(line.find(delimiter) + 1, line.length());

        User* user = new User(username, password);
        this->listUser.push_back(user);
    }
    ReadFile.close();
}

void sig_chld(int sig_no)
{
    pid_t pid;
    int stat;
    pid = waitpid(-1, &stat, WNOHANG);
    printf("child %d terminated\n", pid);
}

void Server::rq_register()
{
    struct rq_register rq = message_to_rq_register(this->buff);
    struct rp_register rp;

    bool check = true;
    for (auto user : this->listUser) {
        if (user->getUsername().compare(rq.username) == 0) {
            rp.accept = false;
            rp.notification = "User existed!!";
            check = false;
            break;
        }
    }
    if (check) {
        rp.accept = true;

        User* u = new User(rq.username, rq.password);
        this->listUser.push_back(u);

        ofstream WriteFile;
        WriteFile.open(userDataPath, std::ios_base::app);
        WriteFile << rq.username << " " << rq.password << "\n";
    }
    
    struct_to_message(&rp, RP_REGISTER, this->buff);

}

void Server::rq_login(struct sockaddr_in *clientAddr, User *&clientUser) {
    struct rq_login rq = message_to_rq_login(this->buff);
    struct rp_login rp;

    bool check = false;
    User *target = nullptr;
    for (auto user:this->listUser) {
        if (user->getUsername().compare(rq.username) == 0) {
            check = true;
            target = user;
            break;
        }
    }
    if (!check) {
        rp.accept = false;
        rp.notification = "Username not exist.";
    } else {
        if (target->checkPassword(rq.password)) {
            if (target->isOnline()) {
                rp.accept = false;
                rp.notification = "User online.";
            } else {
                rp.accept = true;
            }
        } else {
            rp.accept = false;
            rp.notification = "Wrong password.";
        }
    }
    
    if (rp.accept) {
        target->setClientAddr(clientAddr);
        target->setState(ONLINE);
        clientUser = target;
        rp.username = target->getUsername();
    }
    struct_to_message(&rp, RP_LOGIN, this->buff);
}

void Server::rq_logout(User *&clientUser) {
    cout << clientUser->getUsername() << endl;
    struct rq_logout rq = message_to_rq_logout(this->buff);
    struct rp_logout rp;

    clientUser->setState(OFFLINE);
    rp.accept = true;
    
    struct_to_message(&rp, RP_LOGOUT, this->buff);
    
    cout << this->buff << endl;
}

void Server::rq_createRoom(User *&clientUser) {
    rq_create_room rq = message_to_rq_create_room(this->buff);
    rp_create_room rp;

    if(this->listRoom.size() < MAX_ROOM) {
        Room *newRoom = new Room(rq.name, clientUser);

        rp.accept = true;
    } else {
        rp.accept = false;
        rp.notification = "Reach Max Room";
    }
    
    struct_to_message(&rp, RP_CREATE_ROOM, this->buff);
}


void Server::rcvFromClient(int connfd, struct sockaddr_in clientAddr) {
    int rcvBytes = recv(connfd, this->buff, BUFF_SIZE, 0);
    if (rcvBytes < 0) {
        perror("Error");
    }
    if (rcvBytes == 0) {
        close(connfd);
        exit(0);
    }
    this->buff[rcvBytes] = '\0';

    cout << "\nReceive from " << ntohs(clientAddr.sin_port) << "\n{\n" << this->buff << "\n}\n";
}

void Server::sendToClient(int connfd, struct sockaddr_in clientAddr) {
    int sendBytes = send(connfd, this->buff, strlen(this->buff), 0);
    if(sendBytes < 0) {
        perror("Error");
    }
    cout << "\nSend to " << ntohs(clientAddr.sin_port) << "\n{\n" << this->buff << "\n}\n";
}