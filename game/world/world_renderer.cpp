#include "world_renderer.h"


WorldRenderer::WorldRenderer() {
    screen_effect_rect = {0, 0, WINDOW_W, WINDOW_H};
}

void WorldRenderer::load_face_texture(SDL_Renderer* renderer, string name, string path, PlayerInventory& player_inv, bool add_to_player_inv) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, ((path.c_str())));
    all_faces_textures[last_t_id] = texture;
    texture_name_to_id[name] = last_t_id;
    last_t_id++;

    // add to player inv
    if (add_to_player_inv) {
        player_inv.all_textures[name] = texture;
    }
}

void WorldRenderer::load_faces_textures(SDL_Renderer* renderer, PlayerInventory& player_inv) {
    // load textures for blocks
    string base_folder = "game/assets/textures/blocks/";
    string inventory_folder = "game/assets/textures/inventory/";
    string entities_folder = "game/assets/textures/entities/";
    // test
    load_face_texture(renderer, "test_block_side", base_folder + "test.png", player_inv, false);
    load_face_texture(renderer, "test_slab_side", base_folder + "test_slab_side.png", player_inv, false);
    load_face_texture(renderer, "test_stairs_side1", base_folder + "test_stairs_side1.png", player_inv, false);
    load_face_texture(renderer, "test_stairs_side2", base_folder + "test_stairs_side2.png", player_inv, false);
    // grass / dirt
    load_face_texture(renderer, "grass_top", base_folder + "grass/top.png", player_inv, false);
    load_face_texture(renderer, "grass_side", base_folder + "grass/side.png", player_inv, false);
    load_face_texture(renderer, "grass_bottom", base_folder + "grass/bottom.png", player_inv, false);
    // water
    load_face_texture(renderer, "water_top", base_folder + "water/top.png", player_inv, false);
    load_face_texture(renderer, "lava_top", base_folder + "lava/top.png", player_inv, false);
    
    // cobblestone
    load_face_texture(renderer, "cobblestone_side", base_folder + "cobblestone/side.png", player_inv, false);
    load_face_texture(renderer, "cobblestone_slab_side_top", base_folder + "cobblestone/slab_side_top.png", player_inv, false);
    load_face_texture(renderer, "cobblestone_slab_side_bottom", base_folder + "cobblestone/slab_side_bottom.png", player_inv, false);
    
    // sand
    load_face_texture(renderer, "sand_side", base_folder + "sand/side.png", player_inv, false);
    // glass
    load_face_texture(renderer, "glass_side", base_folder + "glass/side.png", player_inv, false);
    // wood
    load_face_texture(renderer, "wood_side", base_folder + "wood/side.png", player_inv, false);
    load_face_texture(renderer, "wood_top", base_folder + "wood/top.png", player_inv, false);
    // fire wood
    load_face_texture(renderer, "fire_wood_side", base_folder + "fire_wood/side.png", player_inv, false);
    // burnt wood
    load_face_texture(renderer, "burnt_wood_side", base_folder + "burnt_wood/side.png", player_inv, false);
    load_face_texture(renderer, "burnt_wood_top", base_folder + "burnt_wood/top.png", player_inv, false);
    // wooden planks
    load_face_texture(renderer, "wooden_planks", base_folder + "wooden_planks/side.png", player_inv, false);
    load_face_texture(renderer, "wooden_beam_side", base_folder + "wooden_planks/beam_side.png", player_inv, false);
    load_face_texture(renderer, "wooden_beam_top", base_folder + "wooden_planks/beam_top.png", player_inv, false);
    
    // wooden slab
    load_face_texture(renderer, "wooden_slab_side_top", base_folder + "wooden_planks/slab_side_top.png", player_inv, false);
    load_face_texture(renderer, "wooden_slab_side_bottom", base_folder + "wooden_planks/slab_side_bottom.png", player_inv, false);
    
    // lamp
    load_face_texture(renderer, "lamp_side", base_folder + "lamp/side.png", player_inv, false);

    // low grass
    load_face_texture(renderer, "low_grass_side1", base_folder + "low_grass/side1.png", player_inv, false);
    load_face_texture(renderer, "low_grass_side2", base_folder + "low_grass/side2.png", player_inv, false);

    // rose
    load_face_texture(renderer, "rose_side1", base_folder + "rose/side1.png", player_inv, false);
    load_face_texture(renderer, "rose_side2", base_folder + "rose/side2.png", player_inv, false);

    // torch
    load_face_texture(renderer, "torch_side", base_folder + "torch/side.png", player_inv, false);
    load_face_texture(renderer, "torch_top", base_folder + "torch/top.png", player_inv, false);
    load_face_texture(renderer, "torch_bottom", base_folder + "torch/bottom.png", player_inv, false);

    // stone
    load_face_texture(renderer, "stone_side", base_folder + "stone/side.png", player_inv, false);
    load_face_texture(renderer, "stone_slab_side_top", base_folder + "stone/slab_side_top.png", player_inv, false);
    load_face_texture(renderer, "stone_slab_side_bottom", base_folder + "stone/slab_side_bottom.png", player_inv, false);
    
    // grayed stone
    load_face_texture(renderer, "grayed_stone_side", base_folder + "grayed_stone/side.png", player_inv, false);

    // granite
    load_face_texture(renderer, "granite_side", base_folder + "granite/side.png", player_inv, false);


    // concrete
    load_face_texture(renderer, "white_concrete_side", base_folder + "concrete/white_side.png", player_inv, false);
    // trapdoor
    load_face_texture(renderer, "wooden_trapdoor_side", base_folder + "wooden_trapdoor/side.png", player_inv, false);
    load_face_texture(renderer, "wooden_trapdoor_top", base_folder + "wooden_trapdoor/top.png", player_inv, false);

    // bed 
    load_face_texture(renderer, "dry_bed_top", base_folder + "grass/dry_bed_top.png", player_inv, false);
    load_face_texture(renderer, "wet_bed_top", base_folder + "grass/wet_bed_top.png", player_inv, false);

    // * plants    
    load_face_texture(renderer, "plant_0_side", base_folder + "plants/0_side.png", player_inv, false);

    // wheat
    load_face_texture(renderer, "wheat_1_side", base_folder + "wheat/1_side.png", player_inv, false);
    load_face_texture(renderer, "wheat_2_side", base_folder + "wheat/2_side.png", player_inv, false);
    load_face_texture(renderer, "wheat_3_side", base_folder + "wheat/3_side.png", player_inv, false);

    // barrel
    load_face_texture(renderer, "barrel_side", base_folder + "barrel/side.png", player_inv, false);
    load_face_texture(renderer, "barrel_top", base_folder + "barrel/top.png", player_inv, false);

    // leaves
    load_face_texture(renderer, "leaves_side", base_folder + "leaves/side.png", player_inv, false);

    // door
    load_face_texture(renderer, "door_top_front", base_folder + "door/top_front.png", player_inv, false);
    load_face_texture(renderer, "door_bottom_front", base_folder + "door/bottom_front.png", player_inv, false);
    load_face_texture(renderer, "door_side", base_folder + "door/side.png", player_inv, false);
    load_face_texture(renderer, "door_top_side", base_folder + "door/top_side.png", player_inv, false);
    load_face_texture(renderer, "door_bottom_side", base_folder + "door/bottom_side.png", player_inv, false);

    // gravel
    load_face_texture(renderer, "gravel_side", base_folder + "gravel/side.png", player_inv, false);
    
    // obsidian
    load_face_texture(renderer, "obsidian_side", base_folder + "obsidian/side.png", player_inv, false);

    // sponges
    load_face_texture(renderer, "dry_sponge_side", base_folder + "sponge/dry_side.png", player_inv, false);
    load_face_texture(renderer, "wet_sponge_side", base_folder + "sponge/wet_side.png", player_inv, false);

    // tnt
    load_face_texture(renderer, "tnt_side", base_folder + "tnt/side.png", player_inv, false);
    load_face_texture(renderer, "tnt_top", base_folder + "tnt/top.png", player_inv, false);

    // stone column
    load_face_texture(renderer, "stone_column_side", base_folder + "stone_column/side.png", player_inv, false);
    load_face_texture(renderer, "stone_column_top", base_folder + "stone_column/top.png", player_inv, false);

    // ores
    load_face_texture(renderer, "coal_ore_side", base_folder + "ores/coal_side.png", player_inv, false);
    load_face_texture(renderer, "iron_ore_side", base_folder + "ores/iron_side.png", player_inv, false);
    load_face_texture(renderer, "gold_ore_side", base_folder + "ores/gold_side.png", player_inv, false);
    load_face_texture(renderer, "diamond_ore_side", base_folder + "ores/diamond_side.png", player_inv, false);

    // crater
    load_face_texture(renderer, "crafter_top", base_folder + "crafter/top.png", player_inv, false);
    load_face_texture(renderer, "crafter_bottom", base_folder + "crafter/bottom.png", player_inv, false);
    load_face_texture(renderer, "crafter_side", base_folder + "crafter/side.png", player_inv, false);

    // * block breaking levels
    load_face_texture(renderer, "block_breaking_1", base_folder + "breaking_levels/1.png", player_inv, false);
    load_face_texture(renderer, "block_breaking_2", base_folder + "breaking_levels/2.png", player_inv, false);
    load_face_texture(renderer, "block_breaking_3", base_folder + "breaking_levels/3.png", player_inv, false);
    load_face_texture(renderer, "block_breaking_4", base_folder + "breaking_levels/4.png", player_inv, false);
    load_face_texture(renderer, "block_breaking_5", base_folder + "breaking_levels/5.png", player_inv, false);
    load_face_texture(renderer, "block_breaking_6", base_folder + "breaking_levels/6.png", player_inv, false);

    // * items drops
    load_face_texture(renderer, "stick", inventory_folder + "stick.png", player_inv, true);

    load_face_texture(renderer, "rose", inventory_folder + "rose.png", player_inv, true);


    // tools
    load_face_texture(renderer, "wooden_pickaxe", inventory_folder + "tools/wooden_pickaxe.png", player_inv, true);
    load_face_texture(renderer, "stone_pickaxe", inventory_folder + "tools/stone_pickaxe.png", player_inv, true);
    load_face_texture(renderer, "iron_pickaxe", inventory_folder + "tools/iron_pickaxe.png", player_inv, true);
    load_face_texture(renderer, "hoe", inventory_folder + "tools/hoe.png", player_inv, true);
    load_face_texture(renderer, "lighter", inventory_folder + "tools/lighter.png", player_inv, true);


    load_face_texture(renderer, "wheat_seeds", inventory_folder + "wheat_seeds.png", player_inv, true);
    load_face_texture(renderer, "wheat", inventory_folder + "wheat.png", player_inv, true);
    load_face_texture(renderer, "low_grass", inventory_folder + "low_grass.png", player_inv, true);
    
    load_face_texture(renderer, "door", inventory_folder + "door.png", player_inv, true);

    load_face_texture(renderer, "coal", inventory_folder + "coal.png", player_inv, true);
    load_face_texture(renderer, "iron_ingot", inventory_folder + "iron_ingot.png", player_inv, true);

    // buckets
    load_face_texture(renderer, "bucket", inventory_folder + "bucket.png", player_inv, true);
    load_face_texture(renderer, "water_bucket", inventory_folder + "water_bucket.png", player_inv, true);
    load_face_texture(renderer, "lava_bucket", inventory_folder + "lava_bucket.png", player_inv, true);

    // * entities
    load_face_texture(renderer, "player_body", entities_folder + "player_body.png", player_inv, false);
}

