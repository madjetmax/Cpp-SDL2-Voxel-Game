#include <string>
#include <iostream>
#include <cstdint>

#include "../../config.h"
#include "../../common/types.h"


using namespace std; 

#ifndef BLOCK_H
#define BLOCK_H



class Block {
public:
    short x, y, z; // pos inside chunk 
    uint8_t id = 0; // 0 = air

    // light
    float sun_light = 0.1; // 1 - max 0 - full darkness
    uint8_t light_level;

    // updates and timers
    uint8_t update_time = 0;

    uint16_t inventory_id = 0; // inventory in world, not ralated to chunk data

    Block(void);
};


#endif