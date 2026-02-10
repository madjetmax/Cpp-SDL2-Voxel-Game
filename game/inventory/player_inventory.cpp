#include "player_inventory.h"


PlayerInventory::PlayerInventory(int sc_w, int sc_h) {
    // load rects
    int x = sc_w / 2 - hotbar_w / 2;
    int y = sc_h - hotbar_h - (slot_selector_h + slot_selector_y_offset * 2);
    hotbar_rect = {x, y, hotbar_w, hotbar_h};

    // set left hand slot rect
    left_hand_slot_rect = {int(x - slot_w * 1.5), y, slot_w, slot_h};

    //      endge of the hotbar        centering in slot                add current slot ind as offset
    x = sc_w / 2 - (hotbar_w / 2) + (slot_w / 2 - slot_selector_w / 2) + (current_slot_ind * slot_w);
    y = sc_h - (slot_selector_h + slot_selector_y_offset);
    slot_selector_rect = {x, y, slot_selector_w, slot_selector_h};
    
    // set bag top left pos
    bag_x = sc_w / 2 - hotbar_w / 2;
    bag_y = sc_h / 2 - (hotbar_h * (bag_slots_h - 2)) / 2;

    // set storage top left pos
    storage_x = sc_w / 2 - hotbar_w / 2;
    storage_y = bag_y - ((storage_slots_h + 0.3) * hotbar_h);

    // set crafter pos
    crafter_x = sc_w / 2 + slot_w * 1;
    crafter_y = bag_y - slot_h * 2.5;

    crafter_result_slot_rect.w = slot_w;
    crafter_result_slot_rect.h = slot_h;

    crafter_result_slot_rect.x = crafter_x + slot_w * 2.5;
    crafter_result_slot_rect.y = crafter_y + slot_w * 0.5;

    // set block crafter pos
    block_crafter_x = sc_w / 2 - slot_w * 2.5;
    block_crafter_y = bag_y - slot_h * 3.5;

    block_crafter_result_slot_rect.w = slot_w;
    block_crafter_result_slot_rect.h = slot_h;

    block_crafter_result_slot_rect.x = block_crafter_x + slot_w * 4.5;
    block_crafter_result_slot_rect.y = block_crafter_y + slot_w * 1;

    update_current_slot(sc_w, sc_h);

    for (size_t i = 1; i <= all_items_count; i++)
    {
        InventorySlot& slot = all_items_slots[i-1];
        slot.item_id = i;
        InventoryItemData& item_data = all_items_data[i];

        slot.items_count = item_data.max_stack;
        slot.durability = item_data.max_durability;
    }
    
    // * load item name to item id
    for (auto item = all_items_data.begin(); item != all_items_data.end(); item++) {
        item_name_to_item_id[item->second.name] = item->first;
    }


    // * get random hotbar slot and set it as ligher
    int rand_hotbar_slot_ind = randint(0, 7);
    hotbar_slots[rand_hotbar_slot_ind] = {49, 1, 0}; // set lighter
}

void PlayerInventory::set_hotbar_on_bottom(int sc_w, int sc_h) {
    hotbar_rect.y = sc_h - hotbar_h - (slot_selector_h + slot_selector_y_offset * 2);

    left_hand_slot_rect.y = hotbar_rect.y;
}

void PlayerInventory::set_hotbar_on_top(int sc_w, int sc_h) {
    hotbar_rect.y = bag_y + (hotbar_h * (bag_slots_h + 0.5));

    left_hand_slot_rect.y = hotbar_rect.y;
}

void PlayerInventory::load_texture(SDL_Renderer* renderer, string name, string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, ((path.c_str())));
    
    all_textures[name] = texture;
}

void PlayerInventory::load_all_textures(SDL_Renderer* renderer) {
    string base_folder = "game/assets/textures/inventory/";
    string blocks_folder = "game/assets/textures/blocks/";
    // base
    load_texture(renderer, "slot", base_folder + "slot.png");
    load_texture(renderer, "hotbar", base_folder + "hotbar.png");
    load_texture(renderer, "slot_selector", base_folder + "slot_selector.png");

    // other
    load_texture(renderer, "grass_block", blocks_folder + "grass/side.png");
    load_texture(renderer, "dirt_block", blocks_folder + "grass/bottom.png");
    load_texture(renderer, "water_block", blocks_folder + "water/top.png");
    load_texture(renderer, "lava_block", blocks_folder + "lava/top.png");
    load_texture(renderer, "sand_block", blocks_folder + "sand/side.png");
    
    load_texture(renderer, "cobblestone_block", blocks_folder + "cobblestone/side.png");
    load_texture(renderer, "cobblestone_slab", base_folder + "cobblestone_slab.png");
    load_texture(renderer, "glass_block", blocks_folder + "glass/side.png");
    load_texture(renderer, "wood_log", blocks_folder + "wood/side.png");
    load_texture(renderer, "wooden_planks", blocks_folder + "wooden_planks/side.png");
    load_texture(renderer, "wooden_slab", base_folder + "wooden_slab.png");

    load_texture(renderer, "torch", blocks_folder + "torch/side.png");
    // lamps
    load_texture(renderer, "white_lamp", base_folder + "white_lamp.png");
    load_texture(renderer, "red_lamp", base_folder + "red_lamp.png");
    load_texture(renderer, "green_lamp", base_folder + "green_lamp.png");
    load_texture(renderer, "blue_lamp", base_folder + "blue_lamp.png");

    load_texture(renderer, "stone_block", blocks_folder + "stone/side.png");
    load_texture(renderer, "stone_slab", base_folder + "stone_slab.png");
    load_texture(renderer, "grayed_stone_block", blocks_folder + "grayed_stone/side.png");
    load_texture(renderer, "granite_block", blocks_folder + "granite/side.png");

    load_texture(renderer, "wooden_beam", base_folder + "wooden_beam.png");
    load_texture(renderer, "stone_column", base_folder + "stone_column.png");


    load_texture(renderer, "storage_box", blocks_folder + "barrel/top.png");

    load_texture(renderer, "leaves_block", blocks_folder + "leaves/side.png");

    // wooden trapdoor
    load_texture(renderer, "wooden_trapdoor", blocks_folder + "wooden_trapdoor/top.png");

    // gravel
    load_texture(renderer, "gravel_block", blocks_folder + "gravel/side.png");
    // obsidian
    load_texture(renderer, "obsidian_block", blocks_folder + "obsidian/side.png");

    // sponges
    load_texture(renderer, "dry_sponge_block", blocks_folder + "sponge/dry_side.png");
    load_texture(renderer, "wet_sponge_block", blocks_folder + "sponge/wet_side.png");

    // tnt
    load_texture(renderer, "tnt_block", blocks_folder + "tnt/side.png");

    // ores
    load_texture(renderer, "coal_ore_block", blocks_folder + "ores/coal_side.png");
    load_texture(renderer, "iron_ore_block", blocks_folder + "ores/iron_side.png");

    // crafter
    load_texture(renderer, "crafter_block", blocks_folder + "crafter/top.png");

    // fire wood
    load_texture(renderer, "fire_wood_block", blocks_folder + "fire_wood/side.png");

    // burnt wood
    load_texture(renderer, "burnt_wood_block", blocks_folder + "burnt_wood/side.png");



    // set images for quick access
    slot_t = all_textures["slot"];
    hotbar_t = all_textures["hotbar"];
    slot_selector_t = all_textures["slot_selector"];
}

void PlayerInventory::update_current_slot(int sc_w, int sc_h) {
    // * update selector rect
    //      endge of the hotbar        centering in slot                add current slot ind as offset
    slot_selector_rect.x = sc_w / 2 - (hotbar_w / 2) + (slot_w / 2 - slot_selector_w / 2) + (current_slot_ind * slot_w);
    // * update data
    current_slot = &hotbar_slots[current_slot_ind];
    // set data
    if (current_slot->item_id != 0) {
        current_slot_data = &all_items_data[current_slot->item_id];
        // set block light
        if (current_slot_data->type == "block" || current_slot_data->type == "torch") {
            FullBlockData& block_data = all_blocks_full_data[current_slot_data->place_blocks_ids_range[0]];
            if (block_data.light.r > 0 || block_data.light.g > 0 || block_data.light.b > 0) {
                current_slot_block_light = &block_data.light;
            } else {
                current_slot_block_light = nullptr;
            }
        } else {
            current_slot_block_light = nullptr;
        }
    }
    // set empty data
    else {
        current_slot_data = nullptr;
        current_slot_block_light = nullptr;
    }

    // set cooldown to show current slot
    show_current_slot_cooldown = 100;
}

void PlayerInventory::clear_current_slot() {
    hotbar_slots[current_slot_ind] = empty_slot;
    current_slot_data = nullptr;
    current_slot_block_light = nullptr;
}

