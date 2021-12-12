#include "asteroids.h"
#include <SDL2/SDL_surface.h>

void set_pixel(SDL_Surface *surf, int x, int y, Uint32 pix) {
    if (x >= 0 && y >= 0 && x < surf->w && y < surf->h) {
        Uint8 *target = (Uint8*) surf->pixels + y * surf->pitch + x * sizeof(Uint32);
        *(Uint32 *)target = pix;
    }
}

void line(SDL_Surface *surf, int x0, int y0, int x1, int y1, Uint32 pix) {
    int dx = abs(x1-x0), 
        sx = x0 < x1 ? 1 : -1; // The horizontal line direction
    int dy = abs(y1-y0), 
        sy = y0 < y1 ? 1 : -1; // The vertical line direction
    int err = (dx>dy ? dx : -dy) / 2, 
        e2;

    while (1) {
        set_pixel(surf, x0, y0, pix);

        if (x0 == x1 && y0 == y1) 
            break; // Exit loop once the end point of the line is reached

        e2 = err;   // A temporary variable to store the value of err before it'll be
                    // changed

        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void lines(SDL_Surface *surf, vec2f_t *lines, int nlines, vec2f_t offset, 
    float theta, Uint32 pix) {
    float costheta = cosf(theta);
    float sintheta = sinf(theta);

    for (int i = 0; i < nlines; i++) {
        float x0 = lines[i*2].x * costheta - lines[i*2].y * sintheta;
        float y0 = lines[i*2].x * sintheta + lines[i*2].y * costheta;
        float x1 = lines[i*2+1].x * costheta - lines[i*2+1].y * sintheta;
        float y1 = lines[i*2+1].x * sintheta + lines[i*2+1].y * costheta;

        line(surf, offset.x + x0, offset.y + y0, 
            offset.x + x1, offset.y + y1, pix);
    }
}
