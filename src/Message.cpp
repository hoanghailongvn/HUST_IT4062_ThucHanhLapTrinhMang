#include "../include/Message.h"

using namespace std;

vector<char *> split(char *input, const char *delimiter) {
    vector<char *> res;
    
    char *token;
    token = strtok(input, delimiter);

    while(token != NULL) {
        char* temp = (char *)malloc(strlen(token) + 1);
        strcpy(temp, token);
        res.push_back(temp);

        token = strtok(NULL, delimiter);
    }

    return res;
}

void struct_to_message(void *p, MessageType type, char *output) {
    stringstream final;
    string temp;
    const char *res;
    switch (type)
    {
    case RQ_REGISTER: 
    {
        auto *struct_obj = (rq_register *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->username << "\n";
        final << struct_obj->password << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_REGISTER:
        break;

    default:
        break;
    }
}

rq_register *message_to_rq_register(char *message) {
    vector <char *> splited_line = split(message, "\n");

    rq_register *res = new rq_register;
    res->type = RQ_REGISTER;
    res->username = splited_line.at(1);
    res->password = splited_line.at(2);

    return res;
}
