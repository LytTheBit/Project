//
// Created by franc on 10/05/2022.
//

#ifndef MAIN_CPP_TOKEN_H
#define MAIN_CPP_TOKEN_H

#include "Librerie.h"

class Token{
private:
    sf::Texture textureSheet;


    //STATISTIC
    std::string name; //nome della pedina
    int Hp; //vita della pedina
    int Atk; //attacco della pedina
    int Def; //difesa della pedina
    int Speed; //quanti quadretti può percorrere
    int PosX; //vita della pedina
    int PosY; //attacco della pedina
    int Owner; //è un nemico? o un amico? 0=neutro, 1=amico, 2=nemico

    //INIT
    void inizializedSprite(const sf::Image& image);


public:
    sf::Sprite sprite;

    //COSTRUTTORE
    Token(std::string inputName, const sf::Image& image, int owner = 0, int InputHp = 10, int InputAtk = 10, int InputDef = 10, int ImputSpeed = 5, int X=0, int Y=0);
    //DISTRUTTORE
    virtual ~Token();

    //COMBATTIMENTO
    void attached(int AttaccoSubito); //metodo per testare lo unit testing

    //Get statistiche
    std::string GetName();
    int GetHp();
    int GetAtk();
    int GetDef();
    int GetSpeed();
    int GetPosX();
    int GetPosY();
    int GetOwner();

    //TODO aggiungere i setter

    //FUNZIONI PER IL MOVIMENTO
    void update(sf::Vector2i& mousePos);
    void updateMovement(sf::Vector2i& mousePos);
    void render(sf::RenderTarget& target);
};
#endif //MAIN_CPP_TOKEN_H
