#include "Game.h"

using namespace std;

int main()
{
    //Crea un oggetto game della classe Game, nel quale si trovano i metodi per renderizare il gioco
    std::cout << "Simulazione start \n";
    Game game;
    game.run();
    std::cout << "Simulazione end! \n";
}