void WorldRenderer::clear_projections() {
    projected_faces_2d.clear();
    selected_faces_2d.clear();

    projected_points_2d.clear();
    projected_lines_2d.clear();
}

// sorters
int projected_faces_sorter(ProjectedFace2d& face1, ProjectedFace2d& face2) {
    // get average faces center z to compare
    int dist_diff;
    if (!FACES_SORT_WITH_DIST) {
        int dist1 =  (
            face1.rotated_point1.z + face1.rotated_point2.z + face1.rotated_point3.z
        ) / 3;
        int dist2 = (
            face2.rotated_point1.z + face2.rotated_point2.z + face2.rotated_point3.z
        ) / 3;
        
        dist_diff = abs(dist1) - abs(dist2);

        // set distances 
        face1.dist = dist1;
        face1.dist = dist2;

    } else {
        float dist1 = sqrt(
            pow((face1.rotated_point1.x + face1.rotated_point2.x + face1.rotated_point3.x) / 3, 2) + 
            pow((face1.rotated_point1.y + face1.rotated_point2.y + face1.rotated_point3.y) / 3, 2) + 
            pow((face1.rotated_point1.z + face1.rotated_point2.z + face1.rotated_point3.z) / 3, 2)
        );
        float dist2 = sqrt(
            pow((face2.rotated_point1.x + face2.rotated_point2.x + face2.rotated_point3.x) / 3, 2) + 
            pow((face2.rotated_point1.y + face2.rotated_point2.y + face2.rotated_point3.y) / 3, 2) + 
            pow((face2.rotated_point1.z + face2.rotated_point2.z + face2.rotated_point3.z) / 3, 2)
        );

        dist_diff = abs(dist1) - abs(dist2);

        // set distances 
        face1.dist = dist1;
        face1.dist = dist2;
    }

    return dist_diff > 0;
}

