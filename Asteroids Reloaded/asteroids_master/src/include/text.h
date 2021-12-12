#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include "pixels.h"

// 36 chars:
// 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ©
#define FONT_CHAR_COUNT 37 // Max amount of chars that the font supports

#define ALIGN_LEFT      0
#define ALIGN_RIGHT     1
#define ALIGN_CENTER    2

#define SET_FONT_POINT(glyph,i,x,y) main_font[glyph][i] = (vec2f_t){x,y}

extern size_t glyph_table[256];

typedef struct {
    float space_scale;
    float max_width;
    float glyph_widths[FONT_CHAR_COUNT];
    size_t points_per_glyph[FONT_CHAR_COUNT];
    size_t num_glyphs;
    vec2f_t **glyph_points;
} font_t;

void init_fonts();
font_t *load_font(const char *name, float scale);
void free_font(font_t *fnt);

void draw_glyph(SDL_Surface *surf, font_t *fnt, size_t glyph_index, vec2f_t pos);
void write_ascii(SDL_Surface *surf, font_t *fnt, char *text, vec2f_t pos, int align);

#endif