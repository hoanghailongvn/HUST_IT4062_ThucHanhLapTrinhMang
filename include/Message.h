#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>

enum MessageType {RQ_REGISTER = 0, RP_REGISTER};

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

void struct_to_message(void *p, MessageType type, char *output);

void message_to_struct(char *message, MessageType *type, void *p);

void split(char *input, const char *delimiter, std::vector<char *> *output);