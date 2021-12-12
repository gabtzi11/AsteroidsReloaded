#include "asteroid.h"
#include "asteroids.h"
#include "collisions.h"

#ifdef DO_AUDIO
#include "audio.h"
#include "SDL_mixer.h"
#endif

void asteroid_init(asteroid_t *asteroid, asteroid_size size) {
    asteroid->nlines = 10; 
    asteroid->lines = malloc(sizeof(vec2f_t) * 2 * asteroid->nlines); 
    asteroid->theta = 0;
    //asteroid->offset = (vec2f_t) {(rand() % SCREENWIDTH), (rand() % SCREENHEIGHT)}; 
    asteroid->size = size;

    switch (rand() % 4) {
    case 0:
        // Left wall
        asteroid->offset.x = 0;
        asteroid->offset.y = rand() % SCREENHEIGHT;
        break;
    case 1:
        // Right wall
        asteroid->offset.x = SCREENWIDTH;
        asteroid->offset.y = rand() % SCREENHEIGHT;
        break;
    case 2:
        // Top wall
        asteroid->offset.x = rand() % SCREENWIDTH;
        asteroid->offset.y = 0;
        break;
    case 3:
        // Bottom wall
        asteroid->offset.x = rand() % SCREENWIDTH;
        asteroid->offset.y = SCREENHEIGHT;
        break;
    }

    if (size == ASTEROID_SMALL)
    {
        //asteroid->velocity = (vec2f_t) {ASTEROID_SPEED_SMALL, ASTEROID_SPEED_SMALL};
        // If asteroids have size-based (random) velocity
        asteroid->velocity = (vec2f_t) {((ASTEROID_SPEED*(rand())/(float)RAND_MAX)-ASTEROID_SPEED_SMALL), 
            ((ASTEROID_SPEED*(rand())/(float)RAND_MAX)-ASTEROID_SPEED_SMALL)};
        asteroid->lines[ 0] = (vec2f_t) {0,-4.5};
        asteroid->lines[ 1] = (vec2f_t) {6,-10.5};
        asteroid->lines[ 2] = (vec2f_t) {6,-10.5};
        asteroid->lines[ 3] = (vec2f_t) {12,-4.5};
        asteroid->lines[ 4] = (vec2f_t) {12,-4.5};
        asteroid->lines[ 5] = (vec2f_t) {9,0};
        asteroid->lines[ 6] = (vec2f_t) {9,0};
        asteroid->lines[ 7] = (vec2f_t) {12,2};
        asteroid->lines[ 8] = (vec2f_t) {12,2};
        asteroid->lines[ 9] = (vec2f_t) {3,10.5};
        asteroid->lines[10] = (vec2f_t) {3,10.5};
        asteroid->lines[11] = (vec2f_t) {-6,10.5};
        asteroid->lines[12] = (vec2f_t) {-6,10.5};
        asteroid->lines[13] = (vec2f_t) {-12,2};
        asteroid->lines[14] = (vec2f_t) {-12,2};
        asteroid->lines[15] = (vec2f_t) {-12,-4.5};
        asteroid->lines[16] = (vec2f_t) {-12,-4.5};
        asteroid->lines[17] = (vec2f_t) {-6,-10.5};
        asteroid->lines[18] = (vec2f_t) {-6,-10.5};
        asteroid->lines[19] = (vec2f_t) {0,-4.5};
    }
    else if (size == ASTEROID_MEDIUM)
    {
        //asteroid->velocity = (vec2f_t) {ASTEROID_SPEED_MEDIUM, ASTEROID_SPEED_MEDIUM};
        // If asteroids have size-based (random) velocity
        asteroid->velocity = (vec2f_t) {((ASTEROID_SPEED*(rand())/(float)RAND_MAX)-ASTEROID_SPEED_MEDIUM), 
            ((ASTEROID_SPEED*(rand())/(float)RAND_MAX)-ASTEROID_SPEED_MEDIUM)};
        asteroid->lines[ 0] = (vec2f_t) {0,-7.5};
        asteroid->lines[ 1] = (vec2f_t) {10,-17.5};
        asteroid->lines[ 2] = (vec2f_t) {10,-17.5};
        asteroid->lines[ 3] = (vec2f_t) {20,-7.5};
        asteroid->lines[ 4] = (vec2f_t) {20,-7.5};
        asteroid->lines[ 5] = (vec2f_t) {15,0};
        asteroid->lines[ 6] = (vec2f_t) {15,0};
        asteroid->lines[ 7] = (vec2f_t) {20,10};
        asteroid->lines[ 8] = (vec2f_t) {20,10};
        asteroid->lines[ 9] = (vec2f_t) {5,17.5};
        asteroid->lines[10] = (vec2f_t) {5,17.5};
        asteroid->lines[11] = (vec2f_t) {-10,17.5};
        asteroid->lines[12] = (vec2f_t) {-10,17.5};
        asteroid->lines[13] = (vec2f_t) {-20,10};
        asteroid->lines[14] = (vec2f_t) {-20,10};
        asteroid->lines[15] = (vec2f_t) {-20,-7.5};
        asteroid->lines[16] = (vec2f_t) {-20,-7.5};
        asteroid->lines[17] = (vec2f_t) {-10,-17.5};
        asteroid->lines[18] = (vec2f_t) {-10,-17.5};
        asteroid->lines[19] = (vec2f_t) {0,-7.5};
    }
    else
    {
        //asteroid->velocity = (vec2f_t) {ASTEROID_SPEED_LARGE, ASTEROID_SPEED_LARGE};
        // If asteroids have size-based (random) velocity
        asteroid->velocity = (vec2f_t) {((ASTEROID_SPEED*(rand())/(float)RAND_MAX)-ASTEROID_SPEED_LARGE), 
            ((ASTEROID_SPEED*(rand())/(float)RAND_MAX)-ASTEROID_SPEED_LARGE)};
        asteroid->lines[ 0] = (vec2f_t) {0,-15};
        asteroid->lines[ 1] = (vec2f_t) {20,-35};
        asteroid->lines[ 2] = (vec2f_t) {20,-35};
        asteroid->lines[ 3] = (vec2f_t) {40,-15};
        asteroid->lines[ 4] = (vec2f_t) {40,-15};
        asteroid->lines[ 5] = (vec2f_t) {30,0};
        asteroid->lines[ 6] = (vec2f_t) {30,0};
        asteroid->lines[ 7] = (vec2f_t) {40,20};
        asteroid->lines[ 8] = (vec2f_t) {40,20};
        asteroid->lines[ 9] = (vec2f_t) {10,35};
        asteroid->lines[10] = (vec2f_t) {10,35};
        asteroid->lines[11] = (vec2f_t) {-20,35};
        asteroid->lines[12] = (vec2f_t) {-20,35};
        asteroid->lines[13] = (vec2f_t) {-40,20};
        asteroid->lines[14] = (vec2f_t) {-40,20};
        asteroid->lines[15] = (vec2f_t) {-40,-15};
        asteroid->lines[16] = (vec2f_t) {-40,-15};
        asteroid->lines[17] = (vec2f_t) {-20,-35};
        asteroid->lines[18] = (vec2f_t) {-20,-35};
        asteroid->lines[19] = (vec2f_t) {0,-15};
    }    
}

