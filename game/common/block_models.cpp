#include "block_models.h"

// blocks points types
vector<vec3> full_block_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50,  50}, // 2 
    { 50, -50,  50}, // 3
    // top
    {-50, 50, -50}, // 4 
    { 50, 50, -50}, // 5
    {-50, 50,  50}, // 6 
    { 50, 50,  50}, // 7
};

vector<vec3> full_slab_top_points = {
    // bottom
    {-50,  0, -50}, // 0 
    { 50,  0, -50}, // 1
    {-50,  0,  50}, // 2 
    { 50,  0,  50}, // 3
    // top
    {-50, 50, -50}, // 4 
    { 50, 50, -50}, // 5
    {-50, 50,  50}, // 6 
    { 50, 50,  50}, // 7
};
vector<vec3> full_slab_bottom_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50,  50}, // 2 
    { 50, -50,  50}, // 3
    // top
    {-50, 0, -50}, // 4 
    { 50, 0, -50}, // 5
    {-50, 0,  50}, // 6 
    { 50, 0,  50}, // 7
};

vector<vec3> full_stairs_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50,  50}, // 2 
    { 50, -50,  50}, // 3
    // top back
    {-50,  0, -50}, // 4 
    { 50,  0, -50}, // 5
    // top front
    {-50, 50,  50}, // 6 
    { 50, 50,  50}, // 7
    // middle middle
    {-50, -1,  1}, // 8 
    { 50, -1,  1}, // 9
    // top middle
    {-50, 50,  0}, // 10
    { 50, 50,  0}, // 11
};

vector<vec3> full_water_points = {
    // bottom
    {-50, -60, -50}, // 0 
    { 50, -60, -50}, // 1
    {-50, -60,  50}, // 2 
    { 50, -60,  50}, // 3
    // top
    {-50, 40, -50}, // 4 
    { 50, 40, -50}, // 5
    {-50, 40,  50}, // 6 
    { 50, 40,  50}, // 7
};


vector<vec3> plant1_points = {
    {0, -60, 0},
    {0, 24, 0},

    {37, -60, 37},
    {37, 24, 37},

    {-37, -60, -37},
    {-37, 24, -37},

    {-37, -60, 37},
    {-37, 24, 37},

    {37, -60, -37},
    {37, 24, -37},
};

vector<vec3> torch_points = {
    // bottom
    {-6, -50, -6}, // 0 
    { 6, -50, -6}, // 1
    {-6, -50,  6}, // 2 
    { 6, -50,  6}, // 3
    // top
    {-6, 12, -6}, // 4 
    { 6, 12, -6}, // 5
    {-6, 12,  6}, // 6 
    { 6, 12,  6}, // 7
};

vector<vec3> torch_side_points = {
    // bottom
    {-6, -34, -56}, // 0 
    { 6, -34, -56}, // 1
    {-6, -40, -44}, // 2 
    { 6, -40, -44}, // 3
    // top
    {-6, 20, -28}, // 4 
    { 6, 20, -28}, // 5
    {-6, 14, -16}, // 6 
    { 6, 14, -16}, // 7
};

vector<vec3> beam_points = {
    // bottom
    {-12.5, -50, -12.5}, // 0 
    { 12.5, -50, -12.5}, // 1
    {-12.5, -50,  12.5}, // 2 
    { 12.5, -50,  12.5}, // 3
    // top
    {-12.5, 50, -12.5}, // 4 
    { 12.5, 50, -12.5}, // 5
    {-12.5, 50,  12.5}, // 6 
    { 12.5, 50,  12.5}, // 7
};

vector<vec3> column_points = {
    // bottom
    {-31.25, -50, -31.25}, // 0 
    { 31.25, -50, -31.25}, // 1
    {-31.25, -50,  31.25}, // 2 
    { 31.25, -50,  31.25}, // 3
    // top
    {-31.25, 50, -31.25}, // 4 
    { 31.25, 50, -31.25}, // 5
    {-31.25, 50,  31.25}, // 6 
    { 31.25, 50,  31.25}, // 7
};

// trapdoor
vector<vec3> closed_trapdoor_top_points = {
    // bottom
    {-50, 31, -50}, // 0 
    { 50, 31, -50}, // 1
    {-50, 31,  50}, // 2 
    { 50, 31,  50}, // 3
    // top
    {-50, 50, -50}, // 4 
    { 50, 50, -50}, // 5
    {-50, 50,  50}, // 6 
    { 50, 50,  50}, // 7
};

vector<vec3> opened_trapdoor_top_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50, -31}, // 2 
    { 50, -50, -31}, // 3
    // top
    {-50, 50, -50}, // 4 
    { 50, 50, -50}, // 5
    {-50, 50, -31}, // 6 
    { 50, 50, -31}, // 7
};

vector<vec3> closed_trapdoor_bottom_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50,  50}, // 2 
    { 50, -50,  50}, // 3
    // top
    {-50, -31, -50}, // 4 
    { 50, -31, -50}, // 5
    {-50, -31,  50}, // 6 
    { 50, -31,  50}, // 7
};

vector<vec3> opened_trapdoor_bottom_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50, -31}, // 2 
    { 50, -50, -31}, // 3
    // top
    {-50, 50, -50}, // 4 
    { 50, 50, -50}, // 5
    {-50, 50, -31}, // 6 
    { 50, 50, -31}, // 7
};


vector<vec3> bed_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50,  50}, // 2 
    { 50, -50,  50}, // 3
    // top
    {-50, 45, -50}, // 4 
    { 50, 45, -50}, // 5
    {-50, 45,  50}, // 6 
    { 50, 45,  50}, // 7
};

vector<vec3> plant2_points = {
    // bottom
    {-35, -65, -35}, // 0 
    { 35, -65, -35}, // 1
    {-35, -65,  35}, // 2 
    { 35, -65,  35}, // 3
    // top
    {-35, 25, -35}, // 4 
    { 35, 25, -35}, // 5
    {-35, 25,  35}, // 6 
    { 35, 25,  35}, // 7
};

vector<vec3> door_part_points = {
    // bottom
    {-50, -50, -50}, // 0 
    { 50, -50, -50}, // 1
    {-50, -50, -31}, // 2 
    { 50, -50, -31}, // 3
    // top
    {-50, 50, -50}, // 4 
    { 50, 50, -50}, // 5
    {-50, 50, -31}, // 6 
    { 50, 50, -31}, // 7
};

// types of blocks models
IndexesBlockModel solid_block = {
    full_block_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

IndexesBlockModel solid_slab_top = {
    full_slab_top_points,
    { 
        // front back
        {3, 7, 2,  0, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  0, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  0,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  0,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 0},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 0},
    }
};

IndexesBlockModel solid_slab_bottom = {
    full_slab_bottom_points,
    { //  points  v angle  v angle add
        // front back
        {3, 7, 2,  0, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  0, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  0,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  0,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 0},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 0},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

IndexesBlockModel solid_stairs = {
    full_stairs_points,
    {//  points  v angle  v angle add
        // front
        {3, 7, 2,  0, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  0, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},
        // back bottom
        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},
        // back top
        {8,  10, 9,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 0},
        {10, 11, 9,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 0},

        // right left
        {3, 7,  1,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'r', 1},
        {9, 5,  1,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'r', 1},
        {7, 11, 9,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'r', 1},

        {2, 6,  0,  0,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'l', 1},
        {8, 4,  0,  0,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'l', 1},
        {6, 10, 8,  0,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'l', 1},

        // top back
        {4, 8, 5,  270,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1}, 't', 0},
        {8, 9, 5,  270,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1}, 't', 0},

        // top front
        {10, 6, 11,  270,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1}, 't', 1},
        { 6, 7, 11,  270,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1}, 't', 1},

        // bottom
        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1}, 'd', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1}, 'd', 1},
    }
};

