#include "world.h"

World::World() {}

void World::on_start() {
    // set copies to world loader
    world_loader.all_blocks_entities = &all_blocks_entities;
    world_loader.all_mobs = &all_mobs;

    load_all_blocks();
    load_drop_items_entities();
    load_mobs();

    auto start_time = high_resolution_clock::now();
    world_generator.generate(chunks, storages, last_storage_id, "superflat");
    auto end_time = high_resolution_clock::now();
    double work_time = duration_cast<duration<double, milli>>(end_time - start_time).count();

    cout << "world generation: " << work_time << endl;

    // set camear pos
    camera.x = player.x;
    camera.y = player.y;
    camera.z = player.z;

    // set mob
    Mob test_mob;
    test_mob.x = 200;
    test_mob.y = 700;
    test_mob.z = 200;
    test_mob.full_model_id = mob_name_to_mob_id["test"];

    // set collider size from model
    FullEntityModel model = all_entity_models[mob_name_to_mob_id["test"]];
    test_mob.collider_size_x = model.collider_size_x;
    test_mob.collider_size_top = model.collider_size_top;
    test_mob.collider_size_bottom = model.collider_size_bottom;
    test_mob.collider_size_z = model.collider_size_z;

    all_mobs.push_back(test_mob);
}


void World::controls(SDL_Event& event, float dt) {
    if (event.type == SDL_KEYDOWN) {
        // reload all chunks  
        if (event.key.keysym.sym == SDLK_F5) {
            world_loader.reload_all_chunks(world_renderer, chunks);
        }
    }

    player.controls(event, camera, dt);
}

float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

// Smoothstep for better transitions (no harsh color changes)
float smoothstep(float t)
{
    return t * t * (3.0f - 2.0f * t);
}

SDL_Color lerpColor(const SDL_Color& a, const SDL_Color& b, float t)
{
    t = std::clamp(t, 0.0f, 1.0f);

    SDL_Color result;
    result.r = static_cast<Uint8>(lerp(a.r, b.r, t));
    result.g = static_cast<Uint8>(lerp(a.g, b.g, t));
    result.b = static_cast<Uint8>(lerp(a.b, b.b, t));
    result.a = 255;

    return result;
}

SDL_Color World::getSkyColor()
{
    float t;

    if (time < TIME_MORNING)
    {
        t = smoothstep(time / float(TIME_MORNING));
        return lerpColor(SKY_NIGHT, SKY_MORNING, t);
    }
    else if (time < TIME_DAY_START)
    {
        t = smoothstep((time - TIME_MORNING) / float(TIME_DAY_START - TIME_MORNING));
        return lerpColor(SKY_MORNING, SKY_DAY, t);
    }
    else if (time < TIME_DAY_END)
    {
        t = smoothstep((time - TIME_DAY_START) / float(TIME_DAY_END - TIME_DAY_START));
        return lerpColor(SKY_DAY, SKY_DAY, t);
    }
    else if (time < TIME_EVENING)
    {
        t = smoothstep((time - TIME_DAY_END) / float(TIME_EVENING - TIME_DAY_END));
        return lerpColor(SKY_DAY, SKY_EVENING, t);
    }
    else
    {
        t = smoothstep((time - TIME_EVENING) / float(TIME_END - TIME_EVENING));
        return lerpColor(SKY_EVENING, SKY_NIGHT, t);
    }
}


void World::update_time(float dt) {
    time += 0.3f * dt;

    if (time > TIME_END) {
        time = 0.0f;
    }

    // set sky color and sun light
    sky_color = getSkyColor();

    float average_color = (float(sky_color.r) + float(sky_color.g) + float(sky_color.b) ) / 3.0f;
    world_renderer.sun_light = average_color / max_sky_color_value;
}

