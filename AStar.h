//
// Created by franc on 17/07/2022.
//

#ifndef MAIN_CPP_IMPLEMENTATION_H
#define MAIN_CPP_IMPLEMENTATION_H

#include <bits/stdc++.h>
#include "Librerie.h"

using namespace std;

#define ROW 6
#define COL 7

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef pair<double, pair<int, int> > pPair;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};

bool isValid(int row, int col);
bool isUnBlocked(int grid[][COL], int row, int col);
bool isDestination(int row, int col, Pair dest);
double calculateHValue(int row, int col, Pair dest);
void tracePath(cell cellDetails[][COL], Pair dest);
void aStarSearch(int grid[][COL], Pair src, Pair dest);

extern sf::Vector2i percorso[10];
extern int distanza;

void SetPercorso(int A, Pair B);
sf::Vector2i GetPercorso(int A);

void SetDistanza(int A);
int GetDistanza();

#endif //MAIN_CPP_IMPLEMENTATION_H
