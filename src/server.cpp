#include <iostream>
#include "../include/User.h"
#include "../include/Server.h"


int main() {
    srand(static_cast<unsigned>(time(NULL)));
    
    Server *server = new Server();
    server->run();
    return 0;
}
