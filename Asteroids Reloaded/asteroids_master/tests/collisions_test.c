#include "unity_src/unity.h"
#include "../src/include/collisions.h"
#include "../src/include/asteroids.h"

vec2f_t test_point;
vec2f_t test_v0, test_v1, test_v2, test_v3;
vec2f_t *test_poly; 
vec2f_t *test_poly2;

void setUp(void) {}

void tearDown(void) {}

void test_lines_intersect(void)
{
    // two crosing lines
    test_v0 = (vec2f_t) {0, 0};
    test_v1 = (vec2f_t) {5, 5};
    test_v2 = (vec2f_t) {0, 5};
    test_v3 = (vec2f_t) {5, -5};

    TEST_ASSERT_EQUAL(1, lines_intersect(test_v0, test_v1, test_v2, test_v3));

    // two parallel lines
    test_v2 = (vec2f_t) {0, 5};
    test_v3 = (vec2f_t) {5, 5};

    TEST_ASSERT_EQUAL(0, lines_intersect(test_v0, test_v1, test_v2, test_v3));

    // two non parallel lines
    test_v2 = (vec2f_t) {0, 5};
    test_v3 = (vec2f_t) {5, 1};

    TEST_ASSERT_EQUAL(0, lines_intersect(test_v0, test_v1, test_v2, test_v3));

    // two nearly crossing lines
    test_v2 = (vec2f_t) {0, 5};
    test_v3 = (vec2f_t) {2, -2};

    TEST_ASSERT_EQUAL(0, lines_intersect(test_v0, test_v1, test_v2, test_v3));
}

void test_point_inside_poly(void)
{
    test_poly = (vec2f_t*) malloc(8 * sizeof(vec2f_t));
    
    // square from (5, 10) to (10, 5)
    test_poly[0] = (vec2f_t) {5, 10};
    test_poly[1] = (vec2f_t) {10, 10};
    test_poly[2] = (vec2f_t) {10, 10};
    test_poly[3] = (vec2f_t) {10, 5};
    test_poly[4] = (vec2f_t) {10, 5};
    test_poly[5] = (vec2f_t) {5, 5};
    test_poly[6] = (vec2f_t) {5, 5};
    test_poly[7] = (vec2f_t) {5, 10};

    // point inside
    test_point = (vec2f_t) {7, 7};

    TEST_ASSERT_EQUAL(1, point_inside_poly(test_point, test_poly,(vec2f_t){0,0}, 8));

    // point not inside
    test_point = (vec2f_t) {20, 20};

    TEST_ASSERT_EQUAL(0, point_inside_poly(test_point, test_poly,(vec2f_t){0,0}, 8));

    // point to the left
    test_point = (vec2f_t) {0, 7};
    
    TEST_ASSERT_EQUAL(0, point_inside_poly(test_point, test_poly,(vec2f_t){0,0}, 8));

    free(test_poly);
}

void test_poly_inside_poly(void)
{
    test_poly = (vec2f_t*) malloc(8 * sizeof(vec2f_t));
    
    // square from (5, 10) to (10, 5)
    test_poly[0] = (vec2f_t) {5, 10};
    test_poly[1] = (vec2f_t) {10, 10};
    test_poly[2] = (vec2f_t) {10, 10};
    test_poly[3] = (vec2f_t) {10, 5};
    test_poly[4] = (vec2f_t) {10, 5};
    test_poly[5] = (vec2f_t) {5, 5};
    test_poly[6] = (vec2f_t) {5, 5};
    test_poly[7] = (vec2f_t) {5, 10};

    test_poly2 = (vec2f_t*) malloc(8 * sizeof(vec2f_t));
    
    // square from (7, 12) to (12, 7)
    test_poly2[0] = (vec2f_t) {7, 12};
    test_poly2[1] = (vec2f_t) {12, 12};
    test_poly2[2] = (vec2f_t) {12, 12};
    test_poly2[3] = (vec2f_t) {12, 7};
    test_poly2[4] = (vec2f_t) {12, 7};
    test_poly2[5] = (vec2f_t) {7, 7};
    test_poly2[6] = (vec2f_t) {7, 7};
    test_poly2[7] = (vec2f_t) {7, 12};

    TEST_ASSERT_EQUAL(1, poly_inside_poly(test_poly, test_poly2, (vec2f_t){5,5}, (vec2f_t){7,7}, 8, 8));

    // square from (0, 1) to (1, 0)
    test_poly2[0] = (vec2f_t) {0, 1};
    test_poly2[1] = (vec2f_t) {1, 1};
    test_poly2[2] = (vec2f_t) {1, 1};
    test_poly2[3] = (vec2f_t) {1, 0};
    test_poly2[4] = (vec2f_t) {1, 0};
    test_poly2[5] = (vec2f_t) {0, 0};
    test_poly2[6] = (vec2f_t) {0, 0};
    test_poly2[7] = (vec2f_t) {0, 1};

    TEST_ASSERT_EQUAL(0, poly_inside_poly(test_poly, test_poly2, (vec2f_t){5,5}, (vec2f_t){0,0}, 8, 8));

    free(test_poly);
    free(test_poly2);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_lines_intersect);
    RUN_TEST(test_point_inside_poly);
    RUN_TEST(test_poly_inside_poly);

    return UNITY_END();
}