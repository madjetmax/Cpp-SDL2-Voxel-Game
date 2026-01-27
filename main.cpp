#include <iostream>
#include "game/game.h"


using namespace std;
#undef main

//!! compile g++ -Llib -O3 main.cpp game/*.cpp -lSDL2 -lSDL2_image
//  g++ -Llib -O3 main.cpp $(find game -name "*.cpp") -lSDL2 -lSDL2_image 

int main(void) { 
    // init game
    Game* game = new Game();
    game->init();
    // start game loop
    game->main_loop();
    
    // clear
    game->clear();

    return 0;
}


