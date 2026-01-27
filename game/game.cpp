#include "game.h"

Game::Game() {}

void Game::init() {
    // init sdl, window and renderer
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = SDL_CreateWindow(
        "Game", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_W, WINDOW_H, 0
    );
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;

    renderer = SDL_CreateRenderer(window, -1, renderer_flags);

    WINDOW_W = SDL_GetWindowSurface(window)->w;     
    WINDOW_H = SDL_GetWindowSurface(window)->h;    

    SDL_ShowCursor(0);   

    player_inventory = new PlayerInventory(WINDOW_W, WINDOW_H);
    world.world_renderer.load_faces_textures(renderer, *player_inventory);

    player_inventory->load_all_textures(renderer);

    world.on_start();

    text_draw.load_all_charecters(renderer);

    // other values
    run = true;
    delta_time = 0;
}

void Game::controls(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            run = false;
        }
        // switch faces sort method
        if (event.key.keysym.sym == SDLK_p) {
            FACES_SORT_WITH_DIST = !FACES_SORT_WITH_DIST;
        }

        // switch faces drawings
        if (event.key.keysym.sym == SDLK_o) {
            FACES_COLORING = !FACES_COLORING;
        }
        if (event.key.keysym.sym == SDLK_t) {
            FACES_TEXTURING = !FACES_TEXTURING;
        }
    }

    // mouse motion
    if (event.type == SDL_MOUSEMOTION) {
        mpos.x = event.motion.x;
        mpos.y = event.motion.y;

        // center mouse 
        if (!world.player.in_inventory) {
            if (mpos.x < WINDOW_W / 2 - 100 || mpos.x > WINDOW_W / 2 + 100) {
                SDL_WarpMouseInWindow(window, WINDOW_W / 2, WINDOW_H / 2);
            }
            if (mpos.y < WINDOW_H / 2 - 100 || mpos.y > WINDOW_H / 2 + 100) {
                SDL_WarpMouseInWindow(window, WINDOW_W / 2, WINDOW_H / 2);
            }
        }
    }
}

void Game::update() {
    world.update(*player_inventory, delta_time);
    player_inventory->update(world.player, world.all_items_drops, mpos, WINDOW_W, WINDOW_H, delta_time);

}

void Game::draw() {
    world.draw(renderer);
    player_inventory->draw(renderer, world.player, text_draw, mpos, WINDOW_W, WINDOW_H);

    debud_draw();
}

void Game::debud_draw() {
    string fps_string = to_string(int(fps));
    text_draw.draw_text(renderer, "fps:" + fps_string, 10, 10, "right", "bottom", 2, true, 150);
}


void Game::main_loop() {
    while (run) {
        
        start_time = SDL_GetTicks();

        // handle events
        SDL_PollEvent(&event);
        controls(event);
        world.controls(event, delta_time);
        player_inventory->controls(event, world.all_items_drops, world.player, WINDOW_W, WINDOW_H);
        if (event.type == SDL_QUIT) {
            run = false;
        }
        
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 5 * world.world_renderer.sun_light, 170 * world.world_renderer.sun_light, 242 * world.world_renderer.sun_light, 255);
        
        SDL_RenderClear(renderer);

        update();
        draw();

        // set fps and delta time
        frame_time = SDL_GetTicks() - start_time;
        fps = (frame_time > 0) ? 1000.0f / frame_time : 0.0f;
        if (fps > 0) {
            delta_time = 100.0f / fps;
        }
        
        // setting window title as game data
        string fps_string = to_string(int(fps));
        string projected_faces_count_string = to_string(world.world_renderer.projected_faces_2d.size());
        string raw_faces3d_count_string = to_string(world.world_renderer.raw_faces_3d.size());
        
        string chunks_to_load_count_string = to_string(world.world_loader.chunks_to_load_queue.size());
        string loaded_chunks_string = to_string(world.world_loader.loaded_chunks.size());
        
        string title = " Raw faces 3d: " + raw_faces3d_count_string + " Projected faces " + projected_faces_count_string + " Sort faces with dist: " + to_string(FACES_SORT_WITH_DIST) + " Dynamic light dist type: " + to_string(DYNAMIC_LIGHT_DIST_TYPE) + " Chunks to load: " + chunks_to_load_count_string +  " Loaded chunks: " + loaded_chunks_string + " FPS: " + fps_string;
        
        SDL_SetWindowTitle(window, title.c_str());
    }
}

void Game::clear() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "game stopped" << endl;
}