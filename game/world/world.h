#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <thread>
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

    bool day = true;
    
    // objects, chunks, blocks
    WorldGenerator world_generator;
    WorldLoader world_loader;

    Chunk chunks[WORLD_SIZE_X * WORLD_SIZE_Y * WORLD_SIZE_Z];
    map<uint16_t, StorageBoxInv> storages;
    uint16_t last_storage_id = 1;

    // * entities
    vector <ItemDrop> all_items_drops;
    vector <BlockEntity> all_blocks_entities;

    World(void);

    void on_start();

    void controls(SDL_Event& event, float dt);

    // * loops for all entities
    void loop_all_entities(PlayerInventory& player_inv, float dt);
    
    void update(PlayerInventory& player_inv, float dt);
    void update_sun_light(float dt);

    void draw(SDL_Renderer* renderer);
};


#endif