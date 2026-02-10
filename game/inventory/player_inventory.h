#include <string>
#include <iostream>
#include <cstdint>
#include <array>
#include <vector>
#include <map>

#include "../../inc/SDL.h"
#include "../../inc/SDL_image.h"

#include "../config.h"
#include "../common/types.h"
#include "../common/text_draw.h"
#include "../common/entity_models.h"

#include "../world/player.h"
#include "../world/entity/entity.h"

#include "items_loader.h"
#include "crafts_recipes.h"


using namespace std; 

#ifndef PLAYER_INVENTORY_H
#define PLAYER_INVENTORY_H


class PlayerInventory {
public:
    map <string, SDL_Texture*> all_textures;

    // hotbar and slots
    int slot_w = 12*3;
    int slot_h = 12*3;

    SDL_Texture* slot_t;

    SDL_Rect left_hand_slot_rect;

    SDL_Texture* hotbar_t;
    SDL_Rect hotbar_rect;

    int hotbar_w = slot_w*9;
    int hotbar_h = slot_h;

    SDL_Texture* slot_selector_t;
    SDL_Rect slot_selector_rect;

    int slot_selector_w = 6*3;
    int slot_selector_h = 3*3;

    int slot_selector_y_offset = 2;

    // crafter
    int crafter_x, crafter_y;

    InventorySlot crafter_slots[2][2];

    SDL_Rect crafter_result_slot_rect;
    InventorySlot crafter_result_slot;
    InventoryItemData* crafter_result_slot_data = nullptr;

    // block crafter
    int block_crafter_x, block_crafter_y;

    InventorySlot block_crafter_slots[3][3];

    SDL_Rect block_crafter_result_slot_rect;
    InventorySlot block_crafter_result_slot;
    InventoryItemData* block_crafter_result_slot_data = nullptr;

    // selected slot ind and other 
    InventorySlot grabbed_item;
    InventoryItemData* grabbed_item_data = nullptr;
    string selected_slot_title = "";

    InventorySlot empty_slot = {0, 0, 0};

    int current_slot_ind = 0;
    
    InventorySlot* current_slot;
    InventoryItemData* current_slot_data = nullptr;
    BlockLight* current_slot_block_light = nullptr;

    float show_current_slot_cooldown = 0;

    InventorySlot hotbar_slots[9];

    InventorySlot left_hand_slot;
    InventoryItemData* left_hand_slot_data = nullptr;
    BlockLight* left_hand_slot_block_light = nullptr;

    int bag_slots_w = 9;
    int bag_slots_h = 3;

    InventorySlot bag_slots[27];

    int bag_x = 0;
    int bag_y = 0;

    int storage_x = 0;
    int storage_y = 0;

    int storage_slots_w = 9;
    int storage_slots_h = 5;

    uint16_t current_storage_id = 0;

    StorageBoxInv* current_storage = nullptr;

    bool on_right_mb = false;
    bool on_left_mb = false;
    bool on_shift = false;
    bool on_slot_change = false;

    // all items slots
    int all_items_count = 50;
    InventorySlot all_items_slots[50];

    bool in_storage_inv = false;
    bool in_block_crafter = false;

    PlayerInventory(int sc_w, int sc_h);

    void set_hotbar_on_bottom(int sc_w, int sc_h);
    void set_hotbar_on_top(int sc_w, int sc_h);

    void load_all_textures(SDL_Renderer* renderer);
    void load_texture(SDL_Renderer* renderer, string name, string path);

    void update_current_slot(int sc_w, int sc_h);
    void clear_current_slot();

    void controls(SDL_Event& event, vector<ItemDrop>& all_items_drops, Player& player, int sc_w, int sc_h);

    void update(Player& player, vector<ItemDrop>& all_items_drops, vec2 mpos, int sc_w, int sc_h, float dt);

    // interactions between invs
    bool all_items_interaction(vec2 mpos, int sc_w, int sc_h);
    bool hotbar_items_interaction(vec2 mpos, int sc_w, int sc_h);
    bool left_hand_interaction(vec2 mpos, int sc_w, int sc_h);

    bool bag_items_interaction(vec2 mpos, int sc_w, int sc_h);
    bool current_storage_interaction(vec2 mpos, int sc_w, int sc_h);
    bool block_crafter_interactions(vec2 mpos, int sc_w, int sc_h);

    bool crafter_interactions(vec2 mpos, int sc_w, int sc_h);

    // movings items
    bool move_item_to_bag(InventorySlot& move_item, InventoryItemData& move_item_data);
    bool move_item_to_hotbar(InventorySlot& move_item, InventoryItemData& move_item_data);
    bool move_item_to_current_storage(InventorySlot& move_item, InventoryItemData& move_item_data);
    bool move_item_to_player_inventory(InventorySlot& move_item, InventoryItemData& move_item_data, bool check_in_bag);

    void draw_slot(SDL_Renderer* renderer, TextDraw& text_draw, SDL_Rect& draw_rect, InventorySlot& slot_data, InventoryItemData* item_data);

    void draw(SDL_Renderer* renderer, Player& player, TextDraw& text_draw, vec2 mpos, int sc_w, int sc_h);
};


#endif