#include "world_loader.h"


WorldLoader::WorldLoader() {}

void WorldLoader::full_chunk_load(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], int chunk_ind, Chunk& chunk) {
    int chunk_x = chunk.x / (CHUNK_SIZE_X * BLOCK_SIZE);
    int chunk_y = chunk.y / (CHUNK_SIZE_Y * BLOCK_SIZE);
    int chunk_z = chunk.z / (CHUNK_SIZE_Z * BLOCK_SIZE);

    // * get near chunks
    set_near_chunks(chunks, chunk_x, chunk_y, chunk_z);
    int light_sources_size = set_light_sources_blocks_around(chunks, chunk_x, chunk_y, chunk_z);

    for (size_t x = 0; x < CHUNK_SIZE_X; x++)
    for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
    for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
    {
        Block& block = chunk.blocks[x][y][z];
        if (block.id == 0) {
            continue;
        }

        // states to hide face
        hide_front_face = false;
        hide_back_face = false;

        hide_right_face = false;
        hide_left_face = false;

        hide_top_face = false;
        hide_bottom_face = false;

        // clear blocks ids around
        if (blocks_around_shadowable_udpated) {
            clear_block_shadowable_around();
            blocks_around_shadowable_udpated = false;
        }

        water_transparency = 200;
        // blocks ids around block
        front_block_id = 0;
        back_block_id = 0;

        right_block_id = 0;
        left_block_id = 0;

        top_block_id = 0;
        bottom_block_id = 0;
                
        // * check if block has neighbour
        // get data
        FullBlockData& full_block_data  = all_blocks_full_data[block.id];

        check_block_faces_visible(block, full_block_data, x, y, z, chunk);
        check_blocks_around(block, full_block_data, x, y, z, chunk, chunks);

        set_block_updates(chunks, block, chunk, chunk_ind);
        // clear light
        float block_sun_light = 0;
        BlockLight block_light;
        // check light sources
        check_light_sources(block, block_sun_light, block_light, light_sources_size);

        // get model
        FullBlockModel block_model = all_blocks_models[block.id];

        // add faces
        for (size_t fi = 0; fi < block_model.faces.size(); fi++)
        {
            RawFace3d& face = block_model.faces[fi];
            
            // skip face if hide
            if (hide_face(face)) {
                continue;
            }

            SDL_Color face_point1_color = {255, 255, 255, 255}; 
            SDL_Color face_point2_color = {255, 255, 255, 255}; 
            SDL_Color face_point3_color = {255, 255, 255, 255}; 

            face.point1_color = face_point1_color;
            face.point2_color = face_point2_color;
            face.point3_color = face_point3_color;

            face.sun_light = block_sun_light;
            face.light = block_light;

            // set transparency for water
            if (face.t_id == 8) {
                face.point1_color.a = water_transparency;
                face.point2_color.a = water_transparency;
                face.point3_color.a = water_transparency;

                // add more blue color
                face.point1_color.r -= water_transparency / 20;
                face.point1_color.g -= water_transparency / 20;
                face.point1_color.g -= water_transparency / 10;

                face.point2_color.r -= water_transparency / 20;
                face.point2_color.g -= water_transparency / 20;
                face.point2_color.g -= water_transparency / 10;

                face.point3_color.r -= water_transparency / 20;
                face.point3_color.g -= water_transparency / 20;
                face.point3_color.g -= water_transparency / 10;
            }
            
            // face shadowind by face normal
            if (full_block_data.light.r <= 0 && full_block_data.light.g <= 0 && full_block_data.light.b <= 0 ) {
                base_face_shadowing(face);
                ambiant_face_shadowing(face);
            }

            // set block and chunk data in face
            face.block_x = x;
            face.block_y = y;
            face.block_z = z;

            face.chunk_ind = chunk_ind;

            update_face_pos(face, block, chunk);

            world_renderer.raw_faces_3d.push_back(face);
        }
    }
}

void WorldLoader::clear_block_shadowable_around() {
    // set ids
    for (size_t x = 0; x < 3; x++)
    for (size_t y = 0; y < 2; y++)
    for (size_t z = 0; z < 3; z++)
    {
        blocks_around_shadowable[x][y][z] = false;
    }
}

// for chunk
void WorldLoader::set_near_chunks(Chunk (&chunks)[CHUNKS_COUNT], int chunk_x, int chunk_y, int chunk_z) {
    // front
    near_chunk_front = nullptr;
    if (chunk_z != WORLD_SIZE_Z - 1) {
        int ind = get_chunk_ind_by_pos(chunk_x, chunk_y, chunk_z+1);
        near_chunk_front = &chunks[ind];
    }
    // back
    near_chunk_back = nullptr;
    if (chunk_z != 0) {
        int ind = get_chunk_ind_by_pos(chunk_x, chunk_y, chunk_z-1);
        near_chunk_back = &chunks[ind];
    }
    // right
    near_chunk_right = nullptr;
    if (chunk_x != WORLD_SIZE_X - 1) {
        int ind = get_chunk_ind_by_pos(chunk_x+1, chunk_y, chunk_z);
        near_chunk_right = &chunks[ind];
    }
    // left
    near_chunk_left = nullptr;
    if (chunk_x != 0) {
        int ind = get_chunk_ind_by_pos(chunk_x-1, chunk_y, chunk_z);
        near_chunk_left = &chunks[ind];
    }
    // top
    near_chunk_top = nullptr;
    if (chunk_y != WORLD_SIZE_Y - 1) {
        int ind = get_chunk_ind_by_pos(chunk_x, chunk_y+1, chunk_z);
        near_chunk_top = &chunks[ind];
    }
    // bottom
    near_chunk_bottom = nullptr;
    if (chunk_y != 0) {
        int ind = get_chunk_ind_by_pos(chunk_x, chunk_y-1, chunk_z);
        near_chunk_bottom = &chunks[ind];
    }
}

int WorldLoader::set_light_sources_blocks_around(Chunk (&chunks)[CHUNKS_COUNT], int chunk_x, int chunk_y, int chunk_z) {
    // clear collected light sources
    light_sources_blocks_around.clear();
    
    // collect blocks
    int light_sources_size = 0;
    
    for (int wx = -1; wx <= 1; wx++)
    for (int wy = -1; wy <= 1; wy++)
    for (int wz = -1; wz <= 1; wz++) {
        // get ind and chunk
        int ind = get_chunk_ind_by_pos(chunk_x+wx, chunk_y+wy, chunk_z+wz);
        if (ind != -1) {
            Chunk& near_chunk = chunks[ind];

            if (near_chunk.is_air) {
                continue;
            }
            // collect light sources
            near_chunk.light_sources_blocks.reserve(100);
            for (size_t bi = 0; bi < near_chunk.light_sources_blocks.size(); bi++)
            {
                Block block = near_chunk.light_sources_blocks[bi];
                block.x += near_chunk.x - chunk_x * (CHUNK_SIZE_X * BLOCK_SIZE);
                block.y += near_chunk.y - chunk_y * (CHUNK_SIZE_Y * BLOCK_SIZE);
                block.z += near_chunk.z - chunk_z * (CHUNK_SIZE_Z * BLOCK_SIZE);

                light_sources_blocks_around.push_back(block);
                light_sources_size++;
            }
        } 
    }
    // return size
    return light_sources_size;
}

int WorldLoader::get_chunk_ind_by_pos(int x, int y, int z) {
    bool x_correct = bool(x >= 0 && x < WORLD_SIZE_X);
    bool y_correct = bool(y >= 0 && y < WORLD_SIZE_Y);
    bool z_correct = bool(z >= 0 && z < WORLD_SIZE_Z);

    if (!x_correct || !y_correct || !z_correct) {
        return -1;
    }
    return x * WORLD_SIZE_Y * WORLD_SIZE_Z + y * WORLD_SIZE_Z + z;
}
// for block
void WorldLoader::check_block_faces_visible(Block& block, FullBlockData& block_data, int x, int y, int z, Chunk& chunk) {
    
    // front
    if (block.z != (CHUNK_SIZE_Z - 1) * BLOCK_SIZE) {
        Block& check_block = chunk.blocks[x][y][z+1];
        // get faces visiblity model
        uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

        FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
        uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

        uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
        HideFacesBlockModel hide_faces = hide_faces_block_models[key];

        if (check_block.id != 0)  {
            front_block_id = check_block.id;
            if (hide_faces.front) hide_front_face = true;
            // update water nead lava
            if (check_block.id == 76 && block.id == 6) {
               block.id = 9; // set cobblestone
                block.update_time = 0;
            } 
        }

    } 
    // block on border
    else {
        if (near_chunk_front) {
            Block& check_block = near_chunk_front->blocks[x][y][0];
            // get faces visiblity model
            uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

            FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
            uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

            uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
            HideFacesBlockModel hide_faces = hide_faces_block_models[key];

            if (check_block.id != 0)  {
                front_block_id = check_block.id;
                if (hide_faces.front) hide_front_face = true;
                // update water nead lava
                if (check_block.id == 76 && block.id == 6) {
                    block.id = 9; // set cobblestone
                    block.update_time = 0;
                } 
            }

        } else {
            hide_front_face = true;
        }
    }
    // back
    if (block.z != 0) {
        Block& check_block = chunk.blocks[x][y][z-1];
        // get faces visiblity model
        uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

        FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
        uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

        uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
        HideFacesBlockModel hide_faces = hide_faces_block_models[key];

        if (check_block.id != 0)  {
            back_block_id = check_block.id;
            if (hide_faces.back) hide_back_face = true;

            // update water nead lava
            if (check_block.id == 76 && block.id == 6) {
                block.id = 9; // set cobblestone
                block.update_time = 0;
            } 
        }
    } 
    // block on border
    else {
        if (near_chunk_back) {
            Block& check_block = near_chunk_back->blocks[x][y][CHUNK_SIZE_Z-1];
            // get faces visiblity model
            uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

            FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
            uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

            uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
            HideFacesBlockModel hide_faces = hide_faces_block_models[key];

            if (check_block.id != 0)  {
                back_block_id = check_block.id;
                if (hide_faces.back) hide_back_face = true;

                // update water nead lava
                if (check_block.id == 76 && block.id == 6) {
                    block.id = 9; // set cobblestone
                    block.update_time = 0;
                } 
            }
        } else {
            hide_back_face = true;
        }
    }

    // right
    if (block.x != (CHUNK_SIZE_X - 1) * BLOCK_SIZE) {
        Block& check_block = chunk.blocks[x+1][y][z];
        // get faces visiblity model
        uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

        FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
        uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

        uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
        HideFacesBlockModel hide_faces = hide_faces_block_models[key];

        if (check_block.id != 0)  {
            right_block_id = check_block.id;
            if (hide_faces.right) hide_right_face = true;

            // update water nead lava
            if (check_block.id == 76 && block.id == 6) {
                block.id = 9; // set cobblestone
                block.update_time = 0;
            } 
        }
    } 
    // block on border
    else {
        if (near_chunk_right) {
            Block& check_block = near_chunk_right->blocks[0][y][z];
            // get faces visiblity model
            uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

            FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
            uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

            uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
            HideFacesBlockModel hide_faces = hide_faces_block_models[key];

            if (check_block.id != 0)  {
                right_block_id = check_block.id;
                if (hide_faces.right) hide_right_face = true;

                // update water nead lava
                if (check_block.id == 76 && block.id == 6) {
                    block.id = 9; // set cobblestone
                    block.update_time = 0;
                } 
            }
        } else {
            hide_right_face = true;
        }
    }
    // left
    if (block.x != 0) {
        Block& check_block = chunk.blocks[x-1][y][z];
        // get faces visiblity model
        uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

        FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
        uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

        uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
        HideFacesBlockModel hide_faces = hide_faces_block_models[key];

        if (check_block.id != 0)  {
            left_block_id = check_block.id;
            if (hide_faces.left) hide_left_face = true;

            // update water nead lava
            if (check_block.id == 76 && block.id == 6) {
                block.id = 9; // set cobblestone
                block.update_time = 0;                
            } 
        }
    } 
    // block on border
    else {
        if (near_chunk_left) {
            Block& check_block = near_chunk_left->blocks[CHUNK_SIZE_X-1][y][z];
            // get faces visiblity model
            uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

            FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
            uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

            uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
            HideFacesBlockModel hide_faces = hide_faces_block_models[key];

            if (check_block.id != 0)  {
                left_block_id = check_block.id;
                if (hide_faces.left) hide_left_face = true;

                // update water nead lava
                if (check_block.id == 76 && block.id == 6) {
                    block.id = 9; // set cobblestone
                    block.update_time = 0;
                    block.light_level = 0;

                    // remove fron light sources
                    delete_block_from_light_sources(block, chunk);
                } 
            }
        } else {
            hide_left_face = true;
        }
    }

    // top
    if (block.y != (CHUNK_SIZE_Y - 1) * BLOCK_SIZE) {
        Block& check_block = chunk.blocks[x][y+1][z];
        // get faces visiblity model
        uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

        FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
        uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

        uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
        HideFacesBlockModel hide_faces = hide_faces_block_models[key];

        if (check_block.id != 0)  {
            top_block_id = check_block.id;
            if (hide_faces.top) hide_top_face = true;
            

            // lava with water on top
            if (block.id == 76 && check_block.id == 6) {
                block.id = randint(77, 80); // set obsidian
                block.light_level = 0;

                // remove fron light sources
                delete_block_from_light_sources(block, chunk);
            }
        }

        // set sun light 0
        if (check_block.id != 0 && block.sun_light > 0) {
            block.sun_light = 0;
            // remove fron light sources
            delete_block_from_light_sources(block, chunk);
        }
    } 
    // block on border
    else {
        if (near_chunk_top) {
            Block& check_block = near_chunk_top->blocks[x][0][z];
            // get faces visiblity model
            uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

            FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
            uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

            uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
            HideFacesBlockModel hide_faces = hide_faces_block_models[key];


            if (check_block.id != 0)  {
                top_block_id = check_block.id;
                if (hide_faces.top) hide_top_face = true;
            }

            // lava with water on top
            if (block.id == 76 && check_block.id == 6) {
                block.id = randint(77, 80); // set obsidian
            }

            // set sun light 0
            if (check_block.id != 0 ) {
                block.sun_light = 0;

                // remove fron light sources
                delete_block_from_light_sources(block, chunk);
            }
        }
    }
    // bottom
    if (block.y != 0) {
        Block& check_block = chunk.blocks[x][y-1][z];
        // get faces visiblity model
        uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

        FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
        uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

        uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
        HideFacesBlockModel hide_faces = hide_faces_block_models[key];

        if (check_block.id != 0)  {
            bottom_block_id = check_block.id;
            if (hide_faces.bottom) hide_bottom_face = true;
        }
    }
    // block on border
    else {
        if (near_chunk_bottom) {
            Block& check_block = near_chunk_bottom->blocks[x][CHUNK_SIZE_Y-1][z];
            // get faces visiblity model
            uint8_t block_hide_faces_model_id = block_data.hide_faces_model_id;

            FullBlockData& check_block_data = all_blocks_full_data[check_block.id];
            uint8_t check_block_hide_faces_model_id = check_block_data.hide_faces_model_id;

            uint16_t key = (block_hide_faces_model_id << 8) | check_block_hide_faces_model_id;
            HideFacesBlockModel hide_faces = hide_faces_block_models[key];

            if (check_block.id != 0)  {
                bottom_block_id = check_block.id;
                if (hide_faces.bottom) hide_bottom_face = true;
            }
        }
    }

    // * check water blocks under water
    if (block.id != 6) {
        return;
    }
    int water_depth_checks = 5;
    for (int i = 0; i < water_depth_checks; i++)
    {
        if (y - i > 0) {
            Block& check_block = chunk.blocks[x][y-i-1][z];
            
            if (check_block.id == 6) {
                water_transparency += 10;
            } 
            // break if block is not water
            else {
                break;
            }
        }
        // block on border
        else {
            if (near_chunk_bottom) {
                Block& check_block = near_chunk_bottom->blocks[x][CHUNK_SIZE_Y-(i + 1)][z];
                
                if (check_block.id == 6) {
                    water_transparency += 10;
                }
                // break if block is not water
                else {
                    break;
                }
            }
        }
    }
}

