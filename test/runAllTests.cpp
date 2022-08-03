#include "gtest/gtest.h"
#include "../Token.cpp"
#include "../TurnSystem.cpp"
#include "../Graphics.cpp"
#include "../AStar.cpp"
#include "../Text.cpp"
#include "../Strategy.cpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
