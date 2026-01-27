#include "entity.h"

// * base entity
Entity::Entity() {}



// * collisions
void Entity::collisions(Chunk (&chunks)[CHUNKS_COUNT]) {
    if (!collider) {
        return;
    }
    // get pos in world to get current chunk
    int world_x = ((x + BLOCK_SIZE / 2) / (CHUNK_SIZE_X * BLOCK_SIZE));
    int world_y = ((y + BLOCK_SIZE / 2) / (CHUNK_SIZE_Y * BLOCK_SIZE));
    int world_z = ((z + BLOCK_SIZE / 2) / (CHUNK_SIZE_Z * BLOCK_SIZE));


    // get current chunk
    int current_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
    if (current_chunk_ind != -1) {
        if (current_chunk_ind >= 0 && current_chunk_ind < CHUNKS_COUNT) {
            Chunk& chunk = chunks[current_chunk_ind];

            // get block pos inside chunk by plr pos 
            int x_in_chunk = int(x + BLOCK_SIZE / 2) % (CHUNK_SIZE_X * BLOCK_SIZE);
            int y_in_chunk = int(y + BLOCK_SIZE / 2) % (CHUNK_SIZE_Y * BLOCK_SIZE);
            int z_in_chunk = int(z + BLOCK_SIZE / 2) % (CHUNK_SIZE_Z * BLOCK_SIZE);
    
            int bx = int(x_in_chunk / BLOCK_SIZE);
            int by = int(y_in_chunk / BLOCK_SIZE);
            int bz = int(z_in_chunk / BLOCK_SIZE);
    
            // check collisions around player pos in chunk
            grounded = false;
            grounded_block_id = 0;

            collide_with_block(bx, by, bz, chunk, chunks, world_x, world_y, world_z, x_in_chunk, y_in_chunk, z_in_chunk);
            // collide_with_block(bx-1, by, bz, chunk, chunks, world_x, world_y, world_z, x_in_chunk, y_in_chunk, z_in_chunk);
            for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 0; ++dy)
            for (int dz = -1; dz <= 1; ++dz) {
                if (dx || dy || dz) 
                    collide_with_block(bx + dx, by + dy, bz + dz, chunk, chunks, world_x, world_y, world_z, x_in_chunk, y_in_chunk, z_in_chunk);
            }

        }
    }
}
void Entity::collide_with_block(int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT], int world_x, int world_y, int world_z, int x_in_chunk, int y_in_chunk, int z_in_chunk) {
    Chunk *neighbour_chunk = nullptr;    
    bool block_on_neighbour_chunk = false;
    // block in right neighbour chunk
    if (bx >= CHUNK_SIZE_X) {
        // break if on border of the world 
        if (world_x >= WORLD_SIZE_X - 1) {
            return;
        }
        // set positions in neighbour chunk
        world_x += 1;
        
        bx = 0;
        x_in_chunk -= CHUNK_SIZE_X * BLOCK_SIZE;
    }
    // block in left neighbour chunk
    if (bx < 0) {
        // break if on border of the world 
        if (world_x <= 0) {
            return;
        }
        // set positions in neighbour chunk
        world_x -= 1;

        bx = CHUNK_SIZE_X - 1;
        x_in_chunk += CHUNK_SIZE_X * BLOCK_SIZE;
    }
    // block in top neighbour chunk
    if (by >= CHUNK_SIZE_Y) {
        // break if on border of the world 
        if (world_y >= WORLD_SIZE_Y - 1) {
            return;
        }
        // set positions in neighbour chunk
        world_y += 1;
        
        by = 0;
        y_in_chunk -= CHUNK_SIZE_Y * BLOCK_SIZE;
    }
    // block in left neighbour chunk
    if (by < 0) {
        // break if on border of the world 
        if (world_y <= 0) {
            return;
        }
        // set positions in neighbour chunk
        world_y -= 1;

        by = CHUNK_SIZE_Y + by;
        y_in_chunk += CHUNK_SIZE_Y * BLOCK_SIZE;
    }
    // block in front neighbour chunk
    if (bz >= CHUNK_SIZE_Z) {
        // break if on border of the world 
        if (world_z >= WORLD_SIZE_Z - 1) {
            return;
        }
        // set positions in neighbour chunk
        world_z += 1;
        
        bz = 0;
        z_in_chunk -= CHUNK_SIZE_Z * BLOCK_SIZE;
    }
    // block in back neighbour chunk
    if (bz < 0) {
        // break if on border of the world 
        if (world_z <= 0) {
            return;
        }
        // set positions in neighbour chunk
        world_z -= 1;
        
        bz = CHUNK_SIZE_Z - 1;
        z_in_chunk += CHUNK_SIZE_Z * BLOCK_SIZE;
    }

    // get neighbour chunk
    int chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
    if (chunk_ind != -1) {
        neighbour_chunk = &chunks[chunk_ind];
    } else {
        return;
    }
    
    // get block in current or neighbour chunk
    Block* block = nullptr;
    if (neighbour_chunk) {
        block = &neighbour_chunk->blocks[bx][by][bz];
    } else {
        block = &chunk.blocks[bx][by][bz];
    }

    if (block->id == 0) {
        return;
    }
    // check collisions
    int size_reduce = 0;

    int size_add = 1;
    int block_size_add = 0;

    // get collider by block data
    FullBlockData block_data = all_blocks_full_data[block->id];
    vector <BlockCollider>* block_colliders = block_data.colliders;

    // loop all colliders
    int colliders_size = block_colliders->size();
    block_colliders->reserve(1);
    for (size_t ci = 0; ci < colliders_size; ci++)
    {
        BlockCollider& collider = (*block_colliders)[ci];


        bool x_same = bool(x_in_chunk + (collider_size_x / 2 - size_reduce) >= block->x + collider.x && x_in_chunk - (collider_size_x / 2 - size_reduce) <= block->x + collider.x + collider.size_x);
        bool y_same = bool(y_in_chunk + (collider_size_top - size_reduce) >= block->y + collider.y && y_in_chunk - (collider_size_bottom - size_reduce) <= block->y + collider.y + collider.size_y);
        bool z_same = bool(z_in_chunk + (collider_size_z / 2 - size_reduce) >= block->z + collider.z && z_in_chunk - (collider_size_z / 2 - size_reduce) <= block->z + collider.z + collider.size_z);

        bool x_collide = bool((y_same && z_same) && (block->x + collider.x + collider.size_x > x_in_chunk - (collider_size_x / 2 + size_add) + mx && block->x + collider.x < x_in_chunk + (collider_size_x / 2 + size_add) + mx));
        bool y_collide = bool((x_same && z_same) && (block->y + collider.y + collider.size_y > y_in_chunk - (collider_size_bottom + size_add) + my && block->y + collider.y < y_in_chunk + (collider_size_top + size_add) + my));
        bool z_collide = bool((x_same && y_same) && (block->z + collider.z + collider.size_z > z_in_chunk - (collider_size_z / 2 + size_add) + mz && block->z + collider.z < z_in_chunk + (collider_size_z / 2 + size_add) + mz));

        // x
        if (x_collide) {
            if (block->id == 6) {

            } 
            // other block
            else {
                mx = 0;
                inert_x = 0;
            }
        }

        // y
        if (y_collide) {
            // water
            if (block->id == 6) {
            } 
            // other block
            else {
                if (block->y < y_in_chunk) {
                    grounded = true;
                    grounded_block_id = block->id;

                    // set cooking with fire wood
                    if (grounded_block_id == 93 && cooking_colldown == 0) {
                        cooking_colldown = 100;
                    }
                }
                my = 0;
                gravity = 0;
                inert_x = 0;
                inert_z = 0;
            }
        }

        // z
        if (z_collide) {
            // water
            if (block->id == 6) {
            } 
            // other block
            else {
                mz = 0;
                inert_z = 0;
            }
        }

        // x, z collision on edge 
        if (x_collide && z_collide) {
            if (block->id != 6) {
                // x
                if (block->x < x_in_chunk) {
                    mx += 1;
                } else {
                    mx -= 1;
                }
                // z
                if (block->z < z_in_chunk) {
                    mz += 1;
                } else {
                    mz -= 1;
                }
            }
        }

        // y, x collision on edge 
        if (y_collide && x_collide) {
            if (block->id != 6) {
                // y
                if (block->y < y_in_chunk) {
                    my += 1;
                } else {
                    my -= 1;
                }
                // x
                if (block->x < x_in_chunk) {
                    mx += 1;
                } else {
                    mx -= 1;
                }
            }
        }

        // y, z collision on edge 
        if (y_collide && z_collide) {
            if (block->id != 6) {
                // y
                if (block->y < y_in_chunk) {
                    my += 1;
                } else {
                    my -= 1;
                }
                // z
                if (block->z < z_in_chunk) {
                    mz += 1;
                } else {
                    mz -= 1;
                }
            }
        }
    }
}

