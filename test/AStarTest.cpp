//
// Created by franc on 03/08/2022.
//
#include "gtest/gtest.h"

#include "../Librerie.h"
#include "../AStar.h"

#define ROW 7
#define COL 8


class AStarTest : public ::testing::Test{
public:
    AStarTest() {
        //TurnSystem test(1);
    }
};

TEST_F(AStarTest, AStarDistanceTest) {
    int grid[ROW][COL];

    //partenza
    Pair src = make_pair(1, 1);
    //arrivo
    Pair dest = make_pair(1,3);

    //creare la mappa
    std::fill(*grid,*grid+ROW*COL,1);
    grid[1][2]=0;

    aStarSearch(grid, src, dest);
    //calcolo distance percorsa
    int distance=GetDistanza();
    //elenco caselle percorse

//controllo se la funzione MouseOnTheBoard funziona
    ASSERT_EQ(4, distance)<< "test distanza";
}

TEST_F(AStarTest, AStarPathTest){
    int grid[ROW][COL];

    //partenza
    Pair src = make_pair(1, 1);
    //arrivo
    Pair dest = make_pair(1,3);

    //creare la mappa
    std::fill(*grid,*grid+ROW*COL,1);
    grid[1][2]=0;

    aStarSearch(grid, src, dest);

    ASSERT_EQ(0, GetPercorso(1).x)<< "1° test percorso X";
    ASSERT_EQ(1, GetPercorso(1).y)<< "1° test percorso Y";

    ASSERT_EQ(0, GetPercorso(2).x)<< "2° test percorso X";
    ASSERT_EQ(2, GetPercorso(2).y)<< "2° test percorso Y";

    ASSERT_EQ(0, GetPercorso(3).x)<< "3° test percorso X";
    ASSERT_EQ(3, GetPercorso(3).y)<< "3° test percorso Y";

    ASSERT_EQ(1, GetPercorso(4).x)<< "4° test percorso X";
    ASSERT_EQ(3, GetPercorso(4).y)<< "4° test percorso Y";
}