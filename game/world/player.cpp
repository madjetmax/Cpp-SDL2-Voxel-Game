#include "player.h"

Player::Player() {
    // x = (WORLD_SIZE_X / 2) * ((CHUNK_SIZE_X) * BLOCK_SIZE);
    x = 0;
    y = (WORLD_SIZE_Y) * ((CHUNK_SIZE_Y) * BLOCK_SIZE);
    // z = (WORLD_SIZE_Z / 2) * ((CHUNK_SIZE_Z) * BLOCK_SIZE);
    z = 0;
    // movement
    mx = 0;
    my = 0;
    mz = 0;

    go_fw = false;
    go_back = false;
    go_right = false;
    go_left = false;
    sneak = false;
    run = false;

    go_up = false;
    go_down = false;

    // interactions
    on_block_break = false;
    on_block_interaction = false;

    rotation_x = 0;
    rotation_y = 0;
}

void Player::controls(SDL_Event& event, Camera& camera, float dt) {
    if (event.type == SDL_KEYDOWN) {
        // * set values
        // forward back
        if (event.key.keysym.sym == SDLK_w) {
            go_fw = true;
        }
        if (event.key.keysym.sym == SDLK_s) {
            go_back = true;
        }
        // left right
        if (event.key.keysym.sym == SDLK_a) {
            go_left = true;            
        }
        if (event.key.keysym.sym == SDLK_d) {
            go_right = true;
        }
        // run 
        if (event.key.keysym.sym == SDLK_LSHIFT) {
            run = true;
        }

        // jump
        if (event.key.keysym.sym == SDLK_SPACE) {
            jump = true;
        }
        // sneak
        if (event.key.keysym.sym == SDLK_LCTRL) {
            sneak = true;
        }

        if (event.key.keysym.sym == SDLK_e) {
            in_inventory = !in_inventory;

            if (in_inventory) {
                SDL_ShowCursor(1);   
            } else {
                SDL_ShowCursor(0);   
            }
        }  

        // fast interactions
        if (event.key.keysym.sym == SDLK_r) {
            fast_interactions = true;
        }   
    }

    if (event.type == SDL_KEYUP) {
        // * clear values
        // forward back
        if (event.key.keysym.sym == SDLK_w) {
            go_fw = false;
        }
        if (event.key.keysym.sym == SDLK_s) {
            go_back = false;
        }
        // left right
        if (event.key.keysym.sym == SDLK_a) {
            go_left = false;            
        }
        if (event.key.keysym.sym == SDLK_d) {
            go_right = false;
        }
        // jump
        if (event.key.keysym.sym == SDLK_SPACE) {
            jump = false;
        }

        // sneak
        if (event.key.keysym.sym == SDLK_LCTRL) {
            sneak = false;
        }
        // fast interactions
        if (event.key.keysym.sym == SDLK_r) {
            fast_interactions = false;
        } 
    }

    // mouse motion
    if (event.type == SDL_MOUSEMOTION) {
        // rotate camera
        if (!in_inventory) {
            rotation_y -= (float)event.motion.xrel * MOUSE_SENS;
            rotation_x += (float)event.motion.yrel * MOUSE_SENS;
        }
    }

    // mouse clicks 
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (!in_inventory) {
            if (int(event.button.button) == 1) {
                on_block_break = true;
            }
            if (int(event.button.button) == 3) {
                on_block_interaction = true;
            }
        }
    }
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (int(event.button.button) == 1) {
            on_block_break = false;
            block_breaking_progress = 0;
        }
        if (int(event.button.button) == 3) {
            on_block_interaction = false;
        }
    }
}

