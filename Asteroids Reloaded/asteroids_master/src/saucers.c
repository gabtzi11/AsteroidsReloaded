#include "include/saucers.h"

#include "collisions.h"
#ifdef DO_AUDIO
#include "audio.h"
#endif

void saucer_init(saucer_t *saucer, saucer_size size) {
    saucer->nlines = 10; 
    saucer->lines = malloc(sizeof(vec2f_t) * 2 * saucer->nlines); 
    saucer->offset = (vec2f_t) {(rand() % SCREENWIDTH)-SCREENWIDTH, rand() % SCREENHEIGHT}; //Spawns on the sides of the screen
    saucer->size = size;
    saucer->theta = 0;
    
    for (int i = 0; i < MAX_SAUCER_BULLETS; i++) {
        saucer->bullets[i] = NULL;
        saucer->bullets_order[i] = -1;
    }

    if(size == SAUCER_SMALL){
        saucer->velocity = (vec2f_t) {((SAUCER_SPEED*(rand())/RAND_MAX)-SAUCER_SMALL_SPEED), 0};

        saucer->lines[ 0] = (vec2f_t){8,-4};
        saucer->lines[ 1] = (vec2f_t){-8,-4};
        saucer->lines[ 2] = (vec2f_t){-8,-4};
        saucer->lines[ 3] = (vec2f_t){-20,4};
        saucer->lines[ 4] = (vec2f_t){-20,4};
        saucer->lines[ 5] = (vec2f_t){20,4};
        saucer->lines[ 6] = (vec2f_t){20,4};
        saucer->lines[ 7] = (vec2f_t){8,12};
        saucer->lines[ 8] = (vec2f_t){8,12};
        saucer->lines[ 9] = (vec2f_t){-8,12};
        saucer->lines[10] = (vec2f_t){-8,12};
        saucer->lines[11] = (vec2f_t){-20,4};
        saucer->lines[12] = (vec2f_t){-8,-4};
        saucer->lines[13] = (vec2f_t){-4,-12};
        saucer->lines[14] = (vec2f_t){-4,-12};
        saucer->lines[15] = (vec2f_t){4,-12};
        saucer->lines[16] = (vec2f_t){4,-12};
        saucer->lines[17] = (vec2f_t){8,-4};
        saucer->lines[18] = (vec2f_t){8,-4};
        saucer->lines[19] = (vec2f_t){20,4};
    }

    else{
        saucer->velocity = (vec2f_t) {((SAUCER_SPEED*(rand())/RAND_MAX)-SAUCER_LARGE_SPEED), 0};

        saucer->lines[ 0] = (vec2f_t){-16,-8};
        saucer->lines[ 1] = (vec2f_t){16,-8};
        saucer->lines[ 2] = (vec2f_t){16,-8};
        saucer->lines[ 3] = (vec2f_t){40,8};
        saucer->lines[ 4] = (vec2f_t){40,8};
        saucer->lines[ 5] = (vec2f_t){-40,8};
        saucer->lines[ 6] = (vec2f_t){-40,8};
        saucer->lines[ 7] = (vec2f_t){-16,24};
        saucer->lines[ 8] = (vec2f_t){-16,24};
        saucer->lines[ 9] = (vec2f_t){16,24};
        saucer->lines[10] = (vec2f_t){16,24};
        saucer->lines[11] = (vec2f_t){40,8};
        saucer->lines[12] = (vec2f_t){16,-8};
        saucer->lines[13] = (vec2f_t){8,-24};
        saucer->lines[14] = (vec2f_t){8,-24};
        saucer->lines[15] = (vec2f_t){-8,-24};
        saucer->lines[16] = (vec2f_t){-8,-24};
        saucer->lines[17] = (vec2f_t){-16,-8};
        saucer->lines[18] = (vec2f_t){-16,-8};
        saucer->lines[19] = (vec2f_t){-40,8};
    }
}

void spawn_saucers(saucer_list_t *saucer_list, ship_t *ship) {
    saucer_list->saucers_n = 0;
    while (saucer_list->saucers_n < MAX_SAUCERS)
    {
        saucer_t *new_saucer = (saucer_t *) malloc(sizeof(saucer_t));
        if (ship->score < 10000) {
            saucer_init(new_saucer, SAUCER_LARGE);
            saucer_shoot(new_saucer, ship);
        }
        else if (ship->score >= 40000) {
            saucer_init(new_saucer, SAUCER_SMALL);
            saucer_shoot(new_saucer, ship);
        }
        else {
            switch (rand()%2 + 1)
            {
                case 1:
                    saucer_init(new_saucer, SAUCER_SMALL);
                    saucer_shoot(new_saucer, ship);
                    break;
                case 2:
                    saucer_init(new_saucer, SAUCER_LARGE);
                    saucer_shoot(new_saucer, ship);
                    break;
                default:
                    break;
            }
        }
        saucer_list->saucer_list_array[saucer_list->saucers_n] = new_saucer;
        saucer_list->saucers_n += 1;
    }
    
}

