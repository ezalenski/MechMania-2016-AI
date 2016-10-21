//
// Created by Edmund Zalenski on 10/9/16.
//
#include <gtest/gtest.h>
#include "GameMap.h"

class GameMapTest : public ::testing::Test
{
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    GameMapTest() : Test() {
        g = new GameMap();
    }

    virtual ~GameMapTest() {
        delete g;
    }

    GameMap* g;
    std::vector<int> pos1;
    std::vector<int> pos2;
};

TEST_F (GameMapTest, GameMapTest_InBounds_Test1) {
    GameMap test = *g;
    pos1 = {2, 2};
    ASSERT_TRUE (test.is_in_bounds(pos1));
}

TEST_F (GameMapTest, GameMapTest_InBounds_Test2) {
    GameMap test = *g;
    pos1 = {0, 0};
    ASSERT_TRUE (test.is_in_bounds(pos1));
}

TEST_F (GameMapTest, GameMapTest_Not_InBounds_Test1) {
    GameMap test = *g;
    pos1 = {5, 5};
    ASSERT_FALSE (test.is_in_bounds(pos1));
}

TEST_F (GameMapTest, GameMapTest_Not_InBounds_Test2) {
    GameMap test = *g;
    pos1 = {6, 6};
    ASSERT_FALSE (test.is_in_bounds(pos1));
}

TEST_F (GameMapTest, GameMapTest_Not_InBounds_Test3) {
    GameMap test = *g;
    pos1 = {3, 3};
    ASSERT_FALSE (test.is_in_bounds(pos1));
}

TEST_F (GameMapTest, GameMapTest_InRange_Test1) {
    GameMap test = *g;
    pos1 = {3, 3};
    pos2 = {3, 3};
    ASSERT_TRUE (test.in_vision_of(pos1, pos2, 5));
}

TEST_F (GameMapTest, GameMapTest_InRange_Test2) {
    GameMap test = *g;
    pos1 = {0, 2};
    pos2 = {0, 5};
    ASSERT_TRUE (test.in_vision_of(pos1, pos2, 5));
}

TEST_F (GameMapTest, GameMapTest_InRange_Test3) {
    GameMap test = *g;
    pos1 = {1, 2};
    pos2 = {3, 2};
    ASSERT_TRUE (test.in_vision_of(pos1, pos2, 5));
}

TEST_F (GameMapTest, GameMapTest_Not_InRange_Test) {
    GameMap test = *g;
    pos1 = {0, 0};
    pos2 = {2, 2};
    ASSERT_FALSE (test.in_vision_of(pos1, pos2, 5));
}

TEST_F (GameMapTest, GameMapTest_Not_InRange_Test2) {
    GameMap test = *g;
    pos1 = {1, 2};
    pos2 = {1, 5};
    ASSERT_FALSE (test.in_vision_of(pos1, pos2, 1));
}

TEST_F (GameMapTest, GameMapTest_Not_InRange_Test3) {
    GameMap test = *g;
    pos1 = {1, 0};
    pos2 = {1, 2};
    ASSERT_FALSE (test.in_vision_of(pos1, pos2, 5));
}

TEST_F (GameMapTest, GameMapTest_Not_InRange_Test4) {
    GameMap test = *g;
    pos1 = {0, 1};
    pos2 = {2, 1};
    ASSERT_FALSE (test.in_vision_of(pos1, pos2, 5));
}