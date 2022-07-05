//
// Created by franc on 05/07/2022.
//
#include "gtest/gtest.h"

#include "../Librerie.h"
#include "../TurnSystem.h"


class TurnSystemSuite : public ::testing::Test{
public:
    TurnSystemSuite() {
        TurnSystem test;
    }
};

TEST_F(TurnSystemSuite, TestMouse) {
    TurnSystem test;

    sf::Vector2i mouseTest={100,200};

    int testX = test.MouseOnTheBoard(mouseTest).x;
    int testY = test.MouseOnTheBoard(mouseTest).y;

//controllo se la funzione MouseOnTheBoard funziona
    ASSERT_EQ(0, testX)<< "test X";
    ASSERT_EQ(0, testY)<< "test Y";
}

TEST_F(TurnSystemSuite, PositionControl) {
    TurnSystem test;
    ASSERT_EQ(true, test.PositionCheck())<< "test che ad inizio partita non ci siano token in 0-0";
}
