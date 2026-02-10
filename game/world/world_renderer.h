#include <string>
#include <iostream>
#include <vector>
#include "../../inc/SDL.h"
#include "../../inc/SDL_image.h"

#include "../common/types.h"
#include "../common/math_help.h"
#include "../common/block_models.h"
#include "../inventory/player_inventory.h"
#include "player.h"

#include "block/block.h"
#include "chunk/chunk.h"


#include "camera.h"

using namespace std; 

#ifndef WORLDRENDERER_H
#define WORLDRENDERER_H

class WorldRenderer {
public:
    vector <RawFace3d> raw_faces_3d;
    vector <ProjectedFace2d> projected_faces_2d;
    vector <ProjectedFace2d> selected_faces_2d;

    ProjectedFace2d* selected_face = nullptr;
    ProjectedFace2d last_selected_face;

    // block breaking
    int current_breaking_block_chunk_ind;

    int current_breaking_block_x;
    int current_breaking_block_y;
    int current_breaking_block_z;

    vector <RawPoint3d> raw_points_3d;
    vector <ProjectedPoint2d> projected_points_2d;

    vector <RawLine3d> raw_lines_3d;
    vector <ProjectedLine2d> projected_lines_2d;

    map <uint8_t, SDL_Texture*> all_faces_textures;
    uint8_t last_t_id = 1;

    float sun_light = 1; // 1 max

    // block outline
    int average_block_outline_y;

    // camera effects
    string camera_effect;
    SDL_Rect screen_effect_rect;

    // methods
    WorldRenderer(void);

    void load_faces_textures(SDL_Renderer* renderer, PlayerInventory& player_inv);
    void load_face_texture(SDL_Renderer* renderer, string name, string path, PlayerInventory& player_inv, bool add_to_player_inv);

    void project_faces(Camera& camera, Player& player, PlayerInventory& player_inv);

    void add_selected_face(ProjectedFace2d& face, PlayerInventory& player_inv);
    void project_points(Camera& camera);
    void project_lines(Camera& camera);

    void clear_projections();
    void sort_faces();

    void update_selected_face();

    void update_block_outline(Chunk (&chunks)[CHUNKS_COUNT], Camera& camera);
    void update_current_chunk_outline(Chunk (&chunks)[CHUNKS_COUNT], Player& player);

    // player body
    void update_player_body(Camera& camera, Player& player);

    // nature
    void update_clouds(Camera& camera);

    void update(Camera& camera, Chunk (&chunks)[CHUNKS_COUNT], Player& player, PlayerInventory& player_inv);

    SDL_Color get_face_point_color(SDL_Color& point_color, ProjectedFace2d& face);
    void draw_face(SDL_Renderer* renderer, Player& player, ProjectedFace2d& face);

    void draw_point(SDL_Renderer* renderer, ProjectedPoint2d& point);
    void draw_line(SDL_Renderer* renderer, ProjectedLine2d& line);

    void draw(SDL_Renderer* renderer, Player& player);

};


#endif