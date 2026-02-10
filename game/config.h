#ifndef CONFIG_H
#define CONFIG_H

extern int WINDOW_W;
extern int WINDOW_H;

extern float MOUSE_SENS;
extern bool FACES_SORT_WITH_DIST;
extern bool FACES_COLORING;
extern bool FACES_TEXTURING;

extern bool DYNAMIC_LIGHT_DIST_TYPE;

// world
constexpr int BLOCK_SIZE = 100;

constexpr int CHUNK_SIZE_X = 10;
constexpr int CHUNK_SIZE_Y = 10;
constexpr int CHUNK_SIZE_Z = 10;

constexpr int WORLD_SIZE_X = 20;
constexpr int WORLD_SIZE_Y = 10;
constexpr int WORLD_SIZE_Z = 20;

constexpr int CHUNKS_COUNT = WORLD_SIZE_X * WORLD_SIZE_Y * WORLD_SIZE_Z;

constexpr int WORLD_CHUNKS_LOAD_DIST = 7000;

constexpr int BLOCK_SELECT_DIST = 2400;

// light
constexpr int SUN_LIGHT_MAX_DIST = 15 * BLOCK_SIZE;
constexpr int LIGHT_MAX_DIST = 10 * BLOCK_SIZE;

#endif