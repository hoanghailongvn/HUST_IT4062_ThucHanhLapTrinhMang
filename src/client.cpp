
#include "../include/Client.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    Client client;

    // Game loop
    while (client.running()) {
        client.update();

        client.render();
    }

    return 0;
}


