#include "../include/Message.h"

using namespace std;

void split(char *input, const char *delimiter, vector<char *> *output) {
    char *token;

    token = strtok(input, delimiter);

    while(token != NULL) {
        char* temp = (char *)malloc(strlen(token) + 1);
        strcpy(temp, token);
        output->push_back(temp);

        token = strtok(NULL, delimiter);
    }
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
    default:
        break;
    }
}

rq_register *message_to_rq_register(char *message) {
    vector <char *> *splited_line = new vector<char *>();
    split(message, "\n", splited_line);

    rq_register *res = new rq_register;
    res->type = RQ_REGISTER;
    res->username = splited_line->at(1);
    res->password = splited_line->at(2);

    return res;
}