void Player::movement(Camera& camera, float dt) {
    // set moltiply
    float move_multiply = 1;
    if (go_fw || go_back) {
        if (go_right || go_left) {
            move_multiply = 0.707f;
        }
    }
    // set speed
    float move_speed = walk_speed * move_multiply;

    // reduce if not on ground
    camera.shaking_speed = camera.walk_shaking_speed;
    if (swimming) {
        move_speed = walk_in_water_speed * move_multiply;
    }
    if (run && go_fw && !in_inventory) {
        move_speed = run_speed * move_multiply;
        if (swimming) {
            move_speed = run_in_water_speed * move_multiply;
        }
        // increase camera fov
        if (camera.fov < camera.run_fov) {
            camera.set_fov(camera.fov + 2 * dt);
        }
        // set camera shaking speed 
        camera.shaking_speed = camera.run_shaking_speed;
    }

    if (sneak && !in_inventory) {
        move_speed = sneak_speed;
        if (swimming) {
            move_speed = walk_in_water_speed * move_multiply;
        }
        run = false;
        // reduce camera fov
        if (camera.fov > camera.walk_fov) {
            camera.set_fov(camera.fov - 2 * dt);
        }
        // set camera shaking speed 
        camera.shaking_speed = camera.sneak_shaking_speed;
        // set bottom collider size
        collider_size_bottom = 130.0f;

        // move under water
        if (swimming) {
            if (gravity > min_swimming_gravity_go_down) {
                gravity -= 0.1 * dt;
            }
        }
    }
    // increate collider size bottom
    else {
        if (collider_size_bottom < 150.0f) {
            if (!swimming) {
                collider_size_bottom += 3.0f * dt;
                my += 5.0f * dt;
            }
            if (collider_size_bottom >= 150.0f) {
                collider_size_bottom = 150.0f;
            }
        }
    }

    // forward back
    if (go_fw && !in_inventory) {
        mz += move_speed *  camera.angle_y_cos * dt;
        mx += move_speed * -camera.angle_y_sin * dt;
        camera.on_shaking = true;
    } else {
        run = false;
        // reduce camera fov
        if (camera.fov > camera.walk_fov) {
            camera.set_fov(camera.fov - 2 * dt);
        }
    }

    if (!in_inventory) {
        if (go_back) {
            mz -= move_speed *  camera.angle_y_cos * dt;
            mx -= move_speed * -camera.angle_y_sin * dt;
            camera.on_shaking = true;
        }
        // left right
        if (go_left) {
            mx += move_speed * -camera.angle_y_cos * dt;
            mz += move_speed * -camera.angle_y_sin * dt;
            camera.on_shaking = true;
        }
        if (go_right) {
            mx -= move_speed * -camera.angle_y_cos * dt;
            mz -= move_speed * -camera.angle_y_sin * dt;
            camera.on_shaking = true;
        }
    }

    // clear camera shaking
    if ((!go_fw && !go_back && !go_right && !go_left) || in_inventory) {
        camera.on_shaking = false;
    }

    // jump or go up in water
    if (!in_inventory) {

        if (jump) {
            if (swimming) {
                if (gravity < max_swimming_gravity) {
                    gravity += 0.1 * dt;
                }
            } else {
                if (grounded) {
                    gravity += jump_height;
                    grounded = false;

                    // boost forward
                    if (go_fw) {
                        mz += (move_speed * 2) *  camera.angle_y_cos * dt;
                        mx += (move_speed * 2) * -camera.angle_y_sin * dt;
                    }
                }
            }
        }
    }
}


