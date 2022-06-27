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

    //STATISTIC
    int Hp; //vita della pedina
    int Atk; //attacco della pedina
    int Def; //difesa della pedina

    //INIT
    void inizializedTexture();
    void inizializedSprite();


public:
    //COSTRUTTORE
    Token(int InputHp = 10, int InputAtk = 10, int InputDef = 10);
    //DISTRUTTORE
    virtual ~Token();

    //COMBATTIMENTO
    void attached(int AttaccoSubito); //metodo per testare lo unit testing

    //Get statistiche
    int GetHp();
    int GetAtk();
    int GetDef();

    //FUNZIONI PER IL MOVIMENTO
    void update(sf::Vector2i& mousePos);
    void updateMovement(sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);
};
#endif //MAIN_CPP_TOKEN_H
