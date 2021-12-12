/* a test file to run unity tests for the asteroid module -- alex was here */

#include "unity_src/unity.h"
#include "../src/include/asteroids.h"
#include "../src/include/asteroid.h"
#include "../src/include/ship.h"
#include "../src/include/saucers.h"
#include "../src/include/collisions.h"
#include "../src/include/bullets.h"
#include <stdlib.h>
#include <unistd.h>

#define TEST_MAX_ASTEROIDS 6

/* test asteroid to run asteroid_init() */
asteroid_t *test_asteroid;
asteroid_list_t test_asteroid_list;
ship_t *test_ship;
saucer_list_t test_saucer_list;
bullet_t test_bullet;
game_state test_state;

void pre_test_setup(void)
{
	test_asteroid = (asteroid_t *) malloc(sizeof(asteroid_t));
	test_ship = (ship_t *) malloc(sizeof(ship_t));
}

void post_test_cleanup(void)
{
	if (test_asteroid != NULL)
	{
		if (test_asteroid->lines != NULL)
			free(test_asteroid->lines);

		free(test_asteroid);
	}
	if (test_ship != NULL)
	{
		if (test_ship->lines != NULL)
			free(test_ship->lines);

		free(test_ship);
	}

	//if (&test_asteroid_list != NULL)
	//	free_asteroid_list(&test_asteroid_list);
}

void setUp(void) {}

void tearDown(void) {}

