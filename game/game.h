#include <string>
#include <iostream>
#include "../inc/SDL.h"

#include "config.h"
#include "world/world.h"
#include "common/block_models.h"
#include "common/text_draw.h"
#include "inventory/player_inventory.h"

using namespace std; 

#ifndef GAME_H
#define GAME_H


class Game {
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    World world;
    PlayerInventory* player_inventory;
    TextDraw text_draw;

    vec2 mpos;
    // other
    bool run;
    Uint32 start_time, frame_time;
    float fps;
    float delta_time;

    Game(void);

    void init();

    void controls(SDL_Event& event);
    void update();
    void draw();
    void debud_draw();
    void main_loop();

    void clear();
};


#endif