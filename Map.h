//
// Created by franc on 18/07/2022.
//

#ifndef TURNSYSTEM_CPP_MAP_H
#define TURNSYSTEM_CPP_MAP_H

#include "librerie.h"

struct GridLocation;

template <> struct std::hash<GridLocation>;

struct SquareGrid;


void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2);
SquareGrid MakeDiagram();

template<class Graph>
void draw_grid(const Graph& graph,std::unordered_map<GridLocation, double>* distances=nullptr,std::unordered_map<GridLocation, GridLocation>* point_to=nullptr,std::vector<GridLocation>* path=nullptr,GridLocation* start=nullptr,GridLocation* goal=nullptr);

template<class Graph>
int DistanceCalculation(const Graph& graph,
                        std::vector<GridLocation>* path=nullptr,
                        GridLocation* start=nullptr,
                        GridLocation* goal=nullptr);
/*
class Map {

};
*/

#endif //TURNSYSTEM_CPP_MAP_H
