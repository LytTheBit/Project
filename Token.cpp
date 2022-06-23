//
// Created by franc on 10/05/2022.
//

#include "Token.h"

void Token::inizializedTexture() {
    this->textureSheet.loadFromFile("C:/Users/franc/Desktop/Reisende/Pipo.png");
}
void Token::inizializedSprite() {
    this->sprite.setTexture(this->textureSheet);
    this->sprite.setTextureRect(sf::IntRect(0,0,32,64));
    this->sprite.setScale(3.f,3.f);
}

Token::Token() {
    this->inizializedTexture();
    this->inizializedSprite();
}

Token::~Token() {

}

//FUNZIONI
void Token::update(sf::Vector2i& mousePos){//aggiorna il token
    sf::Vector2i Pos=mousePos;
    this->updateMovement(Pos);
}
void Token::updateMovement(sf::Vector2i& mousePos) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        for(int i=0; i<=9; i++){
            for(int j=0; j<=9; j++) {
                if (mousePos.x > (i * 32 * 3) && mousePos.y > (j * 32 * 3) &&
                    mousePos.x < ((i + 1) * 32 * 3) && mousePos.y < ((j + 1) * 32 * 3)) {
                    if((i * 32 * 3.f)>this->sprite.getPosition().x){
                        this->sprite.move(1.f,0.f);
                    }
                    else if((i * 32 * 3.f)<this->sprite.getPosition().x){
                        this->sprite.move(-1.f,0.f);
                    }

                    if((j * 32 * 3.f)-96>this->sprite.getPosition().y){
                        this->sprite.move(0.f,1.f);
                    }
                    else if((j * 32 * 3.f)-96<this->sprite.getPosition().y){
                        this->sprite.move(0.f,-1.f);
                    }
                }
            }
        }
    }//insegue la freccia
}
void Token::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}




