#ifndef SHIP_H
#define SHIP_H

#include <string.h>
#include "asteroids.h"
#include "bullets.h"

typedef struct {
    bullet_t *bullets[MAX_BULLETS]; // bullets array (null = no bullet)
    int bullets_order[MAX_BULLETS]; // 0 = newest bullet
    int bulq_front;
    int bulq_back;
    int bulq_n;

    vec2f_t *lines; // Lines making up the ship
    vec2f_t *collision_lines;
    int nlines; // Amount of lines in *lines
    int nlines_collision;
    vec2f_t offset; // Ship position
    vec2f_t velocity; // Added to offset each frame
    float theta; // Rotation of ship
    int lives; // Amount of lives the ship has spare
    int score;
} ship_t;

/* Initialise a ship_t struct.
    ship : the ship to initialise */
void ship_init(ship_t *ship);

/* Set the ship's velocity forward from its current angle. This doesn't update the position.
    ship :          the ship
    delta_time :    the time, in seconds, since the last game frame */
void ship_move(ship_t *ship, double delta_time);

/* Rotate the ship.
    ship:           the ship
    dir:            the direction to rotate. SHIP_DIR_LEFT or SHIP_DIR_RIGHT.
    delta_time :    the time, in seconds, since the last game frame */
void ship_rotate(ship_t *ship, int dir, double delta_time);

/* Update the ship's position from its velocity.
    ship :          the ship*/
void ship_update(ship_t *ship);     // Unused parameter 'double delta_time'

/* Teleports the ship to a random location on screen. Be careful, you might land on an asteroid!
    ship :  the ship */
void ship_hyperdrive(ship_t *ship);

/* Frees all memory associated with the ship.
    ship :  the ship */
void ship_free(ship_t *ship);

/* Find an empty index in the bullet list, or return -1 if there isn't one
    ship :  the ship */
int find_free_bullet_index(ship_t *ship);

/* Find the oldest bullet in the bullet list, or return -1 if there isn't one
    ship :  the ship */
int find_oldest_bullet(ship_t *ship);

/* Makes the ship fire a bullet.
    ship :  the ship */
void ship_shoot(ship_t *ship);

/* Frees the bullet in bullet list at give index.
    ship :  the ship
    i :     the bullet index */
void free_ship_bullet(ship_t *ship, int i);

/* Makes the ship blow up, and then respawn, subtracting 1 from `lives`.
    ship :  the ship */
void ship_destroy(ship_t *ship);

#endif