//
// Created by franc on 29/06/2022.
//

#include "TurnSystem.h"
#include "AStar.cpp"


TurnSystem::TurnSystem() {
    this->InizializedToken();
}

TurnSystem::~TurnSystem() {

}


void TurnSystem::InizializedToken() {
    sf::Image image;
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Soldier.png");
    this->soldier= new Token(image,1,10,10,5,5, 0,0);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Demon.png");
    this->demon= new Token(image,2,6,6,6,3,5,5);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Octopus.png");
    this->octopus= new Token(image,2,8,4,6,3,3,4);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Reptilian.png");
    this->reptilian= new Token(image,2,5,8,5,3,4,3);

    //Colonne
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Column.png");
    this->column[0] = new Token(image,0,20,0,0,0,1,1);
    this->column[1] = new Token(image,0,20,0,0,0,1,4);
    this->column[2] = new Token(image,0,20,0,0,0,5,1);
    this->column[3] = new Token(image,0,20,0,0,0,5,4);
}


void TurnSystem::Update(sf::Vector2i &mousePos) {
    //fase di selezione del pedone
    if (this->phase == PHASE::pawnSelection){

        WhoMoves(mousePos);

    }
    else if (this->phase == PHASE::positionSelection){

        WhereItMove(mousePos);

    }
    else if(this->phase == PHASE::motionAnimation){

        MoveAnimation();

    }/*
    else if (this->phase == PHASE::targetSelection){
        //code
    }
    else if(this->phase == PHASE::attackAnimation){
        //code
    }
     */
}


//Chi vuoi muovere?
void TurnSystem::WhoMoves(sf::Vector2i &pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse
        if(soldier->sprite.getGlobalBounds().contains(pos.x,pos.y)){
            A = soldier;
            std::cout << "Selezionato: soldato \n";
            phase=PHASE::positionSelection;
        }
        else if (demon->sprite.getGlobalBounds().contains(pos.x,pos.y)){
            std::cout << "La pedina e' nemica, selezionane un altra \n";
        }
    }
}

//Dove lo vuoi muovere?
void TurnSystem::WhereItMove(sf::Vector2i &mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {//se clicco il mouse
        destinazione=MouseOnTheBoard(mousePos);
        std::cout << "mouse in posizione: \n"<<destinazione.x<<" e "<<destinazione.y << "\n";

        //Test di A*

        SquareGrid grid = MakeDiagram();

        //pezzi neutri
        for(int i=0;i<4;i++){
            B=this->column[i];
            add_rect(grid, B->GetPosX(), B->GetPosY(),B->GetPosX()+1, B->GetPosY()+1);
        }

        //pezzi nemici
        if(A->GetOwner()==1){
            add_rect(grid, demon->GetPosX(), demon->GetPosY(),demon->GetPosX()+1, demon->GetPosY()+1);
            add_rect(grid, octopus->GetPosX(), octopus->GetPosY(),octopus->GetPosX()+1, octopus->GetPosY()+1);
            add_rect(grid, reptilian->GetPosX(), reptilian->GetPosY(),reptilian->GetPosX()+1, reptilian->GetPosY()+1);
        }

        //pezzi alleati
        if(A->GetOwner()==2){
            add_rect(grid, soldier->GetPosX(), soldier->GetPosY(),soldier->GetPosX()+1, soldier->GetPosY()+1);
        }

        GridLocation start{A->GetPosX(), A->GetPosY()}, goal{destinazione.x, destinazione.y};

        std::unordered_map<GridLocation, GridLocation> came_from;
        std::unordered_map<GridLocation, double> cost_so_far;
        a_star_search(grid, start, goal, came_from, cost_so_far);
        std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);

        int distanza=DistanceCalculation(grid, &path, &start, &goal);

        if(distanza <= A->GetSpeed()){
            phase=PHASE::motionAnimation;
            std::cout << '\n' << "perfetto";
        }
        else{
            std::cout << '\n' << "il personaggio non puo' muoversi per cosi tanto: " << distanza << " , \n cambia destinazione";
        }
    }
}

//Si muove
void TurnSystem::MoveAnimation() {
    A->update(destinazione);
    if(A->GetPosX()==destinazione.x && A->GetPosY()==destinazione.y)
        phase = PHASE::pawnSelection;
}

//TODO Chi vuoi attaccare?
void TurnSystem::WhoAttacks() {

}

//TODO Animazione attacco
void TurnSystem::AttackAnimation() {

}



//controllo del mouse
sf::Vector2i TurnSystem::MouseOnTheBoard(sf::Vector2i &mousePos) {
    sf::Vector2i result=mousePos;
    result.x=mousePos.x-startingPointX;
    result.y=mousePos.y-startingPointY;

    for(int i=0; i<=6; i++){
        for(int j=0; j<=5; j++) {
            if (result.x > (i * 32 * 3.) && result.y > (j * 32 * 3) &&
            result.x < ((i + 1) * 32 * 3) && result.y < ((j + 1) * 32 * 3)) {
                result.x=i;
                result.y=j;
            }
        }
    }
    return result;
}

//render pedine
void TurnSystem::Render(sf::RenderTarget& target) {
    this->soldier->render(target);
    this->demon->render(target);
    this->octopus->render(target);
    this->reptilian->render(target);
    for(int i=0;i<4;i++)
        this->column[i]->render(target);
}