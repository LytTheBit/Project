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
    sf::Vector2i destinazione;

    //TOKEN
    Token* soldier;
    Token* demon;
    Token* octopus;
    Token* reptilian;
    Token* column[4];
    Token* A;
    Token* B;

    void InizializedToken();

public:
    //COSTRUTTORE
    TurnSystem();
    //DISTRUTTORE
    virtual ~TurnSystem();

    //Aggiorna clase
    void Update(sf::Vector2i& mousePos);

    //FASI
    void WhoMoves(sf::Vector2i &pos);
    void WhereItMove(sf::Vector2i &mousePos);
    void MoveAnimation();
    void WhoAttacks();
    void AttackAnimation();

    void MapMaker();

    //controllo del mouse
    sf::Vector2i MouseOnTheBoard(sf::Vector2i &mousePos);

    //Render pedine
    void Render(sf::RenderTarget& target);
};

#endif //MAIN_CPP_TURNSYSTEM_H
