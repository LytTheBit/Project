//
// Created by franc on 06/05/2022.
//

#ifndef REISENDE_ARENA_H
#define REISENDE_ARENA_H
#include "Librerie.h"

class Screen {
    sf::Texture textureArena; //dichiarazione della variabile della textureMenu
    sf::Sprite spriteArena; //dichiarazione della variabile dello spriteMenu
    sf::Texture textureRedCursor;
    sf::Sprite spriteRedCursor;

    sf::Texture textureMenu;
    sf::Sprite spriteMenu;
    sf::Texture textureWin;
    sf::Sprite spriteWin;
    sf::Texture textureLose;
    sf::Sprite spriteLose;


    //FUNZIONI PRIVATE (per la creazione del mago)
    void inizializedTexture(); //la funzione che mi fa inserire la textureMenu
    void inizializedSprite(); //la funzione che mi fa creare lo spriteMenu
public:
    Screen();
    ~Screen();

    //Funzioni
    void update(sf::Vector2i& mousePos); //funzione che mi aggiorna la selezione
    void render(sf::RenderTarget& target, int scope); //funzione che mi fa vedere il mago a schermo
};


#endif //REISENDE_ARENA_H
