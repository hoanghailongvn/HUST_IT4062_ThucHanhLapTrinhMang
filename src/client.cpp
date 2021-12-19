
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
// #include "../include/Client.h"

// int main() {
//     Client *client = new Client();
    
//     client->communicate();

//     client->run();
    
//     // rq_register *stru = new rq_register;
//     // stru->username = "lskdjf";
//     // stru->password = "longdz";

//     // char message[BUFF_SIZE];

//     // struct_to_message((void *)stru, RQ_REGISTER, message);
    
//     // rq_register *res;
//     // res = message_to_rq_register(message);
//     // std::cout<< res->type << "\n";
//     // std::cout << res->username << "\n";

//     return 0;
// }