int selected_faces_sorter(ProjectedFace2d face1, ProjectedFace2d face2) {
    // get average faces center z to compare
	int dist1 =  (
        face1.rotated_point1.z + face1.rotated_point2.z + face1.rotated_point3.z
    ) / 3;
	int dist2 = (
        face2.rotated_point1.z + face2.rotated_point2.z + face2.rotated_point3.z
    ) / 3;

	return abs(dist1) < abs(dist2);
}

void WorldRenderer::sort_faces() {
    sort(projected_faces_2d.begin(), projected_faces_2d.end(), projected_faces_sorter);
    sort(selected_faces_2d.begin(), selected_faces_2d.end(), selected_faces_sorter);
}

void WorldRenderer::project_faces(Camera& camera, Player& player, PlayerInventory& player_inv) {
    size_t faces_3d_count = raw_faces_3d.size();
    raw_faces_3d.reserve(100);

    float last_dist_x = -1.0f;
    float last_dist_y = -1.0f;
    float last_dist_z = -1.0f;

    for (size_t rf_i = 0; rf_i < faces_3d_count; rf_i++)
    {
        RawFace3d& raw_face = raw_faces_3d[rf_i];
        // project with camera
        auto projected_face = camera.full_face_projection(raw_face);
        if (projected_face.has_value()) {
            ProjectedFace2d& face_2d = *projected_face;

            BlockLight total_light = {0, 0, 0};

            // set for current block
            if (player_inv.current_slot_block_light && (player_inv.current_slot_block_light->r > 0 || player_inv.current_slot_block_light->g > 0 || player_inv.current_slot_block_light->b > 0)) {
                total_light = *player_inv.current_slot_block_light;                
            }

            // add left hand
            if (player_inv.left_hand_slot_block_light && (player_inv.left_hand_slot_block_light->r > 0 || player_inv.left_hand_slot_block_light->g > 0 || player_inv.left_hand_slot_block_light->b > 0)) {
                // set if higer
                if (total_light.r < player_inv.left_hand_slot_block_light->r) {
                    total_light.r = player_inv.left_hand_slot_block_light->r;
                }
                if (total_light.g < player_inv.left_hand_slot_block_light->g) {
                    total_light.g = player_inv.left_hand_slot_block_light->g;
                }
                if (total_light.b < player_inv.left_hand_slot_block_light->b) {
                    total_light.b = player_inv.left_hand_slot_block_light->b;
                }
            }
            
            // add item light
            // current slot
            if (player_inv.current_slot_data) {
                // set if higer
                if (total_light.r < player_inv.current_slot_data->item_light.r) {
                    total_light.r = player_inv.current_slot_data->item_light.r;
                }
                if (total_light.g < player_inv.current_slot_data->item_light.g) {
                    total_light.g = player_inv.current_slot_data->item_light.g;
                }
                if (total_light.b < player_inv.current_slot_data->item_light.b) {
                    total_light.b = player_inv.current_slot_data->item_light.b;
                }
            }

            // left hand
            if (player_inv.left_hand_slot_data) {
                // set if higer
                if (total_light.r < player_inv.left_hand_slot_data->item_light.r) {
                    total_light.r = player_inv.left_hand_slot_data->item_light.r;
                }
                if (total_light.g < player_inv.left_hand_slot_data->item_light.g) {
                    total_light.g = player_inv.left_hand_slot_data->item_light.g;
                }
                if (total_light.b < player_inv.left_hand_slot_data->item_light.b) {
                    total_light.b = player_inv.left_hand_slot_data->item_light.b;
                }
            }


            // get and set dynamic light from player on projected face
            if (total_light.r > 0 || total_light.g > 0 || total_light.b > 0) {
                int clear_face_x = round((raw_face.point1.x + raw_face.point2.x + raw_face.point3.x) / 3 / BLOCK_SIZE) * BLOCK_SIZE;
                int clear_face_y = round((raw_face.point1.y + raw_face.point2.y + raw_face.point3.y) / 3 / BLOCK_SIZE) * BLOCK_SIZE;
                int clear_face_z = round((raw_face.point1.z + raw_face.point2.z + raw_face.point3.z) / 3 / BLOCK_SIZE) * BLOCK_SIZE;
                
                float dist_x = player.x - clear_face_x;
                float dist_y = player.y - clear_face_y;
                float dist_z = player.z - clear_face_z;
                
                // check dist from player is correct
                if (abs(dist_x) < LIGHT_MAX_DIST && abs(dist_y) < LIGHT_MAX_DIST && abs(dist_z) < LIGHT_MAX_DIST) {
                    int dist = sqrt(
                        pow(dist_x, 2) +
                        pow(dist_y, 2) +
                        pow(dist_z, 2)
                    );
                    
                    // calc light level from dist
                    int new_r = float(max(0, int(LIGHT_MAX_DIST - dist))) / 1000.0f * (float)total_light.r;
                    int new_g = float(max(0, int(LIGHT_MAX_DIST - dist))) / 1000.0f * (float)total_light.g;
                    int new_b = float(max(0, int(LIGHT_MAX_DIST - dist))) / 1000.0f * (float)total_light.b;

                    // set if brighter
                    if (new_r > (int)projected_face->light.r) projected_face->light.r = (uint8_t)new_r;
                    if (new_g > (int)projected_face->light.g) projected_face->light.g = (uint8_t)new_g;
                    if (new_b > (int)projected_face->light.b) projected_face->light.b = (uint8_t)new_b;
                }
            }
            projected_faces_2d.push_back(face_2d);
            add_selected_face(face_2d, player_inv);
        }
    }
}