void PlayerInventory::controls(SDL_Event& event, vector<ItemDrop>& all_items_drops, Player& player, int sc_w, int sc_h) {
    // update current slot with mouse wheel
    if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y == -1) {
            current_slot_ind++;
            on_slot_change = true;
        }
        if (event.wheel.y == 1) {
            current_slot_ind--;
            on_slot_change = true;
        }
        // limit
        if (current_slot_ind > 8) {
            current_slot_ind = 0;
        }
        if (current_slot_ind < 0) {
            current_slot_ind = 8;
        }

        update_current_slot(sc_w, sc_h);
    }

    // mouse clicks 
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (player.in_inventory) {
            if (int(event.button.button) == 1) {
                on_left_mb = true;
            }

            if (int(event.button.button) == 3) {
                on_right_mb = true;
            }
        }
    }
    
    if (event.type == SDL_KEYDOWN) {
        int last_current_slot_ind = current_slot_ind;
        // set current slot with num keys
        if (event.key.keysym.sym == SDLK_1) current_slot_ind = 0;
        if (event.key.keysym.sym == SDLK_2) current_slot_ind = 1;
        if (event.key.keysym.sym == SDLK_3) current_slot_ind = 2;
        if (event.key.keysym.sym == SDLK_4) current_slot_ind = 3;
        if (event.key.keysym.sym == SDLK_5) current_slot_ind = 4;
        if (event.key.keysym.sym == SDLK_6) current_slot_ind = 5;
        if (event.key.keysym.sym == SDLK_7) current_slot_ind = 6;
        if (event.key.keysym.sym == SDLK_8) current_slot_ind = 7;
        if (event.key.keysym.sym == SDLK_9) current_slot_ind = 8;

        if (current_slot_ind != last_current_slot_ind) {
            update_current_slot(sc_w, sc_h);
        }
        // open close inv
        if (event.key.keysym.sym == SDLK_e) {
            // change hotbar pos
            if (player.in_inventory) set_hotbar_on_top(sc_w, sc_h);
            else set_hotbar_on_bottom(sc_w, sc_h);

            in_storage_inv = false;
            in_block_crafter = false;

            if (!player.in_inventory) {
                // * drop crafter items
                // slots
                for (size_t x = 0; x < 2; x++)
                for (size_t y = 0; y < 2; y++)
                {
                    InventorySlot& slot = crafter_slots[x][y];
                    if (slot.item_id != 0) {
                        ItemDrop new_item_drop;
                        new_item_drop.add_item = slot;
                        new_item_drop.x = player.x + 25 * -player.angle_y_sin;
                        new_item_drop.y = player.y - 25;
                        new_item_drop.z = player.z + 25 * player.angle_y_cos;

                        // set just dropped
                        new_item_drop.just_dropded_cooldown = 20;
                        new_item_drop.pick_up_able = false;

                        // set inertion
                        float inertion = 10;
                        new_item_drop.inert_x = inertion * -player.angle_y_sin;
                        new_item_drop.inert_z = inertion * player.angle_y_cos;

                        new_item_drop.full_model_id = item_id_to_entity_id[slot.item_id];
                        all_items_drops.push_back(new_item_drop);
                    }

                    // set empty
                    crafter_slots[x][y] = empty_slot;
                }
                // set result slot empty
                if (crafter_result_slot_data) {
                    crafter_result_slot = empty_slot;
                    crafter_result_slot_data = nullptr;
                }
            }
        }
        
        // drop item
        if (event.key.keysym.sym == SDLK_q) {
            if (current_slot_data) {
                ItemDrop new_item_drop;
                new_item_drop.add_item = *current_slot;
                new_item_drop.add_item.items_count = 1;
                new_item_drop.x = player.x + 25 * -player.angle_y_sin;
                new_item_drop.y = player.y - 25;
                new_item_drop.z = player.z + 25 * player.angle_y_cos;

                // set just dropped
                new_item_drop.just_dropded_cooldown = 50;
                new_item_drop.pick_up_able = false;

                // set inertion
                float inertion = 10;
                new_item_drop.inert_x = inertion * -player.angle_y_sin;
                new_item_drop.inert_z = inertion * player.angle_y_cos;

                new_item_drop.full_model_id = item_id_to_entity_id[current_slot->item_id];
                all_items_drops.push_back(new_item_drop);
                // reduce count
                current_slot->items_count--;
                if (current_slot->items_count <= 0) {
                    hotbar_slots[current_slot_ind] = empty_slot;
                }
                update_current_slot(sc_w, sc_h);
            }
        }

        // swap left hand slot
        if (event.key.keysym.sym == SDLK_f) {
            if (!player.in_inventory) {
                // left hand empty
                if (left_hand_slot.item_id == 0) {
                    if (current_slot_data) {
                        left_hand_slot = *current_slot;
                        left_hand_slot_data = &all_items_data[left_hand_slot.item_id];
                        // set light
                        if (left_hand_slot_data->type == "block") {
                            left_hand_slot_block_light = &all_blocks_full_data[
                                left_hand_slot_data->place_blocks_ids_range[0]
                            ].light;
                        // clear light
                        } else {
                            left_hand_slot_block_light = nullptr;
                        }

                        // set cur slot empty
                        hotbar_slots[current_slot_ind] = empty_slot;
                        update_current_slot(sc_w, sc_h);
                    }
                }
                // left hand has item
                else {
                    // cur slot empty
                    if (!current_slot_data) {
                        hotbar_slots[current_slot_ind] = left_hand_slot;
                        update_current_slot(sc_w, sc_h);
                        
                        // clear left hand 
                        left_hand_slot = empty_slot;
                        left_hand_slot_data = nullptr;
                        left_hand_slot_block_light = nullptr;

                    }

                    // swap items
                    else {
                        InventorySlot temp_left_hand = left_hand_slot;
                        // set left hand
                        left_hand_slot = *current_slot;
                        left_hand_slot_data = &all_items_data[left_hand_slot.item_id];
                        // set block light
                        if (left_hand_slot_data->type == "block") {
                            left_hand_slot_block_light = &all_blocks_full_data[
                                left_hand_slot_data->place_blocks_ids_range[0]
                            ].light;
                        // clear light
                        } else {
                            left_hand_slot_block_light = nullptr;
                        }
                        // set current slot
                        hotbar_slots[current_slot_ind] = temp_left_hand;
                        update_current_slot(sc_w, sc_h);
                    }
                }
            }
        }
        if (event.key.keysym.sym == SDLK_LSHIFT) {
            on_shift = true;
        }
    }

    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_LSHIFT) {
            on_shift = false;
        }
    }
}

// * interactions
bool PlayerInventory::all_items_interaction(vec2 mpos, int sc_w, int sc_h) {
    // set selected slot
    // set mouse pos on slot
    int start_x = sc_w - (slot_w * 4);

    int mpos_slot_x = int((mpos.x  - start_x) / slot_w);
    int mpos_slot_y = int(mpos.y / slot_h);

    int slot_ind = 0;
    InventorySlot* selected_slot = nullptr;

    if (mpos.x - start_x >= 0) {
        for (size_t y = 0; y < 20; y++) 
        for (size_t x = 0; x < 4; x++) {
            // check mouse pos on slot
            if (mpos_slot_x == x && mpos_slot_y == y && slot_ind < all_items_count) {
                selected_slot = &all_items_slots[slot_ind];

                if (selected_slot->item_id == 0) {
                    selected_slot = nullptr;
                } 
                // set title
                else {
                    InventoryItemData& slot_item_data = all_items_data[selected_slot->item_id];
                    selected_slot_title = slot_item_data.title;
                }
                break;
            }
            slot_ind++;
        }
    }
    // check grab
    if (on_left_mb) {
        if (!grabbed_item_data) {
            if (selected_slot) {
                grabbed_item = *selected_slot;
                // get data
                grabbed_item_data = &all_items_data[grabbed_item.item_id];
                return true;
            }
        }
    } 
    return false;
}

bool PlayerInventory::hotbar_items_interaction(vec2 mpos, int sc_w, int sc_h) {
    // set selected slot
    // set mouse pos on slot
    int start_x = hotbar_rect.x;
    int start_y = hotbar_rect.y;

    int mpos_slot_x = int((mpos.x - start_x) / slot_w);
    int mpos_slot_y = int((mpos.y - start_y) / slot_h);

    int slot_ind = 0;
    InventorySlot* selected_slot = nullptr;

    if (mpos.x - start_x >= 0 && mpos.y - start_y >= 0) {
        for (size_t x = 0; x < 9; x++) {
            // check mouse pos on slot
            if (mpos_slot_x == x && mpos_slot_y == 0 && slot_ind <= 8) {
                selected_slot = &hotbar_slots[slot_ind];

                // set title
                if (selected_slot->item_id != 0) {
                    InventoryItemData& slot_item_data = all_items_data[selected_slot->item_id];
                    selected_slot_title = slot_item_data.title;
                }

                break;
            }
            slot_ind++;
        }
    }
    if (on_left_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                grabbed_item = *selected_slot;
                // get data
                grabbed_item_data = &all_items_data[grabbed_item.item_id];
                // set empty
                hotbar_slots[slot_ind] = empty_slot;

                update_current_slot(sc_w, sc_h);
                
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // set to empty slot
                if (selected_slot->item_id == 0) {
                    hotbar_slots[slot_ind] = grabbed_item;

                    // clear grabbed
                    grabbed_item = empty_slot;
                    grabbed_item_data = nullptr;

                    update_current_slot(sc_w, sc_h);
                }
                // add if same as grabbed 
                else if (selected_slot->item_id == grabbed_item.item_id && selected_slot_item_data.max_stack > 1) {
                    bool interacted = false;
                    hotbar_slots[slot_ind].items_count += grabbed_item.items_count;
                    
                    // add remainder to grabbed
                    if (int(hotbar_slots[slot_ind].items_count) > selected_slot_item_data.max_stack) {
                        grabbed_item.items_count = hotbar_slots[slot_ind].items_count - selected_slot_item_data.max_stack;
                        hotbar_slots[slot_ind].items_count = selected_slot_item_data.max_stack;
                        interacted = true;
                    }
                    // clear grabbed
                    else {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }
                    update_current_slot(sc_w, sc_h);

                    return interacted;
                }
                // swap
                else if (selected_slot->item_id != grabbed_item.item_id || selected_slot_item_data.max_stack == 1) {
                    InventorySlot temp_grabbed = grabbed_item;
                    grabbed_item = hotbar_slots[slot_ind];
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];

                    hotbar_slots[slot_ind] = temp_grabbed;

                    update_current_slot(sc_w, sc_h);

                    return true;
                }
            } 
        } 

        update_current_slot(sc_w, sc_h);
    }

    if (on_right_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                // get data
                grabbed_item = *selected_slot;
                grabbed_item_data = &all_items_data[grabbed_item.item_id];

                // set half count 
                if (selected_slot->items_count % 2 == 0) {
                    grabbed_item.items_count /= 2;
                    hotbar_slots[slot_ind].items_count /= 2;
                } else {
                    // just set empty
                    if (hotbar_slots[slot_ind].items_count == 1) {
                        hotbar_slots[slot_ind] = empty_slot;
                    } 
                    // set grabbed count more by 1 
                    else {
                        hotbar_slots[slot_ind].items_count = uint8_t(float(hotbar_slots[slot_ind].items_count) / 2);
                        grabbed_item.items_count = uint8_t(float(grabbed_item.items_count) / 2 + 1.0f);
                    }
                }

                update_current_slot(sc_w, sc_h);
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // add to empty slot
                if (selected_slot->item_id == 0) {
                    hotbar_slots[slot_ind] = grabbed_item;
                    hotbar_slots[slot_ind].items_count = 1;

                    grabbed_item.items_count--;
                    
                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }
                // add to same as grabbed
                else if (selected_slot->item_id == grabbed_item.item_id) {
                    if (hotbar_slots[slot_ind].items_count < selected_slot_item_data.max_stack) {
                        hotbar_slots[slot_ind].items_count++;
                        grabbed_item.items_count--;
                    }

                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }
            }
        }

        update_current_slot(sc_w, sc_h);
    }
    // * move fast to bag
    if (on_shift && on_left_mb) {
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                if (in_storage_inv) {
                    move_item_to_current_storage(*selected_slot, selected_slot_item_data);
                } else {
                    move_item_to_bag(*selected_slot, selected_slot_item_data);
                }
            }
        }
        if (current_slot_ind == slot_ind) {
            update_current_slot(sc_w, sc_h);
        }
    }


    return false;
}

