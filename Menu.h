//
// Created by franc on 24/07/2022.
//

#ifndef TURNSYSTEM_CPP_MENU_H
#define TURNSYSTEM_CPP_MENU_H
#include "Librerie.h"

class Menu {
    sf::Texture textureMenu; //dichiarazione della variabile della textureMenu
    sf::Sprite spriteMenu; //dichiarazione della variabile dello spriteMenu
    sf::Texture textureWin;
    sf::Sprite spriteWin;
    sf::Texture textureLose;
    sf::Sprite spriteLose;

    //FUNZIONI PRIVATE (per la creazione del mago)
    void inizializedTexture(); //la funzione che mi fa inserire la textureMenu
    void inizializedSprite(); //la funzione che mi fa creare lo spriteMenu
public:
    Menu();
    ~Menu();

    //Funzioni
    void update(); //funzione che mi aggiorna la selezione
    void render(sf::RenderTarget& target, int scope); //funzione che mi fa vedere il mago a schermo
};


#endif //TURNSYSTEM_CPP_MENU_H