void WorldRenderer::add_selected_face(ProjectedFace2d& face, PlayerInventory& player_inv){
    // check distance
    int dist =  (
        face.rotated_point1.z + face.rotated_point2.z + face.rotated_point3.z
    ) / 3;

    if (dist > BLOCK_SELECT_DIST) {
        return;
    }

    // check water, lava and buckets
    if (player_inv.current_slot && (player_inv.current_slot->item_id != 29 && player_inv.current_slot->item_id != 30))
        if (face.t_id == 8 || face.t_id == 9) {
            return;
        }
    
    // check if face is a correct triangle
    bool x_correct = true;
    bool y_correct = true;

    if (face.point1.x == face.point2.x && face.point1.x == face.point3.x) x_correct = false;
    if (face.point1.y == face.point2.y && face.point1.y == face.point3.y) y_correct = false;
    
    if (x_correct && y_correct) {
        bool face_selected = point_in_triangle(
            WINDOW_W / 2.0f,
            WINDOW_H / 2.0f,
            face.point1,
            face.point2,
            face.point3
        );
        // add to selected faces
        if (face_selected) {
            selected_faces_2d.push_back(face);
        }
    }
}


void WorldRenderer::project_points(Camera& camera) {
    size_t points_3d_count = raw_points_3d.size();
    raw_faces_3d.reserve(100);

    for (size_t rp_i = 0; rp_i < points_3d_count; rp_i++)
    {
        RawPoint3d& raw_point = raw_points_3d[rp_i];
        // project with camera
        auto projected_point = camera.full_point_projection(raw_point);
        if (projected_point.has_value()) {
            projected_points_2d.push_back(*projected_point);
        }
    }
}


void WorldRenderer::project_lines(Camera& camera) {
    size_t lines_3d_count = raw_lines_3d.size();
    raw_lines_3d.reserve(100);

    for (size_t rp_i = 0; rp_i < lines_3d_count; rp_i++)
    {
        RawLine3d& raw_line = raw_lines_3d[rp_i];
        // project with camera
        auto projected_line = camera.full_line_projection(raw_line);
        if (projected_line.has_value()) {
            projected_lines_2d.push_back(*projected_line);
        }
    }
}
void WorldRenderer::update_selected_face() {
    // set last selected
    if (selected_face) {
        last_selected_face = *selected_face;
    }

    // clear face
    selected_face = nullptr;
    // set from sorted faces
    if (selected_faces_2d.size() > 0) {
        selected_face = &selected_faces_2d[0];
    }
}


