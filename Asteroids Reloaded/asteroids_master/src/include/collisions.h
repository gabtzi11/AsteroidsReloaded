#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "asteroids.h"

int point_inside_poly(vec2f_t p, vec2f_t *poly, vec2f_t poly_offset, int nlines);

int lines_intersect(vec2f_t a1, vec2f_t a2, vec2f_t b1, vec2f_t b2);

int poly_inside_poly(vec2f_t *poly0, vec2f_t *poly1, vec2f_t poly0_offset, vec2f_t poly1_offset, int poly0_n, int poly1_n);

#endif