int Entity::get_chunk_ind_by_pos(int cx, int cy, int cz) {
    bool x_correct = bool(cx >= 0 && cx < WORLD_SIZE_X);
    bool y_correct = bool(cy >= 0 && cy < WORLD_SIZE_Y);
    bool z_correct = bool(cz >= 0 && cz < WORLD_SIZE_Z);

    if (!x_correct || !y_correct || !z_correct) {
        return -1;
    }
    return cx * WORLD_SIZE_Y * WORLD_SIZE_Z + cy * WORLD_SIZE_Z + cz;
}


void Entity::update_gravity(float dt) {

    float min_value = min_gravity;
    float speed = gravity_speed;
    if (gravity > min_value) {
        gravity -= speed * dt;
    } else {
        gravity = min_value;
    }
    my += gravity * dt;
}

void Entity::update_inert(float dt) {
    float reduce_speed = 0.1;
    // x 
    if (inert_x > 0) {
        inert_x -= reduce_speed * dt;
        inert_x = max(0.0f, inert_x);
    }
    else if (inert_x < 0) {
        inert_x += reduce_speed * dt;
        inert_x = min(0.0f, inert_x);
    }
    mx += inert_x * dt;

    // z 
    if (inert_z > 0) {
        inert_z -= reduce_speed * dt;
        inert_z = max(0.0f, inert_z);
    }
    else if (inert_z < 0) {
        inert_z += reduce_speed * dt;
        inert_z = min(0.0f, inert_z);
    }
    mz += inert_z * dt;
}



