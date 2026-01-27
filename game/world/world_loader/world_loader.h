#include <iostream>
#include <chrono>
#include <thread>
#include "math.h"
#include "../../../inc/SDL.h"

#include "../../config.h"

#include "../block/block.h"
#include "../chunk/chunk.h"
#include "../player.h"

#include "../../common/block_models.h"
#include "../../common/math_help.h"
#include "../world_renderer.h"

#include "../../inventory/player_inventory.h"
#include "../../inventory/items_loader.h"


using namespace std;
using namespace std::chrono; 

#ifndef WORLDLOADER_H
#define WORLDLOADER_H

struct ChunkToLoad {
    Chunk* chunk;
    int chunk_ind;
    bool remove_faces;
    bool add_to_loaded_chunks;
    int dist;
};

class WorldLoader {
public:
    // copies from world
    vector<BlockEntity>* all_blocks_entities = nullptr;

    // chunks 
    vector <Chunk*> loaded_chunks;
    float rand_update_cooldown = 0;

    int last_updated_chunk_ind1 = 0;
    int last_updated_chunk_ind2 = 0;

    // states to hide face while world loading
    bool hide_front_face = false;
    bool hide_back_face = false;

    bool hide_right_face = false;
    bool hide_left_face = false;

    bool hide_top_face = false;
    bool hide_bottom_face = false;

    // blocks ids around block while loading chunk
    uint8_t front_block_id = 0;
    uint8_t back_block_id = 0;

    uint8_t right_block_id = 0;
    uint8_t left_block_id = 0;

    uint8_t top_block_id = 0;
    uint8_t bottom_block_id = 0;

    // for abientn shadowing
    bool blocks_around_shadowable[3][2][3]; // y -1 y +1
    bool blocks_around_shadowable_udpated = false;

    uint8_t water_transparency = 200;

    vector<Block> light_sources_blocks_around;

    // near chunks
    Chunk* near_chunk_front = nullptr;
    Chunk* near_chunk_back = nullptr;
    Chunk* near_chunk_right = nullptr;
    Chunk* near_chunk_left = nullptr;
    Chunk* near_chunk_top = nullptr;
    Chunk* near_chunk_bottom = nullptr;

    // chunks loading
    vector<ChunkToLoad> chunks_to_load_queue;
    int current_chunk_to_load_ind = 0;

    bool force_chunks_load = false;
    
    // last player world pos for chunks loadings
    int last_player_world_x;
    int last_player_world_y;
    int last_player_world_z;

    // interactions
    int last_block_breaking_x = -1;
    int last_block_breaking_y = -1;
    int last_block_breaking_z = -1;

    FullBlockData* current_breaking_block_data = nullptr;

    WorldLoader(void);

    void full_chunk_load(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], int chunk_ind, Chunk& chunk);
    void clear_block_shadowable_around();
    
    void set_near_chunks(Chunk (&chunks)[CHUNKS_COUNT], int chunk_x, int chunk_y, int chunk_z);
    int set_light_sources_blocks_around(Chunk (&chunks)[CHUNKS_COUNT], int chunk_x, int chunk_y, int chunk_z);
    
    int get_chunk_ind_by_pos(int x, int y, int z);

    
    void check_block_faces_visible(Block& block, FullBlockData& block_data, int x, int y, int z, Chunk& chunk);
    Block* get_block_by_pos(int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT]);
    
    void check_blocks_around(Block& block, FullBlockData& block_data, int bx, int by, int bz, Chunk& chunk, Chunk (&chunks)[CHUNKS_COUNT]);

    void set_block_updates(Chunk (&chunks)[CHUNKS_COUNT], Block& block, Chunk& chunk, int chunk_ind);
    void check_light_sources(Block& block, float& block_sun_light, BlockLight& block_light, int light_sources_size);

    bool hide_face(RawFace3d& face);
    
    void base_face_shadowing(RawFace3d& face);
    void ambiant_face_shadowing(RawFace3d& face);

    void update_face_pos(RawFace3d& face, Block& block, Chunk& chunk);

    void clear_chunk_faces(WorldRenderer& world_renderer, int chunk_ind);
    
    void remove_loaded_chunk(Chunk& chunk);
    void check_chunks_to_load(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], Player& player);
    void sort_chunks_to_load_queue();
    void update_chunks_to_load_queue(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], Player& player, float dt);

    void reload_all_chunks(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT]);
    // loaded chunks
    void update_loaded_chunks(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], float dt);

    // player interctions
    bool check_chunk_added_to_load_queue(Chunk& chunk);
    void update_near_chunks(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], Chunk& chunk, int block_x, int block_y, int block_z, Player& player, bool only_on_borders);
    void delete_block_from_light_sources(Block& block, Chunk& chunk);
    void update_block_break(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], vector<ItemDrop>& all_items_drops, map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, Player& player, PlayerInventory& player_inv, float dt);
    bool check_chunk_is_air(Chunk& chunk);

    Chunk* add_block(WorldRenderer& world_renderer, uint8_t block_id, FullBlockData& block_data, Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, int chunk_ind, int& block_x, int& block_y, int& block_z, Player& player);
    void update_block_place(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, Player& player, PlayerInventory& player_inv, float dt);
    
    bool check_block_interaction(WorldRenderer& world_renderer, Block& block, FullBlockData& block_data, Chunk& chunk, int chunk_ind, Chunk (&chunks)[CHUNKS_COUNT], map<uint16_t, StorageBoxInv>& storages, Player& player,  PlayerInventory& player_inv, float dt);

    void update(WorldRenderer& world_renderer, Chunk (&chunks)[CHUNKS_COUNT], vector<ItemDrop>& all_items_drops, map<uint16_t, StorageBoxInv>& storages, uint16_t& last_storage_id, Player& player,  PlayerInventory& player_inv, float dt);
};


#endif