void WorldRenderer::update_block_outline(Chunk (&chunks)[CHUNKS_COUNT], Camera& camera) {
    // get block from selected face
    if (selected_face) {
        // skip uncorect world data 
        if (selected_face->block_x < 0) {
            return;
        }

        Chunk& chunk = chunks[selected_face->chunk_ind];
        Block& block = chunk.blocks[selected_face->block_x][selected_face->block_y][selected_face->block_z];

        float block_x = float(block.x) + chunk.x;
        float block_y = float(block.y) + chunk.y;
        float block_z = float(block.z) + chunk.z;

        // set poitns 
        vec3 points[8] = {
            // bottom
            { // 0
                block_x-BLOCK_SIZE / 2, 
                block_y-BLOCK_SIZE / 2, 
                block_z-BLOCK_SIZE / 2
            }, 
            { // 1
                block_x+BLOCK_SIZE / 2, 
                block_y-BLOCK_SIZE / 2, 
                block_z-BLOCK_SIZE / 2
            },

            { // 2
                block_x-BLOCK_SIZE / 2, 
                block_y-BLOCK_SIZE / 2, 
                block_z+BLOCK_SIZE / 2
            }, 
            { // 3
                block_x+BLOCK_SIZE / 2, 
                block_y-BLOCK_SIZE / 2, 
                block_z+BLOCK_SIZE / 2
            },
            // top
            { // 4
                block_x-BLOCK_SIZE / 2, 
                block_y+BLOCK_SIZE / 2, 
                block_z-BLOCK_SIZE / 2
            }, 
            { // 5
                block_x+BLOCK_SIZE / 2, 
                block_y+BLOCK_SIZE / 2, 
                block_z-BLOCK_SIZE / 2
            },

            { // 6
                block_x-BLOCK_SIZE / 2, 
                block_y+BLOCK_SIZE / 2, 
                block_z+BLOCK_SIZE / 2
            }, 
            { // 7
                block_x+BLOCK_SIZE / 2, 
                block_y+BLOCK_SIZE / 2, 
                block_z+BLOCK_SIZE / 2
            },
        };

        // add lines by face normal
        RawLine3d line1;
        RawLine3d line2;
        RawLine3d line3;
        RawLine3d line4;
        // back
        if (selected_face->normal == 'b') {
            line1 = {
                points[0],
                points[1],
                {0, 0, 0, 255},
            };
            line2 = {
                points[4],
                points[5],
                {0, 0, 0, 255},
            };
            line3 = {
                points[0],
                points[4],
                {0, 0, 0, 255},
            };
            line4 = {
                points[1],
                points[5],
                {0, 0, 0, 255},
            };
        }
        // front
        if (selected_face->normal == 'f') {
            line1 = {
                points[2],
                points[3],
                {0, 0, 0, 255},
            };
            line2 = {
                points[6],
                points[7],
                {0, 0, 0, 255},
            };
            line3 = {
                points[3],
                points[7],
                {0, 0, 0, 255},
            };
            line4 = {
                points[2],
                points[6],
                {0, 0, 0, 255},
            };
        }
        // right
        if (selected_face->normal == 'r') {
            line1 = {
                points[1],
                points[3],
                {0, 0, 0, 255},
            };
            line2 = {
                points[5],
                points[7],
                {0, 0, 0, 255},
            };
            line3 = {
                points[5],
                points[1],
                {0, 0, 0, 255},
            };
            line4 = {
                points[7],
                points[3],
                {0, 0, 0, 255},
            };
        }
        // left
        if (selected_face->normal == 'l') {
            line1 = {
                points[6],
                points[4],
                {0, 0, 0, 255},
            };
            line2 = {
                points[2],
                points[0],
                {0, 0, 0, 255},
            };
            line3 = {
                points[0],
                points[4],
                {0, 0, 0, 255},
            };
            line4 = {
                points[2],
                points[6],
                {0, 0, 0, 255},
            };
        }
        // top
        if (selected_face->normal == 't') {
            line1 = {
                points[4],
                points[5],
                {0, 0, 0, 255},
            };
            line2 = {
                points[6],
                points[7],
                {0, 0, 0, 255},
            };
            line3 = {
                points[4],
                points[6],
                {0, 0, 0, 255},
            };
            line4 = {
                points[5],
                points[7],
                {0, 0, 0, 255},
            };
        }
        // bottom
        if (selected_face->normal == 'd') {
            line1 = {
                points[2],
                points[3],
                {0, 0, 0, 255},
            };
            line2 = {
                points[0],
                points[1],
                {0, 0, 0, 255},
            };
            line3 = {
                points[2],
                points[0],
                {0, 0, 0, 255},
            };
            line4 = {
                points[3],
                points[1],
                {0, 0, 0, 255},
            };
        }

        // project lines and update pos
        auto p_line1 = camera.full_line_projection(line1);
        if (p_line1.has_value()) {
            projected_lines_2d.push_back(*p_line1);
        }
        auto p_line2 = camera.full_line_projection(line2);
        if (p_line2.has_value()) {
            projected_lines_2d.push_back(*p_line2);
        }
        auto p_line3 = camera.full_line_projection(line3);
        if (p_line3.has_value()) {
            projected_lines_2d.push_back(*p_line3);
        }
        auto p_line4 = camera.full_line_projection(line4);
        if (p_line4.has_value()) {
            projected_lines_2d.push_back(*p_line4);
        }

        // set average y
        if (p_line3.has_value() && p_line4.has_value()) {
            average_block_outline_y = (p_line1->start.y + p_line2->end.y + p_line3->start.y + p_line4->end.y) / 4;
        }
    }
}

