#include "../include/Message.h"

using namespace std;

vector<char *> split(char *input, const char *delimiter) {
    vector<char *> res;

    char input_copy[100];
    strcpy(input_copy, input);

    char *token;
    token = strtok(input_copy, delimiter);

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
    {
        auto *struct_obj = (rp_register *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_LOGIN:
    {
        auto *struct_obj = (rq_login *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->username << "\n";
        final << struct_obj->password << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_LOGIN:
    {
        auto *struct_obj = (rp_login *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    default:
        break;
    }
}

rq_register message_to_rq_register(char *message) {
    vector <char *> splited_line = split(message, "\n");
    rq_register res;
    res.type = RQ_REGISTER;
    res.username = splited_line.at(1);
    res.password = splited_line.at(2);

    return res;
}

rp_register message_to_rp_register(char *message) {
    vector <char *> splited_line = split(message, "\n");
    rp_register res;
    res.type = RP_REGISTER;
    res.accept = atoi(splited_line.at(1));
    if (!res.accept) {
        res.notification = splited_line.at(2);
    } else {
        res.notification = "";
    }

    return res;
}

rq_login message_to_rq_login(char *message) {
    vector <char *> splited_line = split(message, "\n");
    rq_login res;
    res.username = splited_line.at(1);
    res.password = splited_line.at(2);

    return res;
}

rp_login message_to_rp_login(char *message) {
    vector <char *> splited_line = split(message, "\n");
    rp_login res;
    res.accept = atoi(splited_line.at(1));
    if (!res.accept) {
        res.notification = splited_line.at(2);
    } else {
        res.notification = "";
    }


    return res;
}

int getCode(char *input) {
    vector <char *> splited_line = split(input, "\n");
    int res = atoi(splited_line.at(0));

    return res;
}
