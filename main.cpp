#include "Game.h"
#include "AStar.cpp"


using namespace std;

int main()
{
    //Crea un oggetto game della classe Game, nel quale si trovano i metodi per renderizare il gioco
    cout << "Link start \n"; //Controllo l'avvio
    Game game;
    game.run();
    cout << "Link end! \n"; //Controllo lo spegnimento


    //Test di A*
    //deve essere diviso e spostato
    //nel programma finale non avrò più bisogno del grafico
    SquareGrid grid = MakeDiagram();
    GridLocation start{2, 5}, goal{2, 1};
    std::unordered_map<GridLocation, GridLocation> came_from;
    std::unordered_map<GridLocation, double> cost_so_far;
    add_rect(grid, 2, 2, 3, 3);//aggiungo un ipotetico pedone
    a_star_search(grid, start, goal, came_from, cost_so_far);
    draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
    std::cout << '\n';
    std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
    std::cout << '\n';
    draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);

}
