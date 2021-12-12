#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include "SDL_keycode.h"
#include "SDL_video.h"
#include "asteroid.h"
#include "saucers.h"
#include "text.h"

#ifdef DO_AUDIO
#include "SDL_mixer.h"
	#include "audio.h"
#endif

int main() {
	int closed = 0;
	SDL_Window* win;
	SDL_Surface* surf;
	SDL_Event ev;
	FILE *file_high = fopen("highscore.txt","a+");

	ship_t ship;
	asteroid_list_t *asteroid_list = (asteroid_list_t *)malloc(sizeof(asteroid_list_t));
	saucer_list_t *saucer_list = (saucer_list_t *)malloc(sizeof(saucer_list_t));
	time_t temp_time, saucer_temp_time;

	game_state scene = mainmenu;

	char score_buf[6] = "00";
	char score_high[6];


	int current_score = 0;
	int time_update_counter = 0;
	int saucer_time_update_counter = 0;
	int level = 1;
	int thrusting = 0;

	Uint64 currenttime = SDL_GetPerformanceCounter(), 
			prevtime = 0;
	double delta = 0; 	// Delta is the amount of (or more like, proportion of) seconds
						// ellapsed between the current frame and the last.
						// This will be used to make sure the game happens at the
						// same speed regardless of fps.

	SDL_Init(SDL_INIT_VIDEO);
	srand(time(NULL));

	fscanf(file_high, "%s", score_high);

	#ifdef DO_AUDIO
		soundtrack_t st;

		if (!audio_init()) {
			return -1;
		}

		soundtrack_init(&st);
		st.beats[0] = sound_samples[0];
		st.beats[1] = sound_samples[1];
		st.playing = 0;
	#endif

	ship_init(&ship);
	spawn_asteroids(asteroid_list, level);

	font_t *font_normal = load_font("font.txt", 1.0f);
	font_t *font_small = load_font("font.txt", 0.4f);
	font_t *font_large = load_font("font.txt", 2.0f);

	win = SDL_CreateWindow("Asteroids", SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, 0);

	surf = SDL_GetWindowSurface(win);

	while (!closed) {
		prevtime = currenttime;
		currenttime = SDL_GetPerformanceCounter();
		delta = (double)(currenttime - prevtime) / (double)SDL_GetPerformanceFrequency();

		#ifdef DO_AUDIO
			soundtrack_play(&st, delta);
		#endif

		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					closed = 1;
					break;
				case SDL_KEYDOWN:
					if (scene == ingame) {
						if (ev.key.keysym.sym == SDLK_RCTRL) ship_hyperdrive(&ship);
						if (ev.key.keysym.sym == SDLK_SPACE) ship_shoot(&ship);
						if (ev.key.keysym.sym == SDLK_p) scene = mainmenu;
						else if (ev.key.keysym.sym == SDLK_ESCAPE) {
							#ifdef DO_AUDIO
							st.playing = 0;
							#endif
							scene = mainmenu;
							ship_free(&ship);
							ship_init(&ship);
							level = 1;
							spawn_asteroids(asteroid_list, level);
						}
					} else if (scene == mainmenu) {
						if (ev.key.keysym.sym == SDLK_SPACE) {
							free_asteroid_list(asteroid_list);

							level = 1;

							spawn_asteroids(asteroid_list, level);

							scene = ingame;

							#ifdef DO_AUDIO
								st.playing = 1;
								st.elapsed_time = 0;
								st.time = 0;
								st.target_delay = SOUNDTRACK_MAX_DELAY;
							#endif
						}
					} else if (scene == gameover) {
						if (ev.key.keysym.sym == SDLK_ESCAPE) {
							scene = mainmenu;
							ship_free(&ship);
							ship_init(&ship);
							sprintf(score_buf, "%d", ship.score);
							level = 1;
							spawn_asteroids(asteroid_list, level);
						}
					}
					break;
			}
		}

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		
		if (scene == ingame) {
			if (keystate[SDL_SCANCODE_RIGHT]) {
				ship_rotate(&ship, SHIP_DIR_RIGHT, delta);
			}
			if (keystate[SDL_SCANCODE_LEFT]) {
				ship_rotate(&ship, SHIP_DIR_LEFT, delta);
			}
			if (keystate[SDL_SCANCODE_UP]) {
				ship_move(&ship, delta);

				if (!thrusting) {
					#ifdef DO_AUDIO
					Mix_PlayChannel(1, sound_samples[6], -1);
					#endif
				}

				thrusting = 1;
			} else {
				ship.lines[11] = ship.lines[13] = (vec2f_t){0,4};

				#ifdef DO_AUDIO
				Mix_HaltChannel(1);
				#endif

				thrusting = 0;
			}
			if (keystate[SDL_SCANCODE_ESCAPE]) {
				scene = mainmenu;
				ship_free(&ship);
				ship_init(&ship);
				level = 1;
				spawn_asteroids(asteroid_list, level);
			}
			if (keystate[SDL_SCANCODE_P]) {
				scene = mainmenu;
			}
			
			ship_update(&ship);
		}
		
		for (int i=0; i < asteroid_list->asteroids_n; i++)
		{
			asteroid_t *temp_asteroid = asteroid_list->asteroid_list_array[i];
			asteroid_update(asteroid_list, temp_asteroid, &ship, saucer_list, scene);
		}

		SDL_memset(surf->pixels, 0, surf->h * surf->pitch); // Clear screen

		if (scene == mainmenu) {
			write_ascii(surf, font_large, "ASTEROIDS", (vec2f_t){(float)SCREENWIDTH/2, (float)SCREENHEIGHT/3}, ALIGN_CENTER);
			write_ascii(surf, font_large, "RELOADED", (vec2f_t){(float)SCREENWIDTH/2, (float)SCREENHEIGHT/2-20}, ALIGN_CENTER);
			write_ascii(surf, font_small, ("\0011979 ATARI INC"), (vec2f_t){(float)SCREENWIDTH/2, (float)SCREENHEIGHT-30}, ALIGN_CENTER);
		} else if (scene == ingame) {
			lines(surf, ship.lines, ship.nlines, ship.offset, ship.theta, 0xffffffff);
			if (ship.lives <= 0)
				scene = gameover;
		} else if (scene == gameover) {
			sprintf(score_buf, "%d", ship.score);
			write_ascii(surf, font_large, "GAME OVER", (vec2f_t){(float)SCREENWIDTH/2, (float)SCREENHEIGHT/2-100}, ALIGN_CENTER);
			write_ascii(surf, font_normal, score_buf, (vec2f_t){(float)SCREENWIDTH/2, (float)SCREENHEIGHT/2+70}, ALIGN_CENTER);
			if (ship.score == atoi(score_high))
				write_ascii(surf, font_normal, "NEW HIGHSCORE", (vec2f_t){(float)SCREENWIDTH/2, (float)SCREENHEIGHT/2+170}, ALIGN_CENTER);
			if(ship.score > atoi(score_high))
			{
				fclose(file_high);
				file_high = fopen("highscore.txt","w+");
				fprintf(file_high, score_buf);
				fclose(file_high);
				file_high = fopen("highscore.txt","r");
				fscanf(file_high, "%s", score_high);
			}
		}

		for (int i=0; i < asteroid_list->asteroids_n; i++)
		{
			asteroid_t *temp_asteroid = asteroid_list->asteroid_list_array[i];
			lines(surf, temp_asteroid->lines, temp_asteroid->nlines, temp_asteroid->offset, temp_asteroid->theta, 0xffffffff);
		}

		for (int i=0; i < saucer_list->saucers_n; i++)
		{
			saucer_t *temp_saucer = saucer_list->saucer_list_array[i];
			lines(surf, temp_saucer->lines, temp_saucer->nlines, temp_saucer->offset, 0, 0xffffffff);
		}

		if (scene == ingame)
		{
			if (current_score != ship.score)
			{
				if (ship.score >= 99990)
					ship.score = 0;
				else if ((current_score/10000) + 1 == ship.score/10000)
					ship.lives++;
				current_score = ship.score;

				/*
				You can change the format string to:
					- "%05d", to make it pad the string up to 5 characters with '0's
					- "%5d", to right-align the number
				*/
				sprintf(score_buf, "%d", ship.score);
			}
			write_ascii(surf, font_small, score_buf, (vec2f_t){10,10}, ALIGN_LEFT);
			write_ascii(surf, font_small, score_high, (vec2f_t){SCREENWIDTH/2,10}, ALIGN_CENTER);
			for (int k=1; k <= ship.lives; k++)
				lines(surf, ship.lines, 5, (vec2f_t){k*20,50}, 0, 0xffffffff);

			for (int i = 0; i < MAX_BULLETS; i++) {
				if (ship.bullets[i]) {
					bullet_update(ship.bullets[i], delta);

					for (int x = 0; x <= 1; x++) {
						for (int y = -1; y <= 0; y++) {
							set_pixel(surf, ship.bullets[i]->pos.x+x,
								ship.bullets[i]->pos.y+y, 0xffffffff);
						}
					}
					int temp_oldest = find_oldest_bullet(&ship);
					if (time(NULL) - ship.bullets[temp_oldest]->bul_time >= BULLET_TIMEOUT)
						free_ship_bullet(&ship, temp_oldest);
				}
			}

			for (int i=0; i < saucer_list->saucers_n; i++)
			{
				saucer_t *temp_saucer = saucer_list->saucer_list_array[i];
				saucer_update(saucer_list, temp_saucer, &ship, scene);

				int oldest_time;
				for (int i = 0; i < MAX_SAUCER_BULLETS; i++) {
					if (temp_saucer->bullets[i]) {
						bullet_update(temp_saucer->bullets[i], delta);
						set_pixel(surf, temp_saucer->bullets[i]->pos.x,
									temp_saucer->bullets[i]->pos.y, 0xffffffff);

						// for (int x = 0; x <= 1; x++) {
						// 	for (int y = -1; y <= 0; y++) {
						// 		set_pixel(surf, temp_saucer->bullets[i]->pos.x+x,
						// 			temp_saucer->bullets[i]->pos.y+y, 0xffffffff);
						// 	}
						// }
						int temp_oldest = find_oldest_saucer_bullet(temp_saucer);
						oldest_time = temp_saucer->bullets[temp_oldest]->bul_time;
						if (time(NULL) - oldest_time >= BULLET_TIMEOUT) {
							free_saucer_bullet(temp_saucer, find_oldest_saucer_bullet(temp_saucer));
						}
					}
					else if (time(NULL) - oldest_time >= BULLET_TIMEOUT){
						saucer_shoot(temp_saucer, &ship);
					}
				}
			}

			if (asteroid_list->asteroids_n == 0) {
				if (time_update_counter == 0) {
					temp_time = time(NULL);
					time_update_counter = 1;
				}
				else if (time(NULL) - temp_time >= SPAWN_TIME_GAP) {
					level += 1;
					spawn_asteroids(asteroid_list, level);
					time_update_counter = 0;
				}
			}

			if (saucer_list->saucers_n == 0) {
				if (saucer_time_update_counter == 0) {
					saucer_temp_time = time(NULL);
					saucer_time_update_counter = 1;
				}
				else if (time(NULL) - saucer_temp_time >= SAUCER_SPAWN_TIME_GAP) {
					spawn_saucers(saucer_list, &ship);
					saucer_time_update_counter = 0;
				}
			}
		}
		
		SDL_UpdateWindowSurface(win);
	}

	#ifdef DO_AUDIO
		audio_cleanup(sound_samples);
	#endif

	SDL_DestroyWindow(win);
	SDL_Quit();

	fclose(file_high);
	ship_free(&ship);
	free_asteroid_list(asteroid_list);
	free(asteroid_list);
	free_saucer_list(saucer_list);
	free_font(font_normal);
	free_font(font_small);
	free_font(font_large);

	return 0;
}
