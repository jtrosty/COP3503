#include "../intAdd.cpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1 basic addition, subtraction, and max values", "[insert]"){
    int test1[] = {1, 1, 1, 1};
    int test2[] = {1, -1};
    int test3[] = {INT32_MAX, INT32_MIN};
    REQUIRE(intAdd(test1, 4) == 4);
    REQUIRE(intAdd(test2, 2) == 0);
    REQUIRE(intAdd(test3, 2) == -1);
}