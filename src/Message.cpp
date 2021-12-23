#include "../include/Message.h"

using namespace std;

vector<string> split(char *input, string delimiter) {
    vector<string> res;

    size_t pos = 0;
    std::string token;
    string input_copy = input;
    while ((pos = input_copy.find(delimiter)) != std::string::npos) {
        token = input_copy.substr(0, pos);
        res.push_back(token);
        input_copy.erase(0, pos + delimiter.length());
    }
    res.push_back(input_copy);

    return res;
}

void struct_to_message(void *p, MessageType type, char *output) {
    stringstream final;
    string temp;
    const char *res;
    switch (type)
    {
    case RQ_EXIT:
    {
        auto *struct_obj = (rq_exit *)p;
        final << struct_obj->type << "\0";
        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
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
        final << struct_obj->notification << "\n";
        final << struct_obj->username << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }

    case RQ_LOGOUT:
    {
        auto *struct_obj = (rq_logout *)p;
        final << struct_obj->type << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_LOGOUT:
    {
        auto *struct_obj = (rp_logout *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_CREATE_ROOM:
    {
        auto *struct_obj = (rq_create_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->name << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_CREATE_ROOM:
    {
        auto *struct_obj = (rp_create_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\n";
        final << struct_obj->roomname << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_JOIN_ROOM:
    {
        auto *struct_obj = (rq_join_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->id << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_JOIN_ROOM:
    {
        auto *struct_obj = (rp_join_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_UPDATE_LOBBY:
    {
        auto *struct_obj = (rq_update_lobby *)p;
        final << struct_obj->type << "\n";
        // final << struct_obj->id << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_UPDATE_LOBBY:
    {
        auto *struct_obj = (rp_update_lobby *)p;
        final << struct_obj->type << "\n";
        // final << struct_obj->accept << "\n";
        // final << struct_obj->notification << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_EXIT_ROOM:
    {
        auto *struct_obj = (rq_exit_room *)p;
        final << struct_obj->type << "\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    default:
        break;
    }
}

rq_register message_to_rq_register(char *message) {
    auto splited_line = split(message, "\n");
    if (splited_line.size() != 3) {
        cout << "message_to_rq_register error!!\n";
        exit(1);
    }
    rq_register res;
    res.type = RQ_REGISTER;
    res.username = splited_line.at(1);
    res.password = splited_line.at(2);

    return res;
}

rp_register message_to_rp_register(char *message) {
    auto splited_line = split(message, "\n");

    rp_register res;
    res.type = RP_REGISTER;
    res.accept = stoi(splited_line.at(1));
    res.notification = splited_line.at(2);
    

    return res;
}

rq_login message_to_rq_login(char *message) {
    auto splited_line = split(message, "\n");
    rq_login res;
    res.username = splited_line.at(1);
    res.password = splited_line.at(2);

    return res;
}

rp_login message_to_rp_login(char *message) {
    auto splited_line = split(message, "\n");
    rp_login res;
    res.accept = stoi(splited_line.at(1));
    if (!res.accept) {
        res.notification = splited_line.at(2);
        res.username = "";
    } else {
        res.username = splited_line.at(3);
    }

    return res;
}

rq_logout message_to_rq_logout(char *message) {
    rq_logout res;
    return res;
}

rp_logout message_to_rp_logout(char *message) {
    auto splited_line = split(message, "\n");
    rp_logout res;
    res.accept = stoi(splited_line.at(1));
    if (!res.accept) {
        res.notification = splited_line.at(2);
    } else {
        res.notification = "";
    }
    
    return res;
}
rq_join_room message_to_rq_join_room(char *message) {
    auto splited_line = split(message, "\n");
    rq_join_room res;
    res.id = splited_line.at(1);

    return res;
}

rp_join_room message_to_rp_join_room(char *message) {
    auto splited_line = split(message, "\n");
    rp_join_room res;
    res.accept = stoi(splited_line.at(1));
    if (!res.accept) {
        res.notification = splited_line.at(2);
    } else {
        res.notification = "";
    }
    
    return res;
}

rq_create_room message_to_rq_create_room(char *message) {
    auto splited_line = split(message, "\n");
    rq_create_room res;
    res.name = splited_line.at(1);
    
    return res;
}

rp_create_room message_to_rp_create_room(char *message) {
    auto splited_line = split(message, "\n");
    rp_create_room res;
    res.accept = stoi(splited_line.at(1));
    if (!res.accept) {
        res.notification = splited_line.at(2);
    } else {
        res.notification = "";
        res.roomname = splited_line.at(3);
    }

    return res;
}

rq_update_lobby message_to_rq_update_lobby(char *message) {
    auto splited_line = split(message, "\n");
    rq_update_lobby res;
    // res.id = splited_line.at(1);

    return res;
}

rp_update_lobby message_to_rp_update_lobby(char *message) {
    auto splited_line = split(message, "\n");
    rp_update_lobby res;
    // res.accept = atoi(splited_line.at(1));
    // if (!res.accept) {
    //     res.notification = splited_line.at(2);
    // } else {
    //     res.notification = "";
    // }
    
    return res;
}
int getCode(char *input) {
    auto splited_line = split(input, "\n");
    int res = stoi(splited_line.at(0));

    return res;
}
