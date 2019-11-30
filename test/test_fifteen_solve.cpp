#include "gtest/gtest.h"
#include "../src/fifteen_solve.h"

TEST(FifteenTestSuite, TestRandom) {
    auto smp = get_random_sample();
    auto smp2 = get_random_sample();
    EXPECT_NE(smp, smp2);
}

TEST(FifteenTestSuite, TestPossibleMoves){
    sample smp = { 0,1,2,3,
                   4,5,6,7,
                   8,9,10,11,
                  12,13,14,15};
    std::list<sample> result = {{4, 1, 2, 3,
                                 0, 5, 6, 7,
                                 8, 9, 10,11,
                                 12,13,14,15},
                                {1, 0, 2, 3,
                                 4, 5, 6, 7,
                                 8, 9, 10,11,
                                 12,13,14,15},
                                };
    EXPECT_EQ(get_possible_moves(smp), result);
}

TEST(FifteenTestSuite, TestHeuristic){
    sample smp = { 0,1,2,3,
                  4,5,6,7,
                  8,9,10,11,
                  12,13,14,15};
    EXPECT_EQ(get_heuristic(smp), 0);
    smp =  { 4,1,2,3,
             0,5,6,7,
             8,9,10,11,
             12,13,14,15};
    EXPECT_EQ(get_heuristic(smp), 2);
}
