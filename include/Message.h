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
enum MessageType {RQ_REGISTER = 0, RP_REGISTER, RQ_LOGIN, RP_LOGIN};

struct rq_register {
    MessageType type = RQ_REGISTER;
    std::string username;
    std::string password;
};

struct rp_register {
    MessageType type = RP_REGISTER;
    bool accept;
    std::string notification;
};

struct rq_login {
    MessageType type = RQ_LOGIN;
    std::string username;
    std::string password;
};

struct rp_login {
    MessageType type = RP_LOGIN;
    bool accept;
    std::string notification;
};

void struct_to_message(void *p, MessageType type, char *output);

rq_register *message_to_rq_register(char *message);
rp_register *message_to_rp_register(char *message);

//TODO
rq_login *message_to_rq_login(char *message);
rp_login *message_to_rp_login(char *message);


//Phân tách input bằng delimiter và trả về vector 
std::vector<char *> split(char *input, const char *delimiter);