Block* WorldLoader::get_block_by_pos(int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT]) {
    Chunk* chunk_ = &chunk;
    int chunk_x = chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X);
    int chunk_y = chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y);
    int chunk_z = chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z);

    bool pos_changed = false;

    // * normalize block and chank pos
    // x 
    if (bx < 0) {
        bx = CHUNK_SIZE_X - 1;
        chunk_x -= 1;
        pos_changed = true;
    }
    if (bx >= CHUNK_SIZE_X) {
        bx = 0;
        chunk_x += 1;
        pos_changed = true;
    }

    // y 
    if (by < 0) {
        by = CHUNK_SIZE_Y - 1;
        chunk_y -= 1;
        pos_changed = true;
    }
    if (by >= CHUNK_SIZE_Y) {
        by = 0;
        chunk_y += 1;
        pos_changed = true;
    }

    // z 
    if (bz < 0) {
        bz = CHUNK_SIZE_Z - 1;
        chunk_z -= 1;
        pos_changed = true;
    }
    if (bz >= CHUNK_SIZE_Z) {
        bz = 0;
        chunk_z += 1;
        pos_changed = true;
    }

    // get chunk 
    if (pos_changed) {
        int chunk_ind = get_chunk_ind_by_pos(chunk_x, chunk_y, chunk_z);
        if (chunk_ind != -1) {
            chunk_ = &chunks[chunk_ind];
        }
    }
    // return block
    return &chunk_->blocks[bx][by][bz];
}

void WorldLoader::check_blocks_around(Block& block, FullBlockData& block_data, int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT]) {
    for (int x = -1; x < 2; x++)
    for (int y = -1; y < 1; y++)
    for (int z = -1; z < 2; z++)
    {
        bool on_check = true;
        // skip if blocks around ids
        if (bottom_block_id != 0 && y == -1) {
            on_check = true;   
        }
        if (top_block_id != 0 && y == 0) {
            on_check = true;   
        }

        // get block
        if (on_check && (x != 0 || z != 0)) {
            int by_ = by + y;
            if (y == 0) {
                by_ = by + 1; 
            }
            Block* check_block = get_block_by_pos(bx+x, by_, bz+z, chunk, chunks);
            // set id to blocks around ids
            if (check_block && check_block->id != 0) {
                FullBlockData& check_block_data = all_blocks_full_data[check_block->id];
                uint8_t hide_faces_model_id = check_block_data.hide_faces_model_id;
                
                // check models to set shadowable
                if (
                    hide_faces_model_id==1 ||
                    hide_faces_model_id==3 ||
                    hide_faces_model_id==3 ||
                    hide_faces_model_id==5 ||
                    hide_faces_model_id==6 ||
                    hide_faces_model_id==7 ||
                    hide_faces_model_id==8
                ) {
                    blocks_around_shadowable[x+1][y+1][z+1] = true;
                    blocks_around_shadowable_udpated = true;
                }
            } else {
                blocks_around_shadowable[x+1][y+1][z+1] = false;
            }
        }
    }   
}

void WorldLoader::set_block_updates(Chunk (&chunks)[CHUNKS_COUNT], Block& block, Chunk& chunk, int chunk_ind) {
    
    // * grass with top block
    if ((block.id == 1 || block.id == 2 || block.id == 3 || block.id == 4)) {
        if (top_block_id != 0) {
            FullBlockData& block_data = all_blocks_full_data[top_block_id];

            if (block.update_time == 0 && block_data.can_destroy_grass) block.update_time = (uint8_t)randint(1, 5);
        } else {
            block.update_time = 0;
        }
    }
    
    // * dirt with grass
    else if (block.id == 5) {
        if (top_block_id == 0) {
            if (
                (front_block_id == 1 || front_block_id == 2 || front_block_id == 3 || front_block_id == 4) || 
                (back_block_id == 1 || back_block_id == 2 || back_block_id == 3 || back_block_id == 4) || 
                (right_block_id == 1 || right_block_id == 2 || right_block_id == 3 || right_block_id == 4) || 
                (left_block_id == 1 || left_block_id == 2 || left_block_id == 3 || left_block_id == 4)
            ) {
                if (block.update_time == 0) block.update_time = (uint8_t)randint(1, 5);
            } else {
                block.update_time = 0;
            }
        } else {
            FullBlockData& block_data = all_blocks_full_data[top_block_id];
            if (!block_data.can_destroy_grass) block.update_time = (uint8_t)randint(1, 5);
            else block.update_time = 0;
        }
    } 

    // * bed with water
    else if (block.id == 45) {
        if (
            (front_block_id == 6) || 
            (back_block_id == 6) || 
            (right_block_id == 6) || 
            (left_block_id == 6)
        ) {
            if (block.update_time == 0) block.update_time = (uint8_t)randint(1, 3);
        } else {
            block.update_time = 0;
        }
    } 

    else if (block.id == 46) {
        if (
            (front_block_id != 6) && 
            (back_block_id != 6) && 
            (right_block_id != 6) && 
            (left_block_id != 6)
        ) {
            if (block.update_time == 0) block.update_time = (uint8_t)randint(1, 3);
        } else {
            block.update_time = 0;
        }
    } 
    // * plants
    // wheat levels
    else if (block.id == 47) {
        if (block.update_time == 0) {
            if (bottom_block_id == 45) block.update_time = (uint8_t)randint(6, 10);
            else if (bottom_block_id == 46) block.update_time = (uint8_t)randint(4, 8);
        }
    }
    else if (block.id == 48) {
        if (block.update_time == 0) {
            if (bottom_block_id == 45) block.update_time = (uint8_t)randint(6, 10);
            else if (bottom_block_id == 46) block.update_time = (uint8_t)randint(4, 8);
        }
    }
    else if (block.id == 49) {
        if (block.update_time == 0) {
            if (bottom_block_id == 45) block.update_time = (uint8_t)randint(6, 10);
            else if (bottom_block_id == 46) block.update_time = (uint8_t)randint(4, 8);
        }
    }    

    // wheat without bed under
    if (block.id == 47 || block.id == 48 || block.id == 49 || block.id == 50) {
        if (bottom_block_id != 45 && bottom_block_id != 46) {
            block.id = 0;
            block.update_time = 0;
        }
    }

    // * water with empty blocks around
    else if (block.id == 6) {
        if (front_block_id == 0 || back_block_id == 0 || right_block_id == 0 || left_block_id == 0 || bottom_block_id == 0) {
            block.update_time = 1;
        }
        else {
            block.update_time = 0;
        }
    }

    // * collblestone with water and lava
    else if (block.id == 9) {
        if (front_block_id == 6 || front_block_id == 76) hide_front_face = false;
        if (back_block_id  == 6 || back_block_id  == 76) hide_back_face  = false;
        if (right_block_id == 6 || right_block_id == 76) hide_right_face = false;
        if (left_block_id  == 6 || left_block_id  == 76) hide_left_face  = false;
    }

    // * obsidian with water on top
    else if (block.id == 77 || block.id == 78 || block.id == 79 || block.id == 80) {
        if (top_block_id == 6) hide_top_face = false;
    }

    // * wet sponge with water around
    else if (block.id == 81) {
        // loop all blocks in chunk and replace water
        if (front_block_id == 6 || back_block_id == 6 || right_block_id == 6 || left_block_id == 6 || top_block_id == 6 || bottom_block_id == 6) {
            for (size_t x = 0; x < CHUNK_SIZE_X; x++)
            for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
            for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
            {
                Block& water_block = chunk.blocks[x][y][z];
                if (water_block.id != 6) {
                    continue;
                }
                
                // get and check dist
                int dist = sqrt(
                    pow((block.x - water_block.x), 2) + 
                    pow((block.y - water_block.y), 2) +
                    pow((block.z - water_block.z), 2)
                );
                // 5 blocks
                if (dist <= 5 * BLOCK_SIZE) {
                    water_block.id = 0; // set air
                    water_block.update_time = 0;
                }
            }

            // set wet sponge
            block.id = 82;

            // add chunk to load queue
            ChunkToLoad chunk_to_load = {&chunk, chunk_ind, true, false, 1};
            chunks_to_load_queue.push_back(chunk_to_load);
        }
    }

    // * falling blocks
    // sand 
    else if (block.id == 7 && bottom_block_id == 0) {
        // add entity
        BlockEntity entity;
        entity.x = block.x + chunk.x;
        entity.y = block.y + chunk.y;
        entity.z = block.z + chunk.z;

        entity.block_id = block.id;

        all_blocks_entities->push_back(entity);

        // clear block
        block.id = 0; // air
        block.update_time = 0;

        // update current chunk
        if (!check_chunk_added_to_load_queue(chunk)) {
            // add to chunks load queue
            ChunkToLoad chunk_to_load = {&chunk, chunk_ind, false, true, 1};
            chunks_to_load_queue.push_back(chunk_to_load);
        }

        // update near chunks
        // x 
        if (block.x == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X) - 1,
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.x == CHUNK_SIZE_X-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X) + 1,
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        // y 
        if (block.y == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y) - 1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.y == CHUNK_SIZE_Y-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y) + 1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }

        // z
        if (block.z == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z) - 1
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.z == CHUNK_SIZE_Z-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z) + 1
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
    } 
    // gravel 
    else if ((block.id == 72 || block.id == 73 || block.id == 74 || block.id == 75) && bottom_block_id == 0) {
        // add entity
        BlockEntity entity;
        entity.x = block.x + chunk.x;
        entity.y = block.y + chunk.y;
        entity.z = block.z + chunk.z;

        entity.block_id = randint(72, 75);

        all_blocks_entities->push_back(entity);

        // clear block
        block.id = 0; // air
        block.update_time = 0;

        // update current chunk
        if (!check_chunk_added_to_load_queue(chunk)) {
            // add to chunks load queue
            ChunkToLoad chunk_to_load = {&chunk, chunk_ind, false, true, 1};
            chunks_to_load_queue.push_back(chunk_to_load);
        }

        // update near chunks
        // x 
        if (block.x == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X) - 1,
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.x == CHUNK_SIZE_X-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X) + 1,
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        // y 
        if (block.y == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y) - 1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.y == CHUNK_SIZE_Y-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y) + 1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }

        // z
        if (block.z == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z) - 1
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.z == CHUNK_SIZE_Z-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z) + 1
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
    } 

    // * tnt
    else if (block.id == 83) {
        // add entity
        BlockEntity entity;
        entity.inert_x = randint(-10, 10) / 4;
        entity.inert_z = randint(-10, 10) / 4;

        entity.gravity = randint(5, 10) / 2;

        entity.x = block.x + chunk.x;
        entity.y = block.y + chunk.y;
        entity.z = block.z + chunk.z;

        entity.block_id = 83;

        all_blocks_entities->push_back(entity);

        // clear block
        block.id = 0; // air
        block.update_time = 0;

        // update current chunk
        if (!check_chunk_added_to_load_queue(chunk)) {
            // add to chunks load queue
            ChunkToLoad chunk_to_load = {&chunk, chunk_ind, false, true, 1};
            chunks_to_load_queue.push_back(chunk_to_load);
        }

        // update near chunks
        // x 
        if (block.x == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X) - 1,
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.x == CHUNK_SIZE_X-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X) + 1,
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        // y 
        if (block.y == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y) - 1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.y == CHUNK_SIZE_Y-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y) + 1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }

        // z
        if (block.z == 0) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z) - 1
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block.z == CHUNK_SIZE_Z-1) {
            int chunk_ind_ = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y),
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z) + 1
            );
            if (chunk_ind_ != 1) {
                Chunk& chunk_ = chunks[chunk_ind_];
                if (!check_chunk_added_to_load_queue(chunk_)) {
                    // add to chunks load queue
                    ChunkToLoad chunk_to_load = {&chunk_, chunk_ind_, false, true, 1};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
    }
}

