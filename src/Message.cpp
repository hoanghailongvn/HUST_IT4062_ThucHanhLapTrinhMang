#include "../include/Message.h"

using namespace std;

std::vector<int> msg_length
{1, //RQ_EXIT
3, 3, //RQ_REGISTER, RP_REGISTER
3, 4,//RQ_LOGIN, RP_LOGIN
1, 3,//RQ_LOGOUT, RP_LOGOUT
2, 4,//RQ_CREATE_ROOM, RP_CREATE_ROOM
2, 3,//RQ_JOIN_ROOM, RP_JOIN_ROOM
4, 4,//UPDATE_LOBBY, UPDATE_ROOM
1, 1,//RQ_READY, RQ_START
1,//START
2,//RQ_ACTION,
6, 2,//UPDATE_GAME, UPDATE_TARGET, 
3,//END_GAME,
1,//RQ_EXIT_ROOM
};

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
        final << struct_obj->type << "\n\0";
        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_REGISTER: 
    {
        auto *struct_obj = (rq_register *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->username << "\n";
        final << struct_obj->password << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_REGISTER:
    {
        auto *struct_obj = (rp_register *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_LOGIN:
    {
        auto *struct_obj = (rq_login *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->username << "\n";
        final << struct_obj->password << "\n\0";

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
        final << struct_obj->username << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }

    case RQ_LOGOUT:
    {
        auto *struct_obj = (rq_logout *)p;
        final << struct_obj->type << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_LOGOUT:
    {
        auto *struct_obj = (rp_logout *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_CREATE_ROOM:
    {
        auto *struct_obj = (rq_create_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->name << "\n\0";

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
        final << struct_obj->roomname << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_JOIN_ROOM:
    {
        auto *struct_obj = (rq_join_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->room_name << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RP_JOIN_ROOM:
    {
        auto *struct_obj = (rp_join_room *)p;
        final << struct_obj->type << "\n";
        final << struct_obj->accept << "\n";
        final << struct_obj->notification << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case UPDATE_LOBBY:
    {
        auto *struct_obj = (update_lobby *)p;
        int nb_room = struct_obj->name.size();
        //Type
        final << struct_obj->type << "\n";
        
        //Room name
        if (nb_room > 0) {
            for (int i = 0; i < nb_room - 1; i++) {
                final << struct_obj->name.at(i) << " ";
            }
            final << struct_obj->name.at(nb_room - 1) << "\n";

            // number user each room
            for (int i = 0; i < nb_room - 1; i++) {
                final << struct_obj->number_user.at(i) << " ";
            }
            final << struct_obj->number_user.at(nb_room - 1) << "\n";

            // room state
            for (int i = 0; i < nb_room - 1; i++) {
                final << struct_obj->ingame.at(i) << " ";
            }
            final << struct_obj->ingame.at(nb_room - 1) << "\n\0";
        } else {
            final << "\n" << "\n" << "\n\0";
        }
        

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case UPDATE_ROOM:
    {
        auto *struct_obj = (update_room *)p;
        int nb_user = struct_obj->username.size();
        //Type
        final << struct_obj->type << "\n";
        
        if (nb_user > 0) {
            //room name
            final << struct_obj->room_name << "\n";

            //user name
            for (int i = 0; i < nb_user - 1; i++) {
                final << struct_obj->username.at(i) << " ";
            }
            final << struct_obj->username.at(nb_user - 1) << "\n";

            // ready state
            for (int i = 0; i < nb_user - 1; i++) {
                final << struct_obj->ready.at(i) << " ";
            }
            final << struct_obj->ready.at(nb_user - 1) << "\n\0";

        } else {
            final << "\n" << "\n" << "\n" << "\n\0";
        }
        

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_EXIT_ROOM:
    {
        auto *struct_obj = (rq_exit_room *)p;
        final << struct_obj->type << "\n\0";
        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_READY:
    {
        auto *struct_obj = (rq_ready *)p;
        final << struct_obj->type << "\n\0";
        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_START:
    {
        auto *struct_obj = (rq_start *)p;
        final << struct_obj->type << "\n\0";
        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case START:
    {
        auto *struct_obj = (start *)p;
        final << struct_obj->type << "\n\0";
        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case UPDATE_GAME:
    {
        auto *struct_obj = (update_game *)p;
        final << struct_obj->type << "\n";

        int nb_user = struct_obj->x.size();

        //time left
        final << struct_obj->time_left << "\n";

        //x
        for(int i = 0; i < nb_user - 1; i++) {
            final << struct_obj->x.at(i) << " ";
        }
        final << struct_obj->x.at(nb_user - 1) << "\n";

        //y
        for(int i = 0; i < nb_user - 1; i++) {
            final << struct_obj->y.at(i) << " ";
        }
        final << struct_obj->y.at(nb_user - 1) << "\n";

        //nb word done
        for(int i = 0; i < nb_user - 1; i++) {
            final << struct_obj->nb_word_done.at(i) << " ";
        }
        final << struct_obj->nb_word_done.at(nb_user - 1) << "\n";

        //point
        for(int i = 0; i < nb_user - 1; i++) {
            final << struct_obj->point.at(i) << " ";
        }
        final << struct_obj->point.at(nb_user - 1) << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case RQ_ACTION:
    {
        auto *struct_obj = (rq_action *)p;
        final << struct_obj->type << "\n";

        final << struct_obj->action << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case UPDATE_TARGET:
    {
        auto *struct_obj = (update_target *)p;
        final << struct_obj->type << "\n";

        final << struct_obj->target << "\n\0";

        temp = final.str();
        strcpy(output, temp.c_str());
        break;
    }
    case END_GAME: 
    {
        auto *struct_obj = (end_game *)p;
        final << struct_obj->type << "\n";

        int nb_user = struct_obj->point.size();

        //username
        for(int i = 0; i < nb_user - 1; i++) {
            final << struct_obj->username.at(i) << " ";
        }
        final << struct_obj->username.at(nb_user - 1) << "\n";

        //Point
        for(int i = 0; i < nb_user - 1; i++) {
            final << struct_obj->point.at(i) << " ";
        }
        final << struct_obj->point.at(nb_user - 1) << "\n\0";

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
    res.room_name = splited_line.at(1);

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

update_lobby message_to_update_lobby(char *message) {
    auto splited_line = split(message, "\n");
    update_lobby res;


    if(splited_line.at(1).length() > 0) {
        char temp[BUFF_SIZE + 1];
        memset(temp, 0, sizeof(temp));
        
        //room name
        strcpy(temp, splited_line.at(1).c_str());
        auto splited_temp = split(temp, " ");
        for (auto name: splited_temp) {
            res.name.push_back(name);
        }

        //nb_user
        memset(temp, 0, sizeof(temp));
        strcpy(temp, splited_line.at(2).c_str());
        splited_temp = split(temp, " ");
        for (auto nb_user: splited_temp) {
            res.number_user.push_back(stoi(nb_user));
        }

        //room state
        memset(temp, 0, sizeof(temp));
        strcpy(temp, splited_line.at(3).c_str());
        splited_temp = split(temp, " ");
        for (auto state: splited_temp) {
            res.ingame.push_back(stoi(state));
        }
    }
    
    return res;
}

update_room message_to_update_room(char *message) {
    auto splited_line = split(message, "\n");
    update_room res;

    res.room_name = splited_line.at(1);

    if(splited_line.at(2).length() > 0) {
        char temp[BUFF_SIZE + 1];
        memset(temp, 0, sizeof(temp));
        
        //user name
        strcpy(temp, splited_line.at(2).c_str());
        auto splited_temp = split(temp, " ");
        for (auto username: splited_temp) {
            res.username.push_back(username);
        }

        //ready
        memset(temp, 0, sizeof(temp));
        strcpy(temp, splited_line.at(3).c_str());
        splited_temp = split(temp, " ");
        for (auto ready: splited_temp) {
            res.ready.push_back(stoi(ready));
        }
    }
    
    return res;
}

update_game message_to_update_game(char *message) {
    auto splited_line = split(message, "\n");
    update_game res;

    //time left
    res.time_left = stoi(splited_line.at(1));

    char temp[BUFF_SIZE + 1];
    memset(temp, 0, sizeof(temp));
    
    //x
    strcpy(temp, splited_line.at(2).c_str());
    auto splited_temp = split(temp, " ");
    for (auto x: splited_temp) {
        res.x.push_back(stoi(x));
    }

    //y
    memset(temp, 0, sizeof(temp));

    strcpy(temp, splited_line.at(3).c_str());
    splited_temp = split(temp, " ");
    for (auto y: splited_temp) {
        res.y.push_back(stoi(y));
    }

    //so chu da hoan thanh
    memset(temp, 0, sizeof(temp));
    strcpy(temp, splited_line.at(4).c_str());
    splited_temp = split(temp, " ");
    for (auto nb_word_done: splited_temp) {
        res.nb_word_done.push_back(stoi(nb_word_done));
    }

    // point
    memset(temp, 0, sizeof(temp));
    strcpy(temp, splited_line.at(5).c_str());
    splited_temp = split(temp, " ");
    for (auto point: splited_temp) {
        res.point.push_back(stoi(point));
    }

    return res;
}
update_target message_to_update_target(char *message) {
    auto splited_line = split(message, "\n");
    update_target res;

    res.target = splited_line.at(1);
    return res;
}
rq_action message_to_rq_action(char *message) {
    auto splitted_line = split(message, "\n");
    rq_action res;
    res.action = (Action)stoi(splitted_line.at(1));
    return res;
}

end_game message_to_end_game(char *message) {
    auto splited_line = split(message, "\n");
    end_game res;
    
    char temp[BUFF_SIZE + 1];

    //username
    memset(temp, 0, sizeof(temp));    
    strcpy(temp, splited_line.at(1).c_str());
    auto splited_temp = split(temp, " ");
    for (auto username: splited_temp) {
        res.username.push_back(username);
    }

    //point
    memset(temp, 0, sizeof(temp));    
    strcpy(temp, splited_line.at(2).c_str());
    splited_temp = split(temp, " ");
    for (auto point: splited_temp) {
        res.point.push_back(stoi(point));
    }
    
    return res;
}

int getCode(char *input) {
    auto splited_line = split(input, "\n");
    int res = stoi(splited_line.at(0));

    return res;
}

