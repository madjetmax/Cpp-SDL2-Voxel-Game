#include <string>
#include <iostream>
#include <cstdint>
#include "math.h"

#include "../../config.h"
#include "../../common/types.h"
#include "../../common/math_help.h"
#include "../../common/block_models.h"

#include "../block/block.h"
#include "../chunk/chunk.h"


using namespace std; 

#ifndef ENTITY_H
#define ENTITY_H


class Entity {
public:
    uint8_t id = 1;
    
    float x, y, z; // pos in world

    uint8_t full_model_id;
    
    // rotations and angle
    float angle_y = 0;
    float last_angle_y = 0;

    float rotation_y = 0;

    float angle_y_sin;
    float angle_y_cos;

    // moving 
    float mx = 0;
    float my = 0;
    float mz = 0;

    float inert_x = 0;
    float inert_z = 0;

    // collsions
    bool collider = true;
    
    int collider_size_x;
    int collider_size_top;
    int collider_size_bottom;
    int collider_size_z;

    float gravity = 0;
    float gravity_speed = 0.25;
    float min_gravity = -30;

    bool grounded = false;
    uint8_t grounded_block_id = 0;

    // cooldowns
    float cooking_colldown = 0;

    // updates to world
    bool on_remove = false;

    Entity(void);

    // collisions
    void collisions(Chunk (&chunks)[CHUNKS_COUNT]);
    void collide_with_block(int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT], int world_x, int world_y, int world_z, int x_in_chunk, int y_in_chunk, int z_in_chunk);
    int get_chunk_ind_by_pos(int x, int y, int z);

    void update_gravity(float dt);
    void update_inert(float dt);

    void update(Chunk (&chunks)[CHUNKS_COUNT],float dt);
};

// * child classes, based on entity
class ItemDrop: public Entity {
public:
    float y_floating_angle = 0; // smooth effect of item floating in air
    float y_floating_offset = 0; // smooth effect of item floating in air

    // cooldowns
    float just_dropded_cooldown = 0;
    bool pick_up_able = true;

    float lifetime = 6000;

    InventorySlot add_item;
    ItemDrop(void);

    void update_cooldowns(float dt);
    void update_grounded_block(float dt);

    void update(Chunk (&chunks)[CHUNKS_COUNT], float dt);
    void set_clear_face_pos(RawFace3d& face);
};

class BlockEntity: public Entity {
public:
    uint8_t block_id;

    // cooldowns
    float blowup_timer = 100;
    
    // world updates
    bool on_update_chunk = false;
    Chunk* current_chunk = nullptr;
    int current_chunk_ind;

    BlockEntity(void);

    void update_cooldowns(float dt);

    void set_block_on_hit(Chunk (&chunks)[CHUNKS_COUNT]);
    void update(Chunk (&chunks)[CHUNKS_COUNT], float dt);

    void set_clear_face_pos(RawFace3d& face);
};

class Mob: public Entity {
public:
    // states
    float damage_redness = 0;

    Mob(void);
    void hurt(float damage);
    void set_clear_face_pos(RawFace3d& face);
    void update_cooldowns(float dt);
    void update(Chunk (&chunks)[CHUNKS_COUNT], float dt);
};

#endif