// * collisions
void Player::collisions(Chunk (&chunks)[CHUNKS_COUNT]) {
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
            swimming = false;
            under_water = false;

            collide_with_block(bx, by, bz, chunk, chunks, world_x, world_y, world_z, x_in_chunk, y_in_chunk, z_in_chunk);
            // collide_with_block(bx-1, by, bz, chunk, chunks, world_x, world_y, world_z, x_in_chunk, y_in_chunk, z_in_chunk);
            for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -2; dy <= 1; ++dy)
            for (int dz = -1; dz <= 1; ++dz) {
                if (dx || dy || dz) 
                    collide_with_block(bx + dx, by + dy, bz + dz, chunk, chunks, world_x, world_y, world_z, x_in_chunk, y_in_chunk, z_in_chunk);
            }

        }
    }
}
void Player::collide_with_block(int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT], int world_x, int world_y, int world_z, int x_in_chunk, int y_in_chunk, int z_in_chunk) {
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
            // water
            if (block->id == 6) {
                swimming = true;
            } 
            // other block
            else {
                mx = 0;
                // autojump
                if (grounded && (collider.auto_jump)) {
                    gravity += jump_height * 0.7;
                    grounded = false;
                }
            }
        }

        // y
        if (y_collide) {
            // water
            if (block->id == 6) {
                swimming = true;
                // set under water
                // int plr_y = int(y + BLOCK_SIZE / 2) % (CHUNK_SIZE_Y * BLOCK_SIZE);
                if ((block->y + chunk.y) > (y - BLOCK_SIZE / 2)) {
                    under_water = true;
                }
            } 
            // other block
            else {
                if (block->y < y_in_chunk) {
                    grounded = true;
                    on_fly = false;
                    go_up = false;
                    go_down = false;
                }
                my = 0;
                gravity = 0;
            }
        }

        // z
        if (z_collide) {
            // water
            if (block->id == 6) {
                swimming = true;
            } 
            // other block
            else {
                mz = 0;
                // autojump
                if (grounded && (collider.auto_jump)) {
                    gravity += jump_height * 0.7;
                    grounded = false;
                }
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

bool Player::collider_with_item_drop(ItemDrop& entity) { // not used in player collisions, calls only in world 
    // check simple dist to entity
    int dist_x = abs(x - entity.x);
    int dist_y = abs(y - entity.y);
    int dist_z = abs(z - entity.z);

    int min_pick_up_dist = 110;

    if (entity.pick_up_able) {
        if (dist_x <= min_pick_up_dist && dist_y / 2 <= min_pick_up_dist && dist_z <= min_pick_up_dist) {
            return true;
        }
    }
    return false;
}


int Player::get_chunk_ind_by_pos(int cx, int cy, int cz) {
    bool x_correct = bool(cx >= 0 && cx < WORLD_SIZE_X);
    bool y_correct = bool(cy >= 0 && cy < WORLD_SIZE_Y);
    bool z_correct = bool(cz >= 0 && cz < WORLD_SIZE_Z);

    if (!x_correct || !y_correct || !z_correct) {
        return -1;
    }
    return cx * WORLD_SIZE_Y * WORLD_SIZE_Z + cy * WORLD_SIZE_Z + cz;
}

void Player::update_gravity(float dt) {

    float min_value = min_gravity;
    float speed = gravity_speed;
    if (swimming) {
        min_value = min_swimming_gravity;
        speed = swimming_gravity_speed;
        if (sneak) {
            min_value = min_swimming_gravity_go_down;
        }
    }

    if (gravity > min_value) {
        gravity -= speed * dt;
    } else {
        gravity = min_value;
    }
    my += gravity * dt;
}

void Player::update_angle_direction(Camera& camera) {
    // 0
    if (camera.angle_y < 45 || camera.angle_y >= 315) angle_dirrection = 0;
    // 90
    else if (camera.angle_y < 135 && camera.angle_y >= 45) angle_dirrection = 90;
    // 180
    else if (camera.angle_y < 225 && camera.angle_y >= 135) angle_dirrection = 180;
    // 270
    else if (camera.angle_y < 315 && camera.angle_y >= 225) angle_dirrection = 270;
}


void Player::update(Camera& camera, Chunk (&chunks)[CHUNKS_COUNT], float dt) {
    movement(camera, dt);
    update_gravity(dt);

    collisions(chunks);


    // update pos
    x += mx;
    y += my;
    z += mz;

    camera.x += mx;
    camera.y += my;
    camera.z += mz;

    camera.angle_x += rotation_x;
    camera.angle_y += rotation_y;

    // limit vertical camera rotation
    if (camera.angle_x > 90) {
        camera.angle_x = 90;
    }
    if (camera.angle_x < -90) {
        camera.angle_x = -90;
    }

    // normalize horizontal camera rotation
    if (camera.angle_y < 0.0f) {
        camera.angle_y += 360.0f;
    }
    if (camera.angle_y > 360.0f) {
        camera.angle_y -= 360.0f;
    }

    angle_y_sin = camera.angle_y_sin;
    angle_y_cos = camera.angle_y_cos;

    update_angle_direction(camera);

    // clear states
    mx = 0;
    my = 0;
    mz = 0;

    rotation_x = 0;
    rotation_y = 0;
}