void WorldLoader::check_light_sources(Block& block, float& block_sun_light, BlockLight& block_light, int light_sources_size) {
    light_sources_blocks_around.reserve(100);

    for (size_t bi = 0; bi < light_sources_size; bi++)
    {
        Block& light_block = light_sources_blocks_around[bi];
        FullBlockData& light_block_data = all_blocks_full_data[light_block.id];

        // get dist and calculate brightness for light
        float dist = sqrt(
            pow(light_block.x - block.x, 2) + 
            pow(light_block.y - block.y, 2) +
            pow(light_block.z - block.z, 2) 
        );

        // * sun light
        // calc light level from dist
        float new_light_level = float(max(0, int(SUN_LIGHT_MAX_DIST - dist))) / 1000.0f * light_block.sun_light;
        if (new_light_level > 1.0f) {
            new_light_level = 1.0f;
        }
        // add only if brighter
        if (new_light_level > block_sun_light) {
            block_sun_light = new_light_level;
        }

        // * rgb light here it is what I ask
        // calc light level from dist
        int new_r = float(max(0, int(LIGHT_MAX_DIST - dist))) / 1000.0f * (float)light_block_data.light.r;
        int new_g = float(max(0, int(LIGHT_MAX_DIST - dist))) / 1000.0f * (float)light_block_data.light.g;
        int new_b = float(max(0, int(LIGHT_MAX_DIST - dist))) / 1000.0f * (float)light_block_data.light.b;

        // // combine color
        // block_light.r = (uint8_t)min(255, (int)block_light.r + new_r);
        // block_light.g = (uint8_t)min(255, (int)block_light.g + new_g);
        // block_light.b = (uint8_t)min(255, (int)block_light.b + new_b);

        // set if new value is higher
        if (new_r > (int)block_light.r) block_light.r = (uint8_t)new_r;
        if (new_g > (int)block_light.g) block_light.g = (uint8_t)new_g;
        if (new_b > (int)block_light.b) block_light.b = (uint8_t)new_b;

        // // calc average
        // block_light.r  = (uint8_t)min(255, ((int)block_light.r + (int)block_light.r + new_r) / 2);
        // block_light.g = (uint8_t)min(255, ((int)block_light.g + (int)block_light.g + new_g) / 2);
        // block_light.b = (uint8_t)min(255, ((int)block_light.b + (int)block_light.b + new_b) / 2);
    }
}

// face
bool WorldLoader::hide_face(RawFace3d& face) {
    if (face.hideable) {
        if (hide_front_face && face.normal == 'f') {
            return true;
        }
        if (hide_back_face && face.normal == 'b') {
            return true;
        }
        
        if (hide_right_face && face.normal == 'r') {
            return true;
        }
        if (hide_left_face && face.normal == 'l') {
            return true;
        }

        if (hide_top_face && face.normal == 't') {
            return true;
        }
        if (hide_bottom_face && face.normal == 'd') {
            return true;
        }
    }
    return false;
}

void WorldLoader::base_face_shadowing(RawFace3d& face) {
    // color division by face normal

    float front_back_multiplier = 0.98;
    float right_left_multiplier = 0.97;
    float top_multiplier = 1;
    float bottom_multiplier = 0.7;

    // front
    if (face.normal == 'f') {
        face.point1_color.r *= front_back_multiplier;
        face.point1_color.g *= front_back_multiplier;
        face.point1_color.b *= front_back_multiplier;

        face.point2_color.r *= front_back_multiplier;
        face.point2_color.g *= front_back_multiplier;
        face.point2_color.b *= front_back_multiplier;

        face.point3_color.r *= front_back_multiplier;
        face.point3_color.g *= front_back_multiplier;
        face.point3_color.b *= front_back_multiplier;
    }

    // back
    if (face.normal == 'b') {
        face.point1_color.r *= front_back_multiplier;
        face.point1_color.g *= front_back_multiplier;
        face.point1_color.b *= front_back_multiplier;

        face.point2_color.r *= front_back_multiplier;
        face.point2_color.g *= front_back_multiplier;
        face.point2_color.b *= front_back_multiplier;

        face.point3_color.r *= front_back_multiplier;
        face.point3_color.g *= front_back_multiplier;
        face.point3_color.b *= front_back_multiplier;
    }

    // right
    if (face.normal == 'r') {
        face.point1_color.r *= right_left_multiplier;
        face.point1_color.g *= right_left_multiplier;
        face.point1_color.b *= right_left_multiplier;

        face.point2_color.r *= right_left_multiplier;
        face.point2_color.g *= right_left_multiplier;
        face.point2_color.b *= right_left_multiplier;

        face.point3_color.r *= right_left_multiplier;
        face.point3_color.g *= right_left_multiplier;
        face.point3_color.b *= right_left_multiplier;
    }

    // left
    if (face.normal == 'l') {
        face.point1_color.r *= right_left_multiplier;
        face.point1_color.g *= right_left_multiplier;
        face.point1_color.b *= right_left_multiplier;

        face.point2_color.r *= right_left_multiplier;
        face.point2_color.g *= right_left_multiplier;
        face.point2_color.b *= right_left_multiplier;

        face.point3_color.r *= right_left_multiplier;
        face.point3_color.g *= right_left_multiplier;
        face.point3_color.b *= right_left_multiplier;
    }
    // top
    if (face.normal == 't') {
        face.point1_color.r *= top_multiplier;
        face.point1_color.g *= top_multiplier;
        face.point1_color.b *= top_multiplier;

        face.point2_color.r *= top_multiplier;
        face.point2_color.g *= top_multiplier;
        face.point2_color.b *= top_multiplier;

        face.point3_color.r *= top_multiplier;
        face.point3_color.g *= top_multiplier;
        face.point3_color.b *= top_multiplier;
    }
    // bottom
    if (face.normal == 'd') {
        face.point1_color.r *= bottom_multiplier;
        face.point1_color.g *= bottom_multiplier;
        face.point1_color.b *= bottom_multiplier;

        face.point2_color.r *= bottom_multiplier;
        face.point2_color.g *= bottom_multiplier;
        face.point2_color.b *= bottom_multiplier;

        face.point3_color.r *= bottom_multiplier;
        face.point3_color.g *= bottom_multiplier;
        face.point3_color.b *= bottom_multiplier;
    }
}

void face_points_shadowing(SDL_Color* color1, SDL_Color* color2, bool& shadowing_condition1, bool& shadowing_condition2, float color_multiplier=0.7) {
    if (color1) {
        if (!shadowing_condition1) {
            color1->r *= color_multiplier;
            color1->g *= color_multiplier;
            color1->b *= color_multiplier;

            shadowing_condition1 = true;
        }
    }
    if (color2) {
        if (!shadowing_condition2) {
            color2->r *= color_multiplier;
            color2->g *= color_multiplier;
            color2->b *= color_multiplier;

            shadowing_condition2 = true;
        }
    }
}

