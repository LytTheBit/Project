//
// Created by franc on 29/06/2022.
//

#include "TurnSystem.h"


TurnSystem::TurnSystem() {
    this->InizializedToken();
}

TurnSystem::~TurnSystem() {

}


void TurnSystem::InizializedToken() {
    sf::Image image;
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Soldier.png");
    this->soldier= new Token(image,10,10,5,1,1);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Dimon.png");
    this->demon= new Token(image,6,6,6,3,3);
}


void TurnSystem::Update(sf::Vector2i &mousePos) {
    sf::Vector2i pos=mousePos;
    this->soldier->update(pos);

    /*
    if (this->phase == PHASE::pawnSelection){
        this->WhoMoves(Pos);
    }
    else if (this->phase == PHASE::positionSelection){
        //code
    }
    else if(this->phase == PHASE::motionAnimation){
        //code
    }
    else if (this->phase == PHASE::targetSelection){
        //code
    }
    else if(this->phase == PHASE::attackAnimation){
        //code
    }
     */
}


void TurnSystem::WhoMoves(sf::Vector2i &mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse

    }
}

void TurnSystem::WhereItMove() {

}

void TurnSystem::MoveAnimation() {

}

void TurnSystem::WhoAttacks() {

}

void TurnSystem::AttackAnimation() {

}

/*
Token TurnSystem::ThereIsATokenThere(sf::Vector2i &mousePos) {
//controlla se si è selezionata una pedina
    return Token();
}
*/
//render pedine
void TurnSystem::Render(sf::RenderTarget& target) {
    this->soldier->render(target);
    this->demon->render(target);

}