bool PlayerInventory::bag_items_interaction(vec2 mpos, int sc_w, int sc_h) {
    // set selected slot
    // set mouse pos on slot
    int start_x = bag_x;
    int start_y = bag_y;

    int mpos_slot_x = int((mpos.x - start_x) / slot_w);
    int mpos_slot_y = int((mpos.y - start_y) / slot_h);

    int slot_ind = 0;
    InventorySlot* selected_slot = nullptr;

    if (mpos.x - start_x >= 0 && mpos.y - start_y >= 0) {
        for (int y = 0; y < bag_slots_h; y++)
        for (int x = 0; x < bag_slots_w; x++) {
        
            // check mouse pos on slot
            if (mpos_slot_x == x && mpos_slot_y == y && slot_ind <= bag_slots_w * bag_slots_h) {
                selected_slot = &bag_slots[slot_ind];

                // set title
                if (selected_slot->item_id != 0) {
                    InventoryItemData& slot_item_data = all_items_data[selected_slot->item_id];
                    selected_slot_title = slot_item_data.title;
                }
                break;
            }
            if (!selected_slot) {
                slot_ind++;
            }
        }
    }
    if (on_left_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                grabbed_item = *selected_slot;
                // get data
                grabbed_item_data = &all_items_data[grabbed_item.item_id];
                // set empty
                bag_slots[slot_ind] = empty_slot;
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // set as grabbed
                if (selected_slot->item_id == 0) {
                    bag_slots[slot_ind] = grabbed_item;

                    // clear grabbed
                    grabbed_item = empty_slot;
                    grabbed_item_data = nullptr;
                    update_current_slot(sc_w, sc_h);
                }
                // add if same as grabbed 
                else if (selected_slot->item_id == grabbed_item.item_id && selected_slot_item_data.max_stack > 1) {
                    bool interacted = false;
                    bag_slots[slot_ind].items_count += grabbed_item.items_count;
                    
                    // add remainder to grabbed
                    if (int(bag_slots[slot_ind].items_count) > selected_slot_item_data.max_stack) {
                        grabbed_item.items_count = bag_slots[slot_ind].items_count - selected_slot_item_data.max_stack;
                        bag_slots[slot_ind].items_count = selected_slot_item_data.max_stack;
                        interacted = true;
                    }
                    // clear grabbed
                    else {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }
                    update_current_slot(sc_w, sc_h);

                    return interacted;
                }
                // swap
                else if (selected_slot->item_id != grabbed_item.item_id || selected_slot_item_data.max_stack == 1) {
                    InventorySlot temp_grabbed = grabbed_item;
                    grabbed_item = bag_slots[slot_ind];
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];

                    bag_slots[slot_ind] = temp_grabbed;
                    return true;
                }
            } 
        } 
    }

    if (on_right_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                // get data
                grabbed_item = *selected_slot;
                grabbed_item_data = &all_items_data[grabbed_item.item_id];

                // set half count 
                if (selected_slot->items_count % 2 == 0) {
                    grabbed_item.items_count /= 2;
                    bag_slots[slot_ind].items_count /= 2;
                } else {
                    // just set empty
                    if (bag_slots[slot_ind].items_count == 1) {
                        bag_slots[slot_ind] = empty_slot;
                    } 
                    // set grabbed count more by 1 
                    else {
                        bag_slots[slot_ind].items_count = uint8_t(float(bag_slots[slot_ind].items_count) / 2);
                        grabbed_item.items_count = uint8_t(float(grabbed_item.items_count) / 2 + 1.0f);
                    }
                }

                update_current_slot(sc_w, sc_h);
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // add to empty slot
                if (selected_slot->item_id == 0) {
                    bag_slots[slot_ind] = grabbed_item;
                    bag_slots[slot_ind].items_count = 1;

                    grabbed_item.items_count--;
                    
                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }
                // add to same as grabbed
                else if (selected_slot->item_id == grabbed_item.item_id) {
                    if (bag_slots[slot_ind].items_count < selected_slot_item_data.max_stack) {
                        bag_slots[slot_ind].items_count++;
                        grabbed_item.items_count--;
                    }

                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }
            }
        }
    }

    // * move fast to bag or current storage
    if (on_shift && on_left_mb) {
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                if (in_storage_inv) {
                    move_item_to_current_storage(*selected_slot, selected_slot_item_data);
                } else {
                    move_item_to_hotbar(*selected_slot, selected_slot_item_data);
                }
            }
        }
        update_current_slot(sc_w, sc_h);
    }

    return false;
}

bool PlayerInventory::current_storage_interaction(vec2 mpos, int sc_w, int sc_h) {
    // set selected slot
    // set mouse pos on slot
    int start_x = storage_x;
    int start_y = storage_y;

    int mpos_slot_x = int((mpos.x - start_x) / slot_w);
    int mpos_slot_y = int((mpos.y - start_y) / slot_h);

    int slot_ind = 0;
    InventorySlot* selected_slot = nullptr;

    if (mpos.x - start_x >= 0 && mpos.y - start_y >= 0) {
        for (int y = 0; y < storage_slots_h; y++)
        for (int x = 0; x < storage_slots_w; x++) {
        
            // check mouse pos on slot
            if (mpos_slot_x == x && mpos_slot_y == y && slot_ind <= storage_slots_w * storage_slots_h) {
                selected_slot = &current_storage->slots[slot_ind];

                // set title
                if (selected_slot->item_id != 0) {
                    InventoryItemData& slot_item_data = all_items_data[selected_slot->item_id];
                    selected_slot_title = slot_item_data.title;
                }
                break;
            }
            if (!selected_slot) {
                slot_ind++;
            }
        }
    }
    if (on_left_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                grabbed_item = *selected_slot;
                // get data
                grabbed_item_data = &all_items_data[grabbed_item.item_id];
                // set empty
                current_storage->slots[slot_ind] = empty_slot;
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // set as grabbed
                if (selected_slot->item_id == 0) {
                    current_storage->slots[slot_ind] = grabbed_item;

                    // clear grabbed
                    grabbed_item = empty_slot;
                    grabbed_item_data = nullptr;

                    if (current_slot_ind == slot_ind) {
                        update_current_slot(sc_w, sc_h);
                    }
                }
                // add if same as grabbed 
                else if (selected_slot->item_id == grabbed_item.item_id && selected_slot_item_data.max_stack > 1) {
                    bool interacted = false;
                    current_storage->slots[slot_ind].items_count += grabbed_item.items_count;
                    
                    // add remainder to grabbed
                    if (int(current_storage->slots[slot_ind].items_count) > selected_slot_item_data.max_stack) {
                        grabbed_item.items_count = current_storage->slots[slot_ind].items_count - selected_slot_item_data.max_stack;
                        current_storage->slots[slot_ind].items_count = selected_slot_item_data.max_stack;
                        interacted = true;
                    }
                    // clear grabbed
                    else {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }
                    return interacted;
                }
                // swap
                else if (selected_slot->item_id != grabbed_item.item_id || selected_slot_item_data.max_stack == 1) {
                    InventorySlot temp_grabbed = grabbed_item;
                    grabbed_item = current_storage->slots[slot_ind];
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];

                    current_storage->slots[slot_ind] = temp_grabbed;

                    if (current_slot_ind == slot_ind) {
                        update_current_slot(sc_w, sc_h);
                    }

                    return true;
                }
            } 
        } 
    }

    if (on_right_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                // get data
                grabbed_item = *selected_slot;
                grabbed_item_data = &all_items_data[grabbed_item.item_id];

                // set half count 
                if (selected_slot->items_count % 2 == 0) {
                    grabbed_item.items_count /= 2;
                    current_storage->slots[slot_ind].items_count /= 2;
                } else {
                    // just set empty
                    if (current_storage->slots[slot_ind].items_count == 1) {
                        current_storage->slots[slot_ind] = empty_slot;
                    } 
                    // set grabbed count more by 1 
                    else {
                        current_storage->slots[slot_ind].items_count = uint8_t(float(current_storage->slots[slot_ind].items_count) / 2);
                        grabbed_item.items_count = uint8_t(float(grabbed_item.items_count) / 2 + 1.0f);
                    }
                }

                if (current_slot_ind == slot_ind) {
                    update_current_slot(sc_w, sc_h);
                }
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // add to empty slot
                if (selected_slot->item_id == 0) {
                    current_storage->slots[slot_ind] = grabbed_item;
                    current_storage->slots[slot_ind].items_count = 1;

                    grabbed_item.items_count--;
                    
                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    if (current_slot_ind == slot_ind) {
                        update_current_slot(sc_w, sc_h);
                    }
                }
                // add to same as grabbed
                else if (selected_slot->item_id == grabbed_item.item_id) {
                    if (current_storage->slots[slot_ind].items_count < selected_slot_item_data.max_stack) {
                        current_storage->slots[slot_ind].items_count++;
                        grabbed_item.items_count--;
                    }

                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    if (current_slot_ind == slot_ind) {
                        update_current_slot(sc_w, sc_h);
                    }
                }
            }
        }
    }

    // * move fast to bag
    if (on_shift && on_left_mb) {
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                move_item_to_player_inventory(*selected_slot, selected_slot_item_data, true);
            }
        }
        if (current_slot_ind == slot_ind) {
            update_current_slot(sc_w, sc_h);
        }
    }

    return false;
}


