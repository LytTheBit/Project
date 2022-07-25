//
// Created by franc on 06/05/2022.
//

#ifndef REISENDE_ARENA_H
#define REISENDE_ARENA_H
#include "Librerie.h"

class Arena {
    sf::Texture texture; //dichiarazione della variabile della textureMenu
    sf::Sprite sprite; //dichiarazione della variabile dello spriteMenu
    sf::Texture textureRed;
    sf::Sprite spriteRed;

    //FUNZIONI PRIVATE (per la creazione del mago)
    void inizializedTexture(); //la funzione che mi fa inserire la textureMenu
    void inizializedSprite(); //la funzione che mi fa creare lo spriteMenu
public:
    Arena();
    ~Arena();

    //Funzioni
    void update(sf::Vector2i& mousePos); //funzione che mi aggiorna la selezione
    void render(sf::RenderTarget& target); //funzione che mi fa vedere il mago a schermo
};


#endif //REISENDE_ARENA_H