void Entity::update(Chunk (&chunks)[CHUNKS_COUNT], float dt) {
    update_gravity(dt);
    update_inert(dt);

    collisions(chunks);

    // update pos
    x += mx;
    y += my;
    z += mz;

    // update angle and rotation
    angle_y += rotation_y;

    // update angle sin cos
    if (angle_y != last_angle_y) {
        angle_y_sin = sin(angle_y * (M_PI / 180));
        angle_y_cos = cos(angle_y * (M_PI / 180));

        last_angle_y = angle_y;
    }
    // normalize angle
    if (angle_y > 360) {
        angle_y -= 360;
    }
    if (angle_y < 0) {
        angle_y += 360;
    }

    // clear states and values
    mx = 0;
    my = 0;
    mz = 0;

    rotation_y = 0;
}

// * item drop

ItemDrop::ItemDrop() {
    collider_size_x = 25;
    collider_size_top = 12;
    collider_size_bottom = 12;
    collider_size_z = 25;
}

void ItemDrop::set_clear_face_pos(RawFace3d& face) {
    float point1_x = face.point1.x;
    float point1_z = face.point1.z;

    face.point1.x = -(point1_x * angle_y_cos - point1_z * angle_y_sin) + x;
    face.point1.y += y + y_floating_offset + 25;
    face.point1.z =  point1_x * angle_y_sin + point1_z * angle_y_cos + z;

    float point2_x = face.point2.x;
    float point2_z = face.point2.z;

    face.point2.x = -(point2_x * angle_y_cos - point2_z * angle_y_sin) + x;
    face.point2.y += y + y_floating_offset + 25;
    face.point2.z =  point2_x * angle_y_sin + point2_z * angle_y_cos + z;

    float point3_x = face.point3.x;
    float point3_z = face.point3.z;

    face.point3.x = -(point3_x * angle_y_cos - point3_z * angle_y_sin) + x;
    face.point3.y += y + y_floating_offset + 25;
    face.point3.z =  point3_x * angle_y_sin + point3_z * angle_y_cos + z;
}

void ItemDrop::update_cooldowns(float dt) {
    // lifetime
    if (lifetime > 0) {
        lifetime -= 1 * dt;
    } else {
        lifetime = 0;
        on_remove = true;
    }

    // just dropped cooldown
    if (just_dropded_cooldown > 0) {
        just_dropded_cooldown -= 1 * dt;
        if (just_dropded_cooldown <= 0) {
            pick_up_able = true;
            just_dropded_cooldown = 0;
        }
    }
}

void ItemDrop::update_grounded_block(float dt) {
    // skip, clear cooking
    if (grounded_block_id == 0) {
        cooking_colldown = 0;
        return;
    }


    // * food cooking with fire wood
    if (grounded_block_id == 93) {
        cooking_colldown -= 1 * dt;
        if (cooking_colldown <= 0) {
            // test
            if (add_item.item_id == 1) {
                add_item.item_id = 2;
                full_model_id = 2;
                cout << 1123123 << endl;
            }

            // clear coodown
            cooking_colldown = 0;
        }
    }
}


