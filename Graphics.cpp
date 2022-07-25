//
// Created by franc on 09/07/2022.
//

#include "Graphics.h"

void Graphics::inizializedTexture() {
    textureBlu.loadFromFile("../Sprites/PointerBlu.png");
}

void Graphics::inizializedSprite() {
    spriteBlu.setTexture(this->textureBlu);
    spriteBlu.setPosition(-96, -96);
}

Graphics::Graphics() {
    inizializedTexture();
    inizializedSprite();
}

Graphics::~Graphics() {

}

void Graphics::PlaceBlu(int X, int Y) {
    spriteBlu.setScale(3.f,3.f);
    spriteBlu.setPosition(startingPointX+X*96, (startingPointY)+Y*96);
}

void Graphics::render(sf::RenderTarget &target) {
    target.draw(this->spriteBlu);
}