void check_saucer_collision(saucer_list_t *saucer_list, saucer_t *saucer, ship_t *ship)
{
    // Collision between ship and saucer
    if (poly_inside_poly(ship->lines, saucer->lines, ship->offset, saucer->offset, ship->nlines, saucer->nlines))
    {
        switch(saucer->size)
        {
            case SAUCER_LARGE:
                ship->score += 200;
                break;
            case SAUCER_SMALL:
                ship->score += 1;
                break;
        }
        ship_destroy(ship);
        saucer_destroy(saucer_list, saucer);
    }
    else
    {
        // Collision between ship bullets and saucer
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (ship->bullets[i] != 0 && 
                point_inside_poly(ship->bullets[i]->pos, saucer->lines, saucer->offset, saucer->nlines*2))
            {
                switch(saucer->size)
                {
                    case SAUCER_LARGE:
                        ship->score += 200;
                        break;
                    case SAUCER_SMALL:
                        ship->score += 1000;
                        break;
                }
                saucer_destroy(saucer_list, saucer);
                free_ship_bullet(ship, i);
            }
        }

        // Collision between saucer bullets and ship
        for (int i = 0; i < MAX_SAUCER_BULLETS; i++) {
            if (saucer->bullets[i] != 0 && 
                point_inside_poly(saucer->bullets[i]->pos, ship->lines, ship->offset, ship->nlines*2))
            {
                ship_destroy(ship);
                free_saucer_bullet(saucer, i);
            }
        }
    }
}

void saucer_update(saucer_list_t *saucer_list, saucer_t *saucer, ship_t *ship, game_state scene){
    saucer->offset.x += saucer->velocity.x;
    saucer->offset.y += saucer->velocity.y;

    if (saucer->offset.x > SCREENWIDTH) saucer->offset.x = 0;
    if (saucer->offset.x < 0) saucer->offset.x = SCREENWIDTH;
    if (saucer->offset.y > SCREENHEIGHT) saucer->offset.y = 0;
    if (saucer->offset.y < 0) saucer->offset.y = SCREENHEIGHT;

    if (scene == ingame)
        check_saucer_collision(saucer_list, saucer, ship);
    
    /*if (scene == ingame)
        spawn_saucers(saucer_list, saucer, ship);*/
}

int find_free_saucer_bullet_index(saucer_t *saucer) {
    for (int i = 0; i < MAX_SAUCER_BULLETS; i++) {
        if (!saucer->bullets[i]) return i;
    }
    return -1;
}

int find_oldest_saucer_bullet(saucer_t *saucer) {
    int oldest_order = -1;
    int oldest = -1;

    for (int i = 0; i < MAX_SAUCER_BULLETS; i++) {
        if (saucer->bullets[i]) {
            if (saucer->bullets_order[i] > oldest_order) {
                oldest = i;
                oldest_order = saucer->bullets_order[i];
            }
        }
    }

    return oldest;
}

void saucer_shoot(saucer_t *saucer, ship_t *ship) {
    vec2f_t pos = ship->offset;
    bullet_t *new_bullet = (bullet_t *)malloc(sizeof(bullet_t));

    float x = saucer->offset.x - pos.x;
    float y = pos.y - saucer->offset.y;
    float val;
    
    if (saucer->size == SAUCER_SMALL) {
        //x = floor(x/100)*100;   // +-100 is the range in which it would shoot randomly
        //y = floor(x/100)*100;   // +-100 is the range in which it would shoot randomly
        val = (atan2f(y, x));
    }
    else {
        val = (2*PI*(rand())/RAND_MAX)-PI;
    }
    
    float costheta = cosf(val);
    float sintheta = sinf(val);
    new_bullet->pos = saucer->offset;
    new_bullet->velocity.x = -costheta * SAUCER_BULLET_SPEED;
    new_bullet->velocity.y = sintheta * SAUCER_BULLET_SPEED;
    new_bullet->bul_time = time(NULL);
    
    int i;
    while ((i = find_free_saucer_bullet_index(saucer)) == -1) {
        // This should only happen one time,
        // because once a bullet is freed, a free
        // bullet index will be found.
        free_saucer_bullet(saucer, find_oldest_saucer_bullet(saucer)); 
    }

    // Increment all bullet orders, because a new bullet is being
    // inserted with order 0
    for (int j = 0; j < MAX_SAUCER_BULLETS; j++) {
        if (saucer->bullets_order[j] >= 0) {
            saucer->bullets_order[j]++;
        }
    }

    saucer->bullets[i] = new_bullet;
    saucer->bullets_order[i] = 0;
}

void free_saucer_bullet(saucer_t *saucer, int i) {
    //printf("Freeing bullet %d\n", i);
    free(saucer->bullets[i]);
    saucer->bullets[i] = NULL;
}

void saucer_free(saucer_list_t *saucer_list, saucer_t *saucer) {
    int i=0;
    free(saucer->lines);
    while (saucer_list->saucer_list_array[i] != saucer) i++;
    for (int n=i; n < saucer_list->saucers_n; n++)
    {
        saucer_list->saucer_list_array[n] = saucer_list->saucer_list_array[n+1];
    }
    free(saucer_list->saucer_list_array[saucer_list->saucers_n-1]);
}

void free_saucer_list(saucer_list_t *saucer_list)
{
    for (int i=0; i < saucer_list->saucers_n; i++)
	{
        if (saucer_list->saucer_list_array[i]) {
		    saucer_free(saucer_list, saucer_list->saucer_list_array[i]);
        }
	}
    free(saucer_list);
}

void saucer_destroy(saucer_list_t *saucer_list, saucer_t *saucer)
{
    saucer_free(saucer_list, saucer);
    saucer_list->saucers_n--;
    #ifdef DO_AUDIO
    Mix_PlayChannel(0, sound_samples[2], 0);
    #endif
}
