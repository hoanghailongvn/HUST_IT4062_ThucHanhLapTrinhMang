
#include "../include/Client.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    Client *client = new Client();
    client->run();

    return 0;
}


