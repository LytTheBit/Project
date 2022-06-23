//
// Created by franc on 06/05/2022.
//

#include "Arena.h"
//COSTRUTTORE E DISTRUTTORE
Arena::Arena() {
    this->inizializedTexture();
    this->inizializedSprite();
}
Arena::~Arena() {

}

void Arena::inizializedTexture() {
    //la funzione che mi fa inserire la texture
    this->texture.loadFromFile("C:/Users/franc/Desktop/Reisende/Sfondo.png");
    this->textureViola.loadFromFile("C:/Users/franc/Desktop/Reisende/Viola.png");
}
void Arena::inizializedSprite() {
    //la funzione che mi fa creare lo sprite

    //Il mio inizializedSprite setta come "texture" dello "sprite" la "texture" che
    // vado ad implementere nel metodo "inizializedTexture"
    this->sprite.setTexture(this->texture);

    //posizione iniziale dello sfondo
    this->sprite.setPosition(0, 0);

    //ridimensiona lo sfondo (in questo caso il triplo della dimensione)
    this->sprite.scale(3.f, 3.f);

    this->spriteViola.setTexture(this->textureViola);
    this->spriteViola.scale(3.f, 3.f);
}

void Arena::update(sf::Vector2i& mousePos) {
    //sposto il quadrato della selezione nella casella selezionata
    for(int i=0; i<=9; i++){
        for(int j=0; j<=9; j++) {
            if (mousePos.x > (i * 32 * 3) && mousePos.y > (j * 32 * 3) &&
                mousePos.x < ((i + 1) * 32 * 3) && mousePos.y < ((j + 1) * 32 * 3)) {
                this->spriteViola.setPosition(i * 32 * 3.f, j * 32 * 3.f);
            }
        }
    }
}
void Arena::render(sf::RenderTarget& target) {
    //il "target" andrà a disegnare il nostro personaggio, e poi il render di game lo disegnerà sullo schermo
    target.draw(this->sprite);
    target.draw(this->spriteViola);
}



