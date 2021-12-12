#include "include/asteroids.h"
#include "collisions.h"

int point_inside_poly(vec2f_t p, vec2f_t *poly, vec2f_t poly_offset, int nlines)
{
    int crossings = 0; // crossings counter for checking parity
    float dx, dy; 
    vec2f_t dv;
    vec2f_t check_vec = (vec2f_t) {2000 - p.x, 0}; // our line beaming rightward
    vec2f_t offset_poly;

    for (int i = 0; i < nlines-1; i += 2) // check each poly pair
    {
        dx = poly[i+1].x - poly[i].x;
        dy = poly[i+1].y - poly[i].y;
        dv = (vec2f_t) {dx, dy};
        offset_poly = (vec2f_t) {poly[i].x + poly_offset.x, poly[i].y + poly_offset.y};

        if (lines_intersect(p, check_vec, offset_poly, dv)) // do they cross
        {
            crossings = !crossings; // if so flip
        }   
    }

    return crossings;
}

int lines_intersect(vec2f_t a1, vec2f_t a2, vec2f_t b1, vec2f_t b2)
{
    float lamda, mew;
    float numerator;
    float denominator = a2.y * b2.x - a2.x * b2.y;

    // no collision or infinite colisions
    if (denominator == 0)
    {
        return 0;
    }

    // calculating lamda
    numerator = b2.y * (a1.x - b1.x) - b2.x * (a1.y - b1.y);
    lamda = numerator / denominator;

    // calculating mew
    numerator = a2.y * (b1.x - a1.x) - a2.x * (b1.y - a1.y);
    mew = numerator / (-1 * denominator);

    // checking if they are within the segment
    if (lamda >= 0 && lamda <= 1 && mew >= 0 && mew <= 1) // lamda and mew will be 0 - 1 as the two given points
    {
        return 1; // yes they collide
    }
    
    return 0; // no collide
}

int poly_inside_poly(vec2f_t *poly0, vec2f_t *poly1, vec2f_t poly0_offset, vec2f_t poly1_offset, int poly0_n, int poly1_n)
{
    float dx0, dy0, dx1, dy1;
    vec2f_t dv0, dv1;
    vec2f_t offset_poly0, offset_poly1;

    for (int i = 0; i < poly0_n-1; i+=2) // for every line in poly 0
    {
        dx0 = poly0[i+1].x - poly0[i].x; // calculate line eq.
        dy0 = poly0[i+1].y - poly0[i].y;
        dv0 = (vec2f_t) {dx0, dy0};
        offset_poly0 = (vec2f_t) {poly0[i].x + poly0_offset.x, poly0[i].y + poly0_offset.y};

        for (int j = 0; j < poly1_n-1; j+=2) // for every line in poly 1
        {
            dx1 = poly1[j+1].x - poly1[j].x; // calculate line eq.
            dy1 = poly1[j+1].y - poly1[j].y;
            dv1 = (vec2f_t) {dx1, dy1};
            offset_poly1 = (vec2f_t) {poly1[j].x + poly1_offset.x, poly1[j].y + poly1_offset.y};

            if (lines_intersect(offset_poly0, dv0, offset_poly1, dv1)) // if they cross
            {
                return 1; // return true
            }
        }
    }

    return 0; // else return false
}