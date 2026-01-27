#include "text_draw.h"

TextDraw::TextDraw() {}

void TextDraw::load_char(SDL_Renderer* renderer, char name, string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, ((path.c_str())));
    all_charecters[name] = texture;
}

void TextDraw::load_all_charecters(SDL_Renderer* renderer) { 
    string base_folder = "game/assets/textures/characters/";
    // letters
    load_char(renderer, 'a', base_folder + "a.png");
    load_char(renderer, 'b', base_folder + "b.png");
    load_char(renderer, 'c', base_folder + "c.png");
    load_char(renderer, 'd', base_folder + "d.png");
    load_char(renderer, 'e', base_folder + "e.png");
    load_char(renderer, 'f', base_folder + "f.png");
    load_char(renderer, 'g', base_folder + "g.png");
    load_char(renderer, 'h', base_folder + "h.png");
    load_char(renderer, 'i', base_folder + "i.png");
    load_char(renderer, 'j', base_folder + "j.png");
    load_char(renderer, 'k', base_folder + "k.png");
    load_char(renderer, 'l', base_folder + "l.png");
    load_char(renderer, 'm', base_folder + "m.png");
    load_char(renderer, 'n', base_folder + "n.png");
    load_char(renderer, 'o', base_folder + "o.png");
    load_char(renderer, 'p', base_folder + "p.png");
    load_char(renderer, 'q', base_folder + "q.png");
    load_char(renderer, 'r', base_folder + "r.png");
    load_char(renderer, 's', base_folder + "s.png");
    load_char(renderer, 't', base_folder + "t.png");
    load_char(renderer, 'u', base_folder + "u.png");
    load_char(renderer, 'v', base_folder + "v.png");
    load_char(renderer, 'w', base_folder + "w.png");
    load_char(renderer, 'x', base_folder + "x.png");
    load_char(renderer, 'y', base_folder + "y.png");
    load_char(renderer, 'z', base_folder + "z.png");
    // numbers
    load_char(renderer, '0', base_folder + "0.png");
    load_char(renderer, '1', base_folder + "1.png");
    load_char(renderer, '2', base_folder + "2.png");
    load_char(renderer, '3', base_folder + "3.png");
    load_char(renderer, '4', base_folder + "4.png");
    load_char(renderer, '5', base_folder + "5.png");
    load_char(renderer, '6', base_folder + "6.png");
    load_char(renderer, '7', base_folder + "7.png");
    load_char(renderer, '8', base_folder + "8.png");
    load_char(renderer, '9', base_folder + "9.png");
    // special chars
    load_char(renderer, ' ', base_folder + "space.png");
    load_char(renderer, ':', base_folder + "2points.png");
    load_char(renderer, '-', base_folder + "minus.png");
}

void TextDraw::draw_text(SDL_Renderer* renderer, string text, 
    int x, int y, string x_pos, string y_pos, float size, bool draw_bg, uint8_t bg_trans) 
{
    int text_lenght = text.length();
    int text_w = 0;

    for (int ci = 0; ci < text_lenght; ci++){
        char ch = text[ci];
        int w_add = char_width * size;

        if (ci < text_lenght - 2) {
            w_add += chars_step * size;
        }

        // reduce by char width
        if (ch == 'f') w_add -= 1 * size;
        if (ch == 'i') w_add -= 2.5 * size;
        if (ch == 'l') w_add -= 2.5 * size;
        if (ch == 't') w_add -= 1 * size;

        text_w += w_add;
    }

    // * set bg
    if (draw_bg) {
        int x_offset = chars_step * size;
        int y_offset = chars_step * size;

        int bg_x = x - x_offset;
        int bg_y = y - y_offset;

        int bg_w = text_w + x_offset * 3;
        int bg_h = char_height * size + y_offset * 2;
        
        // positioning
        if (x_pos == "center") bg_x -= bg_w / 2;
        if (x_pos == "left") bg_x -= bg_w - chars_step * size;

        if (y_pos == "center") bg_y -= bg_h / 2;
        if (y_pos == "top") bg_y -= bg_h - chars_step * size;
    

        SDL_Rect background_rect{
            bg_x, bg_y, bg_w, bg_h
        };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 10, 10, 10, bg_trans);
        SDL_RenderFillRect(renderer, &background_rect);
    }
    // * characters
    SDL_Rect ch_rect;
    ch_rect.w = char_width * size;
    ch_rect.h = char_height * size;

    float total_offset = 0;
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    for (int ci = 0; ci < text_lenght; ci++)
    {
        char ch = text[ci];
        
        ch_rect.x = x + ci * ((char_width + chars_step) * size) + total_offset;
        ch_rect.y = y;


        // set x closer
        if (ch == 'i') ch_rect.x -= 1 * size;
        if (ch == 'l') ch_rect.x -= 1 * size;
        if (ch == 't') ch_rect.x -= 1 * size;

        // set next offset
        if (ch == 'f') total_offset += -(1 * size);
        if (ch == 'i') total_offset += -(2.5 * size);
        if (ch == 'l') total_offset += -(2.5 * size);
        if (ch == 't') total_offset += -(1 * size);

        // set y lower
        if (ch == 'g') ch_rect.y += 1 * size;
        if (ch == 'j') ch_rect.y += 1 * size;
        if (ch == 'p') ch_rect.y += 1 * size;
        if (ch == 'q') ch_rect.y += 1 * size;
        if (ch == 'y') ch_rect.y += 1 * size;

        if (x_pos == "center") ch_rect.x -= text_w / 2 + (chars_step * 1.5) * size;
        if (x_pos == "left") ch_rect.x -= (text_w + (chars_step * 2) * size);

        if (y_pos == "center") ch_rect.y -= ch_rect.h - chars_step * size;
        if (y_pos == "top") ch_rect.y -= ch_rect.h * 2 - (chars_step * 2.5) * size;

        SDL_RenderCopy(renderer, all_charecters[ch], NULL, &ch_rect);
    }
}
