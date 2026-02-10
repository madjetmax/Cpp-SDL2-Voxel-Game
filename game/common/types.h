#include <string>
#include "../../inc/SDL.h"

#ifndef TYPES_H
#define TYPES_H

using namespace std;

struct vec2 {
    float x, y;
};

struct vec3 {
    float x, y, z;
};

struct t_vec2 {
    float x, y;
};

struct BlockLight {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

struct RawIndexesFace3d {
    int ind1, ind2, ind3;

    int visiblity_angle_x, visiblity_angle_y; 
    int visiblity_angle_x_add, visiblity_angle_y_add; 

    // texture
    uint8_t t_id;
    t_vec2 t_pos1, t_pos2, t_pos3;

    // normal and for checks
    char normal;
    bool hideable;
};


struct RawFace3d {
    vec3 point1, point2, point3;

    int visiblity_angle_x, visiblity_angle_y; 
    int visiblity_angle_x_add, visiblity_angle_y_add; 

    // texture
    uint8_t t_id;
    t_vec2 t_pos1, t_pos2, t_pos3;

    // normal and for checks
    char normal;
    bool hideable;

    // color 
    SDL_Color point1_color, point2_color, point3_color;
    float sun_light;
    BlockLight light;

    // block and chunk data
    short block_x = -1; 
    unsigned short block_y, block_z; 
    unsigned short chunk_ind;
};


struct ProjectedFace2d {
    vec2 point1, point2, point3;
    vec2 point4; // optional
    bool has_4_points; // to set if face has additional 4th poitn

    vec3 rotated_point1, rotated_point2, rotated_point3;
    
    // texture
    uint8_t t_id;
    t_vec2 t_pos1, t_pos2, t_pos3;
    
    char normal;

    // color 
    SDL_Color point1_color, point2_color, point3_color;
    float sun_light;
    BlockLight light;

    // block and chunk data
    short block_x = -1;
    unsigned short block_y, block_z; 
    unsigned short chunk_ind;
    
    // dist
    float dist;

    // entity data
    short entity_ind = -1; 
};

struct RawPoint3d
{
    vec3 pos;
};
struct ProjectedPoint2d
{
    vec2 pos;

    vec3 rotated_point;
};


struct RawLine3d
{
    vec3 start, end;

    SDL_Color color;
};
struct ProjectedLine2d
{
    vec2 start, end;

    vec3 rotated_point1;
    vec3 rotated_point2;

    SDL_Color color;
};

// inventory

struct ItemLight {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

struct InventoryItemData {
    string name;
    string title;
    string t_name;

    float item_w;
    float item_h;

    int8_t max_stack;
    float max_durability;

    // interactions
    string type;
    string block_place_type;
    int place_blocks_ids_range[2];

    // drop item
    string drop_item_model_type = "block";
    float drop_item_model_scale = 1;

    // interactions
    float breaking_increase_speed = 1;

    // item light
    ItemLight item_light = {0, 0, 0};
};

struct InventorySlot {
    uint8_t item_id = 0;
    uint8_t items_count = 0;
    float durability = 0;
};

// * inventories
struct StorageBoxInv {
    InventorySlot slots[45];
};

#endif