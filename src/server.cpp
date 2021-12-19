#include <iostream>
#include "../include/User.h"
#include "../include/Server.h"

int main() {
    Server *server = new Server();
    server->run();
    return 0;
}
