#include "../include/Server.h"

using namespace std;

vector<User *> Server::listUser;
vector<Room *> Server::listRoom;
vector<UserClient *> Server::listClient;

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
    int connfd1, connfd2;
    socklen_t clientAddrLen = sizeof(struct sockaddr_in);

    while (1) {
        // Accept request
        UserClient *userClient = new UserClient(nullptr);

        connfd1 = accept(this->listenfd, (sockaddr*)&clientAddr, &clientAddrLen);
        if (connfd1 < 0) {
            perror("Error");
            exit(1);
        }
        cout << "\nGet connection from " << ntohs(clientAddr.sin_port) << "\n";
        connfd2 = accept(this->listenfd, (sockaddr*)&clientAddr, &clientAddrLen);
        if (connfd2 < 0) {
            perror("Error");
            exit(1);
        }
        cout << "\nGet connection from " << ntohs(clientAddr.sin_port) << "\n";

        userClient->setClientfd(connfd1);
        userClient->setWritefd(connfd2);

        Server::listClient.push_back(userClient);

        pthread_t new_thread;
        if (pthread_create(&new_thread, nullptr, Server::routine1, userClient) < 0) {
            perror("Could not create thread:");
            exit(1);
        }
        this->threads.push_back(new_thread);

        pthread_t new_thread2;
        if(pthread_create(&new_thread2, nullptr, Server::routine2, userClient) < 0) {
            perror("Could not create thread: ");
            exit(1);
        }
        this->threads.push_back(new_thread2);
        
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

void Server::rq_login(char *rq_login, char *rp_login, int connfd, UserClient *&userClient) {
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
        userClient->setUser(target);
        target->setState(ONLINE);
        rp.username = target->getUsername();

        Server::updateLobby(userClient);
    }
    struct_to_message(&rp, RP_LOGIN, rp_login);
}

void Server::rq_logout(char *rq_logout, char *rp_logout, UserClient *&userClient) {
    struct rq_logout rq = message_to_rq_logout(rq_logout);
    struct rp_logout rp;

    userClient->getUser()->setState(OFFLINE);
    userClient->setUser(nullptr);
    rp.accept = true;
    
    struct_to_message(&rp, RP_LOGOUT, rp_logout);
}

void Server::rq_createRoom(char *rq_createRoom, char *rp_createRoom, UserClient *&userClient) {
    rq_create_room rq = message_to_rq_create_room(rq_createRoom);
    rp_create_room rp;
    if(Server::listRoom.size() < MAX_ROOM) {
        bool check = true;
        for(auto room: Server::listRoom) {
            if (room->getName().compare(rq.name) == 0) {
                check = false;
                rp.accept = false;
                rp.notification = "Room name existed!!";
                break;
            }
        }

        if (check) {

            Room *newRoom = new Room(rq.name, vector<UserClient *>{userClient}, vector<bool>{false});
            Server::listRoom.push_back(newRoom);
            userClient->setRoom(newRoom);
            rp.accept = true;
            rp.roomname = rq.name;

            Server::updateLobby();
            sleep(0.1);
            Server::updateRoom(newRoom);

        }
        
    } else {
        rp.accept = false;
        rp.notification = "Reach Max Room";
    }
    struct_to_message(&rp, RP_CREATE_ROOM, rp_createRoom);
}

void Server::rq_joinRoom(char *rq_joinRoom, char *rp_joinRoom, UserClient *&userClient) {
    rq_join_room rq = message_to_rq_join_room(rq_joinRoom);
    rp_join_room rp;

    Room *room_target = nullptr;

    for (auto room: Server::listRoom) {
        if (room->getName().compare(rq.room_name) == 0) {
            room_target = room;
            break;
        }
    }

    if (room_target == nullptr) {
        rp.accept = false;
        rp.notification = "Room name not exist!!";
    } else if(room_target->getNumberUser() == 4) {
        rp.accept = false;
        rp.notification = "Full!";
    } else {
        rp.accept = true;
        room_target->addUser(userClient);
        userClient->setRoom(room_target);

        Server::updateLobby();
        sleep(0.1);
        Server::updateRoom(room_target);
    }

    struct_to_message(&rp, RP_JOIN_ROOM, rp_joinRoom);
}

