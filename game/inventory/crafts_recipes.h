#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <cstdint>
#include <unordered_map>

#include "items_loader.h"
#include "../common/types.h"
#include "../config.h"

#ifndef CRAFTS_RECIPES_H
#define CRAFTS_RECIPES_H

using namespace std;

struct CrafterRecipe {
    uint8_t items_ids[2][2];

    uint8_t result_item_id;
    uint8_t result_item_count;
};

struct BlockCrafterRecipe {
    uint8_t items_ids[3][3];

    uint8_t result_item_id;
    uint8_t result_item_count;
};

extern vector <CrafterRecipe> all_crafter_recipes; 
extern vector <BlockCrafterRecipe> all_block_crafter_recipes; 

void check_crafter_recipe(InventorySlot (&crafter_slots)[2][2], InventorySlot& result_slot);
void check_block_crafter_recipe(InventorySlot (&block_crafter_slots)[3][3], InventorySlot& result_slot);

#endif
