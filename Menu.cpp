//
// Created by franc on 24/07/2022.
//

#include "Menu.h"
//COSTRUTTORE E DISTRUTTORE
Menu::Menu() {
    this->inizializedTexture();
    this->inizializedSprite();
}
Menu::~Menu() {

}

void Menu::inizializedTexture() {
    //la funzione che mi fa inserire la textureMenu
    textureMenu.loadFromFile("../Sprites/Menu.png");
    textureWin.loadFromFile("../Sprites/Win.png");
    textureLose.loadFromFile("../Sprites/Lose.png");
}
void Menu::inizializedSprite() {
    //la funzione che mi fa creare lo spriteMenu

    //Il mio inizializedSprite setta come "textureMenu" dello "spriteMenu" la "textureMenu" che
    // vado ad implementere nel metodo "inizializedTexture"
    spriteMenu.setTexture(textureMenu);
    spriteWin.setTexture(textureWin);
    spriteLose.setTexture(textureLose);
    //posizione iniziale dello sfondo
    spriteMenu.setPosition(0, 0);
    spriteWin.setPosition(0, 0);
    spriteLose.setPosition(0, 0);
    //ridimensiona lo sfondo (in questo caso il triplo della dimensione)
    spriteMenu.scale(3.f, 3.f);
    spriteWin.scale(3.f, 3.f);
    spriteLose.scale(3.f, 3.f);
}

void Menu::update() {
    //sposto il quadrato della selezione nella casella selezionata
}
void Menu::render(sf::RenderTarget& target, int scope) {
    if (scope==0)
        target.draw(spriteMenu);
    else if (scope==1)
        target.draw(spriteWin);
    else if (scope==2)
        target.draw(spriteLose);
}
