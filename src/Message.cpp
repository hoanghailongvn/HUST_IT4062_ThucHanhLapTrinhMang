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

void message_to_struct(char *message, MessageType *type, void *p) {
    vector <char *> *splited_line = new vector<char *>();
    split(message, "\n", splited_line);

    switch (atoi(splited_line->at(0)))
    {
    case RQ_REGISTER:
        cout << "OK" << endl;
        break;
    
    default:
        break;
    }
    
}
