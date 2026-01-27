#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <cstdint>
#include <unordered_map>
#include "types.h"
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


// loading all entities
void load_drop_items_entities();

#endif