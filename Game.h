//
// Created by franc on 06/05/2022.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include "TurnSystem.h"
#include "Screen.h"

enum FASE {menu=0, game=1, win=2, lose=3};

class Game {
private:
    //fase del gioco
    short fase = FASE::menu;

    //Window
    unique_ptr<sf::RenderWindow> window;

    unique_ptr<TurnSystem> turnSystem;

    //Screen
    unique_ptr<Screen> screen;
    sf::Vector2i mousePos;

    //--funzioni private--
    void inizializedTurnSystem();
    void inizializedWindow();
    void inizializedClass();

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
    void renderArena(int scope);
    void render();
};


#endif //MAIN_CPP_GAME_H
