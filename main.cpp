#include "Game.h"

using namespace std;

int main()
{
    //Crea un oggetto game della classe Game, nel quale si trovano i metodi per renderizare il gioco
    cout << "Link start \n"; //Controllo l'avvio
    Game game;
    game.run();
    cout << "Link end! \n"; //Controllo lo spegnimento
}
