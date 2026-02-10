#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <thread>
#include <algorithm>
#include "../../inc/SDL.h"

#include "../config.h"

#include "world_renderer.h"
#include "camera.h"
#include "player.h"
#include "block/block.h"
#include "chunk/chunk.h"
#include "entity/entity.h"

#include "world_loader/world_generator.h"
#include "world_loader/world_loader.h"

#include "../common/block_models.h"
#include "../common/entity_models.h"
#include "../common/math_help.h"
#include "../common/types.h"

using namespace std;
using namespace std::chrono; 

#ifndef WORLD_H
#define WORLD_H


class World {
public:
    WorldRenderer world_renderer; // to draw objects

    Camera camera;
    Player player;

    // world time and sky color
    float time = 0; // 0 - TIME_END

    // Time keyframes (0 - 1000)
    const int TIME_NIGHT     = 0;
    const int TIME_MORNING   = 250;
    const int TIME_DAY_START = 350;
    const int TIME_DAY_END   = 650;
    const int TIME_EVENING   = 750;
    const int TIME_END       = 1000;

    // Sky colors
    const SDL_Color SKY_NIGHT   = {10,  15,  35,  255};
    const SDL_Color SKY_MORNING = {255, 90,  70, 255};
    const SDL_Color SKY_DAY     = {135, 206, 235, 255};
    const SDL_Color SKY_EVENING = {255, 140, 90,  255};

    float max_sky_color_value = 192.0f;
    SDL_Color sky_color = {255, 255, 255, 255};
    
    // objects, chunks, blocks
    WorldGenerator world_generator;
    WorldLoader world_loader;

    Chunk chunks[WORLD_SIZE_X * WORLD_SIZE_Y * WORLD_SIZE_Z];
    map<uint16_t, StorageBoxInv> storages;
    uint16_t last_storage_id = 1;

    // * entities
    vector <ItemDrop> all_items_drops;
    vector <BlockEntity> all_blocks_entities;
    vector <Mob> all_mobs;

    World(void);

    void on_start();

    void controls(SDL_Event& event, float dt);

    // * loops for all entities
    void loop_all_entities(PlayerInventory& player_inv, float dt);
    
    SDL_Color getSkyColor();

    void update(PlayerInventory& player_inv, float dt);
    void update_time(float dt);

    void draw(SDL_Renderer* renderer);
};


#endif