IndexesBlockModel water = {
    full_water_points,
    {
         // front back
        {3, 7, 2,  0, 180,   180, 180, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  0, 180,   180, 180, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 180, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 180, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  0,  90,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  0,  90,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};


IndexesBlockModel plant1 = {
    plant1_points,
    {
        {0, 1, 2,  0, 0,  180, 180,  0, {1, 1}, {1, 0}, {0, 1}, 'f', 0},
        {1, 3, 2,  0, 0,  180, 180,  0, {1, 0}, {0, 0}, {0, 1}, 'f', 0},

        {0, 1, 4,  0, 0,  180, 180,  0, {0, 1}, {0, 0}, {1, 1}, 'f', 0},
        {1, 5, 4,  0, 0,  180, 180,  0, {0, 0}, {1, 0}, {1, 1}, 'f', 0},

        {0, 1, 6,  0, 0,  180, 180,  0, {1, 1}, {1, 0}, {0, 1}, 'f', 0},
        {1, 7, 6,  0, 0,  180, 180,  0, {1, 0}, {0, 0}, {0, 1}, 'f', 0},

        {0, 1, 8,  0, 0,  180, 180,  0, {0, 1}, {0, 0}, {1, 1}, 'f', 0},
        {1, 9, 8,  0, 0,  180, 180,  0, {0, 0}, {1, 0}, {1, 1}, 'f', 0},
    }
};


IndexesBlockModel plant2 = {
    plant2_points,
    {   
        // front back
        {3, 7, 2,  180, 180,   180, 180, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 180, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 180, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 180, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},
    }
};

IndexesBlockModel torch = {
    torch_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  0, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  0, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  0,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  0,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top  bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

IndexesBlockModel torch_side = {
    torch_side_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  0, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  0, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  0,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  0,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   180, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   180, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

IndexesBlockModel beam = {
    beam_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};



IndexesBlockModel column = {
    column_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

// trapdoor
IndexesBlockModel closed_trapdoor_top = {
    closed_trapdoor_top_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 0}, {0, 1}, {1, 0},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 1}, {1, 1}, {1, 0},'d', 1},
    }
};

IndexesBlockModel opened_trapdoor_top = {
    opened_trapdoor_top_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 0}, {0, 1}, {1, 0}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 1}, {1, 1}, {1, 0}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 0}, {0, 1}, {1, 0}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 1}, {1, 1}, {1, 0}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

IndexesBlockModel closed_trapdoor_bottom = {
    closed_trapdoor_bottom_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 0}, {0, 1}, {1, 0},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 1}, {1, 1}, {1, 0},'d', 1},
    }
};


IndexesBlockModel opened_trapdoor_bottom = {
    opened_trapdoor_bottom_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};


IndexesBlockModel bed = {
    bed_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'d', 1},
    }
};

// door
IndexesBlockModel door_part = {
    door_part_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {1, 1}, {1, 0}, {0, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {1, 0}, {0, 0}, {0, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 0}, {0, 1}, {1, 0},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 1}, {1, 1}, {1, 0},'d', 1},
    }
};

IndexesBlockModel door_part_opened = {
    door_part_points,
    { //  points  v angle  v angle add       texture             normal
        // front back
        {3, 7, 2,  180, 180,   180, 90, 0, {1, 1}, {1, 0}, {0, 1}, 'f', 1},
        {7, 6, 2,  180, 180,   180, 90, 0, {1, 0}, {0, 0}, {0, 1}, 'f', 1},

        {0, 4, 1,  0, 0,   180, 90, 0, {0, 1}, {0, 0}, {1, 1}, 'b', 1},
        {4, 5, 1,  0, 0,   180, 90, 0, {0, 0}, {1, 0}, {1, 1}, 'b', 1},

        // right left
        {1, 5, 3,  0, 270,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'r', 1},
        {5, 7, 3,  0, 270,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'r', 1},

        {2, 6, 0,  180,  90,   180, 90, 0, {0, 1}, {0, 0}, {1, 1},'l', 1},
        {6, 4, 0,  180,  90,   180, 90, 0, {0, 0}, {1, 0}, {1, 1},'l', 1},

        // top bottom
        {4, 6, 5,  270, 0,   90, 180, 0, {0, 1}, {0, 0}, {1, 1},'t', 1},
        {6, 7, 5,  270, 0,   90, 180, 0, {0, 0}, {1, 0}, {1, 1},'t', 1},

        {2, 0, 3,  90,  0,   90, 180, 0, {0, 0}, {0, 1}, {1, 0},'d', 1},
        {0, 1, 3,  90,  0,   90, 180, 0, {0, 1}, {1, 1}, {1, 0},'d', 1},
    }
};


map <string, uint8_t> texture_name_to_id = {};
map <int, char> angle_x_to_normal = {
    {180, 'f'},
    {0, 'b'},
    {90, 'd'},
    {270, 't'},
};

map <int, char> angle_y_to_normal = {
    {180, 'f'},
    {0, 'b'},
    {270, 'r'},
    {90, 'l'},
};

map <int, char> angle_z_to_normal = {
    {0, 'r'},
    {180, 'l'},
    {90, 'd'},
    {270, 't'},
};

map <char, int> normal_to_visiblity_angle_y = {
    {'r', 270},
    {'l', 90},
};




FullBlockModel get_full_model_from_indexes_model_angle_x(IndexesBlockModel model, int angle) {
    // get angle sin and cos
    int angle_sin, angle_cos;

    switch (angle) {
        case 0:
            angle_sin = 0;
            angle_cos = 1;
            break;
        case 90:
            angle_sin = 1;
            angle_cos = 0;
            break;
        case 180:
            angle_sin = 0;
            angle_cos = -1;
            break;
        case 270:
            angle_sin = -1;
            angle_cos = 0;
            break;
    }

    // set points pos by angle
    if (angle != 0) {
        for (size_t pi = 0; pi < model.points.size(); pi++)
        {
            vec3& point = model.points[pi];

            int y = point.y * angle_cos + point.z * angle_sin;
            int z = -point.y * angle_sin + point.z * angle_cos;
            point.y = y;
            point.z = z;
        }
    }

    vector<RawFace3d> clear_faces;
    // collect clear faces
    for (size_t fi = 0; fi < model.faces.size(); fi++)
    {
        RawIndexesFace3d& face = model.faces[fi];
        RawFace3d full_face = {
            // get points
            model.points[face.ind1],
            model.points[face.ind2],
            model.points[face.ind3],

            // set angles
            face.visiblity_angle_x, face.visiblity_angle_y,
            face.visiblity_angle_x_add, face.visiblity_angle_y_add,

            // texture
            face.t_id,
            face.t_pos1, face.t_pos2, face.t_pos3,
            
            // normal and for checks
            face.normal, face.hideable,
        }; 
        if (full_face.normal != 'r' && full_face.normal != 'l') {
            full_face.visiblity_angle_x += angle;
    
            if (full_face.visiblity_angle_x >= 360) {
                full_face.visiblity_angle_x -= 360;
            }
            // set normal if rotated
            if (angle != 0) {
                full_face.normal = angle_x_to_normal[full_face.visiblity_angle_x];
            }
            if (full_face.normal == 't' || full_face.normal == 'd') {
                full_face.visiblity_angle_y_add = 180;
                full_face.visiblity_angle_x_add = 90;
            }
        }

        clear_faces.push_back(full_face);
    }
    // return full model
    FullBlockModel full_model = {
        clear_faces
    };

    return full_model;
}

