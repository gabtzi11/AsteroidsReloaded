#include "text.h"
#include <stdio.h>
#include <string.h>

size_t glyph_table[256] = {0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void init_fonts() {
}

void draw_glyph(SDL_Surface *surf, font_t *fnt, size_t glyph_index, vec2f_t pos) {
    lines(surf, fnt->glyph_points[glyph_index], fnt->points_per_glyph[glyph_index]/2, pos,
        0, 0xffffffff);
}

void write_ascii(SDL_Surface *surf, font_t *fnt, char *text, vec2f_t pos, int align) {
    if (align != ALIGN_LEFT) {
        float total_width = 0;
        for (char *c = text; *c; c++) {
            if (*c == ' ') {
                total_width += fnt->max_width + 10.f * fnt->space_scale;
            } else {
                //printf("%d\n", (uint8_t)*c);
                total_width += fnt->glyph_widths[glyph_table[(uint8_t)*c]] + 10.f * fnt->space_scale;
            }
        }
        if (align == ALIGN_CENTER) {
            pos.x -= total_width/2;
        } else if (align == ALIGN_RIGHT) {
            pos.x -= total_width;
        }
    }

    for (char *c = text; *c; c++) {
        if (*c == ' ') {
            pos.x += fnt->max_width + 10.f * fnt->space_scale;
        } else {
            draw_glyph(surf, fnt, glyph_table[(uint8_t)*c], pos);
            pos.x += fnt->glyph_widths[glyph_table[(uint8_t)*c]] + 10.f * fnt->space_scale;
        }
    }
}

// Make vec2f from string of form "x,y"
vec2f_t vec2f_from_string(char *str, float scale) {
    char *str2 = strchr(str, ',');
    *str2++ = 0;
    return (vec2f_t){(float)atof(str) * scale, (float)atof(str2) * scale};
}

size_t count_lines(FILE *fp) {
    size_t lines = 0;
    while (!feof(fp)) {
        if (fgetc(fp) == '\n') {
            lines++;
        }
    }
    rewind(fp);
    return lines;
}

font_t *load_font(const char *name, float scale) {
    FILE *fp = fopen(name, "r");
    char *str;
    long fsize;
    font_t *fnt = malloc(sizeof(font_t));
    char *line;
    char *tok;
    const char delim_space[2] = " ";
    size_t i;
    size_t nlines;

    if (!fnt) {
        printf("fnt malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    nlines = count_lines(fp);

    printf("Loading font (%s at %f) with %d glyphs.\n", name, scale, (int)nlines);
    
    fnt->num_glyphs = nlines;
    if (!(fnt->glyph_points = malloc(nlines * sizeof(vec2f_t *)))) {
        printf("points malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    
    fnt->space_scale = scale;

    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    rewind(fp);

    str = malloc(fsize + 1); // Size for file + null terminator
    char *str_save = str;
    fread(str, 1, fsize, fp);
    fclose(fp);
    str[fsize] = 0; // Do the null terminator so it's a C-string

    line = strchr(str, '\n');
    i = 0;
    float max_width = 0;
    while (line != NULL) {
        *line++ = 0;

        size_t amount_points = 0;

        char *str_cpy;
        if (!(str_cpy = malloc(strlen(str)+1))) {
            printf("str cpy malloc failed\n");
            exit(EXIT_FAILURE);
        }
        strcpy(str_cpy, str);

        tok = strtok(str, delim_space);
        while ((tok = strtok(NULL, delim_space))) {
            amount_points++;
        }

        fnt->points_per_glyph[i] = amount_points;
        
        if (!(fnt->glyph_points[i] = malloc(amount_points * sizeof(vec2f_t)))) {
            printf("points[i] malloc failed.\n");
            exit(EXIT_FAILURE);
        }

        size_t point_index = 0;
        float glyph_max_width = 0;

        tok = strtok(str_cpy, delim_space);
        while ((tok = strtok(NULL, delim_space))) {
            fnt->glyph_points[i][point_index] = vec2f_from_string(tok, scale);

            if (fnt->glyph_points[i][point_index].x > glyph_max_width) {
                glyph_max_width = fnt->glyph_points[i][point_index].x;
            }

            point_index++;
        }

        fnt->glyph_widths[i] = glyph_max_width;
        if (glyph_max_width > max_width) max_width = glyph_max_width;

        free(str_cpy);

        str = line;
        line = strchr(str, '\n');
        i++;
    }

    str = str_save;
    free(str);

    fnt->max_width = max_width;

    return fnt;
}

void free_font(font_t *fnt) {
    for (size_t i = 0; i < fnt->num_glyphs; i++) {
        free(fnt->glyph_points[i]);
    }
    free(fnt->glyph_points);
    free(fnt);
}