bool PlayerInventory::block_crafter_interactions(vec2 mpos, int sc_w, int sc_h) {
    int start_x = block_crafter_x;
    int start_y = block_crafter_y;

    int mpos_slot_x = int((mpos.x - start_x) / slot_w);
    int mpos_slot_y = int((mpos.y - start_y) / slot_h);

    int slot_ind_x = 0;
    int slot_ind_y = 0;
    InventorySlot* selected_slot = nullptr;
    // slots
    if (mpos.x - start_x >= 0 && mpos.y - start_y >= 0) {
        for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++) {
            
            // check mouse pos on slot
            if (mpos_slot_x == x && mpos_slot_y == y) {
                slot_ind_x = x;
                slot_ind_y = y;

                selected_slot = &block_crafter_slots[slot_ind_x][slot_ind_y];

                // set title
                if (selected_slot->item_id != 0) {
                    InventoryItemData& slot_item_data = all_items_data[selected_slot->item_id];
                    selected_slot_title = slot_item_data.title;
                }
                break;
            }
        }
    }
    if (on_left_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                grabbed_item = *selected_slot;
                // get data
                grabbed_item_data = &all_items_data[grabbed_item.item_id];
                // set empty
                block_crafter_slots[slot_ind_x][slot_ind_y] = empty_slot;
                
                // check recipe
                check_block_crafter_recipe(
                    block_crafter_slots, 
                    block_crafter_result_slot
                );
                if (block_crafter_result_slot.item_id != 0) {
                    block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                }
                else {
                    block_crafter_result_slot_data = nullptr;
                } 
                
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // set as grabbed
                if (selected_slot->item_id == 0) {
                    block_crafter_slots[slot_ind_x][slot_ind_y] = grabbed_item;

                    // clear grabbed
                    grabbed_item = empty_slot;
                    grabbed_item_data = nullptr;
                    update_current_slot(sc_w, sc_h);

                    // check recipe
                    check_block_crafter_recipe(
                        block_crafter_slots, 
                        block_crafter_result_slot
                    );
                    if (block_crafter_result_slot.item_id != 0) {
                        block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                    }
                    else {
                        block_crafter_result_slot_data = nullptr;
                    } 
                    
                }
                // add if same as grabbed 
                else if (selected_slot->item_id == grabbed_item.item_id && selected_slot_item_data.max_stack > 1) {
                    bool interacted = false;
                    block_crafter_slots[slot_ind_x][slot_ind_y].items_count += grabbed_item.items_count;
                    
                    // add remainder to grabbed
                    if (int(block_crafter_slots[slot_ind_x][slot_ind_y].items_count) > selected_slot_item_data.max_stack) {
                        grabbed_item.items_count = block_crafter_slots[slot_ind_x][slot_ind_y].items_count - selected_slot_item_data.max_stack;
                        block_crafter_slots[slot_ind_x][slot_ind_y].items_count = selected_slot_item_data.max_stack;
                        interacted = true;
                    }
                    // clear grabbed
                    else {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }
                    update_current_slot(sc_w, sc_h);

                    // check recipe
                    check_block_crafter_recipe(
                        block_crafter_slots, 
                        block_crafter_result_slot
                    );
                    if (block_crafter_result_slot.item_id != 0) {
                        block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                    }
                    else {
                        block_crafter_result_slot_data = nullptr;
                    } 

                    return interacted;
                }
                // swap
                else if (selected_slot->item_id != grabbed_item.item_id || selected_slot_item_data.max_stack == 1) {
                    InventorySlot temp_grabbed = grabbed_item;
                    grabbed_item = block_crafter_slots[slot_ind_x][slot_ind_y];
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];

                    block_crafter_slots[slot_ind_x][slot_ind_y]= temp_grabbed;
                    
                    // check recipe
                    check_block_crafter_recipe(
                        block_crafter_slots, 
                        block_crafter_result_slot
                    );
                    if (block_crafter_result_slot.item_id != 0) {
                        block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                    }
                    else {
                        block_crafter_result_slot_data = nullptr;
                    }
                    
                    return true;
                }

                
            } 
        } 
    }

    if (on_right_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                // get data
                grabbed_item = *selected_slot;
                grabbed_item_data = &all_items_data[grabbed_item.item_id];

                // set half count 
                if (selected_slot->items_count % 2 == 0) {
                    grabbed_item.items_count /= 2;
                    block_crafter_slots[slot_ind_x][slot_ind_y].items_count /= 2;
                } else {
                    // just set empty
                    if (block_crafter_slots[slot_ind_x][slot_ind_y].items_count == 1) {
                        block_crafter_slots[slot_ind_x][slot_ind_y] = empty_slot;
                    } 
                    // set grabbed count more by 1 
                    else {
                        block_crafter_slots[slot_ind_x][slot_ind_y].items_count = uint8_t(float(block_crafter_slots[slot_ind_x][slot_ind_y].items_count) / 2);
                        grabbed_item.items_count = uint8_t(float(grabbed_item.items_count) / 2 + 1.0f);
                    }
                }

                update_current_slot(sc_w, sc_h);

                // check recipe
                check_block_crafter_recipe(
                    block_crafter_slots, 
                    block_crafter_result_slot
                );
                if (block_crafter_result_slot.item_id != 0) {
                    block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                }
                else {
                    block_crafter_result_slot_data = nullptr;
                }

                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // add to empty slot
                if (selected_slot->item_id == 0) {
                    block_crafter_slots[slot_ind_x][slot_ind_y] = grabbed_item;
                    block_crafter_slots[slot_ind_x][slot_ind_y].items_count = 1;

                    grabbed_item.items_count--;
                    
                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }
                // add to same as grabbed
                else if (selected_slot->item_id == grabbed_item.item_id) {
                    if (block_crafter_slots[slot_ind_x][slot_ind_y].items_count < selected_slot_item_data.max_stack) {
                        block_crafter_slots[slot_ind_x][slot_ind_y].items_count++;
                        grabbed_item.items_count--;
                    }

                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }

                // check recipe
                check_block_crafter_recipe(
                    block_crafter_slots, 
                    block_crafter_result_slot
                );
                if (block_crafter_result_slot.item_id != 0) {
                    block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                }
                else {
                    block_crafter_result_slot_data = nullptr;
                }
            }
        }
    }

    // * move fast to bag or current storage
    if (on_shift && on_left_mb) {
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                move_item_to_player_inventory(*selected_slot, selected_slot_item_data, true);
                
                // check recipe
                check_block_crafter_recipe(
                    block_crafter_slots, 
                    block_crafter_result_slot
                );

                if (block_crafter_result_slot.item_id != 0) {
                    block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                }
                else {
                    block_crafter_result_slot_data = nullptr;
                }
            }
        }
        update_current_slot(sc_w, sc_h);
    }

    // * result slot
    mpos_slot_x = int((mpos.x - block_crafter_result_slot_rect.x) / slot_w);
    mpos_slot_y = int((mpos.y - block_crafter_result_slot_rect.y) / slot_h);
    
    // check if mouse on slot
    if ((mpos.x - block_crafter_result_slot_rect.x) >= 0 && (mpos.y - block_crafter_result_slot_rect.y) >= 0) {
        if (mpos_slot_x == 0 && mpos_slot_y == 0) {
    
            if (block_crafter_result_slot_data) {
                // set title
                selected_slot_title = block_crafter_result_slot_data->title;
            }
    
            // check grab
            if (on_left_mb && !on_shift) {
                if (!grabbed_item_data) {
                    if (block_crafter_result_slot.item_id != 0) {
                        grabbed_item = block_crafter_result_slot;
                        // get data
                        grabbed_item_data = &all_items_data[grabbed_item.item_id];
                        // set empty
                        block_crafter_result_slot = empty_slot;
                        block_crafter_result_slot_data = nullptr;
    
                        // reduce block crafter slots items coult
                        for (size_t x = 0; x < 3; x++)
                        for (size_t y = 0; y < 3; y++)
                        {
                            InventorySlot& crafter_slot = block_crafter_slots[x][y];
    
                            if (crafter_slot.item_id != 0 && crafter_slot.items_count > 0) {
                                crafter_slot.items_count--;
                                // clear slot
                                if (crafter_slot.items_count <= 0) {
                                    block_crafter_slots[x][y] = empty_slot;
                                }
                            } 
                        }
    
                        // check recipe
                        check_block_crafter_recipe(
                            block_crafter_slots, 
                            block_crafter_result_slot
                        );
    
                        if (block_crafter_result_slot.item_id != 0) {
                            block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                        }
                        else {
                            block_crafter_result_slot_data = nullptr;
                        }
    
                        return true;
                    }
                }
            }
    
            // * move fast to bag
            if (on_shift && on_left_mb) {
                if (!grabbed_item_data) {
                    if (block_crafter_result_slot.item_id != 0) {
                        move_item_to_player_inventory(block_crafter_result_slot, *block_crafter_result_slot_data, true);
    
                        // set empty
                        if (block_crafter_result_slot.items_count <= 0) {
                            block_crafter_result_slot = empty_slot;
                            block_crafter_result_slot_data = nullptr;
                        }

                        // reduce crafter slots items count
                        for (size_t x = 0; x < 3; x++)
                        for (size_t y = 0; y < 3; y++)
                        {
                            InventorySlot& crafter_slot = block_crafter_slots[x][y];
    
                            if (crafter_slot.item_id != 0 && crafter_slot.items_count > 0) {
                                crafter_slot.items_count--;
                                // clear slot
                                if (crafter_slot.items_count <= 0) {
                                    block_crafter_slots[x][y] = empty_slot;
                                }
                            } 
                        }
    
                        // check recipe
                        check_block_crafter_recipe(
                            block_crafter_slots, 
                            block_crafter_result_slot
                        );
    
                        if (block_crafter_result_slot.item_id != 0) {
                            block_crafter_result_slot_data = &all_items_data[block_crafter_result_slot.item_id];
                        }
                        else {
                            block_crafter_result_slot_data = nullptr;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// * interactions with other slots
bool PlayerInventory::left_hand_interaction(vec2 mpos, int sc_w, int sc_h) {
    int mpos_slot_x = int((mpos.x - left_hand_slot_rect.x) / slot_w);
    int mpos_slot_y = int((mpos.y - left_hand_slot_rect.y) / slot_h);

    // check if mouse on slot
    if (mpos_slot_x == 0 && mpos_slot_y == 0) {

        if (left_hand_slot_data) {
            // set title
            selected_slot_title = left_hand_slot_data->title;
        }

        // grab and put
        if (on_left_mb && !on_shift) {
            // check grab
            if (!grabbed_item_data) {
                if (left_hand_slot.item_id != 0) {
                    grabbed_item = left_hand_slot;
                    // get data
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];
                    // set empty
                    left_hand_slot = empty_slot;
                    left_hand_slot_data = nullptr;
                    left_hand_slot_block_light = nullptr;

                    return true;
                }
            }
            // check put
            else {
                if (grabbed_item_data) {
                    // set as grabbed
                    if (left_hand_slot.item_id == 0) {
                        left_hand_slot = grabbed_item;
                        left_hand_slot_data = &all_items_data[left_hand_slot.item_id];
                        if (left_hand_slot_data->type == "block") {
                            left_hand_slot_block_light = &all_blocks_full_data[
                                left_hand_slot_data->place_blocks_ids_range[0]
                            ].light;
                        }

                        // clear grabbed
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                        return true;
                    }
                    // add if same as grabbed 
                    else if (left_hand_slot.item_id == grabbed_item.item_id && left_hand_slot_data->max_stack > 1) {
                        bool interacted = false;
                        left_hand_slot.items_count += grabbed_item.items_count;
                        
                        // add remainder to grabbed
                        if (int(left_hand_slot.items_count) > left_hand_slot_data->max_stack) {
                            grabbed_item.items_count = left_hand_slot.items_count - left_hand_slot_data->max_stack;
                            left_hand_slot.items_count = left_hand_slot_data->max_stack;
                            interacted = true;
                        }
                        // clear grabbed
                        else {
                            grabbed_item = empty_slot;
                            grabbed_item_data = nullptr;
                        }
                        return interacted;
                    }
                    // swap
                    else if (left_hand_slot.item_id != grabbed_item.item_id || left_hand_slot_data->max_stack == 1) {
                        InventorySlot temp_grabbed = grabbed_item;
                        grabbed_item = left_hand_slot;
                        grabbed_item_data = &all_items_data[grabbed_item.item_id];

                        left_hand_slot = temp_grabbed;
                        left_hand_slot_data = &all_items_data[left_hand_slot.item_id];
                        if (left_hand_slot_data->type == "block") {
                            left_hand_slot_block_light = &all_blocks_full_data[
                                left_hand_slot_data->place_blocks_ids_range[0]
                            ].light;
                        }

                        return true;
                    }
                } 
            } 
        }

        if (on_right_mb && !on_shift) {
            // check grab
            if (!grabbed_item_data) {
                if (left_hand_slot.item_id != 0) {
                    // get data
                    grabbed_item = left_hand_slot;
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];

                    // set half count 
                    if (left_hand_slot.items_count % 2 == 0) {
                        grabbed_item.items_count /= 2;
                        left_hand_slot.items_count /= 2;
                    } else {
                        // just set empty
                        if (left_hand_slot.items_count == 1) {
                            left_hand_slot = empty_slot;
                            left_hand_slot_data = nullptr;
                            left_hand_slot_block_light = nullptr;

                        } 
                        // set grabbed count more by 1 
                        else {
                            left_hand_slot.items_count = uint8_t(float(left_hand_slot.items_count) / 2);
                            grabbed_item.items_count = uint8_t(float(grabbed_item.items_count) / 2 + 1.0f);
                        }
                    }
                    return true;
                }
            }
            // check put
            else {
                if (grabbed_item_data) {
                    // add to empty slot
                    if (left_hand_slot.item_id == 0) {
                        left_hand_slot = grabbed_item;
                        left_hand_slot_data = &all_items_data[left_hand_slot.item_id];
                        if (left_hand_slot_data->type == "block") {
                            left_hand_slot_block_light = &all_blocks_full_data[
                                left_hand_slot_data->place_blocks_ids_range[0]
                            ].light;
                        }

                        left_hand_slot.items_count = 1;

                        grabbed_item.items_count--;
                        
                        // clear grabbed
                        if (grabbed_item.items_count <= 0) {
                            grabbed_item = empty_slot;
                            grabbed_item_data = nullptr;
                        }
                    }

                    // add to same as grabbed
                    else if (left_hand_slot.item_id == grabbed_item.item_id) {
                        if (left_hand_slot.items_count < left_hand_slot_data->max_stack) {
                            left_hand_slot.items_count++;
                            grabbed_item.items_count--;
                        }

                        // clear grabbed
                        if (grabbed_item.items_count <= 0) {
                            grabbed_item = empty_slot;
                            grabbed_item_data = nullptr;
                        }
                    }
                }
            }
        }
        // * move fast to bag
        if (on_shift && on_left_mb) {
            if (!grabbed_item_data) {
                if (left_hand_slot.item_id != 0) {
                    move_item_to_bag(left_hand_slot, *left_hand_slot_data);

                    // set empty
                    if (left_hand_slot.items_count <= 0) {
                        left_hand_slot = empty_slot;
                        left_hand_slot_data = nullptr;
                        left_hand_slot_block_light = nullptr;
                    }
                }
            }
        }
    }

    return false;
}



bool PlayerInventory::crafter_interactions(vec2 mpos, int sc_w, int sc_h) {
    int start_x = crafter_x;
    int start_y = crafter_y;

    int mpos_slot_x = int((mpos.x - start_x) / slot_w);
    int mpos_slot_y = int((mpos.y - start_y) / slot_h);

    int slot_ind_x = 0;
    int slot_ind_y = 0;
    InventorySlot* selected_slot = nullptr;
    // slots
    if (mpos.x - start_x >= 0 && mpos.y - start_y >= 0) {
        for (int y = 0; y < 2; y++)
        for (int x = 0; x < 2; x++) {
            
            // check mouse pos on slot
            if (mpos_slot_x == x && mpos_slot_y == y) {
                slot_ind_x = x;
                slot_ind_y = y;

                selected_slot = &crafter_slots[slot_ind_x][slot_ind_y];

                // set title
                if (selected_slot->item_id != 0) {
                    InventoryItemData& slot_item_data = all_items_data[selected_slot->item_id];
                    selected_slot_title = slot_item_data.title;
                }
                break;
            }
        }
    }
    if (on_left_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                grabbed_item = *selected_slot;
                // get data
                grabbed_item_data = &all_items_data[grabbed_item.item_id];
                // set empty
                crafter_slots[slot_ind_x][slot_ind_y] = empty_slot;
                
                // check recipe
                check_crafter_recipe(
                    crafter_slots, 
                    crafter_result_slot
                );
                if (crafter_result_slot.item_id != 0) {
                    crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                }
                else {
                    crafter_result_slot_data = nullptr;
                } 
                
                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // set as grabbed
                if (selected_slot->item_id == 0) {
                    crafter_slots[slot_ind_x][slot_ind_y] = grabbed_item;

                    // clear grabbed
                    grabbed_item = empty_slot;
                    grabbed_item_data = nullptr;
                    update_current_slot(sc_w, sc_h);

                    // check recipe
                    check_crafter_recipe(
                        crafter_slots, 
                        crafter_result_slot
                    );
                    if (crafter_result_slot.item_id != 0) {
                        crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                    }
                    else {
                        crafter_result_slot_data = nullptr;
                    } 
                    
                }
                // add if same as grabbed 
                else if (selected_slot->item_id == grabbed_item.item_id && selected_slot_item_data.max_stack > 1) {
                    bool interacted = false;
                    crafter_slots[slot_ind_x][slot_ind_y].items_count += grabbed_item.items_count;
                    
                    // add remainder to grabbed
                    if (int(crafter_slots[slot_ind_x][slot_ind_y].items_count) > selected_slot_item_data.max_stack) {
                        grabbed_item.items_count = crafter_slots[slot_ind_x][slot_ind_y].items_count - selected_slot_item_data.max_stack;
                        crafter_slots[slot_ind_x][slot_ind_y].items_count = selected_slot_item_data.max_stack;
                        interacted = true;
                    }
                    // clear grabbed
                    else {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }
                    update_current_slot(sc_w, sc_h);

                    // check recipe
                    check_crafter_recipe(
                        crafter_slots, 
                        crafter_result_slot
                    );
                    if (crafter_result_slot.item_id != 0) {
                        crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                    }
                    else {
                        crafter_result_slot_data = nullptr;
                    } 

                    return interacted;
                }
                // swap
                else if (selected_slot->item_id != grabbed_item.item_id || selected_slot_item_data.max_stack == 1) {
                    InventorySlot temp_grabbed = grabbed_item;
                    grabbed_item = crafter_slots[slot_ind_x][slot_ind_y];
                    grabbed_item_data = &all_items_data[grabbed_item.item_id];

                    crafter_slots[slot_ind_x][slot_ind_y]= temp_grabbed;
                    
                    // check recipe
                    check_crafter_recipe(
                        crafter_slots, 
                        crafter_result_slot
                    );
                    if (crafter_result_slot.item_id != 0) {
                        crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                    }
                    else {
                        crafter_result_slot_data = nullptr;
                    }
                    
                    return true;
                }

                
            } 
        } 
    }

    if (on_right_mb && !on_shift) {
        // check grab
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                // get data
                grabbed_item = *selected_slot;
                grabbed_item_data = &all_items_data[grabbed_item.item_id];

                // set half count 
                if (selected_slot->items_count % 2 == 0) {
                    grabbed_item.items_count /= 2;
                    crafter_slots[slot_ind_x][slot_ind_y].items_count /= 2;
                } else {
                    // just set empty
                    if (crafter_slots[slot_ind_x][slot_ind_y].items_count == 1) {
                        crafter_slots[slot_ind_x][slot_ind_y] = empty_slot;
                    } 
                    // set grabbed count more by 1 
                    else {
                        crafter_slots[slot_ind_x][slot_ind_y].items_count = uint8_t(float(crafter_slots[slot_ind_x][slot_ind_y].items_count) / 2);
                        grabbed_item.items_count = uint8_t(float(grabbed_item.items_count) / 2 + 1.0f);
                    }
                }

                update_current_slot(sc_w, sc_h);

                // check recipe
                check_crafter_recipe(
                    crafter_slots, 
                    crafter_result_slot
                );
                if (crafter_result_slot.item_id != 0) {
                    crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                }
                else {
                    crafter_result_slot_data = nullptr;
                }

                return true;
            }
        }
        // check put
        else {
            if (grabbed_item_data && selected_slot) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                // add to empty slot
                if (selected_slot->item_id == 0) {
                    crafter_slots[slot_ind_x][slot_ind_y] = grabbed_item;
                    crafter_slots[slot_ind_x][slot_ind_y].items_count = 1;

                    grabbed_item.items_count--;
                    
                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }
                // add to same as grabbed
                else if (selected_slot->item_id == grabbed_item.item_id) {
                    if (crafter_slots[slot_ind_x][slot_ind_y].items_count < selected_slot_item_data.max_stack) {
                        crafter_slots[slot_ind_x][slot_ind_y].items_count++;
                        grabbed_item.items_count--;
                    }

                    // clear grabbed
                    if (grabbed_item.items_count <= 0) {
                        grabbed_item = empty_slot;
                        grabbed_item_data = nullptr;
                    }

                    update_current_slot(sc_w, sc_h);
                }

                // check recipe
                check_crafter_recipe(
                    crafter_slots, 
                    crafter_result_slot
                );
                if (crafter_result_slot.item_id != 0) {
                    crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                }
                else {
                    crafter_result_slot_data = nullptr;
                }
            }
        }
    }

    // * move fast to bag or current storage
    if (on_shift && on_left_mb) {
        if (!grabbed_item_data) {
            if (selected_slot && selected_slot->item_id != 0) {
                InventoryItemData& selected_slot_item_data = all_items_data[selected_slot->item_id];
                move_item_to_player_inventory(*selected_slot, selected_slot_item_data, true);
                
                // check recipe
                check_crafter_recipe(
                    crafter_slots, 
                    crafter_result_slot
                );

                if (crafter_result_slot.item_id != 0) {
                    crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                }
                else {
                    crafter_result_slot_data = nullptr;
                }
            }
        }
        update_current_slot(sc_w, sc_h);
    }

    // * result slot
    mpos_slot_x = int((mpos.x - crafter_result_slot_rect.x) / slot_w);
    mpos_slot_y = int((mpos.y - crafter_result_slot_rect.y) / slot_h);
    
    // check if mouse on slot
    if ((mpos.x - crafter_result_slot_rect.x) >= 0 && (mpos.y - crafter_result_slot_rect.y) >= 0) {
        if (mpos_slot_x == 0 && mpos_slot_y == 0) {
    
            if (crafter_result_slot_data) {
                // set title
                selected_slot_title = crafter_result_slot_data->title;
            }
    
            // check grab
            if (on_left_mb && !on_shift) {
                if (!grabbed_item_data) {
                    if (crafter_result_slot.item_id != 0) {
                        grabbed_item = crafter_result_slot;
                        // get data
                        grabbed_item_data = &all_items_data[grabbed_item.item_id];
                        // set empty
                        crafter_result_slot = empty_slot;
                        crafter_result_slot_data = nullptr;
    
                        // reduce crafter slots items count
                        for (size_t x = 0; x < 2; x++)
                        for (size_t y = 0; y < 2; y++)
                        {
                            InventorySlot& crafter_slot = crafter_slots[x][y];
    
                            if (crafter_slot.item_id != 0 && crafter_slot.items_count > 0) {
                                crafter_slot.items_count--;
                                // clear slot
                                if (crafter_slot.items_count <= 0) {
                                    crafter_slots[x][y] = empty_slot;
                                }
                            } 
                        }
    
                        // check recipe
                        check_crafter_recipe(
                            crafter_slots, 
                            crafter_result_slot
                        );
    
                        if (crafter_result_slot.item_id != 0) {
                            crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                        }
                        else {
                            crafter_result_slot_data = nullptr;
                        }
    
                        return true;
                    }
                }
            }
    
            // * move fast to bag
            if (on_shift && on_left_mb) {
                if (!grabbed_item_data) {
                    if (crafter_result_slot.item_id != 0) {
                        move_item_to_player_inventory(crafter_result_slot, *crafter_result_slot_data, true);
    
                        // set empty
                        if (crafter_result_slot.items_count <= 0) {
                            crafter_result_slot = empty_slot;
                            crafter_result_slot_data = nullptr;
                        }
                        
                        // reduce crafter slots items count
                        for (size_t x = 0; x < 2; x++)
                        for (size_t y = 0; y < 2; y++)
                        {
                            InventorySlot& crafter_slot = crafter_slots[x][y];
    
                            if (crafter_slot.item_id != 0 && crafter_slot.items_count > 0) {
                                crafter_slot.items_count--;
                                // clear slot
                                if (crafter_slot.items_count <= 0) {
                                    crafter_slots[x][y] = empty_slot;
                                }
                            } 
                        }
    
                        // check recipe
                        check_crafter_recipe(
                            crafter_slots, 
                            crafter_result_slot
                        );
    
                        if (crafter_result_slot.item_id != 0) {
                            crafter_result_slot_data = &all_items_data[crafter_result_slot.item_id];
                        }
                        else {
                            crafter_result_slot_data = nullptr;
                        }
                    }
                }
            }
        }
    }
    return false;
}




