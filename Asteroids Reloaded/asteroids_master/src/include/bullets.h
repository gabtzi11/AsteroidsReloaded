#ifndef BULLETS_H
#define BULLETS_H

#include "asteroids.h"

typedef struct {
    vec2f_t pos;
    vec2f_t velocity;
    double bul_time;
} bullet_t;

/* Makes the bullet move in a single direction. Also checks for any collisions. 
    Should the bullet reach one side of the screen it shall be teleported to the opposite side.
    bullet :    the bullet */
void bullet_update(bullet_t *bullet, double delta_time);

/* Creates a new bullet. This will be used in tandem with ship_shoot, to shoot bullets. 
    There can only be 4 bullets at a time, should the player press it a 5th time when 
    theres 4 already out there, the first shoot gets deleted.
    bullet :    the bullet to intialise
    position :  position to place the bullet at
    velocity :  velocity to add to position every frame */
void bullet_init(bullet_t *bullet, vec2f_t position, vec2f_t velocity);

#endif