#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#ifdef DO_AUDIO
#include "SDL_mixer.h"
#include "audio.h"
#endif

#define PI 3.1415927
#define SCREENWIDTH 1000
#define SCREENHEIGHT 800

// Game constants
#define ASTEROID_SPEED 0.5f
#define ASTEROID_SPEED_SMALL 0.28
#define ASTEROID_SPEED_MEDIUM 0.2
#define ASTEROID_SPEED_LARGE 0.19
#define MAX_ASTEROIDS 26

#define SAUCER_SPEED 0.6
#define SAUCER_SMALL_SPEED 0.4
#define SAUCER_LARGE_SPEED 0.3
#define MAX_SAUCERS 1
#define MAX_SAUCERS_SMALL 1
#define MAX_SAUCERS_LARGE 1

#define SHIP_SPEED 1
#define DECELERATION_VELOCITY 0.9985
#define SHIP_DIR_LEFT -1
#define SHIP_DIR_RIGHT 1

#define BULLET_SPEED 600
#define SAUCER_BULLET_SPEED 400
#define MAX_BULLETS 4
#define MAX_SAUCER_BULLETS 1
#define BULLET_TIMEOUT 2

#define NUM_LIVES 3
#define SPAWN_TIME_GAP 5
#define SAUCER_SPAWN_TIME_GAP 30

typedef enum {
    mainmenu, ingame, gameover
} game_state;

typedef struct {
    float x;
    float y;
} vec2f_t;

#endif