// * items movings
bool PlayerInventory::move_item_to_bag(InventorySlot& move_item, InventoryItemData& move_item_data) {
    // loop all items to find empty or same 
    for (size_t si = 0; si < bag_slots_w*bag_slots_h; si++)
    {
        InventorySlot& bag_slot = bag_slots[si];
        InventoryItemData& bag_slot_data = all_items_data[bag_slot.item_id];

        // slot empty
        if (bag_slot.item_id == 0) {
            bag_slot = move_item;
            move_item = empty_slot;
            return true;
        }
        // same as move item
        else if (bag_slot.item_id == move_item.item_id && bag_slot.items_count < bag_slot_data.max_stack) {
            bag_slot.items_count += move_item.items_count;

            if (bag_slot.items_count > bag_slot_data.max_stack) {
                move_item.items_count = bag_slot.items_count - bag_slot_data.max_stack;
                bag_slot.items_count = bag_slot_data.max_stack;
                return move_item_to_bag(move_item, move_item_data);
            } else {
                move_item = empty_slot;
                return true;
            }
        }
    }
    return false;
}

bool PlayerInventory::move_item_to_hotbar(InventorySlot& move_item, InventoryItemData& move_item_data) {
    // loop all items to find empty or same 
    for (size_t si = 0; si < 9; si++)
    {
        InventorySlot& hotbar_slot = hotbar_slots[si];
        InventoryItemData& hotbar_slot_data = all_items_data[hotbar_slot.item_id];

        // slot empty
        if (hotbar_slot.item_id == 0) {
            hotbar_slot = move_item;
            move_item = empty_slot;
            return true;
        }
        // same as move item
        else if (hotbar_slot.item_id == move_item.item_id && hotbar_slot.items_count < hotbar_slot_data.max_stack) {
            hotbar_slot.items_count += move_item.items_count;

            if (hotbar_slot.items_count > hotbar_slot_data.max_stack) {
                move_item.items_count = hotbar_slot.items_count - hotbar_slot_data.max_stack;
                hotbar_slot.items_count = hotbar_slot_data.max_stack;
                return move_item_to_hotbar(move_item, move_item_data);
            } else {
                move_item = empty_slot;
                return true;
            }
        }
    }
    return false;
}