void Server::rq_exitRoom(UserClient *&userClient) {
    Room *room_target = userClient->getRoom();

    cout << room_target->getNumberUser() << endl;

    if(room_target->getNumberUser() == 1) {
        for (int i = 0; i < Server::listRoom.size(); i++) {
            if (Server::listRoom.at(i) == room_target) {
                Server::listRoom.erase(Server::listRoom.begin() + i);
                break;
            }
        }
    } else {
        room_target->removeUser(userClient);
        Server::updateRoom(room_target);
    }
    userClient->setRoom(nullptr);
    Server::updateLobby();
}

void Server::rq_ready(UserClient *&userClient) {
    Room *room_target = userClient->getRoom();
    room_target->setReady(userClient);
    Server::updateRoom(room_target);
}

struct update_lobby Server::to_struct_update_lobby() {
    struct update_lobby res;
    for (auto room: Server::listRoom) {
        res.name.push_back(room->getName());
        res.ingame.push_back(room->isIngame());
        res.number_user.push_back(room->getNumberUser());
    }
    return res;
}
struct update_room Server::to_struct_update_room(Room *&room) {
    struct update_room res;
    res.room_name = room->getName();

    for (auto user: room->getListUser()) {
        res.username.push_back(user->getUser()->getUsername());
        res.ready = room->getReady();
    }
    return res;
}


void Server::updateLobby() {
    struct update_lobby res = Server::to_struct_update_lobby();
    char send_msg[BUFF_SIZE + 1];
    struct_to_message(&res, UPDATE_LOBBY, send_msg);

    for (auto client: Server::listClient) {
        Server::sendToClient(client->getWritefd(), send_msg);
    }

}
void Server::updateLobby(UserClient *&userClient) {
    struct update_lobby res = Server::to_struct_update_lobby();
    char send_msg[BUFF_SIZE + 1];
    struct_to_message(&res, UPDATE_LOBBY, send_msg);

    Server::sendToClient(userClient->getWritefd(), send_msg);
}

void Server::updateRoom(Room *&room) {
    struct update_room res = Server::to_struct_update_room(room);
    char send_msg[BUFF_SIZE + 1];
    struct_to_message(&res, UPDATE_ROOM, send_msg);

    for (auto client: room->getListUser()) {
        Server::sendToClient(client->getWritefd(), send_msg);
    }
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

    cout << "\nSend: " << "\n{\n" << send_message << "\n}\n";
}

void* Server::routine1(void *input) {
    UserClient *userClient = (UserClient *)input;
    int connfd = userClient->getClientfd();

    char rcv_message[BUFF_SIZE + 1], send_message[BUFF_SIZE + 1];
    
    int exit_check = false;
    while (!exit_check) {
        Server::rcvFromClient(connfd, rcv_message);
        switch (getCode(rcv_message)) {
        case RQ_EXIT:
            exit_check = true;
            if(userClient->getUser() != nullptr) {
                userClient->getUser()->setState(OFFLINE);
                delete userClient;
            }
            break;
        case RQ_REGISTER:
            Server::rq_register(rcv_message, send_message);
            Server::sendToClient(connfd, send_message);
            break;
        
        case RQ_LOGIN:
            Server::rq_login(rcv_message, send_message, connfd, userClient);
            Server::sendToClient(connfd, send_message);
            break;

        case RQ_LOGOUT:
            Server::rq_logout(rcv_message, send_message, userClient);
            Server::sendToClient(connfd, send_message);
            break;

        case RQ_CREATE_ROOM:
            Server::rq_createRoom(rcv_message, send_message, userClient);
            Server::sendToClient(connfd, send_message);
            break;

        case RQ_JOIN_ROOM:
            Server::rq_joinRoom(rcv_message, send_message, userClient);
            Server::sendToClient(connfd, send_message);
            break;

        case RQ_EXIT_ROOM:
            Server::rq_exitRoom(userClient);
            break;

        case RQ_READY:
            Server::rq_ready(userClient);
            break;
        default:
            break;
        }
    }
    close(connfd);

    return nullptr;
}

void *Server::routine2(void *client_socket) {
    int connfd = *(int *)client_socket;

    return nullptr;
}