//
// Created by franc on 09/07/2022.
//

#ifndef TURNSYSTEM_CPP_GRAPHICS_H
#define TURNSYSTEM_CPP_GRAPHICS_H

#include "Librerie.h"

class Graphics{
private:
    sf::Texture textureBlu;
    sf::Sprite spriteBlu;

    //FUNZIONI PRIVATE (per la creazione del mago)
    void inizializedTexture(); //la funzione che mi fa inserire la textureMenu
    void inizializedSprite(); //la funzione che mi fa creare lo spriteMenu
public:
    Graphics();
    ~Graphics();

    //Funzioni
    void PlaceBlu(int X, int Y); //funzione che mi aggiorna la selezione
    void render(sf::RenderTarget& target); //funzione che mi fa vedere il mago a schermo

};

#endif //TURNSYSTEM_CPP_GRAPHICS_H