bool PlayerInventory::move_item_to_current_storage(InventorySlot& move_item, InventoryItemData& move_item_data) {
    // loop all items to find empty or same 
    for (size_t si = 0; si < storage_slots_w*storage_slots_h; si++)
    {
        InventorySlot& hotbar_slot = current_storage->slots[si];
        InventoryItemData& hotbar_slot_data = all_items_data[hotbar_slot.item_id];

        // slot empty
        if (hotbar_slot.item_id == 0) {
            hotbar_slot = move_item;
            move_item = empty_slot;
            return true;
        }
        // same as move item
        else if (hotbar_slot.item_id == move_item.item_id && hotbar_slot.items_count < hotbar_slot_data.max_stack) {
            hotbar_slot.items_count += move_item.items_count;

            if (hotbar_slot.items_count > hotbar_slot_data.max_stack) {
                move_item.items_count = hotbar_slot.items_count - hotbar_slot_data.max_stack;
                hotbar_slot.items_count = hotbar_slot_data.max_stack;
                return move_item_to_current_storage(move_item, move_item_data);
            } else {
                move_item = empty_slot;
                return true;
            }
        }
    }
    return false;
}

bool PlayerInventory::move_item_to_player_inventory(InventorySlot& move_item, InventoryItemData& move_item_data, bool check_in_bag) {
    // * first check in hotbar
    if (!check_in_bag) {
        bool item_added = move_item_to_hotbar(move_item, move_item_data);
        if (!item_added) {
            return move_item_to_bag(move_item, move_item_data);
        }
        return item_added;
    }

    // * first check in bag
    else {
        bool item_added = move_item_to_bag(move_item, move_item_data);
        if (!item_added) {
            return move_item_to_hotbar(move_item, move_item_data);
        }
        return item_added;
    }
    return false;
}

