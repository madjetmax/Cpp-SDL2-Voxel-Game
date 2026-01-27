#include <iostream>
#include <chrono>
#include "../../config.h"

#include "../block/block.h"
#include "../chunk/chunk.h"

#include "../../common/block_models.h"
#include "../../common/math_help.h"
#include "perlin_noise.h"

using namespace std;
using namespace std::chrono; 

#ifndef WORLDFGENERATOR_H
#define WORLDFGENERATOR_H


class WorldGenerator {
public:
    // * alpha
    // values and levels
    int water_level = 33;
    int ground_level = 40;

    int stone_level = 7; // from ground

    // ores spawns
    int coal_ore_area_start_y = 10;
    int coal_ore_area_end_y = 30;
    int coal_ore_chance = 200;

    int iron_ore_area_start_y = 5;
    int iron_ore_area_end_y = 15;
    int iron_ore_chance = 300;

    WorldGenerator(void);
    void generate(Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, string world_type);
    void set_sector_top_map(Chunk (&chunks)[CHUNKS_COUNT], int cx, int cz);
    void set_full_top_map(Chunk (&chunks)[CHUNKS_COUNT]);

    void set_underground(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int wx, int wy, int wz, Block& block, int bx, int by, int bz, int n_by);

    // * structures
    void add_tree(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz);
    // ores
    void add_coal_ore(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz);
    void add_iron_ore(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz);

    void add_other_blocks_ore(Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int chx, int chy, int chz, int bx, int by, int bz, int ids_range_start, int ids_range_end);

};


#endif