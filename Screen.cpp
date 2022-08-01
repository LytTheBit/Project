//
// Created by franc on 06/05/2022.
//

#include "Screen.h"
//COSTRUTTORE E DISTRUTTORE
Screen::Screen() {
    this->inizializedTexture();
    this->inizializedSprite();
}
Screen::~Screen() {

}

void Screen::inizializedTexture() {
    //la funzione che mi fa inserire la textureMenu
    textureArena.loadFromFile("../Sprites/Palace.png");
    textureRedCursor.loadFromFile("../Sprites/Pointer.png");
    textureMenu.loadFromFile("../Sprites/Menu.png");
    textureWin.loadFromFile("../Sprites/Win.png");
    textureLose.loadFromFile("../Sprites/Lose.png");

}
void Screen::inizializedSprite() {
    //Il mio inizializedSprite setta come "textureMenu" dello "spriteMenu" la "textureMenu" che
    // vado ad implementere nel metodo "inizializedTexture"
    spriteArena.setTexture(this->textureArena);
    //posizione iniziale dello sfondo
    spriteArena.setPosition(0, 0);
    //ridimensiona lo sfondo (in questo caso il triplo della dimensione)
    spriteArena.scale(3.f, 3.f);
    spriteRedCursor.setTexture(this->textureRedCursor);
    spriteRedCursor.scale(3.f, 3.f);
    spriteRedCursor.setPosition(startingPointX, startingPointY);

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

void Screen::update(sf::Vector2i& mousePos) {
    //sposto il quadrato della selezione nella casella selezionata
    for(int i=0; i<=6; i++){
        for(int j=0; j<=5; j++) {
            if (mousePos.x > (startingPointX+(i * 32 * 3.f)) && mousePos.y > (startingPointY+(j * 32 * 3.f)) &&
                mousePos.x < (startingPointX+((i + 1) * 32 * 3.f)) && mousePos.y < (startingPointY+((j + 1) * 32 * 3.f))) {
                this->spriteRedCursor.setPosition((startingPointX + (i * 32 * 3.f)), (startingPointY + (j * 32 * 3.f)));
            }
        }
    }
}
void Screen::render(sf::RenderTarget& target, int scope) {
    if (scope==0)
        target.draw(spriteMenu);
    else if (scope==1)
        target.draw(spriteWin);
    else if (scope==2)
        target.draw(spriteLose);
    else if (scope==3){
        target.draw(this->spriteArena);
        target.draw(this->spriteRedCursor);
    }
}



