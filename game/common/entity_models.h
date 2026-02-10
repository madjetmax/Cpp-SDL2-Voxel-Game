#include <vector>
#include <string>
#include <iostream>
#include <array>
#include <map>
#include <cstdint>
#include <unordered_map>
#include "types.h"
#include "math_help.h"
#include "../config.h"
#include "../inventory/items_loader.h"

#include "block_models.h"

#ifndef ENTITYMODELS_H
#define ENTITYMODELS_H

using namespace std;


// structs
struct FullEntityModel
{
    vector<RawFace3d> faces;
    
    // collider
    int collider_size_x = 0;
    int collider_size_top = 0;
    int collider_size_bottom = 0;
    int collider_size_z = 0;
};

struct IndexesEntityModel
{
    vector<vec3> points;
    vector<RawIndexesFace3d> faces;
};

struct CreationEntityModel
{
    string name;
    IndexesEntityModel indexes_model;
    vector<string> textures;
};

struct FullEntityData { // make full block data for all cheks in world and interactions
    string name;
};


// all entities
extern uint8_t last_entity_id;

extern map <uint8_t, FullEntityModel> all_entity_models;
extern vector <CreationEntityModel> all_creation_entities;

extern map <uint8_t, uint8_t> item_id_to_entity_id;
extern map <string, uint8_t> mob_name_to_mob_id;


// loading all entities
void load_drop_items_entities();
void load_mobs();

#endif