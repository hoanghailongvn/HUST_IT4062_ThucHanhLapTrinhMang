#include "../include/Client.h"
#include "../include/Message.h"

int main() {
    // Client *client = new Client();
    
    // client->communicate();
    // while(1) {
    //     client->run();
    // }
    rq_register *stru = new rq_register;
    stru->username = "lskdjf";
    stru->password = "longdz";

    char message[BUFF_SIZE];

    struct_to_message((void *)stru, RQ_REGISTER, message);
    
    MessageType temp;
    void *temp_stru;
    message_to_struct(message, &temp, temp_stru);

    return 0;
}

