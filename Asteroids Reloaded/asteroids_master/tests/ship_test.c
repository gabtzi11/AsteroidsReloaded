/* a test file to run unity tests for the ship module -- alex was here */

#include "unity_src/unity.h"
#include "../src/include/asteroids.h"
#include "../src/include/ship.h"
#include <math.h>

/* a test instance of the ship struct used purely for testing the methods herein */

ship_t *test_ship;
double test_time;

/* this procedure is called with UNITY_BEGIN(), it allocates memory to the
   test ship and gives test_time an initial value of zero. It also calls the
   pseudo constructor 'ship_init()' to give intial values for test_ship's 
   members */

void setUp(void) 
{
    test_ship = (ship_t *) malloc(sizeof(ship_t));
    test_time = 0;
    ship_init(test_ship);
}

/* this procedure runs with UNITY_END(), it frees the test instance and
   also frees the lines member */

void tearDown(void)
{
    free(test_ship->lines);
    free(test_ship);
}

/* this is a test, it tests the ship_init procedure by running example values
   and testing the outcome which was calculated by inspection */

void test_ship_init(void)
{
    TEST_ASSERT_EQUAL_INT(7, test_ship->nlines);
    TEST_ASSERT_FLOAT_WITHIN(500.00, 500.00, test_ship->offset.x);
	TEST_ASSERT_FLOAT_WITHIN(500.00, 500.00, test_ship->offset.y);
    TEST_ASSERT_EQUAL_INT(0, test_ship->theta);
    TEST_ASSERT_EQUAL_FLOAT(0, test_ship->velocity.x);
	TEST_ASSERT_EQUAL_FLOAT(0, test_ship->velocity.y);
    TEST_ASSERT_EQUAL_INT(3, test_ship->lives);

    TEST_ASSERT_EQUAL_FLOAT(0, test_ship->lines[0].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_ship->lines[0].y);
    TEST_ASSERT_EQUAL_FLOAT(-10, test_ship->lines[1].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_ship->lines[1].y);
    TEST_ASSERT_EQUAL_FLOAT(0, test_ship->lines[2].x);
	TEST_ASSERT_EQUAL_FLOAT(-15, test_ship->lines[2].y);
    TEST_ASSERT_EQUAL_FLOAT(10, test_ship->lines[3].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_ship->lines[3].y);
    TEST_ASSERT_EQUAL_FLOAT(10, test_ship->lines[4].x);
	TEST_ASSERT_EQUAL_FLOAT(10, test_ship->lines[4].y);
    TEST_ASSERT_EQUAL_FLOAT(2, test_ship->lines[5].x);
	TEST_ASSERT_EQUAL_FLOAT(4, test_ship->lines[5].y);
}

/* this procedure tests the ship_move function, it gives a fabricated velocity
   and time structure for use in the test and resets these values as to not 
   disturb later tests */

void test_ship_move(void)
{
    ship_move(test_ship, test_time);

    TEST_ASSERT_EQUAL_FLOAT(0, test_ship->velocity.x);
    TEST_ASSERT_EQUAL_FLOAT(0, test_ship->velocity.y);

    test_ship->velocity.x = 1;
    test_time = 1;
    ship_move(test_ship, test_time);

    TEST_ASSERT_EQUAL_FLOAT(1, test_ship->velocity.x);
    TEST_ASSERT_EQUAL_FLOAT(-1, test_ship->velocity.y);

    test_ship->velocity.x = 0;
    test_time = 0;
}

/* this procedure tests the rotate function */

void test_ship_rotate(void)
{
    test_ship->theta = 0;
    test_time = 1;
    ship_rotate(test_ship, SHIP_DIR_LEFT, test_time);
    TEST_ASSERT_EQUAL_FLOAT(-4, test_ship->theta);

    test_ship->theta = 0;
    ship_rotate(test_ship, SHIP_DIR_RIGHT, test_time);
    TEST_ASSERT_EQUAL_FLOAT(4, test_ship->theta);

    test_time = 0;
    test_ship->theta = 0;
}

/* this test ensures that the ship instance is correctly updated */

void test_ship_update(void) 
{
    test_ship->velocity.x = 1;
    test_ship->velocity.y = 1;
    test_ship->offset = (vec2f_t){0, 0};

    ship_update(test_ship);

    TEST_ASSERT_EQUAL_FLOAT(0.9985, test_ship->velocity.x);
    TEST_ASSERT_EQUAL_FLOAT(0.9985, test_ship->velocity.y);
    TEST_ASSERT_EQUAL_FLOAT(0.9985, test_ship->offset.x);
    TEST_ASSERT_EQUAL_FLOAT(0.9985, test_ship->offset.y);

    test_ship->velocity.x = 0;
    test_ship->velocity.y = 0;
    test_ship->offset = (vec2f_t){SCREENWIDTH/2,SCREENHEIGHT/2};
}

/* this test ensures the given value of the hyperdrive is within the bounds
   of the screen */

void test_ship_hyperdrive(void) 
{
    ship_hyperdrive(test_ship);

    TEST_ASSERT_GREATER_OR_EQUAL(0, test_ship->offset.x);
    TEST_ASSERT_LESS_THAN(SCREENWIDTH, test_ship->offset.x);
    TEST_ASSERT_GREATER_OR_EQUAL(0, test_ship->offset.y);
    TEST_ASSERT_LESS_THAN(SCREENHEIGHT, test_ship->offset.y);

    test_ship->offset.x = 0;
    test_ship->offset.y = 0;
}

/* this is where the magic happens. each test is called here, including the 
   setup and teardown */

int main()
{
	UNITY_BEGIN();

	RUN_TEST(test_ship_init);
    RUN_TEST(test_ship_move);
    RUN_TEST(test_ship_rotate);
    RUN_TEST(test_ship_update);
    RUN_TEST(test_ship_hyperdrive);

	return UNITY_END();
}
