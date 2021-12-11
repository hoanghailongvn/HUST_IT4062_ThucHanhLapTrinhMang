#ifndef USER_H
#define USER_H

#include <string.h>

class User {
public: 
    enum State {IN_LOBBY, IN_ROOM, IN_GAME};
private:
    State state;
    char name[30];
public:
    User();

    void set_state(State state);
    State get_state();
};

#endif