void WorldLoader::ambiant_face_shadowing(RawFace3d& face) {
    bool face_point1_shadowed = false;
    bool face_point2_shadowed = false;
    bool face_point3_shadowed = false;

    // all faces around
    if (face.normal != 't' && face.normal != 'd' && bottom_block_id == 0) {
        // first triangle
        if (face.point1.y == face.point3.y && face.point1.y < face.point2.y) {
            face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
        }
        if (face.point1.y == face.point2.y && face.point1.y < face.point3.y) {
            face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
        }
        if (face.point2.y == face.point3.y && face.point2.y < face.point1.y) {
            face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point2_shadowed);
        }

        // second triangle
        if (face.point1.y == face.point3.y && face.point1.y > face.point2.y) {
            face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
        }
        if (face.point1.y == face.point2.y && face.point1.y > face.point3.y) {
            face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
        }
        if (face.point2.y == face.point3.y && face.point2.y > face.point1.y) {
            face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
        }
    }

    // * with blocks around
    // * bottom blocks
    // front back
    if (face.normal == 'f') {
        if (blocks_around_shadowable[1][0][2]) {
            // first triangle
            if (face.point1.y == face.point3.y && face.point1.y < face.point2.y) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y < face.point3.y) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y < face.point1.y) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.y == face.point3.y && face.point1.y > face.point2.y) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y > face.point3.y) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y > face.point1.y) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }
    }
    if (face.normal == 'b') {
        if (blocks_around_shadowable[1][0][0]) {
            // first triangle
            if (face.point1.y == face.point3.y && face.point1.y < face.point2.y) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y < face.point3.y) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y < face.point1.y) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.y == face.point3.y && face.point1.y > face.point2.y) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y > face.point3.y) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y > face.point1.y) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }   
    }
    // right left
    if (face.normal == 'r') {
        if (blocks_around_shadowable[2][0][1]) {
            // first triangle
            if (face.point1.y == face.point3.y && face.point1.y < face.point2.y) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y < face.point3.y) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y < face.point1.y) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.y == face.point3.y && face.point1.y > face.point2.y) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y > face.point3.y) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y > face.point1.y) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }
    }
    if (face.normal == 'l') {
        if (blocks_around_shadowable[0][0][1]) {
            // first triangle
            if (face.point1.y == face.point3.y && face.point1.y < face.point2.y) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y < face.point3.y) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y < face.point1.y) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.y == face.point3.y && face.point1.y > face.point2.y) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.y == face.point2.y && face.point1.y > face.point3.y) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.y == face.point3.y && face.point2.y > face.point1.y) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }   
    }

    // * top blocks
    // front back
    if (face.normal == 't') {
        if (blocks_around_shadowable[1][1][0]) {
            // first triangle
            if (face.point1.z == face.point3.z && face.point1.z < face.point2.z) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.z == face.point2.z && face.point1.z < face.point3.z) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.z == face.point3.z && face.point2.z < face.point1.z) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.z == face.point3.z && face.point1.z > face.point2.z) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.z == face.point2.z && face.point1.z > face.point3.z) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.z == face.point3.z && face.point2.z > face.point1.z) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }
    }
    if (face.normal == 't') {
        if (blocks_around_shadowable[1][1][2]) {
            // first triangle
            if (face.point1.z == face.point3.z && face.point1.z > face.point2.z) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.z == face.point2.z && face.point1.z > face.point3.z) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.z == face.point3.z && face.point2.z > face.point1.z) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.z == face.point3.z && face.point1.z < face.point2.z) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.z == face.point2.z && face.point1.z < face.point3.z) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.z == face.point3.z && face.point2.z < face.point1.z) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }
    }

    // right left
    if (face.normal == 't') {
        if (blocks_around_shadowable[0][1][1]) {
            // first triangle
            if (face.point1.x == face.point3.x && face.point1.x < face.point2.x) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.x == face.point2.x && face.point1.x < face.point3.x) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.x == face.point3.x && face.point2.x < face.point1.x) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.x == face.point3.x && face.point1.x > face.point2.x) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.x == face.point2.x && face.point1.x > face.point3.x) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.x == face.point3.x && face.point2.x > face.point1.x) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }
    }
    if (face.normal == 't') {
        if (blocks_around_shadowable[2][1][1]) {
            // first triangle
            if (face.point1.x == face.point3.x && face.point1.x > face.point2.x) {
                face_points_shadowing(&face.point1_color, &face.point3_color, face_point1_shadowed, face_point3_shadowed);
            }
            if (face.point1.x == face.point2.x && face.point1.x > face.point3.x) {
                face_points_shadowing(&face.point1_color, &face.point2_color, face_point1_shadowed, face_point2_shadowed);
            }
            if (face.point2.x == face.point3.x && face.point2.x > face.point1.x) {
                face_points_shadowing(&face.point2_color, &face.point3_color, face_point2_shadowed, face_point3_shadowed);
            }

            // second triangle
            if (face.point1.x == face.point3.x && face.point1.x < face.point2.x) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            if (face.point1.x == face.point2.x && face.point1.x < face.point3.x) {
                face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
            }
            if (face.point2.x == face.point3.x && face.point2.x < face.point1.x) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
        }
    }

    // * top blocks on corners
    // front 
    if (face.normal == 't') {
        // right
        if (blocks_around_shadowable[0][1][0]) {
            // one triangle
            if (face.point1.z < face.point2.z && face.point1.x < face.point3.x && face.point1.z == face.point3.z) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
            else if (face.point2.z < face.point3.z && face.point2.x < face.point1.x && face.point2.z == face.point1.z && face.point2.x == face.point3.x) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }

            // for two triangles
            else {
                // first
                if (face.point3.z < face.point1.z && face.point3.x < face.point2.x && face.point3.x == face.point1.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point3.z < face.point1.z && face.point3.x < face.point2.x && face.point1.x == face.point2.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }

                // first
                if (face.point1.z < face.point2.z && face.point1.x < face.point3.x && face.point1.x == face.point2.x) {
                    face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point2.z < face.point3.z && face.point2.x < face.point1.x && face.point1.x == face.point3.x) {
                    face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
                }
            }   
        }

        // left
        if (blocks_around_shadowable[2][1][0]) {
            // one triangle
            if (face.point1.z < face.point3.z && face.point1.x > face.point2.x && face.point1.z == face.point2.z && face.point1.x == face.point3.x) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
            else if (face.point2.z < face.point1.z && face.point2.x > face.point3.x && face.point2.z == face.point3.z && face.point2.x == face.point1.x) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }

            // for two triangles
            else {
                // first
                if (face.point3.z < face.point2.z && face.point3.x > face.point1.x && face.point3.x == face.point2.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point3.z < face.point2.z && face.point3.x > face.point1.x && face.point1.x == face.point2.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }

                // first
                if (face.point2.z < face.point1.z && face.point2.x > face.point3.x && face.point1.x == face.point2.x) {
                    face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point1.z < face.point3.z && face.point1.x > face.point2.x && face.point2.x == face.point3.x) {
                    face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
                }
            }   
        }
    }

    // back 
    if (face.normal == 't') {
        // right
        if (blocks_around_shadowable[0][1][2]) {
            // one triangle
            if (face.point1.z > face.point3.z && face.point1.x < face.point2.x && face.point1.z == face.point2.z && face.point1.x == face.point3.x) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }
            else if (face.point2.z > face.point1.z && face.point2.x < face.point3.x && face.point2.z == face.point3.z && face.point2.x == face.point1.x) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }

            // for two triangles
            else {
                // first
                if (face.point1.z > face.point3.z && face.point1.x < face.point2.x && face.point2.x == face.point3.x) {
                    face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point2.z > face.point1.z && face.point2.x < face.point3.x && face.point1.x == face.point2.x) {
                    face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
                }

                // first
                if (face.point3.z > face.point2.z && face.point3.x < face.point1.x && face.point2.x == face.point1.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point3.z > face.point2.z && face.point3.x < face.point1.x && face.point3.x == face.point2.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }
            }   
        }

        // left
        if (blocks_around_shadowable[2][1][2]) {
            // one triangle
            if (face.point2.z > face.point3.z && face.point2.x > face.point1.x && face.point2.z == face.point1.z && face.point2.x == face.point3.x) {
                face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
            }
            else if (face.point1.z > face.point2.z && face.point1.x > face.point3.x && face.point1.z == face.point3.z && face.point1.x == face.point2.x) {
                face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
            }

            // for two triangles
            else {
                // first
                if (face.point2.z > face.point3.z && face.point2.x > face.point1.x && face.point1.x == face.point3.x) {
                    face_points_shadowing(&face.point2_color, nullptr, face_point2_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point1.z > face.point2.z && face.point1.x > face.point3.x && face.point2.x == face.point1.x) {
                    face_points_shadowing(&face.point1_color, nullptr, face_point1_shadowed, face_point2_shadowed);
                }

                // first
                if (face.point3.z > face.point1.z && face.point3.x > face.point2.x && face.point2.x == face.point1.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }
                // second
                if (face.point3.z > face.point1.z && face.point3.x > face.point2.x && face.point3.x == face.point1.x) {
                    face_points_shadowing(&face.point3_color, nullptr, face_point3_shadowed, face_point2_shadowed);
                }
            }   
        }
    }
}

void WorldLoader::update_face_pos(RawFace3d& face, Block& block, Chunk& chunk) {
    face.point1.x += block.x + chunk.x;
    face.point2.x += block.x + chunk.x;
    face.point3.x += block.x + chunk.x;

    face.point1.y += block.y + chunk.y;
    face.point2.y += block.y + chunk.y;
    face.point3.y += block.y + chunk.y;

    face.point1.z += block.z + chunk.z;
    face.point2.z += block.z + chunk.z;
    face.point3.z += block.z + chunk.z;
}



void WorldLoader::clear_chunk_faces(WorldRenderer& world_renderer, int chunk_ind) {
    world_renderer.raw_faces_3d.erase(
        remove_if(world_renderer.raw_faces_3d.begin(), world_renderer.raw_faces_3d.end(), 
            [chunk_ind](const RawFace3d& face) { 
                return face.chunk_ind == chunk_ind; 
            }
        ),
        world_renderer.raw_faces_3d.end()
    );
}

void WorldLoader::remove_loaded_chunk(Chunk& chunk) {
    for (size_t ci = 0; ci < loaded_chunks.size(); ci++)
    {
        Chunk& check_chunk = *loaded_chunks[ci];
        if (chunk.x == check_chunk.x && chunk.y == check_chunk.y && chunk.z == check_chunk.z) {
            loaded_chunks.erase(loaded_chunks.begin() + ci);
            return;
        }
    }
    
}

void WorldLoader::check_chunks_to_load(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], Player& player) {
    // check chunks only if player world pos changes or force
    int player_world_x = ((player.x + BLOCK_SIZE / 2) / (CHUNK_SIZE_X * BLOCK_SIZE));
    int player_world_y = ((player.y + BLOCK_SIZE / 2) / (CHUNK_SIZE_Y * BLOCK_SIZE));
    int player_world_z = ((player.z + BLOCK_SIZE / 2) / (CHUNK_SIZE_Z * BLOCK_SIZE));
    if (!force_chunks_load) {
        if (last_player_world_x == player_world_x && last_player_world_y == player_world_y && last_player_world_z == player_world_z) {
            return;
        }
    }

    force_chunks_load = false;
    // set last world pos
    last_player_world_x = player_world_x;
    last_player_world_y = player_world_y;
    last_player_world_z = player_world_z;
    
    // loop all chunks
    for (size_t ci = 0; ci < CHUNKS_COUNT; ci++)
    {
        Chunk& chunk = chunks[ci];
        if (chunk.is_air) {
            continue;
        }

        // load if chunk not loaded
        if (!chunk.loaded) {
            // check dist
            int dist = sqrt(
                pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
            );
            if (dist < WORLD_CHUNKS_LOAD_DIST) {
                // add to chunks load queue
                ChunkToLoad chunk_to_load = {&chunk, int(ci), false, true, dist};
                chunks_to_load_queue.push_back(chunk_to_load);
                chunk.loaded = true;    
            }

        }
        // check dist to clear faces
        else {
            int dist = sqrt(
                pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
            );
            if (dist > WORLD_CHUNKS_LOAD_DIST) {
                // clear faces
                clear_chunk_faces(world_renderer, ci);
                chunk.loaded = false;    

                // remove from loaded chunks
                remove_loaded_chunk(chunk);
            }
        }
    }
}

int chunks_to_load_queue_sorter(ChunkToLoad& chunk1, ChunkToLoad& chunk2) {
    return chunk1.dist < chunk2.dist;
}

void WorldLoader::sort_chunks_to_load_queue() {
    sort(chunks_to_load_queue.begin(), chunks_to_load_queue.end(), chunks_to_load_queue_sorter);
}
void WorldLoader::update_chunks_to_load_queue(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], Player& player, float dt) {
    int chunks_to_load_size = chunks_to_load_queue.size();

    // load current chunk
    if (current_chunk_to_load_ind < chunks_to_load_size) {
        // get chunk 
        ChunkToLoad& chunk_to_load = chunks_to_load_queue[current_chunk_to_load_ind];
        // check dist to player
        if (chunk_to_load.dist < WORLD_CHUNKS_LOAD_DIST) {
            // clear faces
            if (chunk_to_load.remove_faces) { 
                clear_chunk_faces(world_renderer, chunk_to_load.chunk_ind);
            }  
            // full load 
            full_chunk_load(world_renderer, chunks, chunk_to_load.chunk_ind, *chunk_to_load.chunk);
            // set loaded true to current loaded chunk
            chunk_to_load.chunk->loaded = true;
            // add to loaded chunks
            if (chunk_to_load.add_to_loaded_chunks) {
                loaded_chunks.push_back(chunk_to_load.chunk);
            }
        }
        current_chunk_to_load_ind++;
        
    // clear load queue
    } else {
        chunks_to_load_queue.clear();
        current_chunk_to_load_ind = 0;
    }
}

void WorldLoader::reload_all_chunks(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT]) {
    for (size_t ci = 0; ci < CHUNKS_COUNT; ci++)
    {
        Chunk& chunk = chunks[ci];
        // set loaded = false and clear faces
        chunk.loaded = false;
        
        clear_chunk_faces(world_renderer, ci);        
    }
    force_chunks_load = true;

    // clear load queue
    chunks_to_load_queue.clear();
    current_chunk_to_load_ind = 0;

    loaded_chunks.clear();
}