FullBlockModel get_full_model_from_indexes_model_angle_y(IndexesBlockModel model, int angle) {
    // get angle sin and cos
    int angle_sin, angle_cos;

    switch (angle) {
        case 0:
            angle_sin = 0;
            angle_cos = 1;
            break;
        case 90:
            angle_sin = 1;
            angle_cos = 0;
            break;
        case 180:
            angle_sin = 0;
            angle_cos = -1;
            break;
        case 270:
            angle_sin = -1;
            angle_cos = 0;
            break;
    }

    // set points pos by angle
    if (angle != 0) {
        for (size_t pi = 0; pi < model.points.size(); pi++)
        {
            vec3& point = model.points[pi];

            int x = point.x * angle_cos + point.z * angle_sin;
            int z = -point.x * angle_sin + point.z * angle_cos;
            point.x = x;
            point.z = z;
        }
    }

    vector<RawFace3d> clear_faces;
    // collect clear faces
    for (size_t fi = 0; fi < model.faces.size(); fi++)
    {
        RawIndexesFace3d& face = model.faces[fi];

        RawFace3d full_face = {
            // get points
            model.points[face.ind1],
            model.points[face.ind2],
            model.points[face.ind3],

            // set angles
            face.visiblity_angle_x, face.visiblity_angle_y,
            face.visiblity_angle_x_add, face.visiblity_angle_y_add,

            // texture
            face.t_id,
            face.t_pos1, face.t_pos2, face.t_pos3,
            
            // normal and for checks
            face.normal, face.hideable,
        };
        full_face.visiblity_angle_y += angle;

        if (full_face.visiblity_angle_y >= 360) {
            full_face.visiblity_angle_y -= 360;
        }
        // set normal if rotated
        if (angle != 0 && full_face.visiblity_angle_y_add != 180) {
            full_face.normal = angle_y_to_normal[full_face.visiblity_angle_y];
        }

        clear_faces.push_back(full_face);
    }
    // return full model
    FullBlockModel full_model = {
        clear_faces
    };

    return full_model;
}

FullBlockModel get_full_model_from_indexes_model_angle_z(IndexesBlockModel model, int angle) {
    // get angle sin and cos
    int angle_sin, angle_cos;

    switch (angle) {
        case 0:
            angle_sin = 0;
            angle_cos = 1;
            break;
        case 90:
            angle_sin = 1;
            angle_cos = 0;
            break;
        case 180:
            angle_sin = 0;
            angle_cos = -1;
            break;
        case 270:
            angle_sin = -1;
            angle_cos = 0;
            break;
    }

    // set points pos by angle
    if (angle != 0) {
        for (size_t pi = 0; pi < model.points.size(); pi++)
        {
            vec3& point = model.points[pi];

            int x = point.x * angle_cos + point.y * angle_sin;
            int y = -point.x * angle_sin + point.y * angle_cos;
            point.x = x;
            point.y = y;
        }
    }

    vector<RawFace3d> clear_faces;
    // collect clear faces
    for (size_t fi = 0; fi < model.faces.size(); fi++)
    {
        RawIndexesFace3d& face = model.faces[fi];

        RawFace3d full_face = {
            // get points
            model.points[face.ind1],
            model.points[face.ind2],
            model.points[face.ind3],

            // set angles
            face.visiblity_angle_x, face.visiblity_angle_y,
            face.visiblity_angle_x_add, face.visiblity_angle_y_add,

            // texture
            face.t_id,
            face.t_pos1, face.t_pos2, face.t_pos3,
            
            // normal and for checks
            face.normal, face.hideable,
        };
        if (full_face.normal != 'f' && full_face.normal != 'b') {
            full_face.visiblity_angle_x += angle;
    
            if (full_face.visiblity_angle_x >= 360) {
                full_face.visiblity_angle_x -= 360;
            }
            // set normal if rotated
            if (angle != 0) {
                full_face.normal = angle_z_to_normal[full_face.visiblity_angle_x];
            }
            if (full_face.normal == 't' || full_face.normal == 'd') {
                full_face.visiblity_angle_y_add = 180;
                full_face.visiblity_angle_x_add = 90;

            } else {
                full_face.visiblity_angle_y = normal_to_visiblity_angle_y[full_face.normal];
                full_face.visiblity_angle_y_add = 90;

                full_face.visiblity_angle_x_add = 180;
            }
        }

        clear_faces.push_back(full_face);

    }
    // return full model
    FullBlockModel full_model = {
        clear_faces
    };

    return full_model;
}

// load all blocks
void load_all_blocks() {
    uint8_t block_id = 1; // 0 = air

    for (size_t bi = 0; bi < all_creation_blocks.size(); bi++)
    {
        CreationBlockModel creation_model = all_creation_blocks[bi];
        
        // set texure for indexes model
        IndexesBlockModel& indexes_model = creation_model.indexes_model;
        
        for (size_t fi = 0; fi < creation_model.textures.size(); fi++)
        {
            RawIndexesFace3d& face = indexes_model.faces[fi];
            string texture_name = creation_model.textures[fi];
            if (texture_name == "") {
                face.t_id = 0;
                continue;
            }
            uint8_t texture_id = texture_name_to_id[texture_name];
            face.t_id = texture_id; //creation_model.textures[fi];
        }

        // * add full_models with all angles
        // x
        int angles_count = creation_model.angles_x.size();
        for (size_t ai = 0; ai < angles_count; ai++)
        {
            int angle = creation_model.angles_x[ai];
            uint8_t hide_faces_model_id = creation_model.hide_faces_models_ids[ai];
            uint8_t colliders_id = creation_model.colliders_ids[ai];

            FullBlockModel full_model = get_full_model_from_indexes_model_angle_x(indexes_model, angle);
            all_blocks_models[block_id] = full_model;

            // * add full data
            string name = creation_model.name;
            // add angle suffix to name
            if (angles_count > 0 ) {
                name += to_string(angle);
            } 

            // colliders
            vector <BlockCollider>* colliders = &all_blocks_colliders[colliders_id];

            // drop items 
            vector<FullBlockDropItemData> drop_items = {};
            for (size_t di = 0; di < creation_model.drop_items.size(); di++)
            {
                BlockDropItemData& drop_item_data = creation_model.drop_items[di];
                FullBlockDropItemData full_drop_item = {
                    item_name_to_item_id[drop_item_data.name],
                    {drop_item_data.rand_count_range[0], drop_item_data.rand_count_range[1]},
                    drop_item_data.increaseabe_count
                };
                drop_items.push_back(full_drop_item);
            }

            FullBlockData full_data {
                name, 
                hide_faces_model_id,
                colliders,
                // light
                creation_model.light,
                creation_model.place_on_blocks_ids,
                creation_model.interaction_type,
                drop_items,
                creation_model.can_destroy_grass,
                creation_model.can_destroy_bed,
                creation_model.strength,
                creation_model.breaking_speed_increase_items_ids,
                creation_model.drop_by_items_ids,
            };
            
            all_blocks_full_data[block_id] = full_data;
            block_id++;
        }
        // y
        angles_count = creation_model.angles_y.size();
        for (size_t ai = 0; ai < angles_count; ai++)
        {
            int angle = creation_model.angles_y[ai];
            uint8_t hide_faces_model_id = creation_model.hide_faces_models_ids[ai];
            uint8_t colliders_id = creation_model.colliders_ids[ai];

            FullBlockModel full_model = get_full_model_from_indexes_model_angle_y(indexes_model, angle);
            all_blocks_models[block_id] = full_model;

            // * add full data
            string name = creation_model.name;
            // add angle suffix to name
            if (angles_count > 0 ) {
                name += to_string(angle);
            } 

            // colliders
            vector <BlockCollider>* colliders = &all_blocks_colliders[colliders_id];

            // drop items 
            vector<FullBlockDropItemData> drop_items = {};
            for (size_t di = 0; di < creation_model.drop_items.size(); di++)
            {
                BlockDropItemData& drop_item_data = creation_model.drop_items[di];
                FullBlockDropItemData full_drop_item = {
                    item_name_to_item_id[drop_item_data.name],
                    {drop_item_data.rand_count_range[0], drop_item_data.rand_count_range[1]},
                    drop_item_data.increaseabe_count
                };
                drop_items.push_back(full_drop_item);
            }

            FullBlockData full_data {
                name, 
                hide_faces_model_id,
                colliders,
                // light
                creation_model.light,
                creation_model.place_on_blocks_ids,
                creation_model.interaction_type,
                drop_items,
                creation_model.can_destroy_grass,
                creation_model.can_destroy_bed,
                creation_model.strength,
                creation_model.breaking_speed_increase_items_ids,
                creation_model.drop_by_items_ids,
            };

            all_blocks_full_data[block_id] = full_data;
            block_id++;
        }
        // z
        angles_count = creation_model.angles_z.size();
        for (size_t ai = 0; ai < angles_count; ai++)
        {
            int angle = creation_model.angles_z[ai];
            uint8_t hide_faces_model_id = creation_model.hide_faces_models_ids[ai];
            uint8_t colliders_id = creation_model.colliders_ids[ai];

            FullBlockModel full_model = get_full_model_from_indexes_model_angle_z(indexes_model, angle);
            all_blocks_models[block_id] = full_model;

            // * add full data
            string name = creation_model.name;
            // add angle suffix to name
            if (angles_count > 0 ) {
                name += to_string(angle);
            } 

            // colliders
            vector <BlockCollider>* colliders = &all_blocks_colliders[colliders_id];
            
            // drop items 
            vector<FullBlockDropItemData> drop_items = {};
            for (size_t di = 0; di < creation_model.drop_items.size(); di++)
            {
                BlockDropItemData& drop_item_data = creation_model.drop_items[di];
                FullBlockDropItemData full_drop_item = {
                    item_name_to_item_id[drop_item_data.name],
                    {drop_item_data.rand_count_range[0], drop_item_data.rand_count_range[1]},
                    drop_item_data.increaseabe_count
                };

                drop_items.push_back(full_drop_item);
            }

            FullBlockData full_data {
                name, 
                hide_faces_model_id,
                colliders,
                // light
                creation_model.light,
                creation_model.place_on_blocks_ids,
                creation_model.interaction_type,
                drop_items,
                creation_model.can_destroy_grass,
                creation_model.can_destroy_bed,
                creation_model.strength,
                creation_model.breaking_speed_increase_items_ids,
                creation_model.drop_by_items_ids,
            };
            
            all_blocks_full_data[block_id] = full_data;
            block_id++;
        }
    }
}

