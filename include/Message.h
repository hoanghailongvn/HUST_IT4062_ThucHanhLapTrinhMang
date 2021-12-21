#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>

/*
    Message mình truyền đi ở dạng char[]
    Mình phải chuyển message dạng char[] sang dạng struct cho dễ xử lý hơn
    Cần viết các hàm convert giữa 2 dạng này

    Viết thêm struct message
    Viết hàm convert giữa 2 kiểu tương ứng với messag mới
    
    Chuyển từ struct sang message thì dùng một hàm struct_to_message thôi
    Nhưng chuyển từ message sang struct thì phải viets nhiều hàm do còn phụ thuộc vào kiểu trả về là struct nào

*/

// Nghĩ thêm các loại message rồi cho vô enum
enum MessageType {RQ_REGISTER = 0, RP_REGISTER, RQ_LOGIN, RP_LOGIN, RQ_LOGOUT, RP_LOGOUT, RQ_CREATE_ROOM, RP_CREATE_ROOM, RQ_JOIN_ROOM, RP_JOIN_ROOM,
RQ_UPDATE_LOBBY, RP_UPDATE_LOBBY};

struct rq_register {
    MessageType type = RQ_REGISTER;
    std::string username;
    std::string password;
};

struct rp_register {
    MessageType type = RP_REGISTER;
    bool accept;
    std::string notification = " ";
};

struct rq_login {
    MessageType type = RQ_LOGIN;
    std::string username;
    std::string password;
};

struct rp_login {
    MessageType type = RP_LOGIN;
    bool accept;
    std::string notification = " ";
    std::string username;
};

struct rq_logout {
    MessageType type = RQ_LOGOUT;
};

struct rp_logout {
    MessageType type = RP_LOGOUT;
    bool accept;
    std::string notification = " ";
};
struct rq_create_room {
    MessageType type = RQ_CREATE_ROOM;
    std::string name;
};

struct rp_create_room {
    MessageType type = RP_CREATE_ROOM;
    bool accept;
    std::string notification = " ";
};

struct rq_join_room {
    MessageType type = RQ_JOIN_ROOM;
    std::string id;
};

struct rp_join_room {
    MessageType type = RP_JOIN_ROOM;
    bool accept;
    std::string notification = " ";
};

struct rq_update_lobby{
    MessageType type = RQ_UPDATE_LOBBY;
};

struct rp_update_lobby{
    MessageType type = RP_UPDATE_LOBBY;
};

void struct_to_message(void *p, MessageType type, char *output);

rq_register message_to_rq_register(char *message);
rp_register message_to_rp_register(char *message);

rq_login message_to_rq_login(char *message);
rp_login message_to_rp_login(char *message);

rq_logout message_to_rq_logout(char *message);
rp_logout message_to_rp_logout(char *message);

rq_create_room message_to_rq_create_room(char *message);
rp_create_room message_to_rp_create_room(char *message);

rq_join_room message_to_rq_join_room(char *message);
rp_join_room message_to_rp_join_room(char *message);

rq_update_lobby message_to_rq_update_lobby(char *message);
rp_update_lobby message_to_rp_update_lobby(char *message);

//Phân tách input bằng delimiter và trả về vector 
std::vector<std::string> split(char *input, std::string delimiter);

int getCode(char *input);

#endif