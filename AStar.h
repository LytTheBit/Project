//
// Created by franc on 17/07/2022.
//

#ifndef TURNSYSTEM_CPP_ASTAR_H
#define TURNSYSTEM_CPP_ASTAR_H

#include "Map.h"

template<typename T, typename priority_t>
struct PriorityQueue;

template<typename Location>
std::vector<Location> reconstruct_path(Location start, Location goal,std::unordered_map<Location, Location> came_from);

inline double heuristic(GridLocation a, GridLocation b);

template<typename Location, typename Graph>
void a_star_search(Graph graph, Location start, Location goal, std::unordered_map<Location, Location>& came_from, std::unordered_map<Location, double>& cost_so_far);
/*
class AStar {

};
*/

#endif //TURNSYSTEM_CPP_ASTAR_H