void spawn_asteroids(asteroid_list_t *asteroid_list, int level)
{
    free_asteroid_list(asteroid_list);

    asteroid_list->asteroids_n = 0;
    while (asteroid_list->asteroids_n < 2 + (level*2))  // (level*2) is the rate at which number of asteroids increase per level
    {
        asteroid_t *new_asteroid = (asteroid_t *)malloc(sizeof(asteroid_t));
        asteroid_init(new_asteroid, ASTEROID_LARGE);
        asteroid_list->asteroid_list_array[asteroid_list->asteroids_n] = new_asteroid;
        asteroid_list->asteroids_n += 1;
    }
}

void check_ship_asteroid_collision(asteroid_list_t *asteroid_list, asteroid_t *asteroid, ship_t *ship)
{
    // Collision between ship and asteroid
    if (poly_inside_poly(ship->lines, asteroid->lines, ship->offset, asteroid->offset, ship->nlines, asteroid->nlines))
    {
        switch(asteroid->size)
        {
            case ASTEROID_LARGE:
                ship->score += 20;
                break;
            case ASTEROID_MEDIUM:
                ship->score += 50;
                break;
            case ASTEROID_SMALL:
                ship->score += 100;
                break;
        }
        ship_destroy(ship);
        asteroid_destroy(asteroid_list, asteroid);
    }
    else
    {
        // Collision between ship bullets and asteroid
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (ship->bullets[i] != 0 && 
                point_inside_poly(ship->bullets[i]->pos, asteroid->lines, asteroid->offset, asteroid->nlines * 2))
            {
                switch(asteroid->size)
                {
                    case ASTEROID_LARGE:
                        ship->score += 20;
                        break;
                    case ASTEROID_MEDIUM:
                        ship->score += 50;
                        break;
                    case ASTEROID_SMALL:
                        ship->score += 100;
                        break;
                }
                asteroid_split(asteroid_list, asteroid);
                free_ship_bullet(ship, i);
            }
        }
    }
}

