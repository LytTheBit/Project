//
// Created by franc on 29/06/2022.
//

#ifndef MAIN_CPP_TURNSYSTEM_H
#define MAIN_CPP_TURNSYSTEM_H

#include "Librerie.h"
#include "Token.h"


enum TURN_OF {player=0, computer=1};
enum PHASE {pawnSelection=0, positionSelection=1, motionAnimation=2, targetSelection=3, attackAnimation=4};


class TurnSystem{
private:

    short turnOf = TURN_OF::player;
    short phase = PHASE::pawnSelection;

    //TOKEN
    Token* soldier;
    Token* demon;



    void InizializedToken();

public:
    //COSTRUTTORE
    TurnSystem();
    //DISTRUTTORE
    virtual ~TurnSystem();

    //Aggiorna clase
    void Update(sf::Vector2i& mousePos);

    //FASI
    void WhoMoves(sf::Vector2i &mousePos);
    void WhereItMove();
    void MoveAnimation();
    void WhoAttacks();
    void AttackAnimation();

    //Controllo pedine
    Token ThereIsATokenThere(sf::Vector2i &mousePos);

    //Render pedine
    void Render(sf::RenderTarget& target);
};

#endif //MAIN_CPP_TURNSYSTEM_H