// all blocks
map <uint8_t, FullBlockModel> all_blocks_models;
unordered_map <uint8_t, FullBlockData> all_blocks_full_data;

vector <CreationBlockModel> all_creation_blocks = {
    // {
    //     "test",
    //     solid_block,
    //     {
    //         0, 0,
    //         0, 0,

    //         0, 0,
    //         0, 0,

    //         0, 0,
    //         0, 0,
    //     },
    //     {0},
    //     {1}
    // },
    // {
    //     "test_slab_top",
    //     solid_slab_top,
    //     {
    //         0, 0,
    //         0, 0,

    //         0, 0,
    //         0, 0,

    //         0, 0,
    //         0, 0,
    //     },
    //     {0},
    //     {2}
    // },
    
    // {
    //     "test_stairs",
    //     solid_stairs,
    //     {
    //         0, 0, 

    //         0, 0, 

    //         0, 0, 

    //         0, 
    //         0, 
    //         0, 

    //         0,
    //         0,
    //         0,
            
    //         0, 0, 
            
    //         0, 0, 

    //         0, 0, 
    //     },
    //     {0, 90, 180, 270},
    //     {4, 5, 6, 7}
    // },
    // base world blocks
    {
        "solid_grass",
        solid_block,
        {
            "grass_side", "grass_side", 
            "grass_side", "grass_side", 

            "grass_side", "grass_side", 
            "grass_side", "grass_side", 

            "grass_top", "grass_top", 
            "grass_bottom", "grass_bottom", 
            
        },
        // angles
        {},
        {0, 90, 180, 270},
        {},
        
        {1, 1,  1,   1},
        {1, 1,  1,   1},
        // light 
        {0, 0, 0},
        {},
        "dig_bed",
        {{"dirt_block", {1, 1}}},
        true, true,
        100,
    },
    {
        "solid_dirt",
        solid_block,
        {
            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 

            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 

            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "dig_bed",
        {{"dirt_block", {1, 1}}},
        true, true,
        100,
    },
    {
        "water",
        water,
        {
            "water_top", "water_top",
            "water_top", "water_top",

            "water_top", "water_top",
            "water_top", "water_top",

            "water_top", "water_top",
            "water_top", "water_top",
        },
        // angles
        {}, {0}, {},

        {8},
        {11},
        // light 
        {0, 0, 0},
        {},
        "take_water"
    },
    {
        "solid_sand",
        solid_block,
        {
            "sand_side", "sand_side", 
            "sand_side", "sand_side", 

            "sand_side", "sand_side", 
            "sand_side", "sand_side", 

            "sand_side", "sand_side", 
            "sand_side", "sand_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"sand_block", {1, 1}}},
        true, true,
        100, 
    },
    {
        "low_grass",
        plant1,
        {
            "low_grass_side2","low_grass_side2",
            "low_grass_side1","low_grass_side1",

            "low_grass_side2","low_grass_side2",
            "low_grass_side1","low_grass_side1",
        },
        // angles
        {}, {0}, {},

        {0},
        {0},

        {0, 0, 0},
        {1, 2, 3, 4},
        "",
        {},
        false
    },
    // other 
    {
        "solid_cobblestone",
        solid_block,
        {
            "cobblestone_side", "cobblestone_side", 
            "cobblestone_side", "cobblestone_side", 

            "cobblestone_side", "cobblestone_side", 
            "cobblestone_side", "cobblestone_side", 

            "cobblestone_side", "cobblestone_side", 
            "cobblestone_side", "cobblestone_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"cobblestone_block", {1, 1}}},
        true, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "cobblestone_slab_top",
        solid_slab_top,
        {
            "cobblestone_slab_side_top", "cobblestone_slab_side_top", 
            "cobblestone_slab_side_top", "cobblestone_slab_side_top", 

            "cobblestone_slab_side_top", "cobblestone_slab_side_top", 
            "cobblestone_slab_side_top", "cobblestone_slab_side_top", 

            "cobblestone_side", "cobblestone_side", 
            "cobblestone_side", "cobblestone_side", 
        },
        // angles
        {}, {0}, {},

        {2},
        {3},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"cobblestone_slab", {1, 1}}},
        false, false,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "cobblestone_slab_bottom",
        solid_slab_bottom,
        {
            "cobblestone_slab_side_bottom", "cobblestone_slab_side_bottom", 
            "cobblestone_slab_side_bottom", "cobblestone_slab_side_bottom", 

            "cobblestone_slab_side_bottom", "cobblestone_slab_side_bottom", 
            "cobblestone_slab_side_bottom", "cobblestone_slab_side_bottom", 

            "cobblestone_side", "cobblestone_side", 
            "cobblestone_side", "cobblestone_side", 
        },
        // angles
        {}, {0}, {},

        {3},
        {2},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"cobblestone_slab", {1, 1}}},
        true, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "solid_glass",
        solid_block,
        {
            "glass_side", "glass_side", 
            "glass_side", "glass_side", 

            "glass_side", "glass_side", 
            "glass_side", "glass_side", 

            "glass_side", "glass_side", 
            "glass_side", "glass_side", 
        },
        // angles
        {}, {0}, {},

        {9},
        {1},

        // light 
        {0, 0, 0},
        {},
        "",
        {},
        false, true,
        100,
    },
    {
        "wood_log",
        solid_block,
        {
            "wood_side", "wood_side", 
            "wood_side", "wood_side", 

            "wood_side", "wood_side", 
            "wood_side", "wood_side", 

            "wood_top", "wood_top", 
            "wood_top", "wood_top", 
        },
        // angles
        {90}, {0}, {90},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "lighter_firing",
        {{"wood_log", {1, 1}}},
        true, true,
        300,
    },
    {
        "wooden_planks",
        solid_block,
        {
            "wooden_planks", "wooden_planks", 
            "wooden_planks", "wooden_planks", 

            "wooden_planks", "wooden_planks", 
            "wooden_planks", "wooden_planks", 

            "wooden_planks", "wooden_planks", 
            "wooden_planks", "wooden_planks", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"wooden_planks", {1, 1}}},
        true, true,
        300,
    },
    {
        "torch",
        torch,
        {
            "torch_side", "torch_side", 
            "torch_side", "torch_side", 

            "torch_side", "torch_side", 
            "torch_side", "torch_side", 

            "torch_top", "torch_top",
            "torch_bottom", "torch_bottom",
        },
        // angles
        {}, {0}, {},

        {0},
        {0},

        // light 
        {252, 214, 160},
        {},
        "",
        {{"torch", {1, 1}}},
        false
    },
    {
        "torch side",
        torch_side,
        {
            "torch_side", "torch_side", 
            "torch_side", "torch_side", 

            "torch_side", "torch_side", 
            "torch_side", "torch_side", 

            "torch_top", "torch_top",
            "torch_bottom", "torch_bottom",
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {0, 0, 0, 0},
        {0, 0, 0, 0},

        // light 
        {252, 214, 160},
        {},
        "",
        {{"torch", {1, 1}}},
        false
    },
    // lamps
    {
        "white_lamp",
        solid_block,
        {
            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {255, 255, 255},
        {},
        "",              
        {},              
        true, true,
        200,
    },
    {
        "red_lamp",
        solid_block,
        {
            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},

        // light 
        {255, 50, 50},
        {},
        "",              
        {},              
        true, true,
        200,
    },
    {
        "green_lamp",
        solid_block,
        {
            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},

        // light 
        {50, 255, 50},
        {},
        "",              
        {},              
        true, true,
        200,
    },
    {
        "blue_lamp",
        solid_block,
        {
            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 

            "lamp_side", "lamp_side", 
            "lamp_side", "lamp_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},

        // light 
        {100, 100, 255},
        {},
        "",              
        {},              
        true, true,
        200,
    },
    {
        "stone",
        solid_block,
        {
            "stone_side", "stone_side", 
            "stone_side", "stone_side", 

            "stone_side", "stone_side", 
            "stone_side", "stone_side", 

            "stone_side", "stone_side", 
            "stone_side", "stone_side", 
        },
        // angles
        {}, {0, 180}, {},

        {1, 1},
        {1, 1},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"stone_block", {1, 1}}},
        true, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "wooden_beam",
        beam,
        {
            "wooden_beam_side", "wooden_beam_side", 
            "wooden_beam_side", "wooden_beam_side", 

            "wooden_beam_side", "wooden_beam_side", 
            "wooden_beam_side", "wooden_beam_side", 

            "wooden_beam_top", "wooden_beam_top", 
            "wooden_beam_top", "wooden_beam_top", 
        },
        // angles
        {}, {0}, {},

        {0},
        {4},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"wooden_beam", {1, 1}}},
        false, true,
        300,
    },
    // trapdoor
    {
        "closed_wooden_trapdoor_top",
        closed_trapdoor_top,
        {
            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 

            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 

            "wooden_trapdoor_top", "wooden_trapdoor_top", 
            "wooden_trapdoor_top", "wooden_trapdoor_top", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {0, 0, 0, 0},
        {5, 5, 5, 5},

        // light 
        {0, 0, 0},
        {},
        "open_trapdoor",
        {{"wooden_trapdoor", {1, 1}}},
        false, true,
        300,
    },
    {
        "opened_wooden_trapdoor_top",
        opened_trapdoor_top,
        {
            "wooden_trapdoor_top", "wooden_trapdoor_top", 
            "wooden_trapdoor_top", "wooden_trapdoor_top", 

            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 

            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {0, 0, 0, 0},
        {8, 10, 7, 9},

        // light 
        {0, 0, 0},
        {},
        "close_trapdoor",
        {{"wooden_trapdoor", {1, 1}}},
        false, true,
        300,
    },
    {
        "closed_wooden_trapdoor_bottom",
        closed_trapdoor_bottom,
        {
            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 

            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 

            "wooden_trapdoor_top", "wooden_trapdoor_top", 
            "wooden_trapdoor_top", "wooden_trapdoor_top", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {0, 0, 0, 0},
        {6, 6, 6, 6},

        // light 
        {0, 0, 0},
        {},
        "open_trapdoor",
        {{"wooden_trapdoor", {1, 1}}},
        false, true,
        300,
    },
    {
        "opened_wooden_trapdoor_bottom",
        opened_trapdoor_bottom,
        {
            "wooden_trapdoor_top", "wooden_trapdoor_top", 
            "wooden_trapdoor_top", "wooden_trapdoor_top", 

            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 

            "wooden_trapdoor_side", "wooden_trapdoor_side", 
            "wooden_trapdoor_side", "wooden_trapdoor_side", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {0, 0, 0, 0},
        {8, 10, 7, 9},

        // light 
        {0, 0, 0},
        {},
        "close_trapdoor",
        {{"wooden_trapdoor", {1, 1}}},
        false, true,
        300,
    },

    // bed
    {
        "dry_bed",
        bed,
        {
            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 

            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 

            "dry_bed_top", "dry_bed_top", 
            "grass_bottom", "grass_bottom", 
        },
        // angles
        {}, {0}, {},

        {3},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"dirt_block", {1, 1}}},
        true, true,
        100,
    },
    {
        "wet_bed",
        bed,
        {
            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 

            "grass_bottom", "grass_bottom", 
            "grass_bottom", "grass_bottom", 

            "wet_bed_top", "wet_bed_top", 
            "grass_bottom", "grass_bottom", 
        },
        // angles
        {}, {0}, {},

        {3},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"dirt_block", {1, 1}}},
        true, true,
        100,
    },

    // * plants
    // wheat
    {
        "wheet_0",
        plant2,
        {
            "plant_0_side", "plant_0_side", 
            "plant_0_side", "plant_0_side", 

            "plant_0_side", "plant_0_side", 
            "plant_0_side", "plant_0_side", 
        },
        // angles
        {}, {0}, {},

        {0},
        {0},
        // light 
        {0, 0, 0},
        {45, 46},
        "",
        {{"wheat_seeds", {1, 1}}},
    },
    {
        "wheat_1",
        plant2,
        {
            "wheat_1_side", "wheat_1_side", 
            "wheat_1_side", "wheat_1_side", 

            "wheat_1_side", "wheat_1_side", 
            "wheat_1_side", "wheat_1_side", 
        },
        // angles
        {}, {0}, {},

        {0},
        {0},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"wheat_seeds", {1, 1}}},
    },
    {
        "wheat_2",
        plant2,
        {
            "wheat_2_side", "wheat_2_side", 
            "wheat_2_side", "wheat_2_side", 

            "wheat_2_side", "wheat_2_side", 
            "wheat_2_side", "wheat_2_side", 
        },
        // angles
        {}, {0}, {},

        {0},
        {0},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"wheat_seeds", {1, 1}}},
    },
    {
        "wheat_3",
        plant2,
        {
            "wheat_3_side", "wheat_3_side", 
            "wheat_3_side", "wheat_3_side", 

            "wheat_3_side", "wheat_3_side", 
            "wheat_3_side", "wheat_3_side", 
        },
        // angles
        {}, {0}, {},

        {0},
        {0},
        // light 
        {0, 0, 0},
        {},
        "",
        {
            { "wheat", {1, 1}},
            {"wheat_seeds", {1, 1}}
        },
    },
    {
        "storage_box",
        solid_block,
        {
            "barrel_side", "barrel_side", 
            "barrel_side", "barrel_side", 

            "barrel_side", "barrel_side", 
            "barrel_side", "barrel_side", 

            "barrel_top", "barrel_top", 
            "barrel_top", "barrel_top", 
        },
        // angles
        {90}, {0}, {90},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "storage_inv",
        {{"storage_box", {1, 1}}},
        true, true,
        300,
    },

    {
        "leaves_block",
        solid_block,
        {
            "leaves_side", "leaves_side", 
            "leaves_side", "leaves_side", 

            "leaves_side", "leaves_side", 
            "leaves_side", "leaves_side", 

            "leaves_side", "leaves_side", 
            "leaves_side", "leaves_side", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {0, 0, 0, 0},
        {1, 1, 1, 1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"stick", {-3, 1}}},
        false, true,
        50,
    },

    // door
    {
        "closed_door_top",
        door_part,
        {
            "door_top_front", "door_top_front", 
            "door_top_front", "door_top_front", 
            
            "door_top_side", "door_top_side", 
            "door_side", "door_side", 

            "door_side", "door_side", 
            "", "", 
        },
        // angles
        {}, {0, 180}, {},

        {0, 0},
        {8, 7},

        // light 
        {0, 0, 0},
        {},
        "open_door_top",
        {{"door", {1, 1}}},
        false, true,
        300,
    },
    {
        "opened_door_top",
        door_part_opened,
        {
            "door_top_front", "door_top_front", 
            "door_top_front", "door_top_front", 
            
            "door_side", "door_side", 
            "door_top_side", "door_top_side", 

            "door_side", "door_side", 
            "", "", 
        },
        // angles
        {}, {90, 270}, {},

        {0, 0},
        {10, 9},

        // light 
        {0, 0, 0},
        {},
        "close_door_top",
        {{"door", {1, 1}}},
        false, true,
        300,
    },
    {
        "closed_door_bottom",
        door_part,
        {
            "door_bottom_front", "door_bottom_front", 
            "door_bottom_front", "door_bottom_front", 
            
            "door_bottom_side", "door_bottom_side", 
            "door_side", "door_side", 

            "", "", 
            "door_side", "door_side", 
        },
        // angles
        {}, {0, 180}, {},

        {0, 0},
        {8, 7},

        // light 
        {0, 0, 0},
        {},
        "open_door_bottom",
        {{"door", {1, 1}}},
        false, true,
        300,
    },
    {
        "opened_door_bottom",
        door_part_opened,
        {
            "door_bottom_front", "door_bottom_front", 
            "door_bottom_front", "door_bottom_front", 
            
            "door_side", "door_side", 
            "door_bottom_side", "door_bottom_side", 

            "", "", 
            "door_side", "door_side", 
        },
        // angles
        {}, {90, 270}, {},

        {0, 0},
        {10, 9},

        // light 
        {0, 0, 0},
        {},
        "close_door_bottom",
        {{"door", {1, 1}}},
        false, true,
        300,
    },

    {
        "grayed_stone",
        solid_block,
        {
            "grayed_stone_side", "grayed_stone_side", 
            "grayed_stone_side", "grayed_stone_side", 

            "grayed_stone_side", "grayed_stone_side", 
            "grayed_stone_side", "grayed_stone_side", 

            "grayed_stone_side", "grayed_stone_side", 
            "grayed_stone_side", "grayed_stone_side", 
        },
        // angles
        {}, {0, 180}, {},

        {1, 1},
        {1, 1},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"grayed_stone_block", {1, 1}}},
        true, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },


    {
        "stone_slab_top",
        solid_slab_top,
        {
            "stone_slab_side_top", "stone_slab_side_top", 
            "stone_slab_side_top", "stone_slab_side_top", 

            "stone_slab_side_top", "stone_slab_side_top", 
            "stone_slab_side_top", "stone_slab_side_top", 

            "stone_side", "stone_side", 
            "stone_side", "stone_side", 
        },
        // angles
        {}, {0}, {},

        {2},
        {3},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"stone_slab", {1, 1}}},
        false, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "stone_slab_bottom",
        solid_slab_bottom,
        {
            "stone_slab_side_bottom", "stone_slab_side_bottom", 
            "stone_slab_side_bottom", "stone_slab_side_bottom", 

            "stone_slab_side_bottom", "stone_slab_side_bottom", 
            "stone_slab_side_bottom", "stone_slab_side_bottom", 

            "stone_side", "stone_side", 
            "stone_side", "stone_side", 
        },
        // angles
        {}, {0}, {},

        {3},
        {2},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"stone_slab", {1, 1}}},
        true, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "wooden_slab_top",
        solid_slab_top,
        {
            "wooden_slab_side_top", "wooden_slab_side_top", 
            "wooden_slab_side_top", "wooden_slab_side_top", 

            "wooden_slab_side_top", "wooden_slab_side_top", 
            "wooden_slab_side_top", "wooden_slab_side_top", 

            "wooden_planks", "wooden_planks", 
            "wooden_planks", "wooden_planks", 
        },
        // angles
        {}, {0}, {},

        {2},
        {3},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"wooden_slab", {1, 1}}},
        false, true,
        300,
    },
    {
        "wooden_slab_bottom",
        solid_slab_bottom,
        {
            "wooden_slab_side_bottom", "wooden_slab_side_bottom", 
            "wooden_slab_side_bottom", "wooden_slab_side_bottom", 

            "wooden_slab_side_bottom", "wooden_slab_side_bottom", 
            "wooden_slab_side_bottom", "wooden_slab_side_bottom", 

            "wooden_planks", "wooden_planks", 
            "wooden_planks", "wooden_planks", 
        },
        // angles
        {}, {0}, {},

        {3},
        {2},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"wooden_slab", {1, 1}}},
        false, true,
        300,
    },
    {
        "gravel",
        solid_block,
        {
            "gravel_side", "gravel_side", 
            "gravel_side", "gravel_side", 

            "gravel_side", "gravel_side", 
            "gravel_side", "gravel_side", 

            "gravel_side", "gravel_side", 
            "gravel_side", "gravel_side", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {1, 1, 1, 1},
        {1, 1, 1, 1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"gravel_block", {1, 1}}},
        true, true,
        100,
    },
    {
        "lava",
        water,
        {
            "lava_top", "lava_top",
            "lava_top", "lava_top",

            "lava_top", "lava_top",
            "lava_top", "lava_top",

            "lava_top", "lava_top",
            "lava_top", "lava_top",
        },
        // angles
        {}, {0}, {},

        {8},
        {11},
        // light 
        {255, 230, 100},
        {},
        "take_lava"
    },
    {
        "obsidian",
        solid_block,
        {
            "obsidian_side", "obsidian_side", 
            "obsidian_side", "obsidian_side", 

            "obsidian_side", "obsidian_side", 
            "obsidian_side", "obsidian_side", 

            "obsidian_side", "obsidian_side", 
            "obsidian_side", "obsidian_side", 
        },
        // angles
        {}, {0, 90, 180, 270}, {},

        {1, 1, 1, 1},
        {1, 1, 1, 1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"obsidian_block", {1, 1}}},
        true, true,
        1000,
    },
    {
        "dry_sponge",
        solid_block,
        {
            "dry_sponge_side", "dry_sponge_side", 
            "dry_sponge_side", "dry_sponge_side", 

            "dry_sponge_side", "dry_sponge_side", 
            "dry_sponge_side", "dry_sponge_side", 

            "dry_sponge_side", "dry_sponge_side", 
            "dry_sponge_side", "dry_sponge_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"dry_sponge_block", {1, 1}}},
        true, true,
        200,
    },
    {
        "wet_sponge",
        solid_block,
        {
            "wet_sponge_side", "wet_sponge_side", 
            "wet_sponge_side", "wet_sponge_side", 

            "wet_sponge_side", "wet_sponge_side", 
            "wet_sponge_side", "wet_sponge_side", 

            "wet_sponge_side", "wet_sponge_side", 
            "wet_sponge_side", "wet_sponge_side", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"wet_sponge_block", {1, 1}}},
        true, true,
        200,
    },
    {
        "tnt",
        solid_block,
        {
            "tnt_side", "tnt_side", 
            "tnt_side", "tnt_side", 

            "tnt_side", "tnt_side", 
            "tnt_side", "tnt_side", 

            "tnt_top", "tnt_top", 
            "tnt_top", "tnt_top", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"tnt_block", {1, 1}}},
        true, true,
        50,
    },
    {
        "stone_column",
        column,
        {
            "stone_column_side", "stone_column_side", 
            "stone_column_side", "stone_column_side", 

            "stone_column_side", "stone_column_side", 
            "stone_column_side", "stone_column_side", 

            "stone_column_top", "stone_column_top", 
            "stone_column_top", "stone_column_top", 
        },
        // angles
        {}, {0}, {},

        {0},
        {12},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"stone_column", {1, 1}}},
        false, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },

    // ores
    {
        "coal_ore",
        solid_block,
        {
            "coal_ore_side", "coal_ore_side", 
            "coal_ore_side", "coal_ore_side", 

            "coal_ore_side", "coal_ore_side", 
            "coal_ore_side", "coal_ore_side", 

            "coal_ore_side", "coal_ore_side", 
            "coal_ore_side", "coal_ore_side", 
        },
        // angles
        {}, {0, 180}, {},

        {1, 1},
        {1, 1},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"coal", {1, 3}}},
        true, true,
        600,
        {39, 40}, {39, 40},
    },
    {
        "iron_ore",
        solid_block,
        {
            "iron_ore_side", "iron_ore_side", 
            "iron_ore_side", "iron_ore_side", 

            "iron_ore_side", "iron_ore_side", 
            "iron_ore_side", "iron_ore_side", 

            "iron_ore_side", "iron_ore_side", 
            "iron_ore_side", "iron_ore_side", 
        },
        // angles
        {}, {0, 180}, {},

        {1, 1},
        {1, 1},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"iron_ore_block", {1, 1}}},
        true, true,
        600,
        {39, 40}, {39, 40},
    },

    {
        "rose",
        plant1,
        {
            "rose_side2","rose_side2",
            "rose_side1","rose_side1",

            "rose_side2","rose_side2",
            "rose_side1","rose_side1",
        },
        // angles
        {}, {0}, {},

        {0},
        {0},

        {0, 0, 0},
        {1, 2, 3, 4},
        "",
        {},
        false
    },

    {
        "granite",
        solid_block,
        {
            "granite_side", "granite_side", 
            "granite_side", "granite_side", 

            "granite_side", "granite_side", 
            "granite_side", "granite_side", 

            "granite_side", "granite_side", 
            "granite_side", "granite_side", 
        },
        // angles
        {}, {0, 180}, {},

        {1, 1},
        {1, 1},

        // light 
        {0, 0, 0},
        {},
        "",
        {{"granite_block", {1, 1}}},
        true, true,
        500,
        {38, 39, 40}, {38, 39, 40},
    },
    {
        "crafter",
        solid_block,
        {
            "crafter_side", "crafter_side", 
            "crafter_side", "crafter_side", 

            "crafter_side", "crafter_side", 
            "crafter_side", "crafter_side", 

            "crafter_top", "crafter_top", 
            "crafter_bottom", "crafter_bottom", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},

        // light 
        {0, 0, 0},
        {},
        "crafter",
        {{"crafter_block", {1, 1}}},
        true, true,
        350,
    },
    {
        "fire_wood_log",
        solid_block,
        {
            "fire_wood_side", "fire_wood_side", 
            "fire_wood_side", "fire_wood_side", 

            "fire_wood_side", "fire_wood_side", 
            "fire_wood_side", "fire_wood_side", 

            "wood_top", "wood_top", 
            "wood_top", "wood_top", 
        },
        // angles
        {}, {0}, {},

        {1},
        {1},
        // light 
        {252, 214, 160},
        {},
        "",
        {{"wood_log", {1, 1}}},
        true, true,
        400,
    },
    {
        "burnt_wood_log",
        solid_block,
        {
            "burnt_wood_side", "burnt_wood_side", 
            "burnt_wood_side", "burnt_wood_side", 

            "burnt_wood_side", "burnt_wood_side", 
            "burnt_wood_side", "burnt_wood_side", 

            "burnt_wood_top", "burnt_wood_top", 
            "burnt_wood_top", "burnt_wood_top", 
        },
        // angles
        {90}, {0}, {90},

        {1},
        {1},
        // light 
        {0, 0, 0},
        {},
        "",
        {{"coal", {-3, 2}}},
        true, true,
        200,
    },
};