void PlayerInventory::update(Player& player, vector<ItemDrop>& all_items_drops, vec2 mpos, int sc_w, int sc_h, float dt) {
    selected_slot_title = "";

    // interactions
    if (player.in_inventory) {
        bool interacted = false;
        if (all_items_interaction(mpos, sc_w, sc_h)) interacted = true;
        if (hotbar_items_interaction(mpos, sc_w, sc_h)) interacted = true;
        if (bag_items_interaction(mpos, sc_w, sc_h)) interacted = true;
        if (in_storage_inv) {
            if (current_storage_interaction(mpos, sc_w, sc_h)) interacted = true;
        }
        if (in_block_crafter) {
            if (block_crafter_interactions(mpos, sc_w, sc_h)) interacted = true;
        }
        // other slots in bag
        if (left_hand_interaction(mpos, sc_w, sc_h)) interacted = true;
        if (!in_storage_inv && !in_block_crafter) {
            if (crafter_interactions(mpos, sc_w, sc_h)) interacted = true;
        }
    
        // drop grabbed item
        if (on_left_mb && !interacted) {
            ItemDrop new_item_drop;
            new_item_drop.add_item = grabbed_item;
            new_item_drop.x = player.x + 25 * -player.angle_y_sin;
            new_item_drop.y = player.y - 25;
            new_item_drop.z = player.z + 25 * player.angle_y_cos;

            // set just dropped
            new_item_drop.just_dropded_cooldown = 20;
            new_item_drop.pick_up_able = false;

            // set inertion
            float inertion = 10;
            new_item_drop.inert_x = inertion * -player.angle_y_sin;
            new_item_drop.inert_z = inertion * player.angle_y_cos;

            new_item_drop.full_model_id = item_id_to_entity_id[grabbed_item.item_id];
            all_items_drops.push_back(new_item_drop);

            // clear grabbed
            grabbed_item = empty_slot;
            grabbed_item_data = nullptr;
        }
    } 
    // drop grabbed item
    else {
        if (grabbed_item_data) {
            ItemDrop new_item_drop;
            new_item_drop.add_item = grabbed_item;
            new_item_drop.x = player.x + 25 * -player.angle_y_sin;
            new_item_drop.y = player.y - 25;
            new_item_drop.z = player.z + 25 * player.angle_y_cos;

            // set just dropped
            new_item_drop.just_dropded_cooldown = 20;
            new_item_drop.pick_up_able = false;

            // set inertion
            float inertion = 10;
            new_item_drop.inert_x = inertion * -player.angle_y_sin;
            new_item_drop.inert_z = inertion * player.angle_y_cos;

            new_item_drop.full_model_id = item_id_to_entity_id[grabbed_item.item_id];
            all_items_drops.push_back(new_item_drop);
            
            // clear grabbed
            grabbed_item = empty_slot;
            grabbed_item_data = nullptr;
        }
    }

    on_right_mb = false;
    on_left_mb = false;

    if (show_current_slot_cooldown > 0) {
        show_current_slot_cooldown -= 1 * dt;
    }
}

void PlayerInventory::draw_slot(SDL_Renderer* renderer, TextDraw& text_draw, SDL_Rect& draw_rect, InventorySlot& slot_data, InventoryItemData* item_data) {
    SDL_RenderCopy(renderer, slot_t, NULL, &draw_rect);
    // item
    if (item_data) {
        int item_w = item_data->item_w;
        int item_h = item_data->item_h;

        // set rect
        SDL_Rect rect = {
            draw_rect.x + (slot_w / 2 - item_w / 2), 
            draw_rect.y + (slot_h / 2 - item_h / 2), 
            item_w, item_h
        };

        // load texture and draw
        SDL_Texture* texture = all_textures[item_data->t_name];
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        // draw count
        if (slot_data.items_count > 1) {
            text_draw.draw_text(
                renderer, to_string(slot_data.items_count), 
                draw_rect.x + slot_w,
                draw_rect.y + slot_h,
                "left", "top", 2, true, 50
            );
        }
        // * draw durability
        if (item_data->max_durability > 0 && slot_data.durability < item_data->max_durability) {
            float durability_line_w = slot_w - 4;
            float durability_line_h = 4;
    
            int durability_line_x = draw_rect.x + 2;
            int durability_line_y = draw_rect.y + (slot_h - (durability_line_h + 2));
            
            // draw bg
            SDL_Rect durability_bg_rect{
                durability_line_x, durability_line_y,
                (int)durability_line_w, (int)durability_line_h
            };
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
            SDL_RenderFillRect(renderer, &durability_bg_rect);
    
            // draw item durability
            float w = float(durability_line_w / float(item_data->max_durability)) * float(slot_data.durability);
            SDL_Rect durability_line_rect{
                durability_line_x, durability_line_y,
                int(w), (int)durability_line_h
            };
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &durability_line_rect);
        }
    }
}

