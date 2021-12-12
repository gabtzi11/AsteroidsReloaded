#include "bullets.h"

void bullet_update(bullet_t *bullet, double delta_time) {
    bullet->pos.x += bullet->velocity.x * delta_time;
    bullet->pos.y += bullet->velocity.y * delta_time;

    if (bullet->pos.x > SCREENWIDTH) bullet->pos.x = 0;
    if (bullet->pos.x < 0) bullet->pos.x = SCREENWIDTH;
    if (bullet->pos.y > SCREENHEIGHT) bullet->pos.y = 0;
    if (bullet->pos.y < 0) bullet->pos.y = SCREENHEIGHT;
}

void bullet_init(bullet_t *bullet, vec2f_t position, vec2f_t velocity) {
    bullet->pos = position;
    bullet->velocity = velocity;
}