void WorldRenderer::update_current_chunk_outline(Chunk (&chunks)[CHUNKS_COUNT], Player& player) {
    // get pos in world
    int world_x = ((player.x + BLOCK_SIZE / 2) / (CHUNK_SIZE_X * BLOCK_SIZE));
    int world_y = ((player.y + BLOCK_SIZE / 2) / (CHUNK_SIZE_Y * BLOCK_SIZE));
    int world_z = ((player.z + BLOCK_SIZE / 2) / (CHUNK_SIZE_Z * BLOCK_SIZE));

    int chunk_x = world_x * (CHUNK_SIZE_X * BLOCK_SIZE) - BLOCK_SIZE / 2;
    int chunk_z = world_z * (CHUNK_SIZE_Z * BLOCK_SIZE) - BLOCK_SIZE / 2;
    
    // set poitns 
    vec3 points[8] = {
        // bottom
        { // 0
            float(0 + chunk_x), 
            -BLOCK_SIZE / 2, 
            float(0 + chunk_z)
        }, 
        { // 1
            float(0 + chunk_x + (CHUNK_SIZE_X * BLOCK_SIZE)), 
            -BLOCK_SIZE / 2, 
            float(0 + chunk_z)
        },

        { // 2
            float(0 + chunk_x), 
            -BLOCK_SIZE / 2, 
            float(0 + chunk_z + (CHUNK_SIZE_Z * BLOCK_SIZE))
        }, 
        { // 3
            float(0 + chunk_x + (CHUNK_SIZE_X * BLOCK_SIZE)), 
            -BLOCK_SIZE / 2, 
            float(0 + chunk_z + (CHUNK_SIZE_Z * BLOCK_SIZE))
        },
        // top
        { // 4
            float(0 + chunk_x), 
            (WORLD_SIZE_Y * 2 * CHUNK_SIZE_Y * BLOCK_SIZE) - BLOCK_SIZE / 2, 
            float(0 + chunk_z)
        }, 
        { // 5
            float(0 + chunk_x + (CHUNK_SIZE_X * BLOCK_SIZE)), 
            (WORLD_SIZE_Y * 2 * CHUNK_SIZE_Y * BLOCK_SIZE) - BLOCK_SIZE / 2, 
            float(0 + chunk_z)
        },

        { // 6
            float(0 + chunk_x), 
            (WORLD_SIZE_Y * 2 * CHUNK_SIZE_Y * BLOCK_SIZE) - BLOCK_SIZE / 2, 
            float(0 + chunk_z + (CHUNK_SIZE_Z * BLOCK_SIZE))
        }, 
        { // 7
            float(0 + chunk_x + (CHUNK_SIZE_X * BLOCK_SIZE)), 
            (WORLD_SIZE_Y * 2 * CHUNK_SIZE_Y * BLOCK_SIZE) - BLOCK_SIZE / 2, 
            float(0 + chunk_z + (CHUNK_SIZE_Z * BLOCK_SIZE))
        },
    };

    // * add lines

    // back
    RawLine3d line = {
        points[0],
        points[4],
        {0, 255, 0, 255}
    };
    raw_lines_3d.push_back(line);
    line = {
        points[1],
        points[5],
        {0, 255, 0, 255}
    };
    raw_lines_3d.push_back(line);
    // front
    line = {
        points[2],
        points[6],
        {0, 255, 0, 255}
    };
    raw_lines_3d.push_back(line);
    line = {
        points[3],
        points[7],
        {0, 255, 0, 255}
    };
    raw_lines_3d.push_back(line);

    // horizontal lines from bottom to top

    for (size_t y = 0; y < WORLD_SIZE_Y * 2 * CHUNK_SIZE_Y; y++)
    {
        SDL_Color color = {0, 0, 255, 255};

        if (y % CHUNK_SIZE_Y == 0) {
            color = {255, 0, 0, 255};
        }

        // back
        line = {
            {points[0].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[0].z},
            {points[1].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[1].z},
            color
        };
        raw_lines_3d.push_back(line);
        // front
        line = {
            {points[2].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[2].z},
            {points[3].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[3].z},
            color
        };
        raw_lines_3d.push_back(line);

        // left
        line = {
            {points[0].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[0].z},
            {points[2].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[2].z},
            color
        };
        raw_lines_3d.push_back(line);
        // right
        line = {
            {points[1].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[1].z},
            {points[3].x, float(y * BLOCK_SIZE) - BLOCK_SIZE / 2, points[3].z},
            color
        };
        raw_lines_3d.push_back(line);
    }
}

// player body
void WorldRenderer::update_player_body(Camera& camera, Player& player) {
    // * add body faces
    float offset_y = -15 + camera.shaking_angle_sin * camera.shaking_mult;
    float offset_z = 5;

    float body_heigh = 25.0f;
    float body_width = 25.0f;

    RawFace3d raw_face = {
        {
            player.x + (-body_width / 2.0f) * player.body_angle_cos + offset_z * player.body_angle_sin, 
            player.y + offset_y - body_heigh / 2.0f, 
            player.z + -offset_z * player.body_angle_cos + (-body_width / 2.0f) * player.body_angle_sin
        }, 
        {
            player.x + (-body_width / 2.0f) * player.body_angle_cos + offset_z * player.body_angle_sin, 
            player.y + offset_y + body_heigh / 2.0f, 
            player.z + -offset_z * player.body_angle_cos + (-body_width / 2.0f) * player.body_angle_sin
        }, 
        {
            player.x + (body_width / 2.0f) * player.body_angle_cos + offset_z * player.body_angle_sin, 
            player.y + offset_y - body_heigh / 2.0f, 
            player.z + -offset_z  * player.body_angle_cos + (body_width / 2.0f) * player.body_angle_sin
        }, 

        90,  0, 180, 180,

        0,
        {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f},

        'f',
        false,

        {224, 164, 164, 255}, {224, 164, 164, 255}, {224, 164, 164, 255},
        1.0f,
        {255, 255, 255},

        -1, 0, 0,
        0
    };
    
    // * first face
    auto projected_face = camera.full_face_projection(raw_face);
    if (projected_face.has_value()) {
        ProjectedFace2d& face_2d = *projected_face;

        projected_faces_2d.push_back(face_2d);
    }

    // * second face
    // set new points pos
    raw_face.point1 = {
        player.x + (-body_width / 2.0f) * player.body_angle_cos + offset_z * player.body_angle_sin, 
        player.y + offset_y + body_heigh / 2.0f, 
        player.z + -offset_z * player.body_angle_cos + (-body_width / 2.0f) * player.body_angle_sin
    };
    raw_face.point2 = {
        player.x + (body_width / 2.0f) * player.body_angle_cos + offset_z * player.body_angle_sin, 
        player.y + offset_y + body_heigh / 2.0f, 
        player.z + -offset_z * player.body_angle_cos + (body_width / 2.0f) * player.body_angle_sin
    };
    raw_face.point3 = {
        player.x + (body_width / 2.0f) * player.body_angle_cos + offset_z * player.body_angle_sin, 
        player.y + offset_y - body_heigh / 2.0f, 
        player.z + -offset_z  * player.body_angle_cos + (body_width / 2.0f) * player.body_angle_sin
    };
        
    projected_face = camera.full_face_projection(raw_face);
    if (projected_face.has_value()) {
        ProjectedFace2d& face_2d = *projected_face;

        projected_faces_2d.push_back(face_2d);
    }
}