void PlayerInventory::draw(SDL_Renderer* renderer, Player& player, TextDraw& text_draw, vec2 mpos, int sc_w, int sc_h) {
    // * hotbat and slots
    cout << 421 << endl;
    SDL_RenderCopy(renderer, hotbar_t, NULL, &hotbar_rect);
    if (!player.in_inventory) {
        SDL_RenderCopy(renderer, slot_selector_t, NULL, &slot_selector_rect);
    }
    cout << 422 << endl;

    // * hotbar items slots
    int items_draw_start_x = hotbar_rect.x + slot_w / 2;
    int items_draw_start_y = hotbar_rect.y + slot_h / 2;

    for (size_t si = 0; si < 9; si++)
    {
        InventorySlot& slot = hotbar_slots[si];
        if (slot.item_id == 0) {
            continue;
        }

        InventoryItemData& item_data = all_items_data[slot.item_id];
        int item_w = item_data.item_w;
        int item_h = item_data.item_h;

        // set rect
        int x = items_draw_start_x - (item_w / 2) + (si * slot_w);
        int y = items_draw_start_y - (item_h / 2);

        SDL_Rect rect = {
            x, y, item_w, item_h
        };

        // load texture and draw
        SDL_Texture* texture = all_textures[item_data.t_name];
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        // draw count
        if (slot.items_count > 1) {
            text_draw.draw_text(
                renderer, to_string(slot.items_count), 
                items_draw_start_x + slot_w / 2 + (si * slot_w),
                items_draw_start_y + slot_h / 2,
                "left", "top", 2, true, 50
            );
        }
        // * draw durability
        if (item_data.max_durability > 0 && slot.durability < item_data.max_durability) {
            float durability_line_w = slot_w - 4;
            float durability_line_h = 4;
    
            int durability_line_x = items_draw_start_x + (si * slot_w) - (slot_w / 2 - 2);
            int durability_line_y = items_draw_start_y + (slot_h / 2 - (durability_line_h + 2));
            
            // draw bg
            SDL_Rect durability_bg_rect{
                durability_line_x, durability_line_y,
                (int)durability_line_w, (int)durability_line_h
            };
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
            SDL_RenderFillRect(renderer, &durability_bg_rect);
    
            // draw item durability
            float w = float(durability_line_w / float(item_data.max_durability)) * float(slot.durability);
            SDL_Rect durability_line_rect{
                durability_line_x, durability_line_y,
                int(w), (int)durability_line_h
            };
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &durability_line_rect);
        }
    }
    cout << 423 << endl;
    // * left hand
    if (player.in_inventory || left_hand_slot_data) {
        draw_slot(renderer, text_draw, left_hand_slot_rect, left_hand_slot, left_hand_slot_data);
    }
    cout << 424 << endl;
    if (player.in_inventory) {
        // * all items slots
        int x_start = sc_w - (slot_w * 4);
        int y_start = 0;

        int x = 0;
        int y = 0;
        for (size_t si = 0; si < all_items_count; si++)
        {
            InventorySlot& slot = all_items_slots[si];
            InventoryItemData& item_data = all_items_data[slot.item_id];
            int item_w = item_data.item_w;
            int item_h = item_data.item_h;

            // set rect

            SDL_Rect rect = {
                x + x_start + (slot_w / 2 - item_w / 2), 
                y + y_start + (slot_h / 2 - item_h / 2), 
                item_w, item_h
            };

            // load texture and draw
            SDL_Texture* texture = all_textures[item_data.t_name];
            SDL_RenderCopy(renderer, texture, NULL, &rect);

            // update draw pos
            x += slot_w;
            if (x / slot_w >= 4) {
                y += slot_h;
                x = 0;
            } 
        }

        // * bag slots
        SDL_Rect row_rect;
        row_rect.w = hotbar_w;
        row_rect.h = hotbar_h;

        for (size_t col_i = 0; col_i < bag_slots_h; col_i++)
        {
            row_rect.x = bag_x;
            row_rect.y = bag_y + hotbar_h * col_i;

            // draw
            SDL_RenderCopy(renderer, hotbar_t, NULL, &row_rect);
        }

        // * bag items
        int slot_ind = 0;

        for (int y = 0; y < bag_slots_h; y++)
        for (int x = 0; x < bag_slots_w; x++)
        {
            InventorySlot& slot = bag_slots[slot_ind];
            slot_ind++;

            if (slot.item_id == 0) {
                continue;
            }

            InventoryItemData& item_data = all_items_data[slot.item_id];
            int item_w = item_data.item_w;
            int item_h = item_data.item_h;

            // set rect
            SDL_Rect rect = {
                bag_x + x * slot_w + (slot_w / 2 - item_w / 2), 
                bag_y + y * slot_h + (slot_h / 2 - item_h / 2), 
                item_w, item_h
            };

            // load texture and draw
            SDL_Texture* texture = all_textures[item_data.t_name];
            SDL_RenderCopy(renderer, texture, NULL, &rect);

            // draw count
            if (slot.items_count > 1) {
                text_draw.draw_text(
                    renderer, to_string(slot.items_count), 
                    bag_x + slot_w + x * slot_w,
                    bag_y + slot_h + y * slot_h,
                    "left", "top", 2, true, 50
                );
            }
            // * draw durability
            
            if (item_data.max_durability > 0 && slot.durability < item_data.max_durability) {
                float durability_line_w = slot_w - 4;
                float durability_line_h = 4;
        
                int durability_line_x = bag_x + (x * slot_w) + 2;
                int durability_line_y = bag_y + (y * slot_w) + (slot_h - (durability_line_h + 2));
                
                // draw bg
                SDL_Rect durability_bg_rect{
                    durability_line_x, durability_line_y,
                    (int)durability_line_w, (int)durability_line_h
                };
                SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                SDL_RenderFillRect(renderer, &durability_bg_rect);
        
                // draw item durability
                float w = float(durability_line_w / float(item_data.max_durability)) * float(slot.durability);
                SDL_Rect durability_line_rect{
                    durability_line_x, durability_line_y,
                    int(w), (int)durability_line_h
                };
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderFillRect(renderer, &durability_line_rect);
            }
        }  
        
        // * crafter
        if (!in_storage_inv && !in_block_crafter) {
            SDL_Rect draw_rect = {
                0, 0, slot_w, slot_h
            };

            // slots
            for (size_t x = 0; x < 2; x++)
            for (size_t y = 0; y < 2; y++)
            {
                InventorySlot& slot = crafter_slots[x][y];

                // set data
                InventoryItemData* slot_data = nullptr;
                if (slot.item_id != 0) {
                    slot_data = &all_items_data[slot.item_id];
                }

                // set rect pos
                draw_rect.x = crafter_x + x * slot_w;
                draw_rect.y = crafter_y + y * slot_h;

                draw_slot(renderer, text_draw, draw_rect, slot, slot_data);
            }

            // result slot
            draw_slot(
                renderer, text_draw, 
                crafter_result_slot_rect, 
                crafter_result_slot, crafter_result_slot_data
            );
        }

        // * block crafter
        if (in_block_crafter) {
            SDL_Rect draw_rect = {
                0, 0, slot_w, slot_h
            };

            // slots
            for (size_t x = 0; x < 3; x++)
            for (size_t y = 0; y < 3; y++)
            {
                InventorySlot& slot = block_crafter_slots[x][y];

                // set data
                InventoryItemData* slot_data = nullptr;
                if (slot.item_id != 0) {
                    slot_data = &all_items_data[slot.item_id];
                }

                // set rect pos
                draw_rect.x = block_crafter_x + x * slot_w;
                draw_rect.y = block_crafter_y + y * slot_h;

                draw_slot(renderer, text_draw, draw_rect, slot, slot_data);
            }

            // result slot
            draw_slot(
                renderer, text_draw, 
                block_crafter_result_slot_rect, 
                block_crafter_result_slot, block_crafter_result_slot_data
            );
        }


        // * storage inv
        if (in_storage_inv) {
            SDL_Rect row_rect;
            row_rect.w = hotbar_w;
            row_rect.h = hotbar_h;

            for (size_t col_i = 0; col_i < storage_slots_h; col_i++)
            {
                row_rect.x = storage_x;
                row_rect.y = storage_y + hotbar_h * col_i;

                // draw
                SDL_RenderCopy(renderer, hotbar_t, NULL, &row_rect);
            }

            // * draw storage title
            int text_size = 2;
            text_draw.draw_text(renderer, 
                "storage box " + to_string(int(current_storage_id)), 
                storage_x + text_draw.chars_step * text_size, 
                storage_y + 5 - text_draw.chars_step * text_size, 
                "right", "top", text_size, 
                true, 150
            );

            // * storage items
            int slot_ind = 0;

            for (int y = 0; y < storage_slots_h; y++)
            for (int x = 0; x < storage_slots_w; x++)
            {
                InventorySlot& slot = current_storage->slots[slot_ind];
                slot_ind++;

                if (slot.item_id == 0) {
                    continue;
                }

                InventoryItemData& item_data = all_items_data[slot.item_id];
                int item_w = item_data.item_w;
                int item_h = item_data.item_h;

                // set rect
                SDL_Rect rect = {
                    storage_x + x * slot_w + (slot_w / 2 - item_w / 2), 
                    storage_y + y * slot_h + (slot_h / 2 - item_h / 2), 
                    item_w, item_h
                };

                // load texture and draw
                SDL_Texture* texture = all_textures[item_data.t_name];
                SDL_RenderCopy(renderer, texture, NULL, &rect);

                // draw count
                if (slot.items_count > 1) {
                    text_draw.draw_text(
                        renderer, to_string(slot.items_count), 
                        storage_x + slot_w + x * slot_w,
                        storage_y + slot_h + y * slot_h,
                        "left", "top", 2, true, 50
                    );
                }
                // * draw durability
                
                if (item_data.max_durability > 0 && slot.durability < item_data.max_durability) {
                    float durability_line_w = slot_w - 4;
                    float durability_line_h = 4;
            
                    int durability_line_x = storage_x + (x * slot_w) + 2;
                    int durability_line_y = storage_y + (y * slot_w) + (slot_h - (durability_line_h + 2));
                    
                    // draw bg
                    SDL_Rect durability_bg_rect{
                        durability_line_x, durability_line_y,
                        (int)durability_line_w, (int)durability_line_h
                    };
                    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
                    SDL_RenderFillRect(renderer, &durability_bg_rect);
            
                    // draw item durability
                    float w = float(durability_line_w / float(item_data.max_durability)) * float(slot.durability);
                    SDL_Rect durability_line_rect{
                        durability_line_x, durability_line_y,
                        int(w), (int)durability_line_h
                    };
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                    SDL_RenderFillRect(renderer, &durability_line_rect);
                }
            }
        }
    }
    cout << 425 << endl;
    // * grabbed item
    if (grabbed_item_data) {
        // set rect
        int item_w = grabbed_item_data->item_w;
        int item_h = grabbed_item_data->item_h;


        SDL_Rect rect = {
            (int)mpos.x - int((float)item_w * 1.2f) / 2, 
            (int)mpos.y - int((float)item_h * 1.2f) / 2, 
            int((float)item_w * 1.2f), int((float)item_h * 1.2f)
        };

        // loat texture and draw
        SDL_Texture* texture = all_textures[grabbed_item_data->t_name];
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        // draw count
        if (grabbed_item.items_count > 1) {
            text_draw.draw_text(
                renderer, to_string(grabbed_item.items_count), 
                mpos.x + slot_w / 2,
                mpos.y + slot_h / 2 ,
                "left", "top", 2, true, 50
            );
        }
        // * draw durability
        if (grabbed_item_data->max_durability > 0 && grabbed_item.durability < grabbed_item_data->max_durability) {
            float durability_line_w = slot_w - 4;
            float durability_line_h = 4;
    
            int durability_line_x = mpos.x - (slot_w / 2 - 2);
            int durability_line_y = mpos.y + (slot_h / 2 - (durability_line_h + 2));
            
            // draw bg
            SDL_Rect durability_bg_rect{
                durability_line_x, durability_line_y,
                (int)durability_line_w, (int)durability_line_h
            };
            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
            SDL_RenderFillRect(renderer, &durability_bg_rect);
    
            // draw item durability
            float w = float(durability_line_w / float(grabbed_item_data->max_durability)) * float(grabbed_item.durability);
            SDL_Rect durability_line_rect{
                durability_line_x, durability_line_y,
                int(w), (int)durability_line_h
            };
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &durability_line_rect);
        }
    }
    cout << 426 << endl;
    // * selected slot item title 
    if (selected_slot_title != "") {
        int x = mpos.x + 25;

        string x_pos = "right";
        string y_pos = "center";
        // set left pos
        if (mpos.x > sc_w - 200) {
            x_pos = "left";
            x = mpos.x - 25;
        }

        text_draw.draw_text(renderer, selected_slot_title, x, mpos.y, x_pos, y_pos, 2, true, 150);
    }   
    cout << 427 << endl;
    // * current slot title
    if (show_current_slot_cooldown > 0 && !player.in_inventory) {
        if (current_slot->item_id != 0) {
            int x = WINDOW_W / 2;
            int y = hotbar_rect.y - 20;
    
            string title = current_slot_data->title;
    
            text_draw.draw_text(
                renderer, title, 
                x, y, 
                "center", "center", 
                2, true, 150
            );
        }
    }
}