void test_asteroid_init(void) 
{
	int i;

	pre_test_setup();

	/* SMALL ASTEROID TESTS */

	asteroid_init(test_asteroid, ASTEROID_SMALL);

	TEST_ASSERT_NOT_NULL(test_asteroid);
	TEST_ASSERT_EQUAL_INT(10, test_asteroid->nlines);
	TEST_ASSERT_NOT_NULL(test_asteroid->lines);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->theta);
	TEST_ASSERT_FLOAT_WITHIN(SCREENWIDTH, 0, test_asteroid->offset.x);
	TEST_ASSERT_FLOAT_WITHIN(SCREENHEIGHT, 0, test_asteroid->offset.y);
	TEST_ASSERT_TRUE(test_asteroid->size == ASTEROID_SMALL);
	TEST_ASSERT_FLOAT_WITHIN(1.2, -0.6, test_asteroid->velocity.x);
	TEST_ASSERT_FLOAT_WITHIN(1.2, -0.6, test_asteroid->velocity.y);

	TEST_ASSERT_EQUAL_FLOAT(0   , test_asteroid->lines[ 0].x);
	TEST_ASSERT_EQUAL_FLOAT(-4.5, test_asteroid->lines[ 0].y);

	TEST_ASSERT_EQUAL_FLOAT(6   , test_asteroid->lines[ 1].x);
	TEST_ASSERT_EQUAL_FLOAT(-10.5, test_asteroid->lines[ 1].y);
	
	TEST_ASSERT_EQUAL_FLOAT(6   , test_asteroid->lines[ 2].x);
	TEST_ASSERT_EQUAL_FLOAT(-10.5, test_asteroid->lines[ 2].y);

	TEST_ASSERT_EQUAL_FLOAT(12   , test_asteroid->lines[ 3].x);
	TEST_ASSERT_EQUAL_FLOAT(-4.5, test_asteroid->lines[ 3].y);

	TEST_ASSERT_EQUAL_FLOAT(12   , test_asteroid->lines[ 4].x);
	TEST_ASSERT_EQUAL_FLOAT(-4.5, test_asteroid->lines[ 4].y);

	TEST_ASSERT_EQUAL_FLOAT(9   , test_asteroid->lines[ 5].x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->lines[ 5].y);

	TEST_ASSERT_EQUAL_FLOAT(9   , test_asteroid->lines[ 6].x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->lines[ 6].y);

	TEST_ASSERT_EQUAL_FLOAT(12   , test_asteroid->lines[ 7].x);
	TEST_ASSERT_EQUAL_FLOAT(2, test_asteroid->lines[ 7].y);

	TEST_ASSERT_EQUAL_FLOAT(12   , test_asteroid->lines[ 8].x);
	TEST_ASSERT_EQUAL_FLOAT(2, test_asteroid->lines[ 8].y);

	TEST_ASSERT_EQUAL_FLOAT(3   , test_asteroid->lines[ 9].x);
	TEST_ASSERT_EQUAL_FLOAT(10.5, test_asteroid->lines[ 9].y);

	TEST_ASSERT_EQUAL_FLOAT(3   , test_asteroid->lines[10].x);
	TEST_ASSERT_EQUAL_FLOAT(10.5, test_asteroid->lines[10].y);

	TEST_ASSERT_EQUAL_FLOAT(-6   , test_asteroid->lines[11].x);
	TEST_ASSERT_EQUAL_FLOAT(10.5, test_asteroid->lines[11].y);

	TEST_ASSERT_EQUAL_FLOAT(-6   , test_asteroid->lines[12].x);
	TEST_ASSERT_EQUAL_FLOAT(10.5, test_asteroid->lines[ 12].y);

	TEST_ASSERT_EQUAL_FLOAT(-12   , test_asteroid->lines[13].x);
	TEST_ASSERT_EQUAL_FLOAT(2, test_asteroid->lines[13].y);

	TEST_ASSERT_EQUAL_FLOAT(-12   , test_asteroid->lines[14].x);
	TEST_ASSERT_EQUAL_FLOAT(2, test_asteroid->lines[14].y);

	TEST_ASSERT_EQUAL_FLOAT(-12   , test_asteroid->lines[15].x);
	TEST_ASSERT_EQUAL_FLOAT(-4.5, test_asteroid->lines[15].y);

	TEST_ASSERT_EQUAL_FLOAT(-12   , test_asteroid->lines[16].x);
	TEST_ASSERT_EQUAL_FLOAT(-4.5, test_asteroid->lines[16].y);

	TEST_ASSERT_EQUAL_FLOAT(-6   , test_asteroid->lines[17].x);
	TEST_ASSERT_EQUAL_FLOAT(-10.5, test_asteroid->lines[17].y);

	TEST_ASSERT_EQUAL_FLOAT(-6   , test_asteroid->lines[18].x);
	TEST_ASSERT_EQUAL_FLOAT(-10.5, test_asteroid->lines[18].y);

	TEST_ASSERT_EQUAL_FLOAT(0   , test_asteroid->lines[19].x);
	TEST_ASSERT_EQUAL_FLOAT(-4.5, test_asteroid->lines[19].y);

	TEST_ASSERT_EQUAL_FLOAT(-12, test_asteroid->extremes[0]);
	TEST_ASSERT_EQUAL_FLOAT(-10.5, test_asteroid->extremes[1]);
	TEST_ASSERT_EQUAL_FLOAT(12, test_asteroid->extremes[2]);
	TEST_ASSERT_EQUAL_FLOAT(10.5, test_asteroid->extremes[3]);

	post_test_cleanup();

	/* MEDIUM ASTEROID TESTS */

	pre_test_setup();

	asteroid_init(test_asteroid, ASTEROID_MEDIUM);

	TEST_ASSERT_NOT_NULL(test_asteroid);
	TEST_ASSERT_EQUAL_INT(10, test_asteroid->nlines);
	TEST_ASSERT_NOT_NULL(test_asteroid->lines);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->theta);
	TEST_ASSERT_FLOAT_WITHIN(SCREENWIDTH, 0, test_asteroid->offset.x);
	TEST_ASSERT_FLOAT_WITHIN(SCREENHEIGHT, 0, test_asteroid->offset.y);
	TEST_ASSERT_TRUE(test_asteroid->size == ASTEROID_MEDIUM);
	TEST_ASSERT_FLOAT_WITHIN(1.2, -0.5, test_asteroid->velocity.x);
	TEST_ASSERT_FLOAT_WITHIN(1.2, -0.5, test_asteroid->velocity.y);

	TEST_ASSERT_EQUAL_FLOAT(0   , test_asteroid->lines[ 0].x);
	TEST_ASSERT_EQUAL_FLOAT(-7.5, test_asteroid->lines[ 0].y);

	TEST_ASSERT_EQUAL_FLOAT(10 , test_asteroid->lines[ 1].x);
	TEST_ASSERT_EQUAL_FLOAT(-17.5, test_asteroid->lines[ 1].y);
	
	TEST_ASSERT_EQUAL_FLOAT(10   , test_asteroid->lines[ 2].x);
	TEST_ASSERT_EQUAL_FLOAT(-17.5, test_asteroid->lines[ 2].y);

	TEST_ASSERT_EQUAL_FLOAT(20   , test_asteroid->lines[ 3].x);
	TEST_ASSERT_EQUAL_FLOAT(-7.5, test_asteroid->lines[ 3].y);

	TEST_ASSERT_EQUAL_FLOAT(20   , test_asteroid->lines[ 4].x);
	TEST_ASSERT_EQUAL_FLOAT(-7.5, test_asteroid->lines[ 4].y);

	TEST_ASSERT_EQUAL_FLOAT(15   , test_asteroid->lines[ 5].x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->lines[ 5].y);

	TEST_ASSERT_EQUAL_FLOAT(15   , test_asteroid->lines[ 6].x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->lines[ 6].y);

	TEST_ASSERT_EQUAL_FLOAT(20   , test_asteroid->lines[ 7].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_asteroid->lines[ 7].y);

	TEST_ASSERT_EQUAL_FLOAT(20   , test_asteroid->lines[ 8].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_asteroid->lines[ 8].y);

	TEST_ASSERT_EQUAL_FLOAT(5   , test_asteroid->lines[ 9].x);
	TEST_ASSERT_EQUAL_FLOAT(17.5, test_asteroid->lines[ 9].y);

	TEST_ASSERT_EQUAL_FLOAT(5   , test_asteroid->lines[10].x);
	TEST_ASSERT_EQUAL_FLOAT(17.5, test_asteroid->lines[10].y);

	TEST_ASSERT_EQUAL_FLOAT(-10   , test_asteroid->lines[11].x);
	TEST_ASSERT_EQUAL_FLOAT(17.5, test_asteroid->lines[11].y);

	TEST_ASSERT_EQUAL_FLOAT(-10   , test_asteroid->lines[12].x);
	TEST_ASSERT_EQUAL_FLOAT(17.5, test_asteroid->lines[ 12].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[13].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_asteroid->lines[13].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[14].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_asteroid->lines[14].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[15].x);
	TEST_ASSERT_EQUAL_FLOAT(-7.5, test_asteroid->lines[15].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[16].x);
	TEST_ASSERT_EQUAL_FLOAT(-7.5, test_asteroid->lines[16].y);

	TEST_ASSERT_EQUAL_FLOAT(-10   , test_asteroid->lines[17].x);
	TEST_ASSERT_EQUAL_FLOAT(-17.5, test_asteroid->lines[17].y);

	TEST_ASSERT_EQUAL_FLOAT(-10   , test_asteroid->lines[18].x);
	TEST_ASSERT_EQUAL_FLOAT(-17.5, test_asteroid->lines[18].y);

	TEST_ASSERT_EQUAL_FLOAT(0   , test_asteroid->lines[19].x);
	TEST_ASSERT_EQUAL_FLOAT(-7.5, test_asteroid->lines[19].y);

	TEST_ASSERT_EQUAL_FLOAT(-20, test_asteroid->extremes[0]);
	TEST_ASSERT_EQUAL_FLOAT(-17.5, test_asteroid->extremes[1]);
	TEST_ASSERT_EQUAL_FLOAT(20, test_asteroid->extremes[2]);
	TEST_ASSERT_EQUAL_FLOAT(17.5, test_asteroid->extremes[3]);

	post_test_cleanup();

	/* LARGE ASTEROID TESTS */

	pre_test_setup();

	asteroid_init(test_asteroid, ASTEROID_LARGE);

	TEST_ASSERT_NOT_NULL(test_asteroid);
	TEST_ASSERT_EQUAL_INT(10, test_asteroid->nlines);
	TEST_ASSERT_NOT_NULL(test_asteroid->lines);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->theta);
	TEST_ASSERT_FLOAT_WITHIN(SCREENWIDTH, 0, test_asteroid->offset.x);
	TEST_ASSERT_FLOAT_WITHIN(SCREENHEIGHT, 0, test_asteroid->offset.y);
	TEST_ASSERT_TRUE(test_asteroid->size == ASTEROID_LARGE);
	TEST_ASSERT_FLOAT_WITHIN(1.2, -0.3, test_asteroid->velocity.x);
	TEST_ASSERT_FLOAT_WITHIN(1.2, -0.3, test_asteroid->velocity.y);

	TEST_ASSERT_EQUAL_FLOAT(0   , test_asteroid->lines[ 0].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_asteroid->lines[ 0].y);

	TEST_ASSERT_EQUAL_FLOAT(20 , test_asteroid->lines[ 1].x);
	TEST_ASSERT_EQUAL_FLOAT(-35, test_asteroid->lines[ 1].y);
	
	TEST_ASSERT_EQUAL_FLOAT(20   , test_asteroid->lines[ 2].x);
	TEST_ASSERT_EQUAL_FLOAT(-35, test_asteroid->lines[ 2].y);

	TEST_ASSERT_EQUAL_FLOAT(40   , test_asteroid->lines[ 3].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_asteroid->lines[ 3].y);

	TEST_ASSERT_EQUAL_FLOAT(40   , test_asteroid->lines[ 4].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_asteroid->lines[ 4].y);

	TEST_ASSERT_EQUAL_FLOAT(30   , test_asteroid->lines[ 5].x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->lines[ 5].y);

	TEST_ASSERT_EQUAL_FLOAT(30   , test_asteroid->lines[ 6].x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_asteroid->lines[ 6].y);

	TEST_ASSERT_EQUAL_FLOAT(40   , test_asteroid->lines[ 7].x);
	TEST_ASSERT_EQUAL_FLOAT(20, test_asteroid->lines[ 7].y);

	TEST_ASSERT_EQUAL_FLOAT(40   , test_asteroid->lines[ 8].x);
	TEST_ASSERT_EQUAL_FLOAT(20, test_asteroid->lines[ 8].y);

	TEST_ASSERT_EQUAL_FLOAT(10   , test_asteroid->lines[ 9].x);
	TEST_ASSERT_EQUAL_FLOAT(35, test_asteroid->lines[ 9].y);

	TEST_ASSERT_EQUAL_FLOAT(10   , test_asteroid->lines[10].x);
	TEST_ASSERT_EQUAL_FLOAT(35, test_asteroid->lines[10].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[11].x);
	TEST_ASSERT_EQUAL_FLOAT(35, test_asteroid->lines[11].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[12].x);
	TEST_ASSERT_EQUAL_FLOAT(35, test_asteroid->lines[ 12].y);

	TEST_ASSERT_EQUAL_FLOAT(-40   , test_asteroid->lines[13].x);
	TEST_ASSERT_EQUAL_FLOAT(20, test_asteroid->lines[13].y);

	TEST_ASSERT_EQUAL_FLOAT(-40   , test_asteroid->lines[14].x);
	TEST_ASSERT_EQUAL_FLOAT(20, test_asteroid->lines[14].y);

	TEST_ASSERT_EQUAL_FLOAT(-40   , test_asteroid->lines[15].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_asteroid->lines[15].y);

	TEST_ASSERT_EQUAL_FLOAT(-40   , test_asteroid->lines[16].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_asteroid->lines[16].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[17].x);
	TEST_ASSERT_EQUAL_FLOAT(-35, test_asteroid->lines[17].y);

	TEST_ASSERT_EQUAL_FLOAT(-20   , test_asteroid->lines[18].x);
	TEST_ASSERT_EQUAL_FLOAT(-35, test_asteroid->lines[18].y);

	TEST_ASSERT_EQUAL_FLOAT(0   , test_asteroid->lines[19].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_asteroid->lines[19].y);

	TEST_ASSERT_EQUAL_FLOAT(-40, test_asteroid->extremes[0]);
	TEST_ASSERT_EQUAL_FLOAT(-35, test_asteroid->extremes[1]);
	TEST_ASSERT_EQUAL_FLOAT(40, test_asteroid->extremes[2]);
	TEST_ASSERT_EQUAL_FLOAT(35, test_asteroid->extremes[3]);

	post_test_cleanup();
}