// nature
void WorldRenderer::update_clouds(Camera& camera) {
    float height = 8 * BLOCK_SIZE;

    RawFace3d raw_face = {
        {0,   height, 300}, 
        {0,   height, 0}, 
        {200, height, 300}, 

        90,  0, 180, 180,

        0,
        {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f},

        'b',
        false,

        {255, 255, 255, 180}, {255, 255, 255, 180}, {255, 255, 255, 180},
        1.0f,
        {255, 255, 255},

        -1, 0, 0,
        0
    };
    
    // * first face
    auto projected_face = camera.full_face_projection(raw_face);
    if (projected_face.has_value()) {
        ProjectedFace2d& face_2d = *projected_face;

        projected_faces_2d.push_back(face_2d);
    }

    // * second face
    // set new points pos
    raw_face.point1 = {0,   height, 0};
    raw_face.point2 = {200, height, 0};
    raw_face.point3 = {200, height, 300};

    projected_face = camera.full_face_projection(raw_face);
    if (projected_face.has_value()) {
        ProjectedFace2d& face_2d = *projected_face;

        projected_faces_2d.push_back(face_2d);
    }
}

void WorldRenderer::update(Camera& camera, Chunk (&chunks)[CHUNKS_COUNT], Player& player, PlayerInventory& player_inv) {
    project_faces(camera, player, player_inv);

    // update_player_body(camera, player);
    // update_clouds(camera);

    sort_faces();
    update_selected_face();

    update_block_outline(chunks, camera);
    // update_current_chunk_outline(chunks, player);

    

    project_points(camera);
    project_lines(camera);
    
    // set effects
    camera_effect = "";
    if (player.under_water) {
        camera_effect = "water";
    }

    // clear lines
    raw_lines_3d.clear();
}

SDL_Color WorldRenderer::get_face_point_color(SDL_Color& point_color, ProjectedFace2d& face) {
    // check what more lighter
    float r = (float)point_color.r * (float)face.light.r / 255.0f;
    float g = (float)point_color.g * (float)face.light.g / 255.0f;
    float b = (float)point_color.b * (float)face.light.b / 255.0f;
    float a = point_color.a;

    float sun_r = (float)point_color.r * ((float)sun_light * (float)face.sun_light);
    float sun_g = (float)point_color.g * ((float)sun_light * (float)face.sun_light);
    float sun_b = (float)point_color.b * ((float)sun_light * (float)face.sun_light);

    if (sun_r > r) {
        r = sun_r;
    }
    if (sun_g > g) {
        g = sun_g;
    }
    if (sun_b > b) {
        b = sun_b;
    }

    // face coloring under water
    if (camera_effect == "water") {
        // color
        int effect_start_dist = 0 * BLOCK_SIZE;
        if (face.dist > effect_start_dist) {
            float color_multiply = abs(effect_start_dist - face.dist) / 10;
            r /= (color_multiply / 30 + 1);
            g /= (color_multiply / 30 + 1);
    
            b *= (color_multiply / 20 + 1);
        }
        // trans
        effect_start_dist = 5 * BLOCK_SIZE;
        if (face.dist > effect_start_dist) {
            float trans_reduce = abs(effect_start_dist - face.dist) / 5;
            a -= trans_reduce;
        }
    }
    
    // limit color
    if (r > 255) {
        r = 255;
    }
    if (r < 0) {
        r = 0;
    }

    if (g > 255) {
        g = 255;
    }
    if (g < 0) {
        g = 0;
    }

    if (b > 255) {
        b = 255;
    }
    if (b < 0) {
        b = 0;
    }

    if (a > 255) {
        a = 255;
    }
    if (a < 0) {
        a = 0;
    }

    // set and return full color
    SDL_Color color = {
        Uint8(r), Uint8(g), Uint8(b),
        Uint8(a),
    };
    return color;
}

void WorldRenderer::draw_face(SDL_Renderer* renderer, Player& player, ProjectedFace2d& face) {
    if (face.dist > WORLD_CHUNKS_LOAD_DIST && face.block_x == -1) {
        return;
    }

    // if (face.t_id == 0) {
    //     return;
    // }
    // first triangle
    SDL_Color point1_color;
    SDL_Color point2_color;
    SDL_Color point3_color;

    if (FACES_COLORING) {
        point1_color = get_face_point_color(face.point1_color, face);
        point2_color = get_face_point_color(face.point2_color, face);
        point3_color = get_face_point_color(face.point3_color, face);

        // skip on full transparency 
        if (point1_color.a == 0 && point2_color.a == 0 && point3_color.a == 0) {
            return;
        }
    } else {
        point1_color = {255, 255, 255, 255};
        point2_color = {255, 255, 255, 255};
        point3_color = {255, 255, 255, 255};
    }

    SDL_Vertex vertices[3];
    vertices[0].position.x = face.point1.x;
    vertices[0].position.y = face.point1.y;
    vertices[0].color = point1_color;
    vertices[0].tex_coord = {face.t_pos1.x, face.t_pos1.y};

    vertices[1].position.x = face.point2.x;
    vertices[1].position.y = face.point2.y;
    vertices[1].color = point2_color;
    vertices[1].tex_coord = {face.t_pos2.x, face.t_pos2.y};

    vertices[2].position.x = face.point3.x;
    vertices[2].position.y = face.point3.y;
    vertices[2].color = point3_color;
    vertices[2].tex_coord = {face.t_pos3.x, face.t_pos3.y};
    
    // set bland mode if transparent
    if (point1_color.a < 255 || point2_color.a < 255 || point3_color.a < 255) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }

    // get texture and draw
    SDL_Texture* texture = nullptr;
    if (FACES_TEXTURING) {
        texture = all_faces_textures[face.t_id];
    
        SDL_RenderGeometry(renderer, texture, vertices, 3, NULL, 0);
    } else {
        SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
    }

    // second additional
    if (face.has_4_points) {
        vertices[0].position.x = face.point2.x;
        vertices[0].position.y = face.point2.y;
        vertices[0].color = point1_color;
        
        vertices[1].position.x = face.point3.x;
        vertices[1].position.y = face.point3.y;
        vertices[1].color = point2_color;

        vertices[2].position.x = face.point4.x;
        vertices[2].position.y = face.point4.y;
        vertices[2].color = point3_color;
        // set bland mode if transparent
        if (point1_color.a < 255 || point2_color.a < 255 || point3_color.a < 255) {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        }

        if (texture) {
            SDL_RenderGeometry(renderer, texture, vertices, 3, NULL, 0);
        } else {
            SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
        }
    }

    // * draw face breaking texture
    if (
        player.block_breaking_progress != 0 &&

        face.chunk_ind == current_breaking_block_chunk_ind && 

        face.block_x == current_breaking_block_x && 
        face.block_y == current_breaking_block_y && 
        face.block_z == current_breaking_block_z 
    ) {
        SDL_Vertex vertices[3];
        vertices[0].position.x = face.point1.x;
        vertices[0].position.y = face.point1.y;
        vertices[0].color = point1_color;
        vertices[0].tex_coord = {face.t_pos1.x, face.t_pos1.y};

        vertices[1].position.x = face.point2.x;
        vertices[1].position.y = face.point2.y;
        vertices[1].color = point2_color;
        vertices[1].tex_coord = {face.t_pos2.x, face.t_pos2.y};

        vertices[2].position.x = face.point3.x;
        vertices[2].position.y = face.point3.y;
        vertices[2].color = point3_color;
        vertices[2].tex_coord = {face.t_pos3.x, face.t_pos3.y};

        // get texture and draw
        SDL_Texture* texture = nullptr;
        // set texture by progress
        int breaking_complite_percents = int(
            player.block_breaking_progress / player.max_block_breaking_progress
            * 100
        );
        if (breaking_complite_percents < 16) {
            texture = all_faces_textures[texture_name_to_id["block_breaking_6"]];
        } 
        else if (breaking_complite_percents < 32) {
            texture = all_faces_textures[texture_name_to_id["block_breaking_5"]];
        }
        else if (breaking_complite_percents < 48) {
            texture = all_faces_textures[texture_name_to_id["block_breaking_4"]];
        } 
        else if (breaking_complite_percents < 64) {
            texture = all_faces_textures[texture_name_to_id["block_breaking_3"]];
        }
        else if (breaking_complite_percents < 80) {
            texture = all_faces_textures[texture_name_to_id["block_breaking_2"]];
        }
        else {
            texture = all_faces_textures[texture_name_to_id["block_breaking_1"]];
        }

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderGeometry(renderer, texture, vertices, 3, NULL, 0);
    }
}

