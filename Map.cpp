//
// Created by franc on 30/06/2022.
//

#include "librerie.h"

//Crea un tipo di dato GridLocation, che contiene la posizione sulla scacchiera
struct GridLocation {
    int x, y;
};

namespace std {
    //implementare la funzione hash in modo da poter inserire GridLocation in un unordered_set

    //I unordered_set sono contenitori che memorizzano elementi univoci in nessun ordine particolare
    // e che consentono il recupero rapido di singoli elementi in base al loro valore.
    template <> struct hash<GridLocation> {
        std::size_t operator()(const GridLocation& id) const noexcept {
            // NOTE: better to use something like boost hash_combine
            return std::hash<int>()(id.x ^ (id.y << 16));
        }
    };
}



struct SquareGrid {
    static std::array<GridLocation, 4> DIRS;

    int width, height;
    std::unordered_set<GridLocation> walls;

    SquareGrid(int width_, int height_)
            : width(width_), height(height_) {}

    bool in_bounds(GridLocation id) const {
        return 0 <= id.x && id.x < width
               && 0 <= id.y && id.y < height;
    }

    bool passable(GridLocation id) const {
        return walls.find(id) == walls.end();
    }

    std::vector<GridLocation> neighbors(GridLocation id) const {
        std::vector<GridLocation> results;

        for (GridLocation dir : DIRS) {
            GridLocation next{id.x + dir.x, id.y + dir.y};
            if (in_bounds(next) && passable(next)) {
                results.push_back(next);
            }
        }

        if ((id.x + id.y) % 2 == 0) {
            // see "Ugly paths" section for an explanation:
            std::reverse(results.begin(), results.end());
        }

        return results;
    }
};

std::array<GridLocation, 4> SquareGrid::DIRS = {
        //imposta le direzioni
        GridLocation{1, 0}, //East
        GridLocation{-1, 0}, //West
        GridLocation{0, -1}, //North
        GridLocation{0, 1} //South
};

// Funzioni che possono tornare utili a GridLocation
//Uguale
bool operator == (GridLocation a, GridLocation b) {
    return a.x == b.x && a.y == b.y;
}
//Diverso
bool operator != (GridLocation a, GridLocation b) {
    return !(a == b);
}
//Percorso
bool operator < (GridLocation a, GridLocation b) {
    return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, const GridLocation& loc) {
    out << '(' << loc.x << ',' << loc.y << ')';
    return out;
}

//Aggiunge i muri, può essere modificata per generare gli spazzi occupati dai pezzi
void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2) {
    for (int x = x1; x < x2; ++x) {
        for (int y = y1; y < y2; ++y) {
            grid.walls.insert(GridLocation{x, y}); //genera effettivamente il "muro"
        }
    }
}

//crea la scacchiera e le mura al suo interno
//nel mio caso la scacchiera è 7x6, e non ha muri e aree difficili
//va modificato affinche aggiunga un muro per ogni pezzo che non sia quello mosso
SquareGrid MakeDiagram() {
    SquareGrid grid(7, 6);
    //add_rect(grid, 1, 1, 2, 2);
    typedef GridLocation L;
    return grid;
}



// Crea una classe generica, che viene usata per stampare il grafico della scacchiera
//non è necessaria al gioco, ma può essere utile durante lo sviluppo
template<class Graph>
void draw_grid(const Graph& graph,
               std::unordered_map<GridLocation, double>* distances=nullptr,
               std::unordered_map<GridLocation, GridLocation>* point_to=nullptr,
               std::vector<GridLocation>* path=nullptr,
               GridLocation* start=nullptr,
               GridLocation* goal=nullptr) {
    const int field_width = 3; //crea una costante per la quale alcuni simboli vengono stampati 3 volte
    std::cout << std::string(field_width * graph.width, '_') << '\n'; //stampa la parte alta del grafico ___
    for (int y = 0; y != graph.height; ++y) {
        for (int x = 0; x != graph.width; ++x) {
            GridLocation id {x, y};
            if (graph.walls.find(id) != graph.walls.end()) {
                std::cout << std::string(field_width, '#'); //stampa i muri nel grafico
            } else if (start && id == *start) {
                std::cout << " A "; //stampa start nel grafico
            } else if (goal && id == *goal) {
                std::cout << " Z "; //stampa l'obbiettivo nel grafico
            } else if (path != nullptr && find(path->begin(), path->end(), id) != path->end()) {
                std::cout << " @ "; //stampa il percorso nel grafico
            } else if (point_to != nullptr && point_to->count(id)) {
                GridLocation next = (*point_to)[id];
                if (next.x == x + 1) { std::cout << " > "; }      //stampano i "flussi"
                else if (next.x == x - 1) { std::cout << " < "; } //che partono da start
                else if (next.y == y + 1) { std::cout << " v "; } //e usati, per trovare
                else if (next.y == y - 1) { std::cout << " ^ "; } //il percorso migliore
                else { std::cout << " * "; }
            } else if (distances != nullptr && distances->count(id)) {
                std::cout << ' ' << std::left << std::setw(field_width - 1) << (*distances)[id];
            } else {
                std::cout << " . ";
            }
        }
        std::cout << '\n';
    }
    std::cout << std::string(field_width * graph.width, '~') << '\n'; //stampa la parte bassa del grafico ~~~
}

// Funzione per calcolare la distanza da un punto A ad un punto B
template<class Graph>
int DistanceCalculation(const Graph& graph,
               std::vector<GridLocation>* path=nullptr,
               GridLocation* start=nullptr,
               GridLocation* goal=nullptr) {
int distance=0;
    for (int y = 0; y != graph.height; ++y) {
        for (int x = 0; x != graph.width; ++x) {
            GridLocation id{x, y};
            if (find(path->begin(), path->end(), id) != path->end()) {
                if(find(path->begin(), path->end(), id) == path->begin()){
                }
                else{
                    distance++;
                }
                //std::cout<<"passa da "<< id.x << "-" << id.y <<"\n";
            }
        }
    }
    return distance;
}