void test_check_asteroid_collision(void)
{
	pre_test_setup();

	ship_init(test_ship);
	asteroid_init(test_asteroid, ASTEROID_SMALL);

	test_asteroid_list.asteroid_list_array[0] = test_asteroid;
	test_asteroid_list.asteroid_list_array[0]->offset = (vec2f_t) {0, 0};
	// tests take place on small asteroids, ship is center screen upon init

	// first test is for no collision
	int lives = test_ship->lives;
	check_ship_asteroid_collision(&test_asteroid_list, test_asteroid, test_ship);
	TEST_ASSERT_EQUAL(lives, test_ship->lives); // check no lives lost

	// second test is a collision
	lives = test_ship->lives;
	test_asteroid_list.asteroid_list_array[0]->offset = (vec2f_t) {SCREENWIDTH/2, SCREENHEIGHT/2};
	check_ship_asteroid_collision(&test_asteroid_list, test_asteroid_list.asteroid_list_array[0], test_ship);
	TEST_ASSERT_EQUAL(lives-1, test_ship->lives); // check one life lost

	post_test_cleanup();
	//pre_test_setup();

	// now test for bullet collisions
/*
	bullet_init(&test_bullet, (vec2f_t) {0,0}, (vec2f_t) {0,0});

	// first is no collision

	ship_init(test_ship);

	test_bullet.pos.x = 100;
	test_bullet.pos.y = 0;

	test_asteroid_list.asteroid_list_array[0]->offset.x = 0;
	test_asteroid_list.asteroid_list_array[0]->offset.y = 0;

	check_collision(&test_asteroid_list, test_asteroid_list.asteroid_list_array[0], test_bullet);
	TEST_ASSERT_NOT_NULL(test_asteroid_list.asteroid_list_array[0]);

	// now a real collision

	test_bullet.pos.x = 0;
	check_collision(&test_asteroid_list, test_asteroid_list.asteroid_list_array[0], test_bullet);
	TEST_ASSERT_NULL(test_asteroid_list.asteroid_list_array[0]);

*/

	//post_test_cleanup();
}