void WorldRenderer::draw_point(SDL_Renderer* renderer, ProjectedPoint2d& point) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    // create rect and draw
    int w = 4000 / point.rotated_point.z;
    int h = 4000 / point.rotated_point.z;

    SDL_Rect rect = {(int)point.pos.x - w / 2, (int)point.pos.y - h / 2, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void draw_line_with_width(SDL_Renderer* renderer, vec2& start, vec2& end, float thickness, SDL_Color& color)
{
    // Line direction vector
    float x1 = start.x; 
    float y1 = start.y; 
    float x2 = end.x;
    float y2 = end.y;
    
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = std::sqrt(dx * dx + dy * dy);
    if (len == 0.0f) return;

    // Normalize direction
    dx /= len;
    dy /= len;

    // Perpendicular (normal) vector
    float nx = -dy;
    float ny = dx;

    // Half thickness
    float half_t = thickness / 2.0f;

    // Compute 4 corners of the thick line
    SDL_FPoint points[4] = {
        { x1 + nx * half_t, y1 + ny * half_t },
        { x1 - nx * half_t, y1 - ny * half_t },
        { x2 - nx * half_t, y2 - ny * half_t },
        { x2 + nx * half_t, y2 + ny * half_t }
    };

    // Draw as filled polygon (use SDL2_gfx if available)
    // But if you want pure SDL2, you can approximate using SDL_RenderGeometry (SDL 2.0.18+)
    SDL_Vertex verts[4];
    for (int i = 0; i < 4; ++i) {
        verts[i].position = points[i];
        verts[i].color = color;
    }

    int indices[6] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometry(renderer, NULL, verts, 4, indices, 6);
}

void WorldRenderer::draw_line(SDL_Renderer* renderer, ProjectedLine2d& line) {
    
    int width = 2;
    
    draw_line_with_width(renderer, line.start, line.end, width, line.color);
    // SDL_SetRenderDrawColor(renderer, line.color.r, line.color.g, line.color.b, line.color.a); 
    // SDL_RenderDrawLine(renderer, 
        // line.start.x, line.start.y, 
        // line.end.x, line.end.y
    // );
}

void WorldRenderer::draw(SDL_Renderer* renderer, Player& player) {
    // faces
    size_t projected_faces_count = projected_faces_2d.size();
    projected_faces_2d.reserve(100);
    for (size_t pf_i = 0; pf_i < projected_faces_count; pf_i++)
    {
        ProjectedFace2d& projected_face = projected_faces_2d[pf_i];
        draw_face(renderer, player, projected_face);
    } 

    // points
    size_t projected_points_count = projected_points_2d.size();
    projected_points_2d.reserve(100);
    for (size_t pf_i = 0; pf_i < projected_points_count; pf_i++)
    {
        ProjectedPoint2d& projected_point = projected_points_2d[pf_i];
        draw_point(renderer, projected_point);
    } 

    // lines
    size_t projected_lines_count = projected_lines_2d.size();
    projected_lines_2d.reserve(100);
    for (size_t pf_i = 0; pf_i < projected_lines_count; pf_i++)
    {
        ProjectedLine2d& projected_line = projected_lines_2d[pf_i];
        draw_line(renderer, projected_line);
    } 

    // camera effect
    // water
    if (camera_effect == "water") {
        SDL_SetRenderDrawColor(renderer, 10, 10, 100, 120);
        SDL_RenderFillRect(renderer, &screen_effect_rect);
    }

    // target
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_Rect target_rect{
        WINDOW_W / 2 - 2, 
        WINDOW_H / 2 - 2, 
        4, 4
    };
    SDL_RenderFillRect(renderer, &target_rect);

    // * clear projections
    clear_projections();
}



