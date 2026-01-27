#include "crafts_recipes.h"


// * all crafts
vector <CrafterRecipe> all_crafter_recipes {
    // planks
    {
        {
            {9, 0},
            {0, 0}
        }, 
        10, 4
    },
    // stick
    {
        {
            {10, 0},
            {10, 0}
        }, 
        37, 4
    },
    // torck
    {
        {
            {0,  42},
            {37, 0}
        }, 
        11, 4 
    },
    // crafter
    {
        {
            {9, 9},
            {10, 10}
        },
        47, 1
    }
};

vector <BlockCrafterRecipe> all_block_crafter_recipes {
    // stone pickaxe
    {
        {
            {6, 6,  6},
            {0, 37, 0},
            {0, 37, 0},
        },
        39, 1
    },
    // iron pickaxe
    {
        {
            {41, 41, 41},
            {0,  37, 0},
            {0,  37, 0},
        },
        40, 1
    }
};


InventorySlot empty_slot = {0, 0, 0};

void check_crafter_recipe(InventorySlot (&crafter_slots)[2][2], InventorySlot& result_slot) {
    CrafterRecipe* found_recipe = nullptr;

    // loop all recipies
    for (size_t ri = 0; ri < all_crafter_recipes.size(); ri++)
    {
        CrafterRecipe& recipe = all_crafter_recipes[ri];

        bool skip_recipe = false;
        // compare items with items in crafter
        for (int x = 0; x < 2; x++)
        for (int y = 0; y < 2; y++)
        {
            InventorySlot& slot = crafter_slots[y][x];
            
            if (slot.item_id != recipe.items_ids[x][y]) {
                skip_recipe = true;
                break;
            }

        }
        if (skip_recipe) {
            continue;
        }

        // set recipe
        found_recipe = &recipe;
        break;
    }

    // set result slot 
    if (found_recipe) {
        result_slot.item_id = found_recipe->result_item_id;
        result_slot.items_count = found_recipe->result_item_count;
        return;
    } 
    result_slot = empty_slot;
}



void check_block_crafter_recipe(InventorySlot (&block_crafter_slots)[3][3], InventorySlot& result_slot) {
    BlockCrafterRecipe* found_recipe = nullptr;

    // loop all recipies
    for (size_t ri = 0; ri < all_block_crafter_recipes.size(); ri++)
    {
        BlockCrafterRecipe& recipe = all_block_crafter_recipes[ri];

        bool skip_recipe = false;
        // compare items with items in crafter
        for (int x = 0; x < 2; x++)
        for (int y = 0; y < 2; y++)
        {
            InventorySlot& slot = block_crafter_slots[y][x];
            
            if (slot.item_id != recipe.items_ids[x][y]) {
                skip_recipe = true;
                break;
            }

        }
        if (skip_recipe) {
            continue;
        }

        // set recipe
        found_recipe = &recipe;
        break;
    }

    // set result slot 
    if (found_recipe) {
        result_slot.item_id = found_recipe->result_item_id;
        result_slot.items_count = found_recipe->result_item_count;
        
        // set durability
        InventoryItemData& result_item_data = all_items_data[result_slot.item_id];
        result_slot.durability = result_item_data.max_durability;

        return;
    } 
    result_slot = empty_slot;
}