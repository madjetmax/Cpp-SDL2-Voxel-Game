#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <cstdint>
#include <unordered_map>
#include "types.h"
#include "../config.h"
#include "../inventory/items_loader.h"

#ifndef BLOCKMODELS_H
#define BLOCKMODELS_H

using namespace std;


// structs
struct FullBlockModel
{
    vector<RawFace3d> faces;
};

struct IndexesBlockModel
{
    vector<vec3> points;
    vector<RawIndexesFace3d> faces;
};

struct BlockDropItemData {
    string name;
    int rand_count_range[2];
    bool increaseabe_count = false;
};

struct FullBlockDropItemData {
    uint8_t id;
    int rand_count_range[2];
    bool increaseabe_count = false;
};

struct CreationBlockModel
{
    string name;
    IndexesBlockModel indexes_model;
    vector<string> textures;
    vector<int> angles_x;
    vector<int> angles_y;
    vector<int> angles_z;

    vector<uint8_t> hide_faces_models_ids;
    vector<uint8_t> colliders_ids;

    BlockLight light;

    vector<uint8_t> place_on_blocks_ids;

    string interaction_type = "";

    vector<BlockDropItemData> drop_items = {};
    bool can_destroy_grass = true;
    bool can_destroy_bed = true;

    int strength;
    vector <uint8_t> breaking_speed_increase_items_ids = {};
    vector <uint8_t> drop_by_items_ids = {0}; // {0} == any item or empty slot
};

// colliders
struct BlockCollider 
{
    float x, y, z;
    int size_x, size_y, size_z;
    bool auto_jump = false;
};

struct FullBlockData { // make full block data for all cheks in world and interactions
    string name;
    uint8_t hide_faces_model_id;
    vector <BlockCollider>* colliders;
    // light
    BlockLight light;

    vector<uint8_t> place_on_blocks_ids;

    string interaction_type;

    vector <FullBlockDropItemData> drop_items;
    bool can_destroy_grass;
    bool can_destroy_bed;

    int strength = 5;
    vector <uint8_t> breaking_speed_increase_items_ids;
    vector <uint8_t> drop_by_items_ids;
};

// models of block checks, hide faces, smooth light
struct HideFacesBlockModel
{
    bool front, back, right, left, top, bottom;
};

// blocks points types
extern vector<vec3> full_block_points;
extern vector<vec3> full_slab_top_points;
extern vector<vec3> full_slab_bottom_points;
extern vector<vec3> full_stairs_points;

extern vector<vec3> full_water_points;

// types of blocks models
extern IndexesBlockModel solid_block;
extern IndexesBlockModel solid_slab_top;
extern IndexesBlockModel solid_slab_bottom;
extern IndexesBlockModel solid_stairs;

extern IndexesBlockModel water;


extern map <string, uint8_t> texture_name_to_id;
extern map <int, char> angle_x_to_normal;
extern map <int, char> angle_y_to_normal;
extern map <int, char> angle_z_to_normal;


FullBlockModel get_full_model_from_indexes_model_angle_x(IndexesBlockModel model, int agnle);
FullBlockModel get_full_model_from_indexes_model_angle_y(IndexesBlockModel model, int agnle);
FullBlockModel get_full_model_from_indexes_model_angle_z(IndexesBlockModel model, int agnle);

// all blocks
extern map <uint8_t, FullBlockModel> all_blocks_models;
extern unordered_map <uint8_t, FullBlockData> all_blocks_full_data;
extern vector <CreationBlockModel> all_creation_blocks;

// models for checks for faces hide
extern unordered_map <uint16_t, HideFacesBlockModel> hide_faces_block_models;

// models for colliders
extern unordered_map <uint8_t, vector<BlockCollider>> all_blocks_colliders;

// loading all block
void load_all_blocks();

#endif