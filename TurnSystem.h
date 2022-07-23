//
// Created by franc on 29/06/2022.
//

#ifndef MAIN_CPP_TURNSYSTEM_H
#define MAIN_CPP_TURNSYSTEM_H

#include "Token.h"
#include "AStar.h"

enum TURN_OF {player=0, computer=1};
enum PHASE {pawnSelection=0, positionSelection=1, motionAnimation=2, targetSelection=3, attackAnimation=4};
enum ENEMY {loading=0, movement=1, attack=2};



class TurnSystem{
private:

    short turnOf = TURN_OF::player;
    short phase = PHASE::pawnSelection;
    short enemy = ENEMY::loading;
    sf::Vector2i destination[10]; //ipotizzo che nessuna pedina potrà mai muoversi cosi tanto
    int distance;
    int control=0; //controllo quante volte il nemico ha provato a cercare un bersaglio, se supera il 5, lo faccio semplicemente muovere
    int j=0;
    bool mouseHeld=false;
    int p=9; //quante pedine ho, può essere facilmenye modificato


    //TOKEN
    Token* token[9];
    Token* attacker;
    Token* attacked;

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
    void WhereItMoves(sf::Vector2i &mousePos);
    void MoveAnimation();
    void WhoAttacks(sf::Vector2i &pos);
    void AttackAnimation();

    void EnemyLoading();

    //controlli delle pedine
    bool PositionCheck();
    void DeathCheck();
    void Death(int i);

    //controllo del mouse
    sf::Vector2i MouseOnTheBoard(sf::Vector2i &mousePos);

    //Render pedine
    void Render(sf::RenderTarget& target);

    //Aggiorna il percorso delle pedine
    void UpdatePath();
};

#endif //MAIN_CPP_TURNSYSTEM_H
