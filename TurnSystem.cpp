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
    //pedine giocanti
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Soldier.png");
    this->token[0]= new Token("soldato",image,1,10,10,5,5,1,1,0);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Mage.png");
    this->token[1]= new Token("mago",image,1,8,15,0,4,2,0,1);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Demon.png");
    this->token[2]= new Token("demone",image,2,6,6,6,3,1,5,5);
    image.loadFromFile("C:/Users/franc/Desktop/Reisende/Sprites/Octopus.png");
    this->token[3]= new Token("polipo(?)",image,2,8,4,6,3,2,3,4);
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
    if(this->turnOf == TURN_OF::player){
        control=0;
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
            turnOf = TURN_OF::computer;
        }
    }
    else if(this->turnOf == TURN_OF::computer){
        if(this->enemy==ENEMY::calculing) {
            EnemyCalculation();
        }
        else if(this->enemy==ENEMY::movment){
            MoveAnimation();
        }
        else if(enemy==ENEMY::attack){
            AttackAnimation();
            turnOf = TURN_OF::player;
        }
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
                if(token[i]->GetOwner()!=1)
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
        if(turnOf==TURN_OF::player)
            phase = PHASE::targetSelection;
        else if(turnOf==TURN_OF::computer){
            if(control<=5)
                enemy = ENEMY::attack;
            else{
                enemy = ENEMY::calculing;
                turnOf = TURN_OF::player;
            }
        }
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
                    turnOf = TURN_OF::computer; //quindi tocca al computer
                    phase = PHASE::pawnSelection; //dopo si rincomincerà da capo
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
    std::cout << "è stato attaccato: "<< B->GetName() <<" con "<< A->GetName()<<"\n";
    B->attached(A->GetAtk());
    enemy = ENEMY::calculing;
    phase = PHASE::pawnSelection;
    DeathCheck();
}

void TurnSystem::EnemyCalculation() {
    //crea la scacchiera
    SquareGrid grid = MakeDiagram();

    //aggiorna i pezzi sulla scacchiera
    for (int i = 0; i < p; i++) {//un token può passare dalla casella di un alleato
        if (token[i]->GetOwner() != 2)
            add_rect(grid, token[i]->GetPosX(), token[i]->GetPosY(), token[i]->GetPosX() + 1, token[i]->GetPosY() + 1);
    }
    std::cout << "\n";

    int min=100;
    //scelta: che pezzo attaccare
    if(control==0) { //la prima volta prendo il pezzo con meno vita
        for (int i = 0; i < p; i++) {
            if ((token[i]->GetHp() <= min) && (token[i]->GetOwner() == 1)){
                min = token[i]->GetHp();
                B = token[i];
            }
        }
        std::cout << "preso di mira il token più debole: " <<B->GetName()<< " \n";
    }
    else if(control<=5) { //per 5 volte cerco un pezzo casuale
        while (true) {
            int i = rand() % p;
            if (token[i]->GetOwner() == 1) {
                B = token[i];
                std::cout << "preso di mira: " <<B->GetName()<< " \n";
                break;
            }
        }
    }
    else{ //alla fine rinuncio ad attaccare, e semplicemente lo sposto
        std::cout << "non attacca nessuno, ma si sposta e basta \n";
    }
    control++;//ad ogni giro control sale di uno

    //scelta: token da muovere
    for (int l = 0; l < p; l++) {
        if (token[l]->GetOwner() == 2) {
            A = token[l];
            std::cout << "\nPRESO IN CONSIDERAZIONE: " <<A->GetName()<< " \n";

            //scenta: dove muovere il token
            for (int t = 1; t <= A->GetRange(); t++) {
                int rx = -t;
                int ry = 0;
                std::cout << "il pezzo ha un raggio di: " <<t<< "\n";

                for (int f = 0; f <= t*4; f++) {
                    GridLocation start, goal;

                    if(control>5){ //nel caso non trovi nessuna pedina da attaccare il computer proverà a prendere il controllo di
                        destinazione[0].x = (rand() % 3)+2 + rx; //una casella centrale. "Prendere" il centro è generalmente sempre
                        destinazione[0].y = (rand() % 2)+2 + ry; //una buona mossa nei giochi di strategia come scacchi
                    }
                    else{
                        destinazione[0].x = B->GetPosX() + rx;
                        destinazione[0].y = B->GetPosY() + ry;
                    }

                    //std::cout << "prende in consideraztine (" <<rx<< " , " <<ry<< ") \n";
                    std::cout << "la destinazione sarebbe (" << destinazione[0].x <<" - "<<destinazione[0].y<<") \n";

                    if((destinazione[0].x > 6) || (destinazione[0].x < 0) || (destinazione[0].y > 5) || (destinazione[0].y < 0)){
                        std::cout << "ma uscirebbe dalla mappa \n";
                    }
                    else {
                        std::cout << "controllo fattibilita' del percorso \n";

                        start = {A->GetPosX(), A->GetPosY()};
                        goal = {destinazione[0].x, destinazione[0].y};
                        std::unordered_map<GridLocation, GridLocation> came_from;
                        std::unordered_map<GridLocation, double> cost_so_far;
                        a_star_search(grid, start, goal, came_from, cost_so_far);
                        std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);

                        if(path[0].x == -1 || path[0].y == -1) { //non è stato trovato un percorso in meno di 10 mosse
                            std::cout << "non è una via percorribile \n";
                        }
                        else{ //è stato trovato un percorso
                            distanza = DistanceCalculation(grid, &path, &start, &goal);
                            std::cout << "il pezzo si muove di' " << A->GetSpeed() << " e il percorso e' lungo:"
                                      << distanza << "\n";

                            if (PositionCheck() && (distanza <= A->GetSpeed())) {
                                std::cout << "il percorso va bene ed e': \n";
                                for (int i = 0; i <= distanza; i++) {
                                    std::cout << path[i] << "\n";
                                    destinazione[i].x = path[i].x;
                                    destinazione[i].y = path[i].y;
                                }
                                enemy = ENEMY::movment;

                                //esce dai vari loop
                                l = p;
                                t = A->GetRange() + 1;
                                f = (t * 4) + 1;
                            } else
                                std::cout << "non si puo' muovere li \n";
                        }
                    }
                    /*ESEMPIO LOGICA USATA:
                in questo caso si ha raggio 2, quando t=1 si analizano i ▢, e quando t=2 i ■
                si analizzano in senso orario, partendo da sinistra
                          ■
                       ■  ▢  ■
                    ■  ▢  a  ▢ ■
                       ■  ▢  ■
                          ■
                    */

                    if(rx<0 && ry<=0){
                        rx++;
                        ry--;
                    }
                    else if(rx>=0 && ry<0){
                        rx++;
                        ry++;
                    }
                    else if(rx>0 && ry>=0){
                        rx--;
                        ry++;
                    }
                    else if(rx<=0 && ry>0){
                        rx--;
                        ry--;
                    }
                }
            }
        }
    }
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
    p--;
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