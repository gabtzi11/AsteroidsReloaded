#ifndef ASTEROID_H
#define ASTEROID_H

#include "asteroids.h"
#include "ship.h"
#include "saucers.h"

typedef enum {
    ASTEROID_SMALL, ASTEROID_MEDIUM, ASTEROID_LARGE
} asteroid_size;

typedef struct {
    vec2f_t *lines;
    vec2f_t *collide_lines;
    int nlines;
    vec2f_t offset;
    float theta;
    vec2f_t velocity;
    asteroid_size size;
} asteroid_t;

typedef struct {
    int asteroids_n; // Number of asteroids in the list
    asteroid_t *asteroid_list_array[MAX_ASTEROIDS];
} asteroid_list_t;

/* Initialise a asteroid_t struct.
    asteroid :  the asteroid
    size :      the asteroid size */
void asteroid_init(asteroid_t *asteroid, asteroid_size size);

/* Spawn asteroids for the given level.
    asteroid_list : the list storing all asteroids on screen
    level :         the level */
void spawn_asteroids(asteroid_list_t *asteroid_list, int level);

/* Checks collision between ship and asteroid
    asteroid_list : the list storing all asteroids on screen
    asteroid :      the asteroid
    ship :          the ship */
void check_ship_asteroid_collision(asteroid_list_t *asteroid_list, asteroid_t *asteroid, ship_t *ship);

/* Checks collision between saucer and asteroid
    asteroid_list : the list storing all asteroids on screen
    asteroid :      the asteroid
    saucer_list :   the list storing all saucers on screen
    saucer :        the saucer */
void check_saucer_asteroid_collision(asteroid_list_t *asteroid_list, asteroid_t *asteroid, saucer_list_t *saucer_list, saucer_t *saucer);

/* Update the asteroid's position from its velocity. Also checks collisions between asteroid, ship and saucer.
    asteroid_list : the list storing all asteroids on screen
    asteroid :      the asteroid to be updated
    ship :          the ship
    saucer_list :   the list storing all saucers on screen
    scene :         the current game state (mainmenu/ingame/gameover)*/
void asteroid_update(asteroid_list_t *asteroid_list, asteroid_t *asteroid, ship_t *ship, saucer_list_t *saucer_list, game_state scene);

/* Splits an asteroid into smaller asteroids
    asteroid_list : the list storing all asteroids on screen
    asteroid :      the asteroid */
void asteroid_split(asteroid_list_t *asteroid_list, asteroid_t *asteroid);

/* Frees all memory associated with the asteroid.
    asteroid_list : the list storing all asteroids on screen
    asteroid :      the asteroid */
void asteroid_free(asteroid_list_t *asteroid_list, asteroid_t *asteroid);

/* Frees all the asteroids in the asteroid list.
    asteroid_list : the list storing all asteroids on screen */
void free_asteroid_list(asteroid_list_t *asteroid_list);

/* Makes the asteroid blow up, and removing it from the asteroid list.
    asteroid_list : the list storing all asteroids on screen
    asteroid :      the asteroid */
void asteroid_destroy(asteroid_list_t *asteroid_list, asteroid_t *asteroid);

#endif