// * loops for all entities
void World::loop_all_entities(PlayerInventory& player_inv, float dt) {
    // * items drops
    all_items_drops.reserve(100);
    for (size_t ei = 0; ei < all_items_drops.size(); ei++)
    {
        ItemDrop& entity = all_items_drops[ei];

        entity.update(chunks, dt);
        bool collided = player.collider_with_item_drop(entity);

        // add to item to player_inv
        if (collided) {
            InventoryItemData& add_item_data = all_items_data[entity.add_item.item_id];
            player_inv.move_item_to_player_inventory(entity.add_item, add_item_data, false);
            if (entity.add_item.items_count == 0) {
                entity.on_remove = true;
            }
            player_inv.update_current_slot(WINDOW_W, WINDOW_H);
        }

        // * project faces
        FullEntityModel full_model = all_entity_models[entity.full_model_id];
        full_model.faces.reserve(0);
        for (size_t fi = 0; fi < full_model.faces.size(); fi++) {
            RawFace3d& raw_face = full_model.faces[fi];
            entity.set_clear_face_pos(raw_face);

            // set color
            raw_face.point1_color = {255, 255, 255, 255};
            raw_face.point2_color = {255, 255, 255, 255};
            raw_face.point3_color = {255, 255, 255, 255};

            raw_face.light = {200, 200, 200};
            // raw_face.sun_light = 1.0f;

            // raw_face.visiblity_angle_y -= int(entity.angle_y);

            // // normalize visibility angle
            // if (raw_face.visiblity_angle_y > 360) {
            //     raw_face.visiblity_angle_y -= 360;
            // }
            // if (raw_face.visiblity_angle_y < 0) {
            //     raw_face.visiblity_angle_y += 360;
            // }

            // project with camera and add to projected faces
            auto projected_face = camera.full_face_projection(raw_face);
            if (projected_face.has_value()) {

                ProjectedFace2d& face_2d = *projected_face;
                world_renderer.projected_faces_2d.push_back(face_2d);
            }
        }
    }

    // * remove items drops
    all_items_drops.erase(
        remove_if(all_items_drops.begin(), all_items_drops.end(),
                    [](const ItemDrop& e) { return e.on_remove; }),
        all_items_drops.end()
    );

    // * blocks entities
    all_blocks_entities.reserve(100);
    for (size_t ei = 0; ei < all_blocks_entities.size(); ei++)
    {
        BlockEntity& entity = all_blocks_entities[ei];

        entity.update(chunks, dt);

        // add chunk to load queue
        if (entity.on_update_chunk) {
            if (!world_loader.check_chunk_added_to_load_queue(*entity.current_chunk)) {
                ChunkToLoad chunk_to_load = {
                    entity.current_chunk, entity.current_chunk_ind, 
                    true, true, 0
                };
                world_loader.chunks_to_load_queue.push_back(chunk_to_load);
            }
        }

        // * update chunks if tnt blowup
        if ((entity.blowup_timer <= 0) && entity.block_id == 83) {
            // get pos in world to get current chunk
            int world_x = ((entity.x + BLOCK_SIZE / 2) / (CHUNK_SIZE_X * BLOCK_SIZE));
            int world_y = ((entity.y + BLOCK_SIZE / 2) / (CHUNK_SIZE_Y * BLOCK_SIZE));
            int world_z = ((entity.z + BLOCK_SIZE / 2) / (CHUNK_SIZE_Z * BLOCK_SIZE));
            
            // loop chunks around
            for (int wx = -1; wx <= 1; wx++)
            for (int wy = -1; wy <= 1; wy++)
            for (int wz = -1; wz <= 1; wz++) {
                // get chunk
                int chunk_ind = world_loader.get_chunk_ind_by_pos(world_x+wx, world_y+wy, world_z+wz);
                if (chunk_ind != -1) {
                    Chunk& chunk = chunks[chunk_ind];
                    // loop all blocks and remove
                    bool block_removed = false;
        
                    for (size_t bx_ = 0; bx_ < CHUNK_SIZE_X; bx_++)
                    for (size_t by_ = 0; by_ < CHUNK_SIZE_Y; by_++)
                    for (size_t bz_ = 0; bz_ < CHUNK_SIZE_Z; bz_++)
                    {
                        Block& block = chunk.blocks[bx_][by_][bz_];
                        if (block.id == 0) {
                            continue;
                        }
                        // get and check dist
                        int dist = sqrt(
                            pow(((block.x + chunk.x) - entity.x), 2) + 
                            pow(((block.y + chunk.y) - entity.y), 2) +
                            pow(((block.z + chunk.z) - entity.z), 2)
                        );
                        int rand_dist = randint(5 * BLOCK_SIZE, 5 * BLOCK_SIZE);
                        if (dist <= rand_dist) {
                            FullBlockData& block_full_data = all_blocks_full_data[block.id];

                            // clear block
                            block.id = 0; // air
                            block.update_time = 0;

                            // remove inventory id from storages and frop items
                            if (block.inventory_id != 0) {
                                StorageBoxInv& block_storage = storages[block.inventory_id];
                                // loop all items to drop
                                for (size_t si = 0; si < 45; si++)
                                {
                                    InventorySlot& slot = block_storage.slots[si];
                                    // create new drop
                                    if (slot.item_id != 0 && randint(0, 5) != 5) { // random chance to drop
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

                            // set chunk air
                            chunk.is_air = world_loader.check_chunk_is_air(chunk);

                            // clear in light sources
                            if (block.sun_light == 1 || ((int)block_full_data.light.r > 0 || (int)block_full_data.light.g > 0 || (int)block_full_data.light.b > 0)) {
                                world_loader.delete_block_from_light_sources(block, chunk);
                            }

                            // clear light
                            block.sun_light = 0.0f;
                            block.light_level = 0;

                            block_removed = true;
                        }
                    }
                    // add chunk to load queue                    
                    if (block_removed) {
                        if (!world_loader.check_chunk_added_to_load_queue(chunk)) {
                            ChunkToLoad chunk_to_load = {
                                &chunk, chunk_ind, 
                                true, true, 0
                            };
                            world_loader.chunks_to_load_queue.push_back(chunk_to_load);
                        }
                    }
                } 
            }
            // set remove 
            entity.on_remove = true;
        }

        // * project faces
        FullBlockModel full_model = all_blocks_models[entity.block_id];

        full_model.faces.reserve(0);
        for (size_t fi = 0; fi < full_model.faces.size(); fi++) {
            RawFace3d& raw_face = full_model.faces[fi];
            entity.set_clear_face_pos(raw_face);

            // set color
            raw_face.point1_color = {255, 255, 255, 255};
            raw_face.point2_color = {255, 255, 255, 255};
            raw_face.point3_color = {255, 255, 255, 255};

            raw_face.light = {200, 200, 200};

            // project with camera and add to projected faces
            auto projected_face = camera.full_face_projection(raw_face);
            if (projected_face.has_value()) {

                ProjectedFace2d& face_2d = *projected_face;
                world_renderer.projected_faces_2d.push_back(face_2d);
            }
        }
    }

    // * remove block entities
    all_blocks_entities.erase(
        remove_if(all_blocks_entities.begin(), all_blocks_entities.end(),
                    [](const BlockEntity& e) { return e.on_remove; }),
        all_blocks_entities.end()
    );


    // * mobs
    all_mobs.reserve(100);
    for (size_t ei = 0; ei < all_mobs.size(); ei++)
    {
        Mob& entity = all_mobs[ei];
        
        entity.update(chunks, dt);

        // set selected by player
        bool selected = false;
        if (world_renderer.selected_face && world_renderer.selected_face->entity_ind == ei) {
            selected = true;

            // hurt if player kick
            if (player.on_kick) {
                entity.hurt(10.0f);
                // add inert and gravity
                entity.inert_x += 4.0f * -player.angle_y_sin;
                entity.inert_z += 4.0f * player.angle_y_cos;
                
                if (entity.grounded) {
                    entity.gravity += 5.0f;
                }
            }
        }

        // * project faces
        FullEntityModel full_model = all_entity_models[entity.full_model_id];
        
        full_model.faces.reserve(0);
        for (size_t fi = 0; fi < full_model.faces.size(); fi++) {
            RawFace3d& raw_face = full_model.faces[fi];
            entity.set_clear_face_pos(raw_face);

            // set color
            raw_face.point1_color = {255, 255, 255, 255};
            raw_face.point2_color = {255, 255, 255, 255};
            raw_face.point3_color = {255, 255, 255, 255};

            // set color if hurts
            if (entity.damage_redness > 0) {
                raw_face.point1_color = {255, 130, 130, 255};
                raw_face.point2_color = {255, 130, 130, 255};
                raw_face.point3_color = {255, 130, 130, 255};
            }

            raw_face.light = {200, 200, 200};

            // project with camera and add to projected faces
            auto projected_face = camera.full_face_projection(raw_face);
            if (projected_face.has_value()) {
                // set entity ind
                projected_face->entity_ind = ei;

                ProjectedFace2d& face_2d = *projected_face;
                world_renderer.projected_faces_2d.push_back(face_2d);
                world_renderer.add_selected_face(face_2d, player_inv);
            }
        }
    }

    // * remove mobs
    all_mobs.erase(
        remove_if(all_mobs.begin(), all_mobs.end(),
                    [](const Mob& e) { return e.on_remove; }),
        all_mobs.end()
    );

    // clear player states
    player.on_kick = false;
}

void World::update(PlayerInventory& player_inv, float dt) {
    player.update(camera, chunks, dt);

    camera.update(dt);
    loop_all_entities(player_inv, dt);
    world_loader.update(world_renderer, chunks, all_items_drops, storages, last_storage_id, player, player_inv, dt);

    world_renderer.update(camera, chunks, player, player_inv);

    update_time(dt);

    // clear player inv states
    player_inv.on_slot_change = false;
}

void World::draw(SDL_Renderer* renderer) {
    world_renderer.draw(renderer, player);
}