void test_asteroid_update(void)
{
	pre_test_setup();

	// test asteroid position updates
	asteroid_init(test_asteroid, ASTEROID_SMALL);
	test_asteroid->offset = (vec2f_t) {0, 0};
	test_asteroid->velocity = (vec2f_t) {5, 0}; // some arbitrary amount to test for
	test_state = ingame;
	
	asteroid_update(&test_asteroid_list, test_asteroid, test_ship, &test_saucer_list, test_state);

	TEST_ASSERT_EQUAL(5, test_asteroid->offset.x);
	TEST_ASSERT_EQUAL(0, test_asteroid->offset.y);

	

	// test wraparound
	
	asteroid_init(test_asteroid, ASTEROID_SMALL);
	test_asteroid_list.asteroid_list_array[0] = test_asteroid;
	test_asteroid_list.asteroids_n = 1;
	test_asteroid->offset = (vec2f_t) {SCREENWIDTH + 1, SCREENHEIGHT + 1};
	test_asteroid->velocity = (vec2f_t) {0, 0}; // some arbitrary amount to test for

	asteroid_update(&test_asteroid_list, test_asteroid, test_ship, &test_saucer_list, test_state);

	TEST_ASSERT_EQUAL(0, test_asteroid->offset.x);
	TEST_ASSERT_EQUAL(0, test_asteroid->offset.y);

	
}

int main() {
	UNITY_BEGIN();

	RUN_TEST(test_asteroid_init);
	//RUN_TEST(test_check_asteroid_collision);
	RUN_TEST(test_asteroid_update);

	return UNITY_END();
}
