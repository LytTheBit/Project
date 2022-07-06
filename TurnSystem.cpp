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
    //pedine giocanti
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Soldier.png");
    this->token[0]= new Token("soldato",image,1,10,10,5,5,1,1,0);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Mage.png");
    this->token[1]= new Token("mago",image,1,10,15,0,4,2,0,1);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Demon.png");
    this->token[2]= new Token("demone",image,2,6,6,6,3,1,5,5);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Octopus.png");
    this->token[3]= new Token("polipo(?)",image,2,8,4,6,3,1,3,4);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Reptilian.png");
    this->token[4]= new Token("lucertoloide",image,2,5,8,5,3,1,4,3);

    //Colonne
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Column.png");
    this->token[5] = new Token("colonna",image,0,20,0,0,0,0,1,1);
    this->token[6] = new Token("colonna",image,0,20,0,0,0,0,1,4);
    this->token[7] = new Token("colonna",image,0,20,0,0,0,0,5,1);
    this->token[8] = new Token("colonna",image,0,20,0,0,0,0,5,4);
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

    }
    else if (this->phase == PHASE::targetSelection){

        WhoAttacks(mousePos);

    }
    else if(this->phase == PHASE::attackAnimation){

        AttackAnimation();

    }
}


//Chi vuoi muovere?
void TurnSystem::WhoMoves(sf::Vector2i &pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse
        if(mouseHeld==false){
            mouseHeld=true;
            for(int i=0;i<p;i++){
                if(token[i]->sprite.getGlobalBounds().contains(pos.x,pos.y) && token[i]->GetOwner()==1){
                    A = token[i];
                    std::cout << "Selezionato:" << A->GetName() <<"\n";
                    i=9;
                    phase=PHASE::positionSelection;
                }
                else if (token[i]->sprite.getGlobalBounds().contains(pos.x,pos.y) && token[i]->GetOwner()!=1){
                    std::cout << "non e' una tua pedina, selezionane un altra \n";
                }
            }
        }
    }
    else
        mouseHeld=false;
}

//Dove lo vuoi muovere?
void TurnSystem::WhereItMove(sf::Vector2i &mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse
        if(mouseHeld==false){
            mouseHeld=true;

            destinazione[0]=MouseOnTheBoard(mousePos);

            //Test di A*
            SquareGrid grid = MakeDiagram();

            //aggiorna i pezzi sulla scacchiera
            for(int i=0;i<p;i++){//un token può passare dalla casella di un alleato
                if(token[i]->GetOwner()!=1) //TODO l'1 può essere cambiato in una variabile per rendere i personaggi della giocatore ostacoli per la CPU
                    add_rect(grid, token[i]->GetPosX(), token[i]->GetPosY(),token[i]->GetPosX()+1, token[i]->GetPosY()+1);
            }

            GridLocation start{A->GetPosX(), A->GetPosY()}, goal{destinazione[0].x, destinazione[0].y};

            std::unordered_map<GridLocation, GridLocation> came_from;
            std::unordered_map<GridLocation, double> cost_so_far;
            a_star_search(grid, start, goal, came_from, cost_so_far);
            std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);

            /*
            //Grafici (da eliminare)
            draw_grid(grid, nullptr, &came_from, nullptr, &start, &goal);
            std::cout << '\n';
            draw_grid(grid, nullptr, nullptr, &path, &start, &goal);
            std::cout << '\n';
            draw_grid(grid, &cost_so_far, nullptr, nullptr, &start, &goal);
            */

            //calcolo distanza percorsa
            distanza=DistanceCalculation(grid, &path, &start, &goal);

            if((PositionCheck()==true) && (distanza <= A->GetSpeed()))
            {

                //elenco caselle percorse
                for(int i=0;i<=distanza;i++){
                    std::cout<< "il percorso e' " << path[i] <<"\n";
                    destinazione[i].x=path[i].x;
                    destinazione[i].y=path[i].y;
                }

                phase=PHASE::motionAnimation;
                std::cout << '\n' << "perfetto \n";
            }
            else{
                std::cout << '\n' << "il personaggio non puo' muoversi li, cambia destinazione \n";
            }
        }
    }
    else
        mouseHeld=false;
}

//Si muove
void TurnSystem::MoveAnimation() {
    //elenco caselle percorse

    A->update(destinazione[j]);
    if(A->GetPosX()==destinazione[j].x && A->GetPosY()==destinazione[j].y)
        j++;
    if(A->GetPosX()==destinazione[distanza].x && A->GetPosY()==destinazione[distanza].y){
        j=0;
        phase = PHASE::targetSelection;
    }
}

//sceglie chi attacare
void TurnSystem::WhoAttacks(sf::Vector2i &pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse
        if(mouseHeld==false) {
            mouseHeld = true;
            for (int i = 0; i < p; i++) {
                if (token[i]->sprite.getGlobalBounds().contains(pos.x, pos.y) && token[i]->GetOwner() != 1) {
                    B = token[i];
                    std::cout << "Vuoi attaccare:" << B->GetName() << "\n";
                    i = 9;
                    int ascisse = abs(B->GetPosX() - A->GetPosX());
                    int ordinate = abs(B->GetPosY() - A->GetPosY());
                    if ((ascisse + ordinate) <= A->GetRange())
                        phase = PHASE::attackAnimation;
                } else if (A->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
                    std::cout << "non vuoi attaccare. \n";
                    phase = PHASE::pawnSelection;
                    i = 9;
                } else if (token[i]->sprite.getGlobalBounds().contains(pos.x, pos.y) && token[i]->GetOwner() == 1) {
                    std::cout << "non puoi attaccare una tua pedina \n";
                }
            }
        }
    }
    else
        mouseHeld=false;
}

//attacca
void TurnSystem::AttackAnimation() {
    std::cout << "hai attaccato: "<< B->GetName() <<" con "<< A->GetName()<<"\n";
    B->attached(A->GetAtk());
    phase = PHASE::pawnSelection;
    DeathCheck();
}


bool TurnSystem::PositionCheck() {
    for(int i=0;i<p;i++){
        if( (token[i]->GetPosX()!=A->GetPosX()) || (token[i]->GetPosY()!=A->GetPosY()))
            if(token[i]->GetPosX()==destinazione[0].x && token[i]->GetPosY()==destinazione[0].y)
                return false;
    }
    return true;
}
void TurnSystem::DeathCheck() {
    for(int i=0;i<p;i++){
        if(token[i]->GetHp()<=0)
            Death(i);
    }
}
void TurnSystem::Death(int i) {
    delete token[i];
    for(i;i<p-1;i++)
        token[i]=token[i+1];
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
    for(int i=0;i<p;i++)
        this->token[i]->render(target);
}