// models for checks for faces hide
unordered_map<uint16_t, HideFacesBlockModel> hide_faces_block_models = {
    // * solid block    
    {(1 << 8) | 1, { // solid_block solid_block
        1, 1, 1, 1, 1, 1
    }},
    {(1 << 8) | 2, { // solid_block solid_slab_top
        0, 0, 0, 0, 0, 1
    }},
    {(1 << 8) | 3, { // solid_block solid_slab_bottom
        0, 0, 0, 0, 1, 0
    }},
    {(1 << 8) | 4, { // solid_block solid_stairs_0
        0, 1, 0, 0, 1, 0
    }},
    {(1 << 8) | 5, { // solid_block solid_stairs_90
        0, 0, 0, 1, 1, 0
    }},
    {(1 << 8) | 6, { // solid_block solid_stairs_180
        1, 0, 0, 0, 1, 0
    }},
    {(1 << 8) | 7, { // solid_block solid_stairs_270
        0, 0, 1, 0, 1, 0
    }},
    {(1 << 8) | 8, { // solid_block water
        0, 0, 0, 0, 0, 0
    }},
    {(1 << 8) | 9, { // solid_block glass
        0, 0, 0, 0, 0, 0
    }},

    // * solid_slab_top
    {(2 << 8) | 1, { // solid_slab_top solid_block
        1, 1, 1, 1, 1, 1
    }},
    {(2 << 8) | 2, { // solid_slab_top solid_slab_top
        1, 1, 1, 1, 0, 1
    }},
    {(2 << 8) | 3, { // solid_slab_top solid_slab_bottom
        0, 0, 0, 0, 1, 0
    }},
    {(2 << 8) | 4, { // solid_slab_top solid_stairs_0
        0, 1, 0, 0, 1, 0
    }},
    {(2 << 8) | 5, { // solid_slab_top solid_stairs_90
        0, 0, 0, 1, 1, 0
    }},
    {(2 << 8) | 6, { // solid_slab_top solid_stairs_180
        1, 0, 0, 0, 1, 0
    }},
    {(2 << 8) | 7, { // solid_slab_top solid_stairs_270
        0, 0, 1, 0, 1, 0
    }},
    {(2 << 8) | 8, { // solid_slab_top water
        0, 0, 0, 0, 0, 0
    }},
    {(2 << 8) | 9, { // solid_slab_bottom glass
        0, 0, 0, 0, 0, 0
    }},

    // * solid_slab_bottom
    {(3 << 8) | 1, { // solid_slab_bottom solid_block
        1, 1, 1, 1, 0, 1
    }},
    {(3 << 8) | 2, { // solid_slab_bottom solid_slab_top
        0, 0, 0, 0, 0, 1
    }},
    {(3 << 8) | 3, { // solid_slab_bottom solid_slab_bottom
        1, 1, 1, 1, 1, 0
    }},
    {(3 << 8) | 4, { // solid_slab_bottom solid_stairs_0
        0, 1, 0, 0, 1, 1
    }},
    {(3 << 8) | 5, { // solid_slab_bottom solid_stairs_90
        0, 0, 0, 1, 1, 1
    }},
    {(3 << 8) | 6, { // solid_slab_bottom solid_stairs_180
        1, 0, 0, 0, 1, 1
    }},
    {(3 << 8) | 7, { // solid_slab_bottom solid_stairs_270
        0, 0, 1, 0, 1, 1
    }},
    {(3 << 8) | 8, { // solid_slab_bottom water
        0, 0, 0, 0, 0, 0
    }},
    {(3 << 8) | 9, { // solid_slab_bottom glass
        0, 0, 0, 0, 0, 0
    }},

    // * solid_stairs_0 (facing +Z)
    {(4 << 8) | 1, { // solid_stairs_0 solid_block
        1, 1, 1, 1, 1, 1
    }},
    {(4 << 8) | 2, { // solid_stairs_0 solid_slab_top
        0, 1, 0, 0, 1, 0
    }},
    {(4 << 8) | 3, { // solid_stairs_0 solid_slab_bottom
        0, 1, 0, 0, 1, 1
    }},
    {(4 << 8) | 4, { // solid_stairs_0 solid_stairs_0
        1, 1, 1, 1, 1, 1
    }},
    {(4 << 8) | 5, { // solid_stairs_0 solid_stairs_90
        0, 1, 0, 1, 1, 0
    }},
    {(4 << 8) | 6, { // solid_stairs_0 solid_stairs_180
        1, 0, 0, 0, 1, 0
    }},
    {(4 << 8) | 7, { // solid_stairs_0 solid_stairs_270
        0, 1, 1, 0, 1, 0
    }},
    {(4 << 8) | 8, { // solid_stairs_0 water
        0, 0, 0, 0, 0, 0
    }},
    {(4 << 8) | 9, { // solid_stairs_0 glass
        0, 0, 0, 0, 0, 0
    }},

    // * solid_stairs_90 (facing +X)
    {(5 << 8) | 1, {1, 1, 1, 1, 1, 1}},
    {(5 << 8) | 2, {0, 0, 0, 1, 1, 0}},
    {(5 << 8) | 3, {0, 0, 0, 1, 1, 1}},
    {(5 << 8) | 4, {0, 1, 0, 1, 1, 0}},
    {(5 << 8) | 5, {1, 1, 1, 1, 1, 1}},
    {(5 << 8) | 6, {0, 1, 0, 1, 1, 0}},
    {(5 << 8) | 7, {0, 1, 1, 0, 1, 0}},
    {(5 << 8) | 8, {0, 0, 0, 0, 0, 0}},
    {(5 << 8) | 9, {0, 0, 0, 0, 0, 0}},


    // * solid_stairs_180 (facing -Z)
    {(6 << 8) | 1, {1, 1, 1, 1, 1, 1}},
    {(6 << 8) | 2, {1, 0, 0, 0, 1, 0}},
    {(6 << 8) | 3, {1, 0, 0, 0, 1, 1}},
    {(6 << 8) | 4, {1, 0, 0, 0, 1, 0}},
    {(6 << 8) | 5, {0, 1, 0, 1, 1, 0}},
    {(6 << 8) | 6, {1, 1, 1, 1, 1, 1}},
    {(6 << 8) | 7, {0, 1, 1, 0, 1, 0}},
    {(6 << 8) | 8, {0, 0, 0, 0, 0, 0}},
    {(6 << 8) | 9, {0, 0, 0, 0, 0, 0}},


    // * solid_stairs_270 (facing -X)
    {(7 << 8) | 1, {1, 1, 1, 1, 1, 1}},
    {(7 << 8) | 2, {0, 0, 1, 0, 1, 0}},
    {(7 << 8) | 3, {0, 0, 1, 0, 1, 1}},
    {(7 << 8) | 4, {0, 1, 1, 0, 1, 0}},
    {(7 << 8) | 5, {0, 1, 0, 1, 1, 0}},
    {(7 << 8) | 6, {1, 0, 0, 0, 1, 0}},
    {(7 << 8) | 7, {1, 1, 1, 1, 1, 1}},
    {(7 << 8) | 8, {0, 0, 0, 0, 0, 0}},
    {(7 << 8) | 9, {0, 0, 0, 0, 0, 0}},

    // * water   
    {(8 << 8) | 1, { // water solid_block
        1, 1, 1, 1, 0, 1
    }},
    {(8 << 8) | 2, { // water solid_slab_top
        0, 0, 0, 0, 0, 1
    }},
    {(8 << 8) | 3, { // water solid_slab_bottom
        1, 1, 1, 1, 0, 0
    }},
    {(8 << 8) | 4, { // water solid_stairs_0
        0, 1, 0, 0, 0, 1
    }},
    {(8 << 8) | 5, { // water solid_stairs_90
        0, 0, 0, 1, 0, 1
    }},
    {(8 << 8) | 6, { // water solid_stairs_180
        1, 0, 0, 0, 0, 1
    }},
    {(8 << 8) | 7, { // water solid_stairs_270
        0, 0, 1, 0, 0, 1
    }},
    {(8 << 8) | 8, { // water water
        1, 1, 1, 1, 1, 1
    }},
    {(8 << 8) | 9, { // water glass
        0, 0, 0, 0, 0, 0
    }},

    // * glass
    {(9 << 8) | 1, { // glass solid_block
        1, 1, 1, 1, 1, 1
    }},
    {(9 << 8) | 2, { // glass solid_slab_top
        0, 0, 0, 0, 0, 1
    }},
    {(9 << 8) | 3, { // glass solid_slab_bottom
        0, 0, 0, 0, 1, 0
    }},
    {(9 << 8) | 4, { // glass solid_stairs_0
        0, 1, 0, 0, 1, 0
    }},
    {(9 << 8) | 5, { // glass solid_stairs_90
        0, 0, 0, 1, 1, 0
    }},
    {(9 << 8) | 6, { // glass solid_stairs_180
        1, 0, 0, 0, 1, 0
    }},
    {(9 << 8) | 7, { // glass solid_stairs_270
        0, 0, 1, 0, 1, 0
    }},
    {(9 << 8) | 8, { // glass water
        0, 0, 0, 0, 0, 0
    }},
    {(9 << 8) | 9, { // glass glass
        1, 1, 1, 1, 1, 1
    }},
};

