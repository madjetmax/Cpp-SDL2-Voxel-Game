#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <cstdint>
#include <unordered_map>
#include "../../inc/SDL.h"
#include "../../inc/SDL_image.h"

#include "types.h"
#include "../config.h"

#ifndef TEXTDRAW_H
#define TEXTDRAW_H

using namespace std;

class TextDraw {
public:
    float char_width = 5;
    float char_height = 7;
    float chars_step = 2;

    map <char, SDL_Texture*> all_charecters;
    
    TextDraw(void);
    void load_char(SDL_Renderer* renderer, char name, string path);
    void load_all_charecters(SDL_Renderer* renderer);
    void draw_text(SDL_Renderer* renderer, string text, 
        int x, int y, string x_pos, string y_pos, float size, bool draw_bg, uint8_t bg_trans
    );
    
};


#endif