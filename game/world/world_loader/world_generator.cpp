#include "world_generator.h"

// common help funcs
int get_chunk_ind_by_pos(int x, int y, int z) {
    bool x_correct = bool(x >= 0 && x < WORLD_SIZE_X);
    bool y_correct = bool(y >= 0 && y < WORLD_SIZE_Y);
    bool z_correct = bool(z >= 0 && z < WORLD_SIZE_Z);

    if (!x_correct || !y_correct || !z_correct) {
        return -1;
    }
    return x * WORLD_SIZE_Y * WORLD_SIZE_Z + y * WORLD_SIZE_Z + z;
}


void set_block(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz, uint8_t new_id, bool set_only_air) {
    bool chunk_changed = false;
    
    // x
    if (bx < 0) {
        chx += ceil((bx - CHUNK_SIZE_X - 1) / CHUNK_SIZE_X);
        bx = (bx + CHUNK_SIZE_X) % CHUNK_SIZE_X;
        chunk_changed = true;
    }
    if (bx >= CHUNK_SIZE_X-1) {
        chx += ceil(bx / CHUNK_SIZE_X);
        bx %= CHUNK_SIZE_X;
        chunk_changed = true;
    }
    // y
    if (by < 0) {
        chy += ceil((by - CHUNK_SIZE_Y - 1) / CHUNK_SIZE_Y);
        by = (by + CHUNK_SIZE_Y) % CHUNK_SIZE_Y;
        chunk_changed = true;
    }
    if (by >= CHUNK_SIZE_Y-1) {
        chy += ceil(by / CHUNK_SIZE_Y);
        by %= CHUNK_SIZE_Y;
        chunk_changed = true;
    }
    // z
    if (bz < 0) {
        chz += ceil((bz - CHUNK_SIZE_Z - 1) / CHUNK_SIZE_Z);
        bz = (bz + CHUNK_SIZE_Z) % CHUNK_SIZE_Z;
        chunk_changed = true;
    }
    if (bz >= CHUNK_SIZE_Z-1) {
        chz += ceil(bz / CHUNK_SIZE_Z);
        bz %= CHUNK_SIZE_Z;
        chunk_changed = true;
    }
    
    // update block in current chunk
    if (!chunk_changed) {
        chunk.is_air = false;
        // get and update block
        Block& block = chunk.blocks[bx][by][bz];
        // if (set_only_air) {
        //     if (block.id == 0) {
        //         block.id = new_id; 
        //     }
        // } else {
        //     block.id = new_id; 
        // }
        block.id = new_id; 

        // set pos
        block.x = bx * BLOCK_SIZE;
        block.y = by * BLOCK_SIZE;
        block.z = bz * BLOCK_SIZE;
    }
    // in other
    else {
        // get chunk_ind and chunk
        int chunk_ind = get_chunk_ind_by_pos(chx, chy, chz);
        if (chunk_ind != -1) {
            Chunk& other_chunk = chunks[chunk_ind];
            other_chunk.is_air = false;

            // get and update block
            Block& block = other_chunk.blocks[bx][by][bz];
            block.id = new_id; 

            // set pos
            block.x = bx * BLOCK_SIZE;
            block.y = by * BLOCK_SIZE;
            block.z = bz * BLOCK_SIZE;
        }
    }
}

WorldGenerator::WorldGenerator() {}

