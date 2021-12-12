#include "include/ship.h"

#ifdef DO_AUDIO
#include "SDL_mixer.h"
#endif

void ship_init(ship_t *ship) {
    ship->nlines = 7;
    ship->lines = malloc(sizeof(vec2f_t) * 2 * ship->nlines); // Two coords per line
    ship->offset = (vec2f_t){SCREENWIDTH/2,SCREENHEIGHT/2};
    ship->theta = 0;
    ship->velocity = (vec2f_t){0,0};
    ship->lives = NUM_LIVES;
    ship->score = 0;
    for (int i = 0; i < MAX_BULLETS; i++) {
        ship->bullets[i] = NULL;
        ship->bullets_order[i] = -1;
    }

    ship->lines[0] = (vec2f_t){0,-15};
    ship->lines[1] = (vec2f_t){-10,10};
    ship->lines[2] = (vec2f_t){0,-15};
    ship->lines[3] = (vec2f_t){10,10};
    ship->lines[4] = (vec2f_t){10,10};
    ship->lines[5] = (vec2f_t){2,4};
    ship->lines[6] = (vec2f_t){-10,10};
    ship->lines[7] = (vec2f_t){-2,4};
    ship->lines[8] = (vec2f_t){2,4};
    ship->lines[9] = (vec2f_t){-2,4};
    ship->lines[10] = (vec2f_t){-4,5};
    ship->lines[12] = (vec2f_t){4,5};
}

void ship_move(ship_t *ship, double delta_time) {
    float dx, dy;
    float costheta = cosf(ship->theta);
    float sintheta = sinf(ship->theta);

    dx = sintheta * delta_time * SHIP_SPEED;
    dy = -costheta * delta_time * SHIP_SPEED;

    ship->velocity.x += dx;
    ship->velocity.y += dy;
    ship->lines[11] = (vec2f_t){0,13};
    ship->lines[13] = (vec2f_t){0,13};
}

void ship_rotate(ship_t *ship, int dir, double delta_time) {
    ship->theta += dir * delta_time * 4;
}

void ship_update(ship_t *ship) {
    ship->velocity.x *= DECELERATION_VELOCITY;
    ship->velocity.y *= DECELERATION_VELOCITY;
    ship->offset.x += ship->velocity.x;
    ship->offset.y += ship->velocity.y;
    if (ship->offset.x > SCREENWIDTH) ship->offset.x = 0;
    if (ship->offset.x < 0) ship->offset.x = SCREENWIDTH;
    if (ship->offset.y > SCREENHEIGHT) ship->offset.y = 0;
    if (ship->offset.y < 0) ship->offset.y = SCREENHEIGHT;
}

void ship_hyperdrive(ship_t *ship) {
    ship->offset.x = rand() % SCREENWIDTH;
    ship->offset.y = rand() % SCREENHEIGHT;
    //ship->velocity.x = 0; // I believe the ship maintains its momentum
    //ship->velocity.y = 0;
}

void ship_free(ship_t *ship) {
    free(ship->lines);
}

int find_free_bullet_index(ship_t *ship) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!ship->bullets[i]) return i;
    }
    return -1;
}

int find_oldest_bullet(ship_t *ship) {
    int oldest_order = -1;
    int oldest = -1;

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (ship->bullets[i]) {
            if (ship->bullets_order[i] > oldest_order) {
                oldest = i;
                oldest_order = ship->bullets_order[i];
            }
        }
    }

    return oldest;
}

void ship_shoot(ship_t *ship) {
    bullet_t *new_bullet = (bullet_t *)malloc(sizeof(bullet_t));

    float costheta = cosf(ship->theta);
    float sintheta = sinf(ship->theta);
    new_bullet->pos = ship->offset;
    new_bullet->velocity.x = sintheta * BULLET_SPEED;
    new_bullet->velocity.y = -costheta * BULLET_SPEED;
    new_bullet->bul_time = time(NULL);
    
    int i;
    while ((i = find_free_bullet_index(ship)) == -1) {
        // This should only happen one time,
        // because once a bullet is freed, a free
        // bullet index will be found.
        free_ship_bullet(ship, find_oldest_bullet(ship)); 
    }

    // Increment all bullet orders, because a new bullet is being
    // inserted with order 0
    for (int j = 0; j < MAX_BULLETS; j++) {
        if (ship->bullets_order[j] >= 0) {
            ship->bullets_order[j]++;
        }
    }

    ship->bullets[i] = new_bullet;
    ship->bullets_order[i] = 0;

#ifdef DO_AUDIO
    Mix_PlayChannel(0, sound_samples[5], 0);
#endif
}

void free_ship_bullet(ship_t *ship, int i) {
    free(ship->bullets[i]);
    ship->bullets[i] = NULL;
}

void ship_destroy(ship_t *ship)
{
#ifdef DO_AUDIO
    Mix_PlayChannel(0, sound_samples[3], 0);
#endif

    for (int i = 0; i < MAX_BULLETS; i++) {
        free_ship_bullet(ship, i);
    }
    if (ship->lives > 0)
    {
        int current_lives = ship->lives;
        int current_score = ship->score;
        ship_free(ship);        // Need to implement a delay between spawn
        ship_init(ship);
        ship->score = current_score;
        ship->lives = current_lives-1;
    }
}