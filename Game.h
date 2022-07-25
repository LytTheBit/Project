//
// Created by franc on 06/05/2022.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include "TurnSystem.h"
#include "Menu.h"
#include "Arena.h"

enum FASE {menu=0, game=1, win=2, lose=3};

class Game {
private:
    //fase del gioco
    short fase = FASE::menu;

    //Window
    sf::RenderWindow* window;
    //sf::Music music;
    TurnSystem* turnSystem;

    //Menu
    Menu* menu;

    //Arena
    Arena* arena;
    sf::Vector2i mousePos;

    //--funzioni private--
    void inizializedTurnSystem();
    void inizializedWindow();
    void inizializedMusic();
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
    void renderMenu(int scope);
    void renderToken();
    void renderArena();
    void render();
};


#endif //MAIN_CPP_GAME_H
