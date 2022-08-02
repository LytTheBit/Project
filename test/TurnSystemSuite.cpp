//
// Created by franc on 05/07/2022.
//
#include "gtest/gtest.h"

#include "../Librerie.h"
#include "../Graphics.h"
#include "../AStar.h"
#include "../Text.h"

#include "../TurnSystem.h"


class TurnSystemSuite : public ::testing::Test{
public:
    TurnSystemSuite() {
        TurnSystem test(1);
    }
};

TEST_F(TurnSystemSuite, TestMouse) {
    TurnSystem test(1);

    sf::Vector2i mouseTest={100,200};

    int testX = test.MouseOnTheBoard(mouseTest).x;
    int testY = test.MouseOnTheBoard(mouseTest).y;

//controllo se la funzione MouseOnTheBoard funziona
    ASSERT_EQ(0, testX)<< "test X";
    ASSERT_EQ(0, testY)<< "test Y";
}

TEST_F(TurnSystemSuite, PositionControl_1) {
    TurnSystem test(1);
    ASSERT_EQ(true, test.PositionCheck())<< "test che ad inizio partita non ci siano token in 0-0";
}
TEST_F(TurnSystemSuite, PositionControl_2) {
    TurnSystem test(2);
    ASSERT_EQ(true, test.PositionCheck())<< "test che al inizio livello 2 non ci siano token in 0-0";
}
TEST_F(TurnSystemSuite, PositionControl_3) {
    TurnSystem test(3);
    ASSERT_EQ(true, test.PositionCheck())<< "test che al inizio livello 3 non ci siano token in 0-0";
}