void check_saucer_asteroid_collision(asteroid_list_t *asteroid_list, asteroid_t *asteroid, saucer_list_t *saucer_list, saucer_t *saucer) {
    // Collision between saucer and asteroid
    if (poly_inside_poly(saucer->lines, asteroid->lines, saucer->offset, asteroid->offset, saucer->nlines, asteroid->nlines))
    {
        saucer_destroy(saucer_list, saucer);
        asteroid_destroy(asteroid_list, asteroid);
    }
    else
    {
        // Collision between saucer bullets and asteroid
        for (int i = 0; i < MAX_SAUCER_BULLETS; i++) {
            if (saucer->bullets[i] != 0 && 
                point_inside_poly(saucer->bullets[i]->pos, asteroid->lines, asteroid->offset, asteroid->nlines * 2))
            {
                asteroid_split(asteroid_list, asteroid);
                
                free_saucer_bullet(saucer, i);
            }
        }
    }
}

void asteroid_update(asteroid_list_t *asteroid_list, asteroid_t *asteroid, ship_t *ship, saucer_list_t *saucer_list, game_state scene) {   // Unused parameter 'double delta_time'
    asteroid->offset.x += asteroid->velocity.x;
    asteroid->offset.y += asteroid->velocity.y;

    if (asteroid->offset.x > SCREENWIDTH) asteroid->offset.x = 0;
    if (asteroid->offset.x < 0) asteroid->offset.x = SCREENWIDTH;
    if (asteroid->offset.y > SCREENHEIGHT) asteroid->offset.y = 0;
    if (asteroid->offset.y < 0) asteroid->offset.y = SCREENHEIGHT;

    if (scene == ingame) {
        check_ship_asteroid_collision(asteroid_list, asteroid, ship);
        for (int i = 0; i < saucer_list->saucers_n; i++) {
            if (saucer_list->saucer_list_array[i])
                check_saucer_asteroid_collision(asteroid_list, asteroid, saucer_list, saucer_list->saucer_list_array[i]);
        }
    }
}

void asteroid_split(asteroid_list_t *asteroid_list, asteroid_t *asteroid) {
    switch(asteroid->size)
    {
        vec2f_t temp_offset;
        case ASTEROID_LARGE:
            #ifdef DO_AUDIO
            Mix_PlayChannel(0, sound_samples[4], 0);
            #endif
            if (asteroid_list->asteroids_n != MAX_ASTEROIDS)
            {
                asteroid_t *new_asteroid = (asteroid_t *)malloc(sizeof(asteroid_t));
                asteroid_init(new_asteroid, ASTEROID_MEDIUM);
                new_asteroid->offset = asteroid->offset;
                asteroid_list->asteroid_list_array[asteroid_list->asteroids_n] = new_asteroid;
                asteroid_list->asteroids_n ++;
            }
            free(asteroid->lines);
            temp_offset = asteroid->offset;
            asteroid_init(asteroid, ASTEROID_MEDIUM);
            asteroid->offset = temp_offset;
            break;
        case ASTEROID_MEDIUM:
            #ifdef DO_AUDIO
            Mix_PlayChannel(0, sound_samples[3], 0);
            #endif
            if (asteroid_list->asteroids_n != MAX_ASTEROIDS)
            {
                asteroid_t *new_asteroid = (asteroid_t *)malloc(sizeof(asteroid_t));
                asteroid_init(new_asteroid, ASTEROID_SMALL);
                new_asteroid->offset = asteroid->offset;
                asteroid_list->asteroid_list_array[asteroid_list->asteroids_n] = new_asteroid;
                asteroid_list->asteroids_n ++;
            }
            free(asteroid->lines);
            temp_offset = asteroid->offset;
            asteroid_init(asteroid, ASTEROID_SMALL);
            asteroid->offset = temp_offset;
            break;
        default:
            #ifdef DO_AUDIO
            Mix_PlayChannel(0, sound_samples[2], 0);
            #endif
            asteroid_destroy(asteroid_list, asteroid);
            break;
    }
}

void asteroid_free(asteroid_list_t *asteroid_list, asteroid_t *asteroid) {
    int i=0;
    free(asteroid->lines);
    while (asteroid_list->asteroid_list_array[i] != asteroid) i++;
    for (int n=i; n < asteroid_list->asteroids_n; n++)
    {
        asteroid_list->asteroid_list_array[n] = asteroid_list->asteroid_list_array[n+1];
    }
    free(asteroid_list->asteroid_list_array[asteroid_list->asteroids_n-1]);
}

void free_asteroid_list(asteroid_list_t *asteroid_list)
{
    for (int i=0; i < asteroid_list->asteroids_n; i++)
	{
		if (asteroid_list->asteroid_list_array[i]) {
		    asteroid_free(asteroid_list, asteroid_list->asteroid_list_array[i]);
        }
	}
}

void asteroid_destroy(asteroid_list_t *asteroid_list, asteroid_t *asteroid)     // Causing Seg Fault (Temporarily fixed); Asteroid destruction animation pending
{
    asteroid_free(asteroid_list, asteroid);
    asteroid_list->asteroids_n --;
}