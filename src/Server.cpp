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
    int rcvBytes, sendBytes;
    signal(SIGCHLD, sig_chld);
    int connfd;

    while (1) {
        // Accept request
        connfd = accept(this->listenfd, (sockaddr*)&clientAddr, &clientAddrLen);
        cout << connfd << endl;
        if (connfd < 0) {
            perror("Error");
            exit(1);
        }
        this->pid = fork();
        if (this->pid == 0) {
            close(this->listenfd);
            printf("You got a connection from port %d\n", ntohs(clientAddr.sin_port));
            while (1) {
                rcvBytes = recv(connfd, this->buff, BUFF_SIZE, 0);
                if (rcvBytes < 0) {
                    perror("Error");
                }
                if (rcvBytes == 0) {
                    close(connfd);
                    exit(0);
                }
                this->buff[rcvBytes] = '\0';
                switch (getCode(this->buff)) {
                case RQ_REGISTER:
                    this->rq_register();
                    this->sendToClient(connfd);
                    break;
                
                case RQ_LOGIN:
                    this->rq_login();

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
        rp.notification = "";

        User* u = new User(rq.username, rq.password);
        this->listUser.push_back(u);

        ofstream WriteFile;
        WriteFile.open(userDataPath, std::ios_base::app);
        WriteFile << rq.username << " " << rq.password << "\n";
    }
    
    struct_to_message(&rp, RP_REGISTER, this->buff);
}

void Server::rq_login() {
    struct rq_login rq = message_to_rq_login(this->buff);
    struct rp_login rp;
    
}


void Server::sendToClient(int connfd) {
    int sendBytes = send(connfd, this->buff, strlen(this->buff), 0);
    if(sendBytes < 0) {
        perror("Error");
    }
    cout << "\nSend; \n" << this->buff << "\n";
}