//
// Created by franc on 10/05/2022.
//

#ifndef MAIN_CPP_TOKEN_H
#define MAIN_CPP_TOKEN_H

#include "Librerie.h"
class Token{
private:
    sf::Texture textureSheet;
    sf::Sprite sprite;


    //ANIMATION
    //MOVMENT
    //INIT
    void inizializedTexture();
    void inizializedSprite();
public:
    Token();
    virtual ~Token();

    //FUNZIONI
    void update(sf::Vector2i& mousePos);
    void updateMovement(sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);
};
#endif //MAIN_CPP_TOKEN_H
