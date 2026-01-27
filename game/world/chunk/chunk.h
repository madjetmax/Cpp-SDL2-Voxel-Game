#include <string>
#include <iostream>
#include <cstdint>
#include <array>
#include <vector>

#include "../../config.h"
#include "../../common/types.h"
#include "../block/block.h"


using namespace std; 

#ifndef CHUNK_H
#define CHUNK_H


class Chunk {
public:
    int x, y, z;

    Block blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
    vector<Block> light_sources_blocks;

    bool loaded = false;

    bool is_air = true; // to redice loads if chunk full of air

    Chunk(void);
};


#endif