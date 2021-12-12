#ifndef SAUCERS_H
#define SAUCERS_H

#include "asteroids.h"
#include "bullets.h"
#include "ship.h"

typedef enum {
    SAUCER_SMALL, SAUCER_LARGE
} saucer_size;

typedef struct {
    bullet_t *bullets[MAX_SAUCER_BULLETS];  // bullets array (null = no bullet)
    int bullets_order[MAX_SAUCER_BULLETS];  // 0 = newest bullet
    int bulq_front;
    int bulq_back;
    int bulq_n;

    vec2f_t *lines;
    vec2f_t *lines_collision;
    int nlines;
    int nlines_collision;
    vec2f_t offset;
    vec2f_t velocity;
    saucer_size size;
    float theta;
} saucer_t;

typedef struct {
    int saucers_n;  // Number of saucers in the list
    saucer_t *saucer_list_array[MAX_SAUCERS];
} saucer_list_t;

/* Initialise a saucer_t struct.
    saucer :    the saucer
    size :      the saucer size */
void saucer_init(saucer_t *saucer, saucer_size size);

/* Spawn saucers on screen.
    asteroid_list : the list storing all saucers on screen
    ship :          the ship */
void spawn_saucers(saucer_list_t *saucer_list, ship_t *ship);

/* Checks collision between ship and saucer
    saucer_list :   the list storing all saucers on screen
    saucer :        the saucer
    ship :          the ship */
void check_saucer_collision(saucer_list_t *saucer_list, saucer_t *saucer, ship_t *ship);

/* Update the saucer's position from its velocity. Also checks collisions between ship and saucer.
    saucer_list :   the list storing all saucers on screen
    saucer :        the saucer to be updated
    ship :          the ship
    scene :         the current game state (mainmenu/ingame/gameover)*/
void saucer_update(saucer_list_t *saucer_list, saucer_t *saucer, ship_t *ship, game_state scene);

/* Find an empty index in the bullet list, or return -1 if there isn't one
    saucer :  the saucer */
int find_free_saucer_bullet_index(saucer_t *saucer);

/* Find the oldest bullet in the bullet list, or return -1 if there isn't one
    saucer :  the saucer */
int find_oldest_saucer_bullet(saucer_t *saucer);

/* Makes the saucer fire a bullet.
    saucer :    the saucer
    ship :      the ship */
void saucer_shoot(saucer_t *saucer, ship_t *ship);

/* Frees the bullet in bullet list at give index.
    saucer :    the saucer
    i :         the bullet index */
void free_saucer_bullet (saucer_t *saucer, int i);

/* Frees all memory associated with the saucer.
    saucer_list :   the list storing all saucers on screen
    saucer :        the saucer */
void saucer_free(saucer_list_t *saucer_list, saucer_t *saucer);

/* Frees all the saucers in the saucer list.
    saucer_list :   the list storing all saucers on screen */
void free_saucer_list(saucer_list_t *saucer_list);

/* Makes the saucer blow up, and removing it from the saucer list.
    saucer_list :   the list storing all saucers on screen
    saucer :        the saucer */
void saucer_destroy(saucer_list_t *saucer_list, saucer_t *saucer);

#endif