void WorldLoader::update_loaded_chunks(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], float dt) {
    // changle cooldown
    if (rand_update_cooldown >= 0) {
        rand_update_cooldown -= 0.1 * dt;
        rand_update_cooldown = max(0.0f, rand_update_cooldown);
    }
    
    if (rand_update_cooldown == 0.0f) {
        int loaded_chunks_size = loaded_chunks.size();
        if (loaded_chunks_size <= 0) {
            return;
        }

        // set rand update cooldonw
        rand_update_cooldown = 5.0f / (float(loaded_chunks_size) / 10);
        rand_update_cooldown = min(10.0f, rand_update_cooldown);

        // get chunk
        int rand_chunk_ind = randint(0, loaded_chunks_size - 1);
        // keep getting chunk ind until it's not last ind
        if (loaded_chunks_size > 2) {
            while (rand_chunk_ind == last_updated_chunk_ind1 || rand_chunk_ind == last_updated_chunk_ind2) {
                rand_chunk_ind = randint(0, loaded_chunks_size - 1);
            }
        }
        
        last_updated_chunk_ind2 = last_updated_chunk_ind1;
        last_updated_chunk_ind1 = rand_chunk_ind;

        Chunk* chunk = loaded_chunks[rand_chunk_ind];

        bool chunk_has_updates = false;

        // loop all blocks to update
        for (size_t x = 0; x < CHUNK_SIZE_X; x++)
        for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
        for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
        {
            Block& block = chunk->blocks[x][y][z];
            if (block.id == 0 || block.update_time == 0) {
                continue;
            }
            // * dirt
            if (block.id == 5) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // set as grass
                    block.id = randint(1, 4);
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 

                block.update_time = (uint8_t)update_time;                    
            }

            // * grass
            else if (block.id == 1 || block.id == 2 || block.id == 3 || block.id == 4) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // set as dirt
                    block.id = 5;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 

                block.update_time = (uint8_t)update_time;                    
            }

            // * dry bed
            else if (block.id == 45) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // set as wet
                    block.id = 46;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 

                block.update_time = (uint8_t)update_time;                    
            }

            // * wet bed
            else if (block.id == 46) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // set as dry
                    block.id = 45;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 

                block.update_time = (uint8_t)update_time;                    
            }

            // * plants
            // wheat levels
            else if (block.id == 47) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // increase level
                    block.id++;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 
                block.update_time = (uint8_t)update_time;  
            }
            else if (block.id == 48) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // increase level
                    block.id++;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 
                block.update_time = (uint8_t)update_time;  
            }
            else if (block.id == 49) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // increase level
                    block.id++;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                } 
                block.update_time = (uint8_t)update_time;  
            }
            // * water
            else if (block.id == 6) {
                float update_time = (float)block.update_time;
                update_time -= 1;

                uint8_t bottom_block_id_ = 0;
                if (update_time <= 0) {
                    // * add water on bottom
                    if (y != 0) {
                        Block& bottom_block = chunk->blocks[x][y-1][z];
                        bottom_block_id_ = bottom_block.id;
                        if (bottom_block.id == 0) {
                            // set pos
                            bottom_block.x = block.x;
                            bottom_block.y = block.y - BLOCK_SIZE;
                            bottom_block.z = block.z;
                            // set id and update time
                            bottom_block.id = 6;
                            bottom_block.update_time = 1;
                            
                            chunk_has_updates = true;
                        }
                    }
                    // bottom chunk
                    else {
                        int chunk_ind = get_chunk_ind_by_pos(
                            chunk->x / (BLOCK_SIZE * CHUNK_SIZE_X), 
                            chunk->y / (BLOCK_SIZE * CHUNK_SIZE_Y) - 1, 
                            chunk->z / (BLOCK_SIZE * CHUNK_SIZE_Z)
                        );
                        if (chunk_ind != -1) {
                            Chunk& bottom_chunk = chunks[chunk_ind];
                            Block& bottom_block = bottom_chunk.blocks[x][CHUNK_SIZE_Y-1][z];
                            bottom_block_id_ = bottom_block.id;
                            if (bottom_block.id == 0) {
                                // set pos
                                bottom_block.x = block.x;
                                bottom_block.y = (CHUNK_SIZE_Y-1) * BLOCK_SIZE;
                                bottom_block.z = block.z;
                                // set id and update time
                                bottom_block.id = 6;
                                
                                chunk_has_updates = true;

                                // add to load queue
                                ChunkToLoad chunk_to_load = {&bottom_chunk, chunk_ind, true, false, 0};
                                chunks_to_load_queue.push_back(chunk_to_load);
                            }
                        }
                    }
                    // only if solid or other block, not water
                    if (bottom_block_id_ != 0 && bottom_block_id_ != 6) {
                        Block* block_ = nullptr;
                        // * add on front
                        if (z != CHUNK_SIZE_Z - 1) {
                            block_ = &chunk->blocks[x][y][z+1];
                            if (block_->id == 0) {
                                // set pos
                                block_->x = block.x;
                                block_->y = block.y;
                                block_->z = block.z + BLOCK_SIZE;
                                // set id and update time
                                block_->id = 6;
                                chunk_has_updates = true;
                            }
                        }
                        // * add on back
                        if (z != 0) {
                            block_ = &chunk->blocks[x][y][z-1];
                            if (block_->id == 0) {
                                // set pos
                                block_->x = block.x;
                                block_->y = block.y;
                                block_->z = block.z - BLOCK_SIZE;
                                // set id and update time
                                block_->id = 6;
                                chunk_has_updates = true;
                            }
                        }
    
                        // * add on right
                        if (x != CHUNK_SIZE_X - 1) {
                            block_ = &chunk->blocks[x+1][y][z];
                            if (block_->id == 0) {
                                // set pos
                                block_->x = block.x + BLOCK_SIZE;
                                block_->y = block.y;
                                block_->z = block.z;
                                // set id and update time
                                block_->id = 6;
                                
                                chunk_has_updates = true;
                            }
                        }
                        // * add on left
                        if (x != 0) {
                            block_ = &chunk->blocks[x-1][y][z];
                            if (block_->id == 0) {
                                // set pos
                                block_->x = block.x - BLOCK_SIZE;
                                block_->y = block.y;
                                block_->z = block.z;
                                // set id and update time
                                block_->id = 6;
                                
                                chunk_has_updates = true;
                            }
                        }
                    }
                    update_time = 0.0f;
                } 

                block.update_time = (uint8_t)update_time;    
            }
            // fire wood
            else if (block.id == 93) {
                float update_time = (float)block.update_time;
                update_time -= 1;
                if (update_time <= 0) {
                    // set as burnt wood
                    block.id = 95;
                    chunk_has_updates = true;
                    update_time = 0.0f;
                    
                    // delete from light sources
                    delete_block_from_light_sources(block, *chunk);
                } 

                block.update_time = (uint8_t)update_time;                    
            }
        }
        
        // add to load queue
        if (chunk_has_updates) {
            int chunk_world_ind = get_chunk_ind_by_pos(chunk->x / (CHUNK_SIZE_X * BLOCK_SIZE), chunk->y / (CHUNK_SIZE_Y * BLOCK_SIZE), chunk->z / (CHUNK_SIZE_Z * BLOCK_SIZE));
            if (chunk_world_ind != -1) {
                ChunkToLoad chunk_to_load = {chunk, chunk_world_ind, true, false, 0};
                chunks_to_load_queue.push_back(chunk_to_load);
            }
        }
    }
}


bool WorldLoader::check_chunk_added_to_load_queue(Chunk& chunk) {
    for (size_t ci = 0; ci < chunks_to_load_queue.size(); ci++)
    {
        ChunkToLoad &added_chunk = chunks_to_load_queue[ci];
        if (chunk.x == added_chunk.chunk->x && chunk.y == added_chunk.chunk->y && chunk.z == added_chunk.chunk->z) {
            return true;
        }
    }
    return false;
}

// player interctions
bool item_can_increase_breaking_speed(InventorySlot& slot, FullBlockData& block_data) {
    // block_data.breaking_speed_increase_items_ids.reserve(100);
    for (size_t i = 0; i < block_data.breaking_speed_increase_items_ids.size(); i++)
    {
        uint8_t& item_id = block_data.breaking_speed_increase_items_ids[i];
        if (item_id == slot.item_id) {
            return true;
        }
    }
    return false;
}


void WorldLoader::update_near_chunks(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int block_x, int block_y, int block_z, Player& player, bool only_on_borders) {
    // get chunk pos in world
    int world_x = chunk.x / (CHUNK_SIZE_X * BLOCK_SIZE);
    int world_y = chunk.y / (CHUNK_SIZE_Y * BLOCK_SIZE);
    int world_z = chunk.z / (CHUNK_SIZE_Z * BLOCK_SIZE);

    // update near chunks if block pos on border
    if (only_on_borders) {
        // x
        if (block_x == 0) {
            // get chunk
            int chunk_ind = get_chunk_ind_by_pos(world_x-1, world_y, world_z);
            if (chunk_ind != -1) {
                Chunk& near_chunk = chunks[chunk_ind];
                // check dist to player
                int dist = sqrt(
                    pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                    pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                    pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                );
                if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                    // add to load queue
                    ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block_x == CHUNK_SIZE_X-1) {
            // get chunk
            int chunk_ind = get_chunk_ind_by_pos(world_x+1, world_y, world_z);
            if (chunk_ind != -1) {
                Chunk& near_chunk = chunks[chunk_ind];
                // check dist to player
                int dist = sqrt(
                    pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                    pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                    pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                );
                if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                    // add to load queue
                    ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }

        // y
        if (block_y == 0) {
            // get chunk
            int chunk_ind = get_chunk_ind_by_pos(world_x, world_y-1, world_z);
            if (chunk_ind != -1) {
                Chunk& near_chunk = chunks[chunk_ind];
                // check dist to player
                int dist = sqrt(
                    pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                    pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                    pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                );
                if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                    // add to load queue
                    ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block_y == CHUNK_SIZE_Y-1) {
            // get chunk
            int chunk_ind = get_chunk_ind_by_pos(world_x, world_y+1, world_z);
            if (chunk_ind != -1) {

                Chunk& near_chunk = chunks[chunk_ind];
                // check dist to player
                int dist = sqrt(
                    pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                    pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                    pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                );
                if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                    // add to load queue
                    ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }

        // z
        if (block_z == 0) {
            // get chunk
            int chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z-1);
            if (chunk_ind != -1) {
                Chunk& near_chunk = chunks[chunk_ind];
                // check dist to player
                int dist = sqrt(
                    pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                    pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                    pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                );
                if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                    // add to load queue
                    ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
        if (block_z == CHUNK_SIZE_Z-1) {
            // get chunk
            int chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z+1);
            if (chunk_ind != -1) {
                Chunk& near_chunk = chunks[chunk_ind];
                // check dist to player
                int dist = sqrt(
                    pow((player.x - (chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                    pow((player.y - (chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                    pow((player.z - (chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                );
                if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                    // add to load queue
                    ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                    chunks_to_load_queue.push_back(chunk_to_load);
                }
            }
        }
    } 
    // update around 
    else {
        for (int wx = -1; wx <= 1; wx++)
        for (int wy = -1; wy <= 1; wy++)
        for (int wz = -1; wz <= 1; wz++) {
            if (wx != 0 || wy != 0 || wz != 0) {
                // get chunk
                int chunk_ind = get_chunk_ind_by_pos(world_x+wx, world_y+wy, world_z+wz);
                if (chunk_ind != -1) {
                    Chunk& near_chunk = chunks[chunk_ind];
                    // check dist to player
                    int dist = sqrt(
                        pow((player.x - (near_chunk.x + CHUNK_SIZE_X / 2 * BLOCK_SIZE)), 2) + 
                        pow((player.y - (near_chunk.y + CHUNK_SIZE_Y / 2 * BLOCK_SIZE)), 2) +
                        pow((player.z - (near_chunk.z + CHUNK_SIZE_Z / 2 * BLOCK_SIZE)), 2)
                    );
                    if (dist < WORLD_CHUNKS_LOAD_DIST && !check_chunk_added_to_load_queue(near_chunk)) {
                        // add to load queue
                        ChunkToLoad chunk_to_load = {&near_chunk, chunk_ind, true, false, dist};
                        chunks_to_load_queue.push_back(chunk_to_load);
                    }
                }
            }
        }
    }
}
void WorldLoader::delete_block_from_light_sources(Block& block, Chunk& chunk) {
    for (size_t lbi = 0; lbi < chunk.light_sources_blocks.size(); lbi++)
    {
        // find block
        Block& check_block = chunk.light_sources_blocks[lbi];
        // pop block and break
        if (block.x == check_block.x && block.y == check_block.y && block.z == check_block.z) {
            chunk.light_sources_blocks.erase(chunk.light_sources_blocks.begin() + lbi);
            return;
        }
    }
}

void WorldLoader::update_block_break(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], vector<ItemDrop>& all_items_drops, map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, Player& player, PlayerInventory& player_inv, float dt) {
    if (player.on_block_break) {
        // get selected face data
        if (world_renderer.selected_face) {
            // get world data 
            int chunk_ind = world_renderer.selected_face->chunk_ind;

            int block_x = world_renderer.selected_face->block_x;
            int block_y = world_renderer.selected_face->block_y;
            int block_z = world_renderer.selected_face->block_z;

            // set progress 
            if (player.block_breaking_progress == 0.0f) {
                Chunk& chunk = chunks[chunk_ind];
                Block& block = chunk.blocks[block_x][block_y][block_z];
                FullBlockData& block_full_data = all_blocks_full_data[block.id];
                current_breaking_block_data = &block_full_data;

                player.block_breaking_progress = block_full_data.strength;
                player.max_block_breaking_progress = block_full_data.strength;

                // world data set in world renderer
                world_renderer.current_breaking_block_chunk_ind = chunk_ind;

                world_renderer.current_breaking_block_x = block_x;
                world_renderer.current_breaking_block_y = block_y;
                world_renderer.current_breaking_block_z = block_z;
            }

            // check selected face change and set progress
            if (
                (world_renderer.selected_face->block_x != last_block_breaking_x) ||
                (world_renderer.selected_face->block_y != last_block_breaking_y) ||
                (world_renderer.selected_face->block_z != last_block_breaking_z)
            ) {
                Chunk& chunk = chunks[chunk_ind];
                Block& block = chunk.blocks[block_x][block_y][block_z];
                FullBlockData& block_full_data = all_blocks_full_data[block.id];
                current_breaking_block_data = &block_full_data;


                player.block_breaking_progress = block_full_data.strength;
                player.max_block_breaking_progress = block_full_data.strength;

                last_block_breaking_x = world_renderer.selected_face->block_x;
                last_block_breaking_y = world_renderer.selected_face->block_y;
                last_block_breaking_z = world_renderer.selected_face->block_z;

                // world data set in world renderer
                world_renderer.current_breaking_block_chunk_ind = chunk_ind;

                world_renderer.current_breaking_block_x = block_x;
                world_renderer.current_breaking_block_y = block_y;
                world_renderer.current_breaking_block_z = block_z;
            }

            // * reduce progress
            // set speed
            float speed = 1;
            if (player_inv.current_slot_data && player_inv.current_slot_data->breaking_increase_speed != 1) {
                bool can_increase_speed = item_can_increase_breaking_speed(
                    *player_inv.current_slot, *current_breaking_block_data
                );
                // increase speed
                if (can_increase_speed) {
                    speed *= player_inv.current_slot_data->breaking_increase_speed;
                }
            }
            // reduce
            player.block_breaking_progress -= speed * dt;

            if (player.block_breaking_progress > 0.0f && !player.fast_interactions) {
                return;
            }
            player.block_breaking_progress = 0;
            
            // get block data
            Chunk& chunk = chunks[chunk_ind];
            Block& block = chunk.blocks[block_x][block_y][block_z];
            FullBlockData& block_full_data = all_blocks_full_data[block.id];
            
            // remove expanded block (door)
            // bottom
            if (block.id == 58 || block.id == 59 || block.id == 60 || block.id == 61) {
                if (block_y-1 != -1) {
                    chunk.blocks[block_x][block_y-1][block_z].id = 0; // set air
                }
                // block in bottom chunk
                else {
                    int botton_chunk_ind = get_chunk_ind_by_pos(chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X), chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y)-1, chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z));
                    if (botton_chunk_ind != -1) {
                        chunks[botton_chunk_ind].blocks[block_x][CHUNK_SIZE_Y-1][block_z].id = 0; // set air
                    }
                }
            }

            // top
            if (block.id == 62 || block.id == 63 || block.id == 64 || block.id == 65) {
                if (block_y+1 != CHUNK_SIZE_Y) {
                    chunk.blocks[block_x][block_y+1][block_z].id = 0; // set air
                }
                // block in top chunk
                else {
                    int top_chunk_ind = get_chunk_ind_by_pos(chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X), chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y)+1, chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z));
                    if (top_chunk_ind != -1) {
                        chunks[top_chunk_ind].blocks[block_x][0][block_z].id = 0; // set air
                    }
                }
            }
            
            block.id = 0; // air

            // add drop items
            bool on_items_drop = false;
            if (block_full_data.drop_by_items_ids[0] == 0) { // any item or empty slot
                on_items_drop = true;
            }
            // loop all to find same as current item
            else {
                if (player_inv.current_slot_data) {
                    for (size_t i = 0; i < block_full_data.drop_by_items_ids.size(); i++)
                    {
                        uint8_t item_id = block_full_data.drop_by_items_ids[i];
                        if (item_id == player_inv.current_slot->item_id) {
                            on_items_drop = true;
                            break;
                        }
                    }
                }
            }


            if (on_items_drop) {
                for (size_t di = 0; di < block_full_data.drop_items.size(); di++)
                {
                    FullBlockDropItemData& drop_item = block_full_data.drop_items[di];
    
                    ItemDrop new_item_drop;
                    int items_count = randint(drop_item.rand_count_range[0], drop_item.rand_count_range[1]);
                    if (items_count > 0) {
                        new_item_drop.add_item = {drop_item.id, (uint8_t)items_count, 0};
                        new_item_drop.x = block.x + chunk.x;
                        new_item_drop.y = block.y + chunk.y;
                        new_item_drop.z = block.z + chunk.z;
        
                        // set just dropped
                        new_item_drop.just_dropded_cooldown = 20;
                        new_item_drop.pick_up_able = false;
        
                        // set inertion
                        float inertion = 4;
                        new_item_drop.inert_x = inertion * ((float)randint(-10, 10) / 10.0f);
                        new_item_drop.inert_z = inertion * ((float)randint(-10, 10) / 10.0f);
        
                        new_item_drop.full_model_id = item_id_to_entity_id[drop_item.id];
                        all_items_drops.push_back(new_item_drop);
                    }
                }
            }

            // remove inventory id from storages and drop items
            if (block.inventory_id != 0) {
                StorageBoxInv& block_storage = storages[block.inventory_id];
                // loop all items to drop
                for (size_t si = 0; si < 45; si++)
                {
                    InventorySlot& slot = block_storage.slots[si];
                    // create new drop
                    if (slot.item_id != 0) {
                        ItemDrop new_item_drop;
                        new_item_drop.add_item = slot;
                        new_item_drop.x = block.x + chunk.x;
                        new_item_drop.y = block.y + chunk.y;
                        new_item_drop.z = block.z + chunk.z;

                        // set just dropped
                        new_item_drop.just_dropded_cooldown = 20;
                        new_item_drop.pick_up_able = false;

                        // set inertion
                        float inertion = 4;
                        new_item_drop.inert_x = inertion * ((float)randint(-10, 10) / 10.0f);
                        new_item_drop.inert_z = inertion * ((float)randint(-10, 10) / 10.0f);

                        new_item_drop.full_model_id = item_id_to_entity_id[slot.item_id];
                        all_items_drops.push_back(new_item_drop);
                    }
                }
                
                storages.erase(block.inventory_id);
                // reduce last id
                if (block.inventory_id >= last_storage_id - 1) {
                    last_storage_id--;
                }

                block.inventory_id = 0;
            }

            // reduce tool durability and break
            if (player_inv.current_slot_data && player_inv.current_slot_data->type == "tool") {
                int item_durability = int(player_inv.current_slot->durability);
        
                item_durability -= randint(1, 2);
                if (item_durability <= 0) {
                    player_inv.clear_current_slot();
                } else {
                    player_inv.current_slot->durability = uint8_t(item_durability);
                }
            }

            // set chunk air
            chunk.is_air = check_chunk_is_air(chunk);

            bool update_chunks_only_on_borders = true;
            if (block.sun_light == 1 || ((int)block_full_data.light.r > 0 || (int)block_full_data.light.g > 0 || (int)block_full_data.light.b > 0)) {
                update_chunks_only_on_borders = false;
            }

            // clear light
            block.sun_light = 0.0f;
            block.light_level = 0;

            // clear in light sources
            delete_block_from_light_sources(block, chunk);
            
            // clear chunk faces
            clear_chunk_faces(world_renderer, chunk_ind);
            // load chunks faces
            full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

            // update near chunks, add to load queue
            update_near_chunks(world_renderer, chunks, chunk, block_x, block_y, block_z, player, update_chunks_only_on_borders);
        }
    }
}

bool WorldLoader::check_chunk_is_air(Chunk& chunk) {
    // loop all blocks to check
    for (size_t x = 0; x < CHUNK_SIZE_X; x++)
    for (size_t y = 0; y < CHUNK_SIZE_Y; y++)
    for (size_t z = 0; z < CHUNK_SIZE_Z; z++)
    {
        Block& block = chunk.blocks[x][y][z];
        if (block.id != 0) {
            return false;
        }
    }
    return true;
}

Chunk* WorldLoader::add_block(WorldRenderer& world_renderer, uint8_t block_id, FullBlockData& block_data, Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, int chunk_ind, int& block_x, int& block_y, int& block_z, Player& player) {
    Chunk* chunk = &chunks[chunk_ind];

    int world_x = chunk->x / (CHUNK_SIZE_X * BLOCK_SIZE);
    int world_y = chunk->y / (CHUNK_SIZE_Y * BLOCK_SIZE);
    int world_z = chunk->z / (CHUNK_SIZE_Z * BLOCK_SIZE);
    
    // block pos in neighbour chunk
    // front
    if (block_z == CHUNK_SIZE_Z) {
        // set block pos inside chunk
        block_z = 0;
        world_z += 1;
        // get chunk ind and set chunk
        int n_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (n_chunk_ind != -1) {
            chunk = &chunks[n_chunk_ind];
        } else {
            return nullptr;
        }
    }
    // back
    if (block_z == -1) {
        // set block pos inside chunk
        block_z = CHUNK_SIZE_Z - 1;
        world_z -= 1;
        // get chunk ind and set chunk
        int n_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (n_chunk_ind != -1) {
            chunk = &chunks[n_chunk_ind];
        } else {
            return nullptr;
        }
    }
    // right
    if (block_x == CHUNK_SIZE_X) {
        // set block pos inside chunk
        block_x = 0;
        world_x += 1;
        // get chunk ind and set chunk
        int n_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (n_chunk_ind != -1) {
            chunk = &chunks[n_chunk_ind];
        } else {
            return nullptr;
        }
    }
    // left
    if (block_x == -1) {
        // set block pos inside chunk
        block_x = CHUNK_SIZE_X - 1;
        world_x -= 1;
        // get chunk ind and set chunk
        int n_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (n_chunk_ind != -1) {
            chunk = &chunks[n_chunk_ind];
        } else {
            return nullptr;
        }
    }
    // top
    if (block_y == CHUNK_SIZE_Y) {
        // set block pos inside chunk
        block_y = 0;
        world_y += 1;
        // get chunk ind and set chunk
        int n_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (n_chunk_ind != -1) {
            chunk = &chunks[n_chunk_ind];
        } else {
            return nullptr;
        }
    }
    // bottom
    if (block_y == -1) {
        // set block pos inside chunk
        block_y = CHUNK_SIZE_Y - 1;
        world_y -= 1;
        // bottom_block_y = CHUNK_SIZE_Y - 2;
        // get chunk ind and set chunk
        int n_chunk_ind = get_chunk_ind_by_pos(world_x, world_y, world_z);
        if (n_chunk_ind != -1) {
            chunk = &chunks[n_chunk_ind];
        } else {
            return nullptr;
        }
    }

    // * get bottom block
    uint8_t bottom_block_id = 0;
    
    int bottom_block_y = block_y - 1;

    // block in another chunk
    if (bottom_block_y == -1) {
        // set block pos inside chunk
        bottom_block_y = CHUNK_SIZE_Y - 1;
        // get chunk ind and set chunk
        int bottom_chunk_ind = get_chunk_ind_by_pos(world_x, world_y - 1, world_z);
        if (bottom_chunk_ind != -1) {
            Chunk& bottom_chunk = chunks[bottom_chunk_ind];
            Block& bottom_block = bottom_chunk.blocks[block_x][bottom_block_y][block_z];
            bottom_block_id = bottom_block.id;
        } 
    }
    // in current chunk
    else {
        Block& bottom_block = chunk->blocks[block_x][bottom_block_y][block_z];
        bottom_block_id = bottom_block.id;
    }
    // check if block can be placed on bottom block
    bool can_be_placed = false;
    int place_on_blocks_ids_size = block_data.place_on_blocks_ids.size();
    // can be placed on all
    if (place_on_blocks_ids_size == 0) {
        can_be_placed = true;
    } 
    // on only specific
    else {
        for (size_t pbi = 0; pbi < place_on_blocks_ids_size; pbi++)
        {
            uint8_t id = block_data.place_on_blocks_ids[pbi];
            if (id == bottom_block_id) {
                can_be_placed = true;
                break;
            }
        }
    }

    if (!can_be_placed) {
        return nullptr;
    }
    
    // check if block is not on player pos
    int x_right_in_chunk = int(int(player.x + player.collider_size_x / 2 + BLOCK_SIZE / 2) / BLOCK_SIZE);
    int x_left_in_chunk = int(int(player.x - player.collider_size_x / 2 + BLOCK_SIZE / 2) / BLOCK_SIZE);
    
    int y_top_in_chunk = int(int(player.y + player.collider_size_top + BLOCK_SIZE / 2) / BLOCK_SIZE);
    int y_middle_in_chunk = int(int(player.y - player.collider_size_bottom / 2 + BLOCK_SIZE / 2) / BLOCK_SIZE);
    int y_bottom_in_chunk = int(int(player.y - player.collider_size_bottom + BLOCK_SIZE / 2) / BLOCK_SIZE);
    
    int z_front_in_chunk = int(int(player.z + player.collider_size_z / 2 + BLOCK_SIZE / 2) / BLOCK_SIZE);
    int z_back_in_chunk = int(int(player.z - player.collider_size_z / 2 + BLOCK_SIZE / 2) / BLOCK_SIZE);

    if (((block_x + chunk->x / BLOCK_SIZE) == x_left_in_chunk || (block_x + chunk->x / BLOCK_SIZE) == x_right_in_chunk) && ((block_y + chunk->y / BLOCK_SIZE) == y_top_in_chunk || (block_y + chunk->y / BLOCK_SIZE) == y_middle_in_chunk || (block_y + chunk->y / BLOCK_SIZE) == y_bottom_in_chunk) && ((block_z + chunk->z / BLOCK_SIZE) == z_front_in_chunk || (block_z + chunk->z / BLOCK_SIZE)  == z_back_in_chunk)) {
        return nullptr;
    }
    chunk->is_air = false;

    // get and change block
    Block& block = chunk->blocks[block_x][block_y][block_z];
    if (block.id != 0 && block.id != 6) {
        return nullptr;
    }
    block.id = block_id;
    
    block.x = block_x * BLOCK_SIZE;
    block.y = block_y * BLOCK_SIZE;
    block.z = block_z * BLOCK_SIZE;

    // set and add inventory
    if (block_data.interaction_type == "storage_inv") {
        block.inventory_id = last_storage_id;
        StorageBoxInv storage;
        storages[last_storage_id] = storage;
        last_storage_id++;
    }

    // add to light sources
    if (block_data.light.r > 0 || block_data.light.g > 0 || block_data.light.b > 0) {
        chunk->light_sources_blocks.push_back(block);
    }

    return chunk;
}

void WorldLoader::update_block_place(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, Player& player, PlayerInventory& player_inv,  float dt) {
    if (player.on_block_interaction) {
        if (!player.fast_interactions) {
            player.on_block_interaction = false;
        }
        // get selected face data
        if (world_renderer.selected_face) {
            // get chunk and block
            int chunk_ind = world_renderer.selected_face->chunk_ind;

            int block_x = world_renderer.selected_face->block_x;
            int block_y = world_renderer.selected_face->block_y;
            int block_z = world_renderer.selected_face->block_z;

            // set block in chunk.blocks
            int new_block_x = block_x;
            int new_block_y = block_y;
            int new_block_z = block_z;
            // set block pos by selected face normal
            // front
            if (world_renderer.selected_face->normal == 'f') {
                new_block_z += 1;
            }
            // back
            if (world_renderer.selected_face->normal == 'b') {
                new_block_z -= 1;
            }
            // right
            if (world_renderer.selected_face->normal == 'r') {
                new_block_x += 1;
            }
            // left
            if (world_renderer.selected_face->normal == 'l') {
                new_block_x -= 1;
            }
            // top
            if (world_renderer.selected_face->normal == 't') {
                new_block_y += 1;
            }
            // bottom
            if (world_renderer.selected_face->normal == 'd') {
                new_block_y -= 1;
            }

            // block data
            Chunk& selected_chunk = chunks[chunk_ind];
            Block& selected_block = selected_chunk.blocks[block_x][block_y][block_z];
            FullBlockData& selected_block_data = all_blocks_full_data[selected_block.id];
            
            // check interaction
            if (selected_block_data.interaction_type != "" && !player.sneak) {
                bool interacted = check_block_interaction(world_renderer, selected_block, selected_block_data, selected_chunk, chunk_ind, chunks, storages, player, player_inv, dt);
                if (interacted) {
                    return;
                }
            }

            if (!player_inv.current_slot_data) {
                bool interacted = check_block_interaction(
                    world_renderer, 
                    selected_block, selected_block_data, selected_chunk, chunk_ind, 
                    chunks, storages, 
                    player, player_inv, 
                    dt
                );
                if (interacted) {
                    return;
                }
            } else {
                if (player_inv.current_slot_data->type != "block") {
                    bool interacted = check_block_interaction(
                        world_renderer, 
                        selected_block, selected_block_data, selected_chunk, chunk_ind, 
                        chunks, storages, 
                        player, player_inv, 
                        dt
                    );                    
                    if (interacted) {
                        return;
                    }
                }
            }

            // defile ids and place type
            int start_id, end_id;
            string place_type, place_item_name;
            bool placed_from_right_hand = true;

            // skip if item empty or not block
            if (!player_inv.current_slot_data || player_inv.current_slot_data->type != "block") {
                // set ids and place type from left hand
                if (player_inv.left_hand_slot_data && player_inv.left_hand_slot_data->type == "block") {
                    start_id = player_inv.left_hand_slot_data->place_blocks_ids_range[0];
                    end_id = player_inv.left_hand_slot_data->place_blocks_ids_range[1];
                    place_type = player_inv.left_hand_slot_data->block_place_type;
                    place_item_name = player_inv.left_hand_slot_data->name;
                    placed_from_right_hand = false;
                }
                // all hands have no blocks
                else {
                    return;
                }
            } 
            // set ids and place type
            else {
                start_id = player_inv.current_slot_data->place_blocks_ids_range[0];
                end_id = player_inv.current_slot_data->place_blocks_ids_range[1];
                place_type = player_inv.current_slot_data->block_place_type;
                place_item_name = player_inv.current_slot_data->name;
            }

            // * place
            // get id and full data of place block
            uint8_t block_id;
            
            // set start id 
            if (place_type == "block") {
                block_id = start_id;
            }

            // get rand id 
            else if (place_type == "rand") {
                block_id = randint(start_id, end_id);
            }
            // set slab
            else if (place_type == "slab") {
                // top
                if (world_renderer.selected_face->normal == 'd') {
                    block_id = start_id;
                }
                // bottom
                else if (world_renderer.selected_face->normal == 't') {
                    block_id = end_id;
                }
                // get from pos on sides
                else {
                    // get selected face average y pos
                    int average_y = world_renderer.average_block_outline_y;
                    // top
                    if (average_y >= 300) block_id = start_id;
                    // bottom
                    else block_id = end_id;
                }
            }
            // set as wood etc, with rotation
            else if (place_type == "pipe") {
                int middle_id = start_id + 1;
                // top
                if (world_renderer.selected_face->normal == 't') {
                    block_id = middle_id;
                }
                // bottom
                else if (world_renderer.selected_face->normal == 'd') {
                    block_id = middle_id;
                }

                // front
                if (world_renderer.selected_face->normal == 'f') {
                    block_id = start_id;
                }
                // back
                else if (world_renderer.selected_face->normal == 'b') {
                    block_id = start_id;
                }

                // right
                if (world_renderer.selected_face->normal == 'r') {
                    block_id = end_id;
                }
                // left
                else if (world_renderer.selected_face->normal == 'l') {
                    block_id = end_id;
                }
            }
            // set as torch rotation
            else if (place_type == "torch") {
                // bottom
                if (world_renderer.selected_face->normal == 't') {
                    block_id = start_id;
                } 
                // front 
                else if (world_renderer.selected_face->normal == 'b') {
                    block_id = start_id + 3;
                } 
                // back 
                else if (world_renderer.selected_face->normal == 'f') {
                    block_id = start_id + 1;
                } 

                // right 
                else if (world_renderer.selected_face->normal == 'l') {
                    block_id = start_id + 4;
                } 
                // left 
                else if (world_renderer.selected_face->normal == 'r') {
                    block_id = start_id + 2;
                } 
                else {
                    return;
                }
            }
            // set a trapdoor
            else if (place_type == "trap_door") {
                int average_y = world_renderer.average_block_outline_y;
                // top
                if (average_y > 300) {
                    // front
                    if (world_renderer.selected_face->normal == 'b') {
                        block_id = start_id + 2;
                    } 
                    // back 
                    else if (world_renderer.selected_face->normal == 'f') {
                        block_id = start_id;
                    } 

                    // right 
                    else if (world_renderer.selected_face->normal == 'l') {
                        block_id = start_id + 3;
                    } 
                    // left 
                    else if (world_renderer.selected_face->normal == 'r') {
                        block_id = start_id + 1;
                    } 
                } 
                // bottom
                else {
                    // front
                    if (world_renderer.selected_face->normal == 'b') {
                        block_id = start_id + 10;
                    } 
                    // back 
                    else if (world_renderer.selected_face->normal == 'f') {
                        block_id = start_id + 8;
                    } 

                    // right 
                    else if (world_renderer.selected_face->normal == 'l') {
                        block_id = start_id + 11;
                    } 
                    // left 
                    else if (world_renderer.selected_face->normal == 'r') {
                        block_id = start_id + 9;
                    } 
                } 
                // top with camera angle dirrection
                if (world_renderer.selected_face->normal == 'd') {
                    // front
                    if (player.angle_dirrection == 0) block_id = start_id + 2;
                    // back
                    if (player.angle_dirrection == 180) block_id = start_id;
                    // right
                    if (player.angle_dirrection == 270) block_id = start_id + 3;
                    // left
                    if (player.angle_dirrection == 90) block_id = start_id + 1;
                }
                // bottom with camera angle dirrection
                else if (world_renderer.selected_face->normal == 't') {
                    // front
                    if (player.angle_dirrection == 0) block_id = start_id + 10;
                    // back
                    if (player.angle_dirrection == 180) block_id = start_id + 8;
                    // right
                    if (player.angle_dirrection == 270) block_id = start_id + 11;
                    // left
                    if (player.angle_dirrection == 90) block_id = start_id + 9;
                }
            }

            // set as door
            else if (place_type == "door") {
                // front
                if (player.angle_dirrection == 180) block_id = start_id + 1;   
                // back
                if (player.angle_dirrection == 0) block_id = start_id;   
                // right
                if (player.angle_dirrection == 270) block_id = start_id + 2; 
                // left
                if (player.angle_dirrection == 90) block_id = start_id + 3; 
            }

            FullBlockData& block_data = all_blocks_full_data[block_id];
            // * expanded block (door)
            if (place_item_name == "door") {
                // bottom
                int new_top_block_x = new_block_x;
                int new_top_block_z = new_block_z;

                Chunk* chunk1 = add_block(world_renderer, block_id, block_data, chunks, storages, last_storage_id, chunk_ind, new_block_x, new_block_y, new_block_z, player);

                // top
                Chunk* chunk2 = nullptr;
                int new_top_block_y = new_block_y+1;

                if (chunk1) {
                    FullBlockData& top_block_data = all_blocks_full_data[block_id-4];
    
                    chunk_ind = get_chunk_ind_by_pos(chunk1->x / (CHUNK_SIZE_X * BLOCK_SIZE), chunk1->y / (CHUNK_SIZE_Y * BLOCK_SIZE), chunk1->z / (CHUNK_SIZE_Z * BLOCK_SIZE));
                    chunk2 = add_block(world_renderer, block_id-4, top_block_data, chunks, storages, last_storage_id, chunk_ind, new_top_block_x, new_top_block_y, new_top_block_z, player);
                }

                bool update_only_on_borders = true;
                if (block_data.light.r > 0 || block_data.light.g > 0 || block_data.light.b > 0) {
                    update_only_on_borders = false;
                }
                
                // cancel block place on chunks if one fail
                if (chunk1 && !chunk2) {
                    chunk1->blocks[new_block_x][new_block_y][new_block_z].id = 0; // set air
                }

                else if (chunk2 && !chunk1) {
                    chunk2->blocks[new_top_block_x][new_top_block_y][new_top_block_z].id = 0; // set air
                }

                // update chunk and chunks around
                else if (chunk1 && chunk2) {
                    // reduce current slot items count
                    if (placed_from_right_hand) {
                        player_inv.current_slot->items_count--;
                        if (player_inv.current_slot->items_count <= 0) {
                            player_inv.hotbar_slots[player_inv.current_slot_ind] = player_inv.empty_slot;
                            player_inv.update_current_slot(WINDOW_W, WINDOW_H);
                        }
                    }
                    // update left hand
                    else {
                        player_inv.left_hand_slot.items_count--;
                        if (player_inv.left_hand_slot.items_count <= 0) {
                            player_inv.left_hand_slot = player_inv.empty_slot;
                            player_inv.left_hand_slot_data = nullptr;
                            player_inv.left_hand_slot_block_light = nullptr;
                        }
                    }
                    
                    chunk_ind = get_chunk_ind_by_pos(chunk1->x / (CHUNK_SIZE_X * BLOCK_SIZE), chunk1->y / (CHUNK_SIZE_Y * BLOCK_SIZE), chunk1->z / (CHUNK_SIZE_Z * BLOCK_SIZE));
                    // clear chunk faces
                    clear_chunk_faces(world_renderer, chunk_ind);
                    // load chunks faces
                    full_chunk_load(world_renderer, chunks, chunk_ind, *chunk1);
                    
                    // clean new block pos inside chunk
                    if (new_block_x == CHUNK_SIZE_X) new_block_x = 0;
                    if (new_block_x == -1) new_block_x = CHUNK_SIZE_X-1;
                    
                    if (new_block_y == CHUNK_SIZE_Y) new_block_y = 0;
                    if (new_block_y == -1) new_block_y = CHUNK_SIZE_Y-1;
                    
                    if (new_block_z == CHUNK_SIZE_Z) new_block_z = 0;
                    if (new_block_z == -1) new_block_z = CHUNK_SIZE_X-1;
                    
                    // update near chunks, add to load queue
                    update_near_chunks(world_renderer, chunks, *chunk1, new_block_x, new_block_y, new_block_z, player, update_only_on_borders);
                } 
            }
            // * default block (only in one pos)
            else {
                Chunk* chunk = add_block(world_renderer, block_id, block_data, chunks, storages, last_storage_id, chunk_ind, new_block_x, new_block_y, new_block_z, player);
    
                bool update_only_on_borders = true;
                if (block_data.light.r > 0 || block_data.light.g > 0 || block_data.light.b > 0) {
                    update_only_on_borders = false;
                }
    
                // update chunk and chunks around
                if (chunk) {

                    if (placed_from_right_hand) {
                        // set empty bucket
                        if (player_inv.current_slot->item_id == 30 || player_inv.current_slot->item_id == 31) {
                            player_inv.current_slot->item_id = 29;
                            player_inv.update_current_slot(WINDOW_W, WINDOW_H);
                        } 
                        // reduce current slot items count
                        else {
                            player_inv.current_slot->items_count--;
                            if (player_inv.current_slot->items_count <= 0) {
                                player_inv.hotbar_slots[player_inv.current_slot_ind] = player_inv.empty_slot;
                                player_inv.update_current_slot(WINDOW_W, WINDOW_H);
                            }
                        }   
                    }
                    // update left hand
                    else {
                        // set empty bucket
                        if (player_inv.left_hand_slot.item_id == 30 || player_inv.left_hand_slot.item_id == 31) {
                            player_inv.left_hand_slot.item_id = 29;
                            player_inv.left_hand_slot_data = &all_items_data[player_inv.left_hand_slot.item_id];
                        } 
                        // reduce slot items count
                        else {
                            player_inv.left_hand_slot.items_count--;
                            if (player_inv.left_hand_slot.items_count <= 0) {
                                player_inv.left_hand_slot = player_inv.empty_slot;
                                player_inv.left_hand_slot_data = nullptr;
                                player_inv.left_hand_slot_block_light = nullptr;
                            }
                        }
                    }
                    chunk_ind = get_chunk_ind_by_pos(chunk->x / (CHUNK_SIZE_X * BLOCK_SIZE), chunk->y / (CHUNK_SIZE_Y * BLOCK_SIZE), chunk->z / (CHUNK_SIZE_Z * BLOCK_SIZE));
                    // clear chunk faces
                    clear_chunk_faces(world_renderer, chunk_ind);
                    // load chunks faces
                    full_chunk_load(world_renderer, chunks, chunk_ind, *chunk);
                    
                    // clean new block pos inside chunk
                    if (new_block_x == CHUNK_SIZE_X) new_block_x = 0;
                    if (new_block_x == -1) new_block_x = CHUNK_SIZE_X-1;
                    
                    if (new_block_y == CHUNK_SIZE_Y) new_block_y = 0;
                    if (new_block_y == -1) new_block_y = CHUNK_SIZE_Y-1;
                    
                    if (new_block_z == CHUNK_SIZE_Z) new_block_z = 0;
                    if (new_block_z == -1) new_block_z = CHUNK_SIZE_X-1;
                    
                    // update near chunks, add to load queue
                    update_near_chunks(world_renderer, chunks, *chunk, new_block_x, new_block_y, new_block_z, player, update_only_on_borders);
                }
            }
        }
    }
}

bool WorldLoader::check_block_interaction(WorldRenderer& world_renderer, Block& block, FullBlockData& block_data, Chunk& chunk, int chunk_ind, Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, Player& player,  PlayerInventory& player_inv, float dt) {
    string interaction_type = block_data.interaction_type;

    // open close trapdoor
    if (interaction_type == "open_trapdoor") {
        // update block id by next id
        block.id += 4;
        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);
        return true;

    }
    else if (interaction_type == "close_trapdoor") {
        // update block id by next id
        block.id -= 4;
        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);
        return true;

    }
    // * open close door
    // top
    else if (interaction_type == "open_door_top") {

        // update block id by next id
        if (block.id == 58) block.id += 3;
        else if (block.id == 59) block.id += 1;

        // * update bottom block
        int bottom_y = block.y / BLOCK_SIZE - 1;

        if (bottom_y == -1) {
            int bottom_chunk_ind = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y)-1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (bottom_chunk_ind != 1) {
                Chunk& bottom_chunk = chunks[bottom_chunk_ind];
                Block& bottom_block =  bottom_chunk.blocks[block.x / BLOCK_SIZE][CHUNK_SIZE_Y-1][block.z / BLOCK_SIZE];
                
                if (bottom_block.id == 62) bottom_block.id += 3;
                else if (bottom_block.id == 63) bottom_block.id += 1;
            }
        } else {
            Block& bottom_block = chunk.blocks[block.x / BLOCK_SIZE][bottom_y][block.z / BLOCK_SIZE];
            
            if (bottom_block.id == 62) bottom_block.id += 3;
            else if (bottom_block.id == 63) bottom_block.id += 1;
        }

        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, false);

        return true;
    }

    else if (interaction_type == "close_door_top") {
        // update block id by prev id
        if (block.id == 61) block.id -= 3;
        else if (block.id == 60) block.id -= 1;

        // * update bottom block
        int bottom_y = block.y / BLOCK_SIZE - 1;

        if (bottom_y == -1) {
            int bottom_chunk_ind = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y)-1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (bottom_chunk_ind != 1) {
                Chunk& bottom_chunk = chunks[bottom_chunk_ind];
                Block& bottom_block =  bottom_chunk.blocks[block.x / BLOCK_SIZE][CHUNK_SIZE_Y-1][block.z / BLOCK_SIZE];
                
                if (bottom_block.id == 65) bottom_block.id -= 3;
                else if (bottom_block.id == 64) bottom_block.id -= 1;
            }
        } else {
            Block& bottom_block = chunk.blocks[block.x / BLOCK_SIZE][bottom_y][block.z / BLOCK_SIZE];

            if (bottom_block.id == 65) bottom_block.id -= 3;
            else if (bottom_block.id == 64) bottom_block.id -= 1;
        }
        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, false);

        return true;
    }

    // bottom
    else if (interaction_type == "open_door_bottom") {
        // update block id by next id
        if (block.id == 62) block.id += 3;
        else if (block.id == 63) block.id += 1;

        // * update top block
        int top_y = block.y / BLOCK_SIZE + 1;
        if (top_y == CHUNK_SIZE_Y) {
            int top_chunk_ind = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y)+1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (top_chunk_ind != 1) {
                Chunk& top_chunk = chunks[top_chunk_ind];
                Block& top_block =  top_chunk.blocks[block.x / BLOCK_SIZE][0][block.z / BLOCK_SIZE];
                
                if (top_block.id == 58) top_block.id += 3;
                else if (top_block.id == 59) top_block.id += 1;
            }
        } else {
        
            Block& top_block = chunk.blocks[block.x / BLOCK_SIZE][top_y][block.z / BLOCK_SIZE];
            
            if (top_block.id == 58) top_block.id += 3;
            else if (top_block.id == 59) top_block.id += 1;
        }
        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, false);

        return true;
    }

    else if (interaction_type == "close_door_bottom") {
        // update block id by prev id
        if (block.id == 65) block.id -= 3;
        else if (block.id == 64) block.id -= 1;

        // * update top block
        int top_y = block.y / BLOCK_SIZE + 1;

        if (top_y == CHUNK_SIZE_Y) {
            int top_chunk_ind = get_chunk_ind_by_pos(
                chunk.x / (BLOCK_SIZE * CHUNK_SIZE_X),
                chunk.y / (BLOCK_SIZE * CHUNK_SIZE_Y)+1,
                chunk.z / (BLOCK_SIZE * CHUNK_SIZE_Z)
            );
            if (top_chunk_ind != 1) {
                Chunk& top_chunk = chunks[top_chunk_ind];
                Block& top_block =  top_chunk.blocks[block.x / BLOCK_SIZE][0][block.z / BLOCK_SIZE];
                
                if (top_block.id == 61) top_block.id -= 3;
                else if (top_block.id == 60) top_block.id -= 1;
            }
        } else {
            Block& top_block = chunk.blocks[block.x / BLOCK_SIZE][top_y][block.z / BLOCK_SIZE];
            
            if (top_block.id == 61) top_block.id -= 3;
            else if (top_block.id == 60) top_block.id -= 1;
        }
        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, false);

        return true;
    }

    // dig a bed with a hoe
    else if (interaction_type == "dig_bed" && player_inv.current_slot->item_id == 19) {
        // set block id as dry bed
        block.id = 45;
        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, false);

        // reduce hoe durability 
        int item_durability = int(player_inv.current_slot->durability);
        
        item_durability -= randint(0, 2);
        if (item_durability <= 0) {
            player_inv.clear_current_slot();
        } else {
            player_inv.current_slot->durability = uint8_t(item_durability);
        }
        return true;
    }

    // open inventory
    else if (interaction_type == "storage_inv") {
        player.in_inventory = true;
        player_inv.in_storage_inv = true;
        player_inv.set_hotbar_on_top(WINDOW_W, WINDOW_H);

        StorageBoxInv& block_storage = storages[block.inventory_id];

        player_inv.current_storage_id = block.inventory_id;
        player_inv.current_storage = &block_storage;

        SDL_ShowCursor(1);   


        return true;
    }
    // open crafter
    else if (interaction_type == "crafter") {
        player.in_inventory = true;
        player_inv.in_block_crafter = true;

        player_inv.set_hotbar_on_top(WINDOW_W, WINDOW_H);

        SDL_ShowCursor(1);   

        return true;
    }

    // water take
    else if (interaction_type == "take_water" && player_inv.current_slot->item_id == 29) {
        // set air
        block.id = 0; 

        // set water bucket
        player_inv.current_slot->item_id = 30;
        player_inv.update_current_slot(WINDOW_W, WINDOW_H);

        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, false);
        
        return true;
    }
    // lava take
    else if (interaction_type == "take_lava" && player_inv.current_slot->item_id == 29) {
        // set air
        block.id = 0; 

        // set lava bucket
        player_inv.current_slot->item_id = 31;
        player_inv.update_current_slot(WINDOW_W, WINDOW_H);

        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);

        delete_block_from_light_sources(block, chunk);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, true);
        
        return true;
    }

    // wood firing with lighter
    else if (interaction_type == "lighter_firing" && player_inv.current_slot->item_id == 49) {
        // set fire wood
        block.id = 93; 

        // set firing update time 
        block.update_time = 10;

        // update chunk
        clear_chunk_faces(world_renderer, chunk_ind);
        full_chunk_load(world_renderer, chunks, chunk_ind, chunk);
        
        // light sources update
        delete_block_from_light_sources(block, chunk);
        chunk.light_sources_blocks.push_back(block);

        // update near chunks, add to load queue
        update_near_chunks(world_renderer, chunks, chunk, block.x / BLOCK_SIZE, block.y / BLOCK_SIZE, block.z / BLOCK_SIZE, player, true);
        
        return true;
    }

    return false;
}

void WorldLoader::update(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], vector<ItemDrop>& all_items_drops, map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id,  Player& player,  PlayerInventory& player_inv, float dt) {
    // player interctions
    update_block_break(world_renderer, chunks, all_items_drops, storages, last_storage_id, player, player_inv, dt);
    update_block_place(world_renderer, chunks, storages, last_storage_id, player, player_inv, dt);
    // load chunks
    check_chunks_to_load(world_renderer, chunks, player);
    
    update_chunks_to_load_queue(world_renderer, chunks, player, dt);

    update_loaded_chunks(world_renderer, chunks, dt);
}