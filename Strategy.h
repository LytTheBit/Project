//
// Created by franc on 02/08/2022.
//

#ifndef MAIN_CPP_STRATEGY_H
#define MAIN_CPP_STRATEGY_H

#include "Librerie.h"
#include "Token.h"

//TreadMill Class (Base class of different strategy)
class EnemyStrategy{
protected:
    std::unique_ptr<Token> token[9];
public:
    virtual int Start() = 0;
};

class FirstAttack : public EnemyStrategy{
public:
    int pawns;
    FirstAttack(std::unique_ptr<Token> pieces[9], int p){
        for(int i=0; i<p; i++){
            token[i] = std::move(pieces[i]);
            std::cout<<token[i]->GetName()<<"\n";
        }
        pawns=p;
    }
    ~FirstAttack(){}
    int Start() override{
        std::cout<<"1";
        int min=100;
        int attacked;
        for (int i = 0; i < pawns; i++) {
            if ((token[i]->GetHp() <= min) && (token[i]->GetOwner() == 1)){
                min = token[i]->GetHp();
                attacked = i;
            }
        }
        std::cout<<"2";
        return attacked;
    }
};

//Adult TreadMill Mode
class WarStrategy: public EnemyStrategy{
public:
    int pawns;
    WarStrategy(std::unique_ptr<Token> pieces[9], int p){
        for(int i=0; i<p; i++)
            token[i] = std::move(pieces[i]);
        pawns=p;
    }
    ~WarStrategy(){}

    int Start() override {
        int attacked;
        while (true) {
            int i = rand() % pawns;
            if (token[i]->GetOwner() == 1) {
                attacked = i;
                std::cout << "preso di mira: " << token[attacked]->GetName() << " \n";
                break;
            }
        }
        return attacked;
    }
};

//Controller
class Controller{
    EnemyStrategy* strategy;
public:
    Controller(EnemyStrategy* tm): strategy(tm){

    }
    ~Controller(){

    }
    int WhoToAttack(){
        return strategy->Start();
    }
};
#endif //MAIN_CPP_STRATEGY_H
