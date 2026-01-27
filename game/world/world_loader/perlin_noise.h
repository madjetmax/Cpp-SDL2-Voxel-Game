#pragma once

#include <vector>
#include <cmath>
#include <cstdint>
#include <iostream>


using namespace std;


typedef struct {
    float x, y;
} vector2;

class PerlinNoise {
public:
    // * settings
    float set1;
    float set2;
    int   set3;
    float set4;
    float set5;
    float set6;
    float set7;
    int   set8;
    float set9;
    float set10;
    float set11;
    float set12;

    int   grid_size;

    float max_height;
    float min_height;

    // * biomes locations
    string current_biome_name = "default";

    // mountains
    int mount_biome_x = 8 * 10;
    int mount_biome_z = 8 * 10;

    float mount_biome_dist = 14 * 10;

    // desert
    int desert_biome_x = 15 * 10;
    int desert_biome_z = 15 * 10;

    float desert_biome_dist = 4 * 10;

    // * default settings
    float def_set1 = 2.0;
    float def_set2 = 2.0;
    int   def_set3 = 1;
    float def_set4 = 3.0;
    float def_set5 = 2.0;
    float def_set6 = 7.0;
    float def_set7 = 5.2;
    int   def_set8 = 5;
    float def_set9 = 3.1;
    float def_set10 = 2.5;
    float def_set11 = 1.5;
    float def_set12 = 3.0;

    int   def_grid_size = 120;

    float def_max_height = 8.5;
    float def_min_height = -3.0;

    // * mountains settings

    // sharper frequency growth
    float mount_set9 = 1.1f;

    // stronger high-frequency contribution
    float mount_set10 = 1.05f;

    float mount_set11 = 5.5f;   // keep peaks strong
    float mount_set12 = 3.0f;   // lakes stay deep

    // less smoothing from scale
    int   mount_grid_size = 150;

    float mount_max_height = 48.0f;
    float mount_min_height = -3.0f;

    // * desert settings

    float desert_set9 = 3.1;
    float desert_set10 = 2.5f;

    float desert_set11 = 2.5;
    float desert_set12 = 1.0;

    int   desert_grid_size = 200;

    float desert_max_height = 8.5;
    float desert_min_height = 1.0;


    PerlinNoise(void);

    vector2 randomGradient(int ix, int iy);

    // Computes the dot product of the distance and gradient vectors.
    float dotGridGradient(int ix, int iy, float x, float y);
    
    float interpolate(float a0, float a1, float w);
    
    // Sample Perlin noise at coordinates x, y
    float perlin(float x, float y);

    int noise_height(int x, int z);
};