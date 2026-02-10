#include <iostream>
#include <vector>
#include <optional>
#include "math.h"
#include "../../inc/SDL.h"

#include "../config.h"
#include "camera.h"
#include "block/block.h"
#include "chunk/chunk.h"
#include "../common/block_models.h"
#include "entity/entity.h"

using namespace std; 

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    float x, y, z;

    int collider_size_x = 60;
    int collider_size_top = 25;
    float collider_size_bottom = 150;
    int collider_size_z = 60;

    bool collider = true;

    int angle_dirrection = 0;

    // movement
    float mx, my, mz;
    float inert_x = 0;
    float inert_z = 0;

    float inert_speed = 0.5;

    bool go_fw, go_back, go_right, go_left;
    bool sneak = false;

    bool run;
    bool jump;

    bool go_up, go_down;
    bool on_fly = false;

    float gravity = 0;
    float gravity_speed = 0.25;
    float min_gravity = -30;

    float swimming_gravity_speed = 0.05;
    float min_swimming_gravity = -2;
    float min_swimming_gravity_go_down = -6;
    float max_swimming_gravity = 2;

    bool grounded = false;
    bool swimming = false;
    bool under_water = false;

    // interactions
    bool on_block_break;
    float block_breaking_progress = 0.0f;
    float max_block_breaking_progress = 0.0f;

    bool on_block_interaction;
    float block_interactions_cooldown = 0;
    bool on_kick;

    bool fast_interactions = false;

    bool in_inventory = false;

    uint8_t place_block_id = 1;

    float rotation_x, rotation_y;

    float angle_y_sin, angle_y_cos;

    // speeds and values
    float walk_speed = 3.5;
    float run_speed = 6;
    float sneak_speed = 1.2;

    float walk_in_water_speed = 1.2;
    float run_in_water_speed = 3.8;

    float jump_height = 7.3;
    
    float up_down_speed = 5;

    // world renderer body
    float body_angle_rotation = 0;
    float body_angle_diff = 60;
    
    float body_angle = 0;
    float last_body_angle = 0;
    
    float body_angle_sin = 0;
    float body_angle_cos = 0;
    

    // methods
    Player(void);

    void controls(SDL_Event& event, Camera& camera, float dt);
    void movement(Camera& camera, float dt);
    // collisions
    void collisions(Chunk (&chunks)[CHUNKS_COUNT]);
    void collide_with_block(int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT], int world_x, int world_y, int world_z, int x_in_chunk, int y_in_chunk, int z_in_chunk);
    bool collider_with_item_drop(ItemDrop& entity);
    int get_chunk_ind_by_pos(int x, int y, int z);

    void update_colldowns(float dt);
    void update_gravity(float dt);
    void update_angle_direction(Camera& camera);
    void update_body_angle(Camera& camera, float dt);
    void update(Camera& camera, Chunk (&chunks)[CHUNKS_COUNT], float dt);
};


#endif