void ItemDrop::update(Chunk (&chunks)[CHUNKS_COUNT], float dt) {
    update_gravity(dt);
    update_inert(dt);

    collisions(chunks);

    update_cooldowns(dt);
    update_grounded_block(dt);

    // update pos
    x += mx;
    y += my;
    z += mz;

    // rotate
    rotation_y += 0.6 * dt;

    // update floating with math sin
    float floating_amplitude = 20;
    y_floating_angle += 0.8 * dt;
    y_floating_offset = sin(y_floating_angle * (M_PI / 180)) * floating_amplitude;

    // update angle and rotation
    angle_y += rotation_y;

    
    // update angle sin cos
    if (angle_y != last_angle_y) {
        angle_y_sin = sin(angle_y * (M_PI / 180));
        angle_y_cos = cos(angle_y * (M_PI / 180));
        
        last_angle_y = angle_y;
    }
    
    // normalize angle
    if (angle_y > 360) {
        angle_y -= 360;
    }
    if (angle_y < 0) {
        angle_y += 360;
    }
    
    // clear states and values
    mx = 0;
    my = 0;
    mz = 0;

    rotation_y = 0;
}

// * Block
BlockEntity::BlockEntity() {
    collider_size_x = BLOCK_SIZE - 1;
    collider_size_top = BLOCK_SIZE / 2 - 1;
    collider_size_bottom = BLOCK_SIZE / 2 - 1;
    collider_size_z = BLOCK_SIZE - 1;
}

void BlockEntity::set_clear_face_pos(RawFace3d& face) {
    face.point1.x += x;
    face.point1.y += y;
    face.point1.z += z;

    face.point2.x += x;
    face.point2.y += y;
    face.point2.z += z;

    face.point3.x += x;
    face.point3.y += y;
    face.point3.z += z;
}

void BlockEntity::update_cooldowns(float dt) {
    // update blowup tnt
    if (block_id == 83) {
        blowup_timer -= 1 * dt;
    }
}

void BlockEntity::set_block_on_hit(Chunk (&chunks)[CHUNKS_COUNT]) {
    if (grounded) {
        // get pos in world to get current chunk
        int world_x = ((x + BLOCK_SIZE / 2) / (CHUNK_SIZE_X * BLOCK_SIZE));
        int world_y = ((y + BLOCK_SIZE / 2) / (CHUNK_SIZE_Y * BLOCK_SIZE));
        int world_z = ((z + BLOCK_SIZE / 2) / (CHUNK_SIZE_Z * BLOCK_SIZE));
        
        // get chunk
        int chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (chunk_ind != -1) {
            Chunk& chunk = chunks[chunk_ind];

            // get block pos inside chunk
            int x_in_chunk = int(x) % (CHUNK_SIZE_X * BLOCK_SIZE);
            int y_in_chunk = int(y) % (CHUNK_SIZE_Y * BLOCK_SIZE);
            int z_in_chunk = int(z) % (CHUNK_SIZE_Z * BLOCK_SIZE);
    
            int bx = int(x_in_chunk / BLOCK_SIZE);
            int by = int(y_in_chunk / BLOCK_SIZE);
            int bz = int(z_in_chunk / BLOCK_SIZE);

            // * not tnt block
            if (block_id != 83) {
                // set block
                Block& block = chunk.blocks[bx][by][bz];
                block.id = block_id;
                block.x = bx * BLOCK_SIZE;
                block.y = by * BLOCK_SIZE;
                block.z = bz * BLOCK_SIZE;
                
                // set updates
                on_remove = true;
                on_update_chunk = true;
                current_chunk_ind = chunk_ind;
                current_chunk = &chunk;
            }
        }
    }
}

void BlockEntity::update(Chunk (&chunks)[CHUNKS_COUNT], float dt) {
    update_gravity(dt);
    update_inert(dt);

    collisions(chunks);

    set_block_on_hit(chunks);
    
    update_cooldowns(dt);

    // update pos
    x += mx;
    y += my;
    z += mz;

    // rotate
    rotation_y += 0.6 * dt;

    // update angle and rotation
    angle_y += rotation_y;
    
    // update angle sin cos
    if (angle_y != last_angle_y) {
        angle_y_sin = sin(angle_y * (M_PI / 180));
        angle_y_cos = cos(angle_y * (M_PI / 180));
        
        last_angle_y = angle_y;
    }
    
    // normalize angle
    if (angle_y > 360) {
        angle_y -= 360;
    }
    if (angle_y < 0) {
        angle_y += 360;
    }
    
    // clear states and values
    mx = 0;
    my = 0;
    mz = 0;

    rotation_y = 0;
}