#include "items_loader.h"


map <uint8_t, InventoryItemData> all_items_data = {
    {1, {
        "grass_block",
        "grass block", 
        "grass_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {1, 4}
    }}, 
    {2, {
        "dirt_block",
        "dirt block", 
        "dirt_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {5, 5}
    }}, 
    {3, {
        "water_block",
        "water block", 
        "water_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {6, 6}
    }}, 
    {4, {
        "sand_block",
        "sand block", 
        "sand_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {7, 7}
    }}, 
    {5, {
        "low_grass",
        "low grass", 
        "low_grass",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {8, 8},
        "2d", 1.5
    }}, 
    {6, {
        "cobblestone_block",
        "cobblestone block", 
        "cobblestone_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {9, 9}
    }}, 
    {7, {
        "cobblestone_slab",
        "cobblestone slab", 
        "cobblestone_slab",

        8*3, 8*3,
        64,
        0,
        "block",
        "slab",
        {10, 11}
    }}, 
    {8, {
        "glass_block",
        "glass block", 
        "glass_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {12, 12}
    }}, 
    {9, {
        "wood_log",
        "wood log", 
        "wood_log",

        8*3, 8*3,
        64,
        0,
        "block",
        "pipe",
        {13, 15}
    }}, 
    {10, {
        "wooden_planks",
        "wooden planks", 
        "wooden_planks",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {16, 16}
    }}, 
    {11, {
        "torch",
        "torch", 
        "torch",

        int(2*1.7), int(10*1.7),
        64,
        0,
        "block",
        "torch",
        {17, 21},
        "block", 2
    }}, 
    // lamps
    {12, {
        "white_lamp",
        "white lamp", 
        "white_lamp",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {22, 22}
    }}, 

    {13, {
        "red_lamp",
        "red lamp", 
        "red_lamp",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {23, 23}
    }}, 
    {14, {
        "green_lamp",
        "green lamp", 
        "green_lamp",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {24, 24}
    }}, 
    {15, {
        "blue_lamp",
        "blue lamp", 
        "blue_lamp",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {25, 25}
    }}, 
    {16, {
        "stone_block",
        "stone block", 
        "stone_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {26, 27}
    }}, 
    {17, {
        "wooden_beam",
        "wooden beam", 
        "wooden_beam",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {28, 28},
        "block", 2
    }}, 
    {18, {
        "wooden_trapdoor",
        "wooden trapdoor", 
        "wooden_trapdoor",

        8*3, 8*3,
        64,
        0,
        "block",
        "trap_door",
        {29, 43},
        "block", 2
    }}, 
    {19, {
        "hoe",
        "hoe", 
        "hoe",

        10.5*3, 10.5*3,
        1,
        132,
        "tool",
        "",
        {0, 0},
        "2d", 2.5
    }}, 
    {20, {
        "wheat_seeds",
        "wheat seeds", 
        "wheat_seeds",

        11*3, 11*3,
        16,
        0,
        "block",
        "block",
        {47, 47},
        "2d", 2.5
    }}, 
    {21, {
        "storage_box",
        "storage box", 
        "storage_box",

        8*3, 8*3,
        16,
        0,
        "block",
        "pipe",
        {51, 53},
    }},
    {22, {
        "leaves_block",
        "leaves block", 
        "leaves_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {54, 57},
    }}, 
    {23, {
        "wheat",
        "wheat", 
        "wheat",

        11*3, 11*3,
        16,
        0,
        "item",
        "",
        {0, 0},
        "2d", 2.5
    }}, 
    {24, {
        "door",
        "door", 
        "door",

        11*3, 11*3,
        1,
        0,
        "block",
        "door",
        {62, 65},
        "2d", 2.5
    }}, 
    {25, {
        "grayed_stone_block",
        "grayed stone block", 
        "grayed_stone_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {66, 67}
    }},
    
    {26, {
        "stone_slab",
        "stone slab", 
        "stone_slab",

        8*3, 8*3,
        64,
        0,
        "block",
        "slab",
        {68, 69}
    }}, 
    {27, {
        "wooden_slab",
        "wooden slab", 
        "wooden_slab",

        8*3, 8*3,
        64,
        0,
        "block",
        "slab",
        {70, 71}
    }}, 
    {28, {
        "gravel_block",
        "gravel block", 
        "gravel_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {72, 75}
    }},
    {29, {
        "bucket",
        "bucket", 
        "bucket",

        11*3, 11*3,
        1,
        0,
        "item",
        "",
        {0, 0},
        "2d", 2.5
    }}, 
    {30, {
        "water_bucket",
        "water bucket", 
        "water_bucket",

        11*3, 11*3,
        1,
        0,
        "block",
        "block",
        {6, 6},
        "2d", 2.5
    }}, 
    {31, {
        "lava_bucket",
        "lava bucket", 
        "lava_bucket",

        11*3, 11*3,
        1,
        0,
        "block",
        "block",
        {76, 76},
        "2d", 2.5
    }}, 
    {32, {
        "obsidian_block",
        "obsidian block", 
        "obsidian_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {77, 80}
    }},
    {33, {
        "dry_sponge_block",
        "dry sponge block", 
        "dry_sponge_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {81, 81}
    }},
    {34, {
        "wet_sponge_block",
        "wet sponge block", 
        "wet_sponge_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {82, 82}
    }},
    {35, {
        "tnt_block",
        "tnt block", 
        "tnt_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {83, 83}
    }},
    {36, {
        "stone_column",
        "stone column", 
        "stone_column",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {84, 84}
    }},

    {37, {
        "stick",
        "stick", 
        "stick",

        10.5*3, 10.5*3,
        64,
        0,
        "item",
        "",
        {0, 0},
        "2d", 2.5
    }}, 
    {38, {
        "wooden_pickaxe",
        "wooden pickaxe", 
        "wooden_pickaxe",

        10.5*3, 10.5*3,
        1,
        600,
        "tool",
        "",
        {0, 0},
        "2d", 2.5,
        3,
    }},  
    {39, {
        "stone_pickaxe",
        "stone pickaxe", 
        "stone_pickaxe",

        10.5*3, 10.5*3,
        1,
        1300,
        "tool",
        "",
        {0, 0},
        "2d", 2.5,
        5,
    }},  
    {40, {
        "iron_pickaxe",
        "iron pickaxe", 
        "iron_pickaxe",

        10.5*3, 10.5*3,
        1,
        2500,
        "tool",
        "",
        {0, 0},
        "2d", 2.5,
        7,
    }},
    {41, {
        "iron_ingot",
        "iron ingot", 
        "iron_ingot",

        10.5*3, 10.5*3,
        64,
        0,
        "item",
        "",
        {0, 0},
        "2d", 2.5,
    }}, 
    {42, {
        "coal",
        "coal", 
        "coal",

        10.5*3, 10.5*3,
        64,
        0,
        "item",
        "",
        {0, 0},
        "2d", 2.5,
    }},    

    // ores
    {43, {
        "coal_ore_block",
        "coal_ore block", 
        "coal_ore_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {85, 86}
    }},
    {44, {
        "iron_ore_block",
        "iron_ore block", 
        "iron_ore_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {87, 88}
    }},
    {45, {
        "rose",
        "rose", 
        "rose",

        10.5*3, 10.5*3,
        64,
        0,
        "block",
        "block",
        {89, 89},
        "2d", 2.5,
    }},
    {46, {
        "granite_block",
        "granite block", 
        "granite_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "rand",
        {90, 91}
    }},

    {47, {
        "crafter_block",
        "crafter block", 
        "crafter_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "block",
        {92, 92}
    }},
    {48, {
        "fire_wood_block",
        "fire wood block", 
        "fire_wood_block",

        8*3, 8*3,
        1,
        0,
        "block",
        "rand",
        {93, 93}
    }},
    {49, {
        "lighter",
        "lighter", 
        "lighter",

        10.5*3, 10.5*3,
        1,
        0,
        "item",
        "",
        {0, 0},
        "2d", 2.5, 1,
        {84, 71, 53}
    }}, 
    {50, {
        "burnt_wood_block",
        "burnt wood block", 
        "burnt_wood_block",

        8*3, 8*3,
        64,
        0,
        "block",
        "pipe",
        {94, 96}
    }},
};


map <string, uint8_t> item_name_to_item_id = {};