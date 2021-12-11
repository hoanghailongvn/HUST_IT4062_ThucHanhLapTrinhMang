#include <iostream>
#include "../include/Game.h"

using namespace std;

int main()
{
    //Init game engine
    Game game;

    //Game loop
    while (game.running()) {
        //update
        game.update();

        //render
        game.render();
    }


    return 0;
}