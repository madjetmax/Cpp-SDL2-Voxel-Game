#include "perlin_noise.h"
// PerlinTerrain.cpp


PerlinNoise::PerlinNoise() {}

vector2 PerlinNoise::randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = set1 * sizeof(unsigned);
    const unsigned s = w / set2; 
    unsigned a = ix, b = iy;
    // a *= 444324242940018;
    // a *= 343492904032;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    // b *= 4234244909312423;
    b *= 987285003;
    // b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 1391038418745;
    // a *= 2344343;
    // a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> set3)); // in [0, 2*Pi]
    
    // Create the vector from the angle
    vector2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    vector2 gradient = randomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * gradient.x + dy * gradient.y);
}

float PerlinNoise::interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (set4 - w * set5) * w * w + a0;
}


// Sample Perlin noise at coordinates x, y
float PerlinNoise::perlin(float x, float y) {
    
    // Determine grid cell corner coordinates
    int x0 = (int)x; 
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    
    // Compute Interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;
    
    // Compute and interpolate top two corners
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);
    
    // Compute and interpolate bottom two corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);
    
    // Final step: interpolate between the two previously interpolated values, now in y
    float value = interpolate(ix0, ix1, sy);
    
    return value;
}


int PerlinNoise::noise_height(int x, int z) {
    // * setting settings
    
    set1       = def_set1;
    set2       = def_set2;
    set3       = def_set3;
    set4       = def_set4;
    set5       = def_set5;
    set6       = def_set6;
    set7       = def_set7;
    set8       = def_set8;
    set9       = def_set9;
    set10      = def_set10;
    set11      = def_set11;
    set12      = def_set12;

    grid_size  = def_grid_size;

    max_height = def_max_height;
    min_height = def_min_height;

    // set biome data
    current_biome_name = "default";

    // * set mout biome
    int dist_x = abs(mount_biome_x - x);
    int dist_z = abs(mount_biome_z - z);

    if (dist_x <= mount_biome_dist && dist_z <= mount_biome_dist) {
        float dist = sqrt(
            dist_x*dist_x + 
            dist_z*dist_z
        );
        if (dist <= mount_biome_dist) {
            dist /= 80.0f;

            set9       = min(mount_set9  * (dist + 1.0f), def_set9);
            set10      = min(mount_set10 * (dist + 1.0f), def_set10);

            set11      = max(mount_set11 / (dist + 1.0f), def_set11);
            set12      = max(mount_set12 / (dist + 1.0f), def_set12);
    
            grid_size  = int(max(float(mount_grid_size) / (dist + 1.0f), float(def_grid_size)));
    
            max_height = max(mount_max_height / (dist + 1.0f), def_max_height);
            min_height = min(mount_min_height * (dist + 1.0f), def_min_height);

            // set biome data
            current_biome_name = "mountains";
        }
    }

    // * desert
    dist_x = abs(desert_biome_x - x);
    dist_z = abs(desert_biome_z - z);

    if (dist_x <= desert_biome_dist && dist_z <= desert_biome_dist) {
        float dist = sqrt(
            dist_x*dist_x + 
            dist_z*dist_z
        );
        if (dist <= desert_biome_dist) {
            dist /= 80.0f;

            set10      = min(desert_set10 * (dist + 1.0f), def_set10);

            set11      = max(desert_set11 / (dist + 1.0f), def_set11);
            set12      = max(desert_set12 / (dist + 1.0f), def_set12);
    
            grid_size  = int(max(float(desert_grid_size) / (dist + 1.0f), float(def_grid_size)));
    
            max_height = max(desert_max_height / (dist + 1.0f), def_max_height);
            min_height = min(desert_min_height * (dist + 1.0f), def_min_height);

            // set biome data
            current_biome_name = "desert";
        }
    }

    // * calculations
    int index = (z * set6 + x) * set7;
    float val = 0.0f;
    float freq = 1.0f;
    float amp = 1.0f;

    for (size_t i = 0; i < set8; i++) {
        val += perlin(x * freq / grid_size, z * freq / grid_size) * amp;
        freq *= set9;
        amp /= set10;
    }

    // Apply amplification
    if (val > 0.0f) {
        val *= set11;
    } else {
        val *= set12;
    }


    // Clamp to max/min heights
    if (val > max_height)
        val = max_height;

    if (val < min_height)
        val = min_height;

    // Final remap and return as height
    return (int)((((val + 1.0f) * 0.5f) * 255) - 120) / 10;
}
