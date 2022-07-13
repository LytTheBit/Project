//
// Created by franc on 30/06/2022.
//

#include "Map.cpp"

template<typename T, typename priority_t>
struct PriorityQueue {
    typedef std::pair<priority_t, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>,
            std::greater<PQElement>> elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(T item, priority_t priority) {
        elements.emplace(priority, item);
    }

    T get() {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

template<typename Location>
std::vector<Location> reconstruct_path(
        Location start, Location goal,
        std::unordered_map<Location, Location> came_from) {
    std::vector<Location> path;
    int control=0;
    Location current = goal;
    while (current != start) {  // fallisce se non trova un percorso
        //std::cout<< "cos'e' current " << current <<"\n";//percorso al contrario
        path.push_back(current);
        current = came_from[current];
        control++;
        if(control==10){  //se non trova il percorso
            path[0].x=-1; //allora esce forzatamente
            path[0].y=-1; //e ritorna un path simbolico che
            return path;  //viene letto dal programma per capire cosa è successo
        }
    }
    //std::cout<< "cos'e' current " << current <<"\n";//percorso al contrario
    path.push_back(start); // opzionale
    std::reverse(path.begin(), path.end());
    return path;
}

inline double heuristic(GridLocation a, GridLocation b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

template<typename Location, typename Graph>
void a_star_search
        (Graph graph,
         Location start,
         Location goal,
         std::unordered_map<Location, Location>& came_from,
         std::unordered_map<Location, double>& cost_so_far)
{
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        Location current = frontier.get();

        if (current == goal) {
            break;
        }

        for (Location next : graph.neighbors(current)) {
            double new_cost = cost_so_far[current] + 1;
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}