// blocks colliders
unordered_map <uint8_t, vector<BlockCollider>> all_blocks_colliders = {
    {1, // solid
        {
            {
                0, 0, 0,
                BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
            }
        }
    },
    {2, // slab bottom
        {
            {
                0, 0, 0,
                BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE,
                true
            }
        }
    },
    {3, // slab top
        {
            {
                0, BLOCK_SIZE / 2, 0,
                BLOCK_SIZE, BLOCK_SIZE / 2, BLOCK_SIZE,
                true
            }
        }
    },
    {4, // beam
        {
            {
                37.5, 0, 37.5,
                25, BLOCK_SIZE, 25,
            }
        }
    },
    // trapdoor
    {5, // closed top
        {
            {
                0, BLOCK_SIZE-19, 0,
                BLOCK_SIZE, 19, BLOCK_SIZE,
            }
        }
    },
    {6, // closed bottom
        {
            {
                0, 0, 0,
                BLOCK_SIZE, 19, BLOCK_SIZE,
            }
        }
    },
    {7, // opened front
        {
            {
                0, 0, BLOCK_SIZE-19,
                BLOCK_SIZE, BLOCK_SIZE, 19,
            }
        }
    },
    {8, // opened back
        {
            {
                0, 0, 0,
                BLOCK_SIZE, BLOCK_SIZE, 19,
            }
        }
    },
    {9, // opened right
        {
            {
                BLOCK_SIZE-19, 0, 0,
                19, BLOCK_SIZE, BLOCK_SIZE,
            }
        }
    },
    {10, // opened left
        {
            {
                0, 0, 0,
                19, BLOCK_SIZE, BLOCK_SIZE,
            }
        }
    },

    {11, // water, lava
        {
            {
                0, 0, 0,
                BLOCK_SIZE, BLOCK_SIZE-5, BLOCK_SIZE,
            }
        }
    },

    {12, // beam
        {
            {
                18.75, 0, 18.75,
                62, BLOCK_SIZE,  62,
            }
        }
    },
};