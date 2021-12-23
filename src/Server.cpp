#include "../include/Server.h"

using namespace std;

std::vector<User *> Server::listUser;
std::vector<Room *> Server::listRoom;

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
    for (auto user : Server::listUser) {
        delete user;

    }
    Server::listUser.clear();
    for (auto room : Server::listRoom) {
        delete room;
    }
    Server::listRoom.clear();
}

void Server::run()
{
    struct sockaddr_in clientAddr;
    int connfd;
    socklen_t clientAddrLen = sizeof(struct sockaddr_in);

    while (1) {
        // Accept request
        connfd = accept(this->listenfd, (sockaddr*)&clientAddr, &clientAddrLen);
        if (connfd < 0) {
            perror("Error");
            exit(1);
        }
        cout << "\nGet connection from " << ntohs(clientAddr.sin_port) << "\n";
        pthread_t new_thread;
        if (pthread_create(&new_thread, nullptr, routine, &connfd) < 0) {
            perror("Could not create thread:");
            exit(1);
        }
        this->threads.push_back(new_thread);
        
    }
    for (auto thread: this->threads) {
            pthread_join(thread, nullptr);
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
        Server::listUser.push_back(user);
    }
    ReadFile.close();
}

void Server::rq_register(char *rq_register, char *rp_register)
{
    struct rq_register rq = message_to_rq_register(rq_register);
    struct rp_register rp;

    bool check = true;
    for (auto user : Server::listUser) {
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
        Server::listUser.push_back(u);

        ofstream WriteFile;
        WriteFile.open(userDataPath, std::ios_base::app);
        WriteFile << rq.username << " " << rq.password << "\n";
    }
    
    struct_to_message(&rp, RP_REGISTER, rp_register);

}

void Server::rq_login(char *rq_login, char *rp_login, int connfd, User *&clientUser) {
    struct rq_login rq = message_to_rq_login(rq_login);
    struct rp_login rp;

    bool check = false;
    User *target = nullptr;
    for (auto user:Server::listUser) {
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
        target->setConnfd(connfd);
        target->setState(ONLINE);
        clientUser = target;
        rp.username = target->getUsername();
    }
    struct_to_message(&rp, RP_LOGIN, rp_login);
}

void Server::rq_logout(char *rq_logout, char *rp_logout, User *&clientUser) {
    struct rq_logout rq = message_to_rq_logout(rq_logout);
    struct rp_logout rp;

    clientUser->setState(OFFLINE);
    rp.accept = true;
    
    struct_to_message(&rp, RP_LOGOUT, rp_logout);
}

void Server::rq_createRoom(char *rq_createRoom, char *rp_createRoom, User *&clientUser) {
    rq_create_room rq = message_to_rq_create_room(rq_createRoom);
    rp_create_room rp;

    if(Server::listRoom.size() < MAX_ROOM) {
        Room *newRoom = new Room(rq.name, clientUser);
        Server::listRoom.push_back(newRoom);
        rp.accept = true;
    } else {
        rp.accept = false;
        rp.notification = "Reach Max Room";
    }
    
    struct_to_message(&rp, RP_CREATE_ROOM, rp_createRoom);
}


void Server::rcvFromClient(int connfd, char *rcv_message) {
    int rcvBytes = recv(connfd, rcv_message, BUFF_SIZE, 0);
    if (rcvBytes < 0) {
        perror("Error");
    }
    if (rcvBytes == 0) {
        close(connfd);
        exit(0);
    }
    rcv_message[rcvBytes] = '\0';

    cout << "\nReceive: " << "\n{\n" << rcv_message << "\n}\n";
}

void Server::sendToClient(int connfd, char *send_message) {
    int sendBytes = send(connfd, send_message, strlen(send_message), 0);
    if(sendBytes < 0) {
        perror("Error");
    }
}

void* Server::routine(void *client_socket) {
    int connfd = *(int *)client_socket;
    
    User *clientUser = nullptr;
    char rcv_message[BUFF_SIZE + 1], send_message[BUFF_SIZE + 1];
    
    bool exit_check = false;
    while (!exit_check) {
        Server::rcvFromClient(connfd, rcv_message);
        switch (getCode(rcv_message)) {
        case RQ_EXIT:
            exit_check = true;
            clientUser->setState(OFFLINE);
            break;
        case RQ_REGISTER:
            Server::rq_register(rcv_message, send_message);
            Server::sendToClient(connfd, send_message);
            break;
        
        case RQ_LOGIN:
            Server::rq_login(rcv_message, send_message, connfd, clientUser);
            Server::sendToClient(connfd, send_message);
            break;

        case RQ_LOGOUT:
            Server::rq_logout(rcv_message, send_message, clientUser);
            Server::sendToClient(connfd, send_message);
            break;

        case RQ_CREATE_ROOM:
            Server::rq_createRoom(rcv_message, send_message, clientUser);
            Server::sendToClient(connfd, send_message);
            break;
        default:
            break;
        }
    }
    close(connfd);

    return nullptr;
}