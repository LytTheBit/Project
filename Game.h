//
// Created by franc on 06/05/2022.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include "Librerie.h"
#include "Arena.h"
#include "TurnSystem.h"
#include "Token.h"


class Game {
private:
    //Window
    sf::RenderWindow* window;

    TurnSystem* prova;


    //Arena
    Arena* arena;
    sf::Vector2i mousePos;

    //--funzioni private--
    void inizializedTurnSystem();
    void inizializedWindow();
    void inizializedArena();
public:
    //costruttore e distruttore
    Game();
    virtual ~Game();

    //--Accesso--
    void run();

    //--funzioni pubbliche--
    void update();
    void updateTurnSystem();
    void updateMouse();
    void updatePointer();
    void renderToken();
    void renderArena();
    void render();
};


#endif //MAIN_CPP_GAME_H
