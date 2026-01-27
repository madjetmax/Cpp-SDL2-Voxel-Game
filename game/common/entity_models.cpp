#include "entity_models.h"

uint8_t last_entity_id = 1;

map <uint8_t, FullEntityModel> all_entity_models = {};
vector <CreationEntityModel> all_creation_entities = {};
map <uint8_t, uint8_t> item_id_to_entity_id = {};

void load_drop_items_entities() {
    // loop all items data and load models
    for (auto item = all_items_data.begin(); item != all_items_data.end(); item++) {
        // load as block 
        if (item->second.drop_item_model_type == "block") {
            float scale = 0.25 * item->second.drop_item_model_scale;
            FullBlockModel block_model = all_blocks_models[item->second.place_blocks_ids_range[0]];
            // resize model
            for (size_t fi = 0; fi < block_model.faces.size(); fi++)
            {
                RawFace3d& face = block_model.faces[fi];
                face.point1.x *= scale;
                face.point1.y *= scale;
                face.point1.z *= scale;

                face.point2.x *= scale;
                face.point2.y *= scale;
                face.point2.z *= scale;

                face.point3.x *= scale;
                face.point3.y *= scale;
                face.point3.z *= scale;

                face.visiblity_angle_x_add = 180;
                face.visiblity_angle_y_add = 180;
            }
            
            // add full model
            FullEntityModel full_entity_model = {
                block_model.faces
            };
            
            all_entity_models[last_entity_id] = full_entity_model;
            item_id_to_entity_id[item->first] = last_entity_id;
            last_entity_id++;
        }
        // load as 2d texture
        else if (item->second.drop_item_model_type == "2d") {

            uint8_t texture_id = texture_name_to_id[item->second.t_name];
            // faces as 2d face
            float scale = item->second.drop_item_model_scale;
            vector<RawFace3d> faces = {
                {
                    {-12 * scale, -12 * scale, 0}, {-12 * scale, 12 * scale, 0}, {12 * scale, -12 * scale, 0},
                    0, 0, 180, 180,
                    texture_id,  // texture id
                    {0, 1}, {0, 0}, {1, 1}, 'f', 1,
                },
                {
                    {-12 * scale, 12 * scale, 0}, {12 * scale, 12 * scale, 0}, {12 * scale, -12 * scale, 0},
                    0, 0, 180, 180,
                    texture_id,  // texture id
                    {0, 0}, {1, 0}, {1, 1}, 'f', 1
                },
            };

            // add full model
            FullEntityModel full_entity_model = {faces};
            
            all_entity_models[last_entity_id] = full_entity_model;
            item_id_to_entity_id[item->first] = last_entity_id;
            last_entity_id++;
        }
    };
}