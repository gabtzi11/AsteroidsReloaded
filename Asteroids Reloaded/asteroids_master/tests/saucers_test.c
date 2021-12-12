/* a test file to run unity tests for the saucers module -- alex was here */

#include "unity_src/unity.h"
#include "../src/include/asteroids.h"
#include "../src/include/saucers.h"
#include "../src/include/ship.h"
#include "../src/include/collisions.h"

/* test instances of saucer and time */

saucer_t *test_saucer;
ship_t *test_ship;
saucer_list_t test_saucer_list;
game_state test_state;
double test_time;

/* this is the setup method called by UNITY_BEGIN() */

void setUp(void) 
{
    test_saucer = (saucer_t *) malloc(sizeof(saucer_t));
    test_time = 0;
}

/* this is the the tearDown called by UNITY_END() */

void tearDown(void)
{
    free(test_saucer->lines);
    free(test_saucer);
}

/* this test runs currently to test the initialisation of a 
   small saucer */

void test_saucer_init(void)
{
    // tests for the small saucer
    
    saucer_init(test_saucer, SAUCER_SMALL);

    TEST_ASSERT_EQUAL_INT(10, test_saucer->nlines);
    TEST_ASSERT_NOT_NULL(test_saucer->lines);

    TEST_ASSERT_GREATER_OR_EQUAL(-1000, test_saucer->offset.x);
    TEST_ASSERT_LESS_THAN(0, test_saucer->offset.x);
    TEST_ASSERT_GREATER_OR_EQUAL(0, test_saucer->offset.y);
    TEST_ASSERT_LESS_THAN(1000, test_saucer->offset.y);
    TEST_ASSERT_LESS_THAN(SCREENWIDTH, test_saucer->offset.x);
    TEST_ASSERT_LESS_THAN(SCREENHEIGHT, test_saucer->offset.y);

    TEST_ASSERT_EQUAL(SAUCER_SMALL, test_saucer->size);

    TEST_ASSERT_GREATER_OR_EQUAL(-0.4, test_saucer->velocity.x);
    TEST_ASSERT_LESS_THAN(0.2, test_saucer->velocity.x);
    TEST_ASSERT_EQUAL_FLOAT(SAUCER_SMALL_SPEED, test_saucer->velocity.x);

    TEST_ASSERT_EQUAL_INT(-2, test_saucer->lines[0].x);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[0].y);
    TEST_ASSERT_EQUAL_INT(2, test_saucer->lines[1].x);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[1].y);
    TEST_ASSERT_EQUAL_INT(2, test_saucer->lines[2].x);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[2].y);
    TEST_ASSERT_EQUAL_INT(5, test_saucer->lines[3].x);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[3].y);
    TEST_ASSERT_EQUAL_INT(5, test_saucer->lines[4].x);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[4].y);
    TEST_ASSERT_EQUAL_INT(-5, test_saucer->lines[5].x);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[5].y);
    TEST_ASSERT_EQUAL_INT(-5, test_saucer->lines[6].x);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[6].y);
    TEST_ASSERT_EQUAL_INT(-2, test_saucer->lines[7].x);
    TEST_ASSERT_EQUAL_INT(-3, test_saucer->lines[7].y);
    TEST_ASSERT_EQUAL_INT(-2, test_saucer->lines[8].x);
    TEST_ASSERT_EQUAL_INT(-3, test_saucer->lines[8].y);
    TEST_ASSERT_EQUAL_INT(2, test_saucer->lines[9].x);
    TEST_ASSERT_EQUAL_INT(-3, test_saucer->lines[9].y);
    TEST_ASSERT_EQUAL_INT(2, test_saucer->lines[10].x);
    TEST_ASSERT_EQUAL_INT(-3, test_saucer->lines[10].y);
    TEST_ASSERT_EQUAL_INT(5, test_saucer->lines[11].x);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[11].y);

    TEST_ASSERT_EQUAL_INT(2, test_saucer->lines[12].x);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[12].y);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[13].x);
    TEST_ASSERT_EQUAL_INT(3, test_saucer->lines[13].y);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[14].x);
    TEST_ASSERT_EQUAL_INT(3, test_saucer->lines[14].y);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[15].x);
    TEST_ASSERT_EQUAL_INT(3, test_saucer->lines[15].y);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[16].x);
    TEST_ASSERT_EQUAL_INT(3, test_saucer->lines[16].y);
    TEST_ASSERT_EQUAL_INT(-2, test_saucer->lines[17].x);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[17].y);
    TEST_ASSERT_EQUAL_INT(-2, test_saucer->lines[18].x);
    TEST_ASSERT_EQUAL_INT(1, test_saucer->lines[18].y);
    TEST_ASSERT_EQUAL_INT(-5, test_saucer->lines[19].x);
    TEST_ASSERT_EQUAL_INT(-1, test_saucer->lines[19].y);
    
}

/* this test makes sure the updates are correctly performed */

void test_saucer_update(void)
{
    // extreme case: zero values
    test_saucer->offset.x = 0;
    test_saucer->offset.y = 0;
    test_state = ingame;

    saucer_update(&test_saucer_list, test_saucer, test_ship, test_state);

    TEST_ASSERT_EQUAL_FLOAT(0 + SAUCER_SMALL_SPEED, test_saucer->offset.x);
    TEST_ASSERT_EQUAL_FLOAT(0 + SAUCER_SMALL_SPEED, test_saucer->offset.y);

    // extreme case: extreme edge value
    test_saucer->offset.x = SCREENWIDTH;
    test_saucer->offset.y = SCREENHEIGHT;

    saucer_update(&test_saucer_list, test_saucer, test_ship, test_state);

    // should reset the offset to zero as it goes off screen
    TEST_ASSERT_EQUAL_FLOAT(0, test_saucer->offset.x);
    TEST_ASSERT_EQUAL_FLOAT(0, test_saucer->offset.y);
}

/* this function runs the test procedures */

int main()
{
	UNITY_BEGIN();

	RUN_TEST(test_saucer_init);
    //RUN_TEST(test_saucer_update);

	return UNITY_END();
}