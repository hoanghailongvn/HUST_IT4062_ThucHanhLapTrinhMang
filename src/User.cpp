#include "../include/User.h"

User::User() {};

void User::set_state(State state) {
    this->state = state;
}

User::State User::get_state() {
    return this->state;
}