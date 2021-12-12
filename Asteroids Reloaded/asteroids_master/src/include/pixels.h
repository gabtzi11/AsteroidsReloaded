#ifndef PIXELS_H
#define PIXELS_H

#include "asteroids.h"

/* Sets a pixel at position (x, y).

    pix = the colour of the pixel. format:
    0xAARRGGBB
      | | | |
      | | | \- Blue
      | | \--- Green
      | \----- Red
      \------- Alpha */
void set_pixel(SDL_Surface *surf, int x, int y, Uint32 pix);

/* Draws a line between the points (x0,y0) and (x1,y1).
    pix :   the pixel colour; refer to set_pixel.
    surf :  the surface to draw the line on. */
void line(SDL_Surface *surf, int x0, int y0, int x1, int y1, Uint32 pix);

/* Draws lots of lines.
    surf :      the surface to draw on.
    lines :     an array of positions, where each pair of positions is one line.
    nlines :    the amount of lines in `lines`. Probably the length of `lines` / 2.
    offset :    an offset applied to every position.
    theta :     the angle to rotate the points in `lines` by. rotates around (0,0).
    pix :       the colour to draw the lines in */
void lines(SDL_Surface *surf, vec2f_t *lines, int nlines, vec2f_t offset,
    float theta, Uint32 pix);

#endif