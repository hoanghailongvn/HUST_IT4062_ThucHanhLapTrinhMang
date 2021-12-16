#include "../include/Window.h"
#include "../include/Textbox.h"
#include <iostream>

using namespace std;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    Window window;

    // Game loop
    while (window.running()) {
        window.update();

        window.render();
    }

    return 0;
}