void WorldGenerator::generate(Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, string world_type) {
    // * create superflat
    if (world_type == "superflat") {
        // create chunks
        unsigned short chunk_ind = 0;

        for (size_t wx = 0; wx < WORLD_SIZE_X; wx++)
        for (size_t wy = 0; wy < WORLD_SIZE_Y; wy++)
        for (size_t wz = 0; wz < WORLD_SIZE_Z; wz++)
        {
            Chunk chunk;

            // set pos
            chunk.x = wx * (CHUNK_SIZE_X * BLOCK_SIZE);
            chunk.y = wy * (CHUNK_SIZE_Y * BLOCK_SIZE);
            chunk.z = wz * (CHUNK_SIZE_Z * BLOCK_SIZE);
            
            if (wy != 0) {
                chunks[chunk_ind] = chunk;

                chunk_ind++;
                continue;
            }

            chunk.is_air = false;
            // create blocks
            unsigned short block_ind = 0;
            for (size_t bx = 0; bx < CHUNK_SIZE_X; bx++)
            for (size_t by = 0; by < 5; by++)
            for (size_t bz = 0; bz < CHUNK_SIZE_Z; bz++)
            {
                Block block;
                // grass
                if (by == 4) {
                    block.id = randint(1, 4);
                    // block.id = 5;
                    // block.update_time = (uint8_t)randint(20, 50);

                    if ((bx == 2 || bx == 7) && (bz == 2 || bz == 7)) {
                        block.sun_light = 1.0;
                        chunk.light_sources_blocks.push_back(block);
                    }

                    // place rand storage
                    if (randint(0, 30) == 0) {
                        Block storage_block;

                        storage_block.x = bx * BLOCK_SIZE;
                        storage_block.y = (by + 1) * BLOCK_SIZE;
                        storage_block.z = bz * BLOCK_SIZE;

                        storage_block.id = randint(51, 53);
                        // set inventory id
                        storage_block.inventory_id = last_storage_id;

                        StorageBoxInv storage;
                        for (size_t si = 0; si < 45; si++)
                        {

                            InventorySlot& slot = storage.slots[si];
                            int item_id = randint(-20, 28);
                            if (item_id <= 0) {
                                continue;
                            }

                            slot.item_id = uint8_t(item_id);

                            InventoryItemData& item_data = all_items_data[slot.item_id];
                            if (item_data.max_durability > 0) {
                                slot.durability = randint(1, item_data.max_durability);
                            }
                            slot.items_count = randint(1, item_data.max_stack);
                        }
                        
                        storages[last_storage_id] = storage;
                        last_storage_id++;

                        // add to blocks
                        if (storage_block.y >= 0 && storage_block.y < CHUNK_SIZE_Y * BLOCK_SIZE) {
                            chunk.blocks[bx][storage_block.y / BLOCK_SIZE][bz] = storage_block;
                        }
                    }

                } else {
                    block.id = 5;
                }

                // set pos
                block.x = bx * BLOCK_SIZE;
                // block.y = (by - bx - bz + 4) * BLOCK_SIZE;
                block.y = by * BLOCK_SIZE;
                block.z = bz * BLOCK_SIZE;

                // add to blocks
                if (block.y >= 0 && block.y < CHUNK_SIZE_Y * BLOCK_SIZE) {
                    chunk.blocks[bx][block.y / BLOCK_SIZE][bz] = block;
                }
            }

            // add chunk
            chunks[chunk_ind] = chunk;

            chunk_ind++;
        }
    }
    // * create with terrain
    if (world_type == "alpha") {
        // define perlin noise
        PerlinNoise noise;
        

        // create chunks
        unsigned short chunk_ind = 0;

        for (int wx = 0; wx < WORLD_SIZE_X; wx++)
        for (int wy = 0; wy < WORLD_SIZE_Y; wy++)
        for (int wz = 0; wz < WORLD_SIZE_Z; wz++)
        {
            Chunk& chunk = chunks[chunk_ind];

            // set pos
            chunk.x = wx * (CHUNK_SIZE_X * BLOCK_SIZE);
            chunk.y = wy * (CHUNK_SIZE_Y * BLOCK_SIZE);
            chunk.z = wz * (CHUNK_SIZE_Z * BLOCK_SIZE);

            // create blocks
            unsigned short block_ind = 0;
            
            for (int bx = 0; bx < CHUNK_SIZE_X; bx++)
            for (int bz = 0; bz < CHUNK_SIZE_Z; bz++) {
                int n_by = noise.noise_height(bx + (wx * CHUNK_SIZE_X), bz + (wz * CHUNK_SIZE_Z));

                for (int by = -(WORLD_SIZE_Y*CHUNK_SIZE_Y); by <= ground_level; by++) {
                    Block block;
                    // set as top block
                    if (by == ground_level - 1) {
                        // set as sand
                        if (n_by <= 1) {
                            block.id = 7;
                        }
                        // grass or sand
                        else if (n_by == 2) {
                            // set sun light 
                            if ((bx == 2 || bx == 7) && (bz == 2 || bz == 7)) {
                                block.sun_light = 1.0;
                                chunk.light_sources_blocks.push_back(block);
                            }
                            
                            if (randint(0, 2) == 0) {
                                block.id = block.id = randint(1, 4);;                                
                            } else {
                                block.id = 7;
                            }
                        }
                        // set ground
                        else {
                            // based on current biome
                            if (noise.current_biome_name == "default") {
                                block.id = randint(1, 4); // grass
                            }
                            else if (noise.current_biome_name == "mountains") {
                                if (by + n_by >= ground_level + (30 + randint(0, 2))) {
                                    int rand_block = randint(0, 10);

                                    // stone
                                    if (rand_block <= 5) {
                                        block.id = randint(26, 27);
                                    } 
                                    // grayed stone
                                    else if (rand_block >= 6 && rand_block <= 8) {
                                        block.id = randint(66, 67);
                                    }
                                    // gravel
                                    else if (rand_block >= 9) {
                                        block.id = randint(72, 75);
                                    }
                                } else {
                                    block.id = randint(1, 4);  // grass
                                }
                            }
                            else if (noise.current_biome_name == "desert") {
                                block.id = 7; // sand
                            } 
    
                            // set sun light 
                            if ((bx == 2 || bx == 7) && (bz == 2 || bz == 7)) {
                                block.sun_light = 1.0;
                                chunk.light_sources_blocks.push_back(block);
                            }
                        }
                    }
                    // blocks and others above grass
                    else if (by == ground_level && (by + n_by) - 8 > water_level) {
                        if (noise.current_biome_name == "default") {
                            //  plants
                            int rand_plant = randint(0, 600);
        
                            // low grass
                            if (rand_plant <= 50) {
                                block.id = 8; 
                            }
    
                            // flowers
                            if (rand_plant >= 51 && rand_plant <= 60) {
                                block.id = 89;
                            }
                            
                            // tree
                            if (rand_plant == 61) {
                            // if (bx == 0 && bz == 0) {
                                block.id = 14; 
                                add_tree(
                                    chunks, chunk, 
                                    wx, wy, wz, 
                                    bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz
                                );
                            }
                        }
    
                        if (noise.current_biome_name == "mountains" && by + n_by < ground_level + (27 + randint(0, 4))) {
                            //  plants
                            int rand_plant = randint(0, 500);
        
                            // low grass
                            if (rand_plant <= 10) {
                                block.id = 8; 
                            }
    
                            // flowers
                            if (rand_plant >= 11 && rand_plant <= 44) {
                                block.id = 89;
                            }
                            
                            // tree
                            if (rand_plant == 51) {
                            // if (bx == 0 && bz == 0) {
                                block.id = 14; 
                                add_tree(
                                    chunks, chunk, 
                                    wx, wy, wz, 
                                    bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz
                                );
                            }
                        }
                    }
                    // dirt stone 
                    else if (by < ground_level) {
                        // set stone
                        if (noise.current_biome_name == "mountains" && n_by >= (31 + randint(0, 2))) {
                            set_underground(
                                chunks, chunk, 
                                wx, wy, wz, 
                                block, 
                                bx, by, bz, n_by
                            ); 

                        // defauld or desers
                        } else {
                            if (by < ground_level - stone_level) {
                                set_underground(
                                    chunks, chunk, 
                                    wx, wy, wz, 
                                    block, 
                                    bx, by, bz, n_by
                                ); 
                            } else {
                                // set stone or dirt based on random height reduce
                                if (noise.current_biome_name != "desert") {
                                    if (by < (ground_level - stone_level) + randint(1, 3)){
                                        set_underground(
                                            chunks, chunk, 
                                            wx, wy, wz, 
                                            block, 
                                            bx, by, bz, n_by
                                        ); 

                                    } else {
                                        block.id = 5;
                                    }
                                }
                                // set gravel and stone or sand based on random height reduce
                                else {
                                    int rand_height_add = randint(3, 5);
                                    if (by < (ground_level - (stone_level + rand_height_add))) {
                                        set_underground(
                                            chunks, chunk, 
                                            wx, wy, wz, 
                                            block, 
                                            bx, by, bz, n_by
                                        );                                        
                                    } else {
                                        block.id = 7;
                                    }
                                }
                            }
                        }
                    }
    
                    // set pos
                    block.x = bx * BLOCK_SIZE;
                    block.y = ((n_by + by - wy * CHUNK_SIZE_Y)-5) * BLOCK_SIZE;
                    block.z = bz * BLOCK_SIZE;
    
                    // add to blocks
                    if (block.y >= 0 && block.y < CHUNK_SIZE_Y * BLOCK_SIZE) {
                        chunk.blocks[bx][block.y / BLOCK_SIZE][bz] = block;
                        chunk.is_air = false;
                    }
                }
            }
            
            // set water on level
            if (wy == int(water_level / (CHUNK_SIZE_X - 1))) {
                for (size_t bx = 0; bx < CHUNK_SIZE_X; bx++)
                for (size_t by = 0; by <= water_level % (CHUNK_SIZE_Y - 1); by++)
                for (size_t bz = 0; bz < CHUNK_SIZE_Z; bz++) {
                    Block& block = chunk.blocks[bx][by][bz];

                    // set pos
                    block.x = bx * BLOCK_SIZE;
                    block.y = by * BLOCK_SIZE;
                    block.z = bz * BLOCK_SIZE;
    
                    // check if air
                    if (block.id == 0) {
                        block.id = 6;
                        chunk.is_air = false;

                        // set sun light 
                        if (by == water_level % (CHUNK_SIZE_Y - 1)) {
                            if ((bx == 2 || bx == 7) && (bz == 2 || bz == 7)) {
                                block.sun_light = 1.0;
                                chunk.light_sources_blocks.push_back(block);
                            }
                        }
                    }
                }
            }
            // set under level
            if (wy < int(water_level / (CHUNK_SIZE_X - 1)) && wy >= int(water_level / (CHUNK_SIZE_X - 1)) - 2) {
                for (size_t bx = 0; bx < CHUNK_SIZE_X; bx++)
                for (size_t by = 0; by < CHUNK_SIZE_Y; by++)
                for (size_t bz = 0; bz < CHUNK_SIZE_Z; bz++) {
                    Block& block = chunk.blocks[bx][by][bz];

                    // set pos
                    block.x = bx * BLOCK_SIZE;
                    block.y = by * BLOCK_SIZE;
                    block.z = bz * BLOCK_SIZE;
    
                    // check if air
                    if (block.id == 0) {
                        block.id = 6;
                        chunk.is_air = false;
                    }
                }
            }

            chunk_ind++;
        }
    }

    set_sector_top_map(chunks, 0, 0);
}


void WorldGenerator::set_underground(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int wx, int wy, int wz, Block& block, int bx, int by, int bz, int n_by) {
    block.id = randint(26, 27); // stone
    bool ore_added = false;
    // * ores
    // coal
    if (by + n_by >= coal_ore_area_start_y && by + n_by <= coal_ore_area_end_y) {
        int rand_ore = randint(0, coal_ore_chance);
        if (rand_ore == 0) {
            add_coal_ore(
                chunks, chunk, 
                wx, wy, wz,
                bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz
            );
            ore_added = true;
        }
    }

    // iron
    if (by + n_by >= iron_ore_area_start_y && by + n_by <= iron_ore_area_end_y) {
        int rand_ore = randint(0, iron_ore_chance);
        if (rand_ore == 0) {
            add_iron_ore(
                chunks, chunk, 
                wx, wy, wz,
                bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz
            );
            ore_added = true;
        }
    }

    // add other blocks ore
    if (!ore_added && (by < ground_level - 15 && by + n_by < ground_level + 5)) {
        int rand_chance = randint(0, 20000);
        // dirt
        if (rand_chance == 0) {
            add_other_blocks_ore(
                chunks, chunk, 
                wx, wy, wz,
                bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz,
                5, 5
            );
        }

        // granite
        else if (rand_chance == 1 && (by + n_by) - 10 > 0) {
            add_other_blocks_ore(
                chunks, chunk, 
                wx, wy, wz,
                bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz,
                90, 91
            );
        }

        // grayed stone
        else if (rand_chance >= 2 && rand_chance <= 5) {
            add_other_blocks_ore(
                chunks, chunk, 
                wx, wy, wz,
                bx, (n_by + by - wy * CHUNK_SIZE_Y) - 5, bz,
                66, 67
            );
        }
    }
}

// * structures
void WorldGenerator::add_tree(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz) {
    if (by < 0 || by >= CHUNK_SIZE_Y) {
        return;
    }

    // wood
    int wood_height = randint(3, 6);
    for (int y = 0; y < wood_height; y++)
    {
        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx, by + y, bz, 14,
            true
        );
    }

    // * leaves

    // base
    for (size_t y = 0; y < 3; y++)
    {
        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx, 
            by + wood_height + y, 
            bz, 
            randint(54, 57), // leaves block
            true
        );
    }

    for (int x = -1; x <= 1; x++)
    for (int z = -1; z <= 1; z++)
    {
        if (x != 0 && z != 0) {
            set_block(
                chunks, chunk,
                chx, chy, chz,
                bx + x, 
                by + wood_height, 
                bz + z, 
                randint(54, 57), // leaves block
                true
            );   
        }
    }
    

    int leaves_count = 90;
    for (size_t i = 0; i < leaves_count; i++)
    {
        int rand_x = randint(-1, 1);
        int rand_y = randint(-2, 3);
        int rand_z = randint(-1, 1);

        // skip if pos in wood
        if (rand_x == 0 && rand_z == 0 && rand_y <= 0) {
            continue;
        }

        // skip top
        if (rand_x != 0 && rand_z != 0) {
            continue;
        }

        // set block
        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + rand_y + wood_height, 
            bz + rand_z, 
            randint(54, 57), // leaves block
            true
        );

    }

    // layers
    leaves_count = 70;
    for (size_t i = 0; i < leaves_count; i++)
    {
        int rand_x = randint(-2, 2);
        int rand_z = randint(-2, 2);

        // skip if pos in wood
        if (rand_x == 0 && rand_z == 0) {
            continue;
        }
        // skip egdes
        if (abs(rand_x) == 2 && abs(rand_z) == 2) {
            continue;
        }

        // set block
        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + wood_height - 1, 
            bz + rand_z, 
            randint(54, 57), // leaves block
            true
        );
    }

    leaves_count = 40;
    for (size_t i = 0; i < leaves_count; i++)
    {
        int rand_x = randint(-2, 2);
        int rand_z = randint(-2, 2);

        // skip egdes
        if (abs(rand_x) == 2 && abs(rand_z) == 2) {
            continue;
        }

        // set block
        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + wood_height + 1, 
            bz + rand_z, 
            randint(54, 57), // leaves block
            false
        );
    }
}

// ores
void WorldGenerator::add_coal_ore(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz) {
    if (by < 0 || by >= CHUNK_SIZE_Y) {
        return;
    }
    
    int count = 25;
    
    for (size_t i = 0; i < count; i++)
    {
        int rand_x = randint(-1, 1);
        int rand_y = randint(-1, 1);
        int rand_z = randint(-1, 1);

        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + rand_y, 
            bz + rand_z, 
            randint(85, 86), 
            false
        );   
    }
}

void WorldGenerator::add_iron_ore(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz) {
    if (by < 0 || by >= CHUNK_SIZE_Y) {
        return;
    }
    
    int count = 20;
    
    for (size_t i = 0; i < count; i++)
    {
        int rand_x = randint(-3, 3);
        int rand_y = randint(-3, 3);
        int rand_z = randint(-3, 3);

        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + rand_y, 
            bz + rand_z, 
            randint(87, 88), 
            false
        );   
    }
}

void WorldGenerator::add_other_blocks_ore(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz, int ids_range_start, int ids_range_end) {
    if (by < 0 || by >= CHUNK_SIZE_Y) {
        return;
    }
    // base
    for (int x = -4; x <= 4; x++)
    for (int y = -4; y <= 4; y++)
    for (int z = -4; z <= 4; z++)
    {
        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + x, 
            by + y, 
            bz + z, 
            randint(ids_range_start, ids_range_end), 
            false
        );  
    }

    // rand around
    int count = 20;

    for (size_t i = 0; i < count; i++)
    {
        int rand_x = randint(-6, -4);
        int rand_y = randint(-4, 4);
        int rand_z = randint(-6, -4);

        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + rand_y, 
            bz + rand_z, 
            randint(ids_range_start, ids_range_end), 
            false
        );   
    }

    for (size_t i = 0; i < count; i++)
    {
        int rand_x = randint(4, 6);
        int rand_y = randint(-4, 4);
        int rand_z = randint(4, 6);

        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + rand_y, 
            bz + rand_z,
            randint(ids_range_start, ids_range_end), 
            false
        );   
    }

    for (size_t i = 0; i < count; i++)
    {
        int rand_x = randint(-3, 3);
        int rand_y = randint(-6, 6);
        int rand_z = randint(-3, 3);

        set_block(
            chunks, chunk,
            chx, chy, chz,
            bx + rand_x, 
            by + rand_y, 
            bz + rand_z, 
            randint(ids_range_start, ids_range_end), 
            false
        );   
    }
}

void WorldGenerator::set_sector_top_map(Chunk (&chunks)[CHUNKS_COUNT], int cx, int cz) {
    // go fron world top to bottom until hit block
    Chunk* last_chunk = nullptr;
    int last_chunk_y = -1;

    for (size_t bx = 0; bx < CHUNK_SIZE_X; bx++)
    for (size_t bz = 0; bz < CHUNK_SIZE_Z; bz++) {
        int world_by = (CHUNK_SIZE_Y * WORLD_SIZE_Y)-1;
        // for (int world_by = (CHUNK_SIZE_Y * WORLD_SIZE_Y)-1; world_by >=  0; world_by--)
        while (world_by >= 0)
        { 
            // get chunk
            int cy = int(world_by / WORLD_SIZE_Y);
            // get and set chunk
            if(last_chunk_y != cy) {
                int chunk_ind = get_chunk_ind_by_pos(cx, cy, cz);
                if (chunk_ind != -1) {
                    last_chunk = &chunks[chunk_ind];
                }
            }
            // skip block y if chunk is air
            if (last_chunk->is_air) {
                world_by -= CHUNK_SIZE_Y;
                continue;
            }
    
            // check chunk top block
            int by = world_by % CHUNK_SIZE_Y;
    
            Block& top_block = last_chunk->blocks[bx][by][bz];
            if (top_block.id != 0) {
                break;
            }
            world_by--;
        }
    }
}

void WorldGenerator::set_full_top_map(Chunk (&chunks)[CHUNKS_COUNT]) {

}

