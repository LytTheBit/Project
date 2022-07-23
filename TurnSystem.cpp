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
    image.loadFromFile("../Sprites/Soldier.png");
    token[0]= new Token("soldato",image,1,10,10,5,5,1,1,0);
    image.loadFromFile("../Sprites/Mage.png");
    token[1]= new Token("mago",image,1,8,15,0,4,2,0,1);
    image.loadFromFile("../Sprites/Demon.png");
    token[2]= new Token("demone",image,2,6,6,6,3,1,5,5);
    image.loadFromFile("../Sprites/Octopus.png");
    token[3]= new Token("polipo(?)",image,2,8,4,6,3,2,3,4);
    image.loadFromFile("../Sprites/Reptilian.png");
    token[4]= new Token("lucertoloide",image,2,5,8,5,3,1,4,3);

    //Colonne
    image.loadFromFile("../Sprites/Column.png");
    token[5] = new Token("colonna",image,0,20,0,0,0,0,1,1);
    token[6] = new Token("colonna",image,0,20,0,0,0,0,1,4);
    token[7] = new Token("colonna",image,0,20,0,0,0,0,5,1);
    token[8] = new Token("colonna",image,0,20,0,0,0,0,5,4);
}


void TurnSystem::Update(sf::Vector2i &mousePos) {

    switch (this->turnOf) {
        case TURN_OF::player:
            control=0;
            switch (this->phase) {
                case PHASE::pawnSelection:
                    WhoMoves(mousePos);
                    break;
                case PHASE::positionSelection:
                    WhereItMoves(mousePos);
                    break;

                case PHASE::motionAnimation:
                    MoveAnimation();
                    break;

                case PHASE::targetSelection:
                    WhoAttacks(mousePos);
                    break;

                case PHASE::attackAnimation:
                    AttackAnimation();
                    turnOf = TURN_OF::computer;
                    break;

            }
            // break of turnOf
            break;
        case TURN_OF::computer:
            switch (this->enemy) {
                case ENEMY::loading:
                    EnemyLoading();
                    break;
                case ENEMY::movement:
                    MoveAnimation();
                    break;
                case ENEMY::attack:
                    AttackAnimation();
                    turnOf = TURN_OF::player;
                    break;
            }
            // break of turnOf
            break;
    }
}


//Chi vuoi muovere?
void TurnSystem::WhoMoves(sf::Vector2i &pos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse
        if(mouseHeld==false){
            mouseHeld=true;
            for(int i=0;i<p;i++){
                if(token[i]->sprite.getGlobalBounds().contains(pos.x,pos.y) && token[i]->GetOwner()==1){
                    attacker = token[i];
                    std::cout << "Selezionato:" << attacker->GetName() << "\n";
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
void TurnSystem::WhereItMoves(sf::Vector2i &mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {//se clicco il mouse
        if(mouseHeld==false){
            mouseHeld=true;

            destination[0]=MouseOnTheBoard(mousePos);

            //Test di A*
            int grid[ROW][COL]
                    = { { 1, 1, 1, 1, 1, 1, 1},
                        { 1, 1, 1, 1, 1, 1, 1},
                        { 1, 1, 1, 1, 1, 1, 1},
                        { 1, 1, 1, 1, 1, 1, 1},
                        { 1, 1, 1, 1, 1, 1, 1},
                        { 1, 1, 1, 1, 1, 1, 1}};

            //aggiorna i pezzi sulla scacchiera
            for(int i=0;i<p;i++){//un token può passare dalla casella di un alleato
                if(token[i]->GetOwner()!=1)
                    grid[token[i]->GetPosX()][token[i]->GetPosY()]=0;
            }

            // partenza
            Pair src = make_pair(attacker->GetPosX(), attacker->GetPosY());
            // arrivo
            Pair dest = make_pair(destination[0].x, destination[0].y);

            aStarSearch(grid, src, dest);

            //calcolo distance percorsa
            distance=GetDistanza();

            if((PositionCheck()==true) && (distance <= attacker->GetSpeed()))
            {

                //elenco caselle percorse
                UpdatePath();

                phase=PHASE::motionAnimation;
                std::cout << '\n' << "perfetto \n";
            }
            else{
                std::cout << '\n' << "il personaggio non puo' muoversi li, cambia destination \n";
            }
        }
    }
    else
        mouseHeld=false;
}

//Si muove
void TurnSystem::MoveAnimation() {
    //elenco caselle percorse

    attacker->update(destination[j]);
    if(attacker->GetPosX() == destination[j].x && attacker->GetPosY() == destination[j].y)
        j++;
    if(attacker->GetPosX() == destination[distance].x && attacker->GetPosY() == destination[distance].y){
        j=0;
        if(turnOf==TURN_OF::player)
            phase = PHASE::targetSelection;
        else if(turnOf==TURN_OF::computer){
            if(control<=5)
                enemy = ENEMY::attack;
            else{
                enemy = ENEMY::loading;
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
                    attacked = token[i];
                    std::cout << "Vuoi attaccare:" << attacked->GetName() << "\n";
                    i = 9;
                    int ascisse = abs(attacked->GetPosX() - attacker->GetPosX());
                    int ordinate = abs(attacked->GetPosY() - attacker->GetPosY());
                    if ((ascisse + ordinate) <= attacker->GetRange())
                        phase = PHASE::attackAnimation;
                } else if (attacker->sprite.getGlobalBounds().contains(pos.x, pos.y)) {
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
    std::cout << "è stato attaccato: " << attacked->GetName() << " con " << attacker->GetName() << "\n";
    attacked->attached(attacker->GetAtk());
    enemy = ENEMY::loading;
    phase = PHASE::pawnSelection;
    DeathCheck();
}

void TurnSystem::EnemyLoading() {
    //crea la scacchiera
    //TODO creare una funzione per generare la mappa
    int grid[ROW][COL]
            = { { 1, 1, 1, 1, 1, 1, 1},
                { 1, 1, 1, 1, 1, 1, 1},
                { 1, 1, 1, 1, 1, 1, 1},
                { 1, 1, 1, 1, 1, 1, 1},
                { 1, 1, 1, 1, 1, 1, 1},
                { 1, 1, 1, 1, 1, 1, 1}};

    //aggiorna i pezzi sulla scacchiera
    for (int i = 0; i < p; i++) {//un token può passare dalla casella di un alleato
        if (token[i]->GetOwner() != 2)
            grid[token[i]->GetPosX()][token[i]->GetPosY()]=0;
    }
    std::cout << "\n";

    int min=100;
    //scelta: che pezzo attaccare
    if(control==0) { //la prima volta prendo il pezzo con meno vita
        for (int i = 0; i < p; i++) {
            if ((token[i]->GetHp() <= min) && (token[i]->GetOwner() == 1)){
                min = token[i]->GetHp();
                attacked = token[i];
            }
        }
        std::cout << "preso di mira il token più debole: " << attacked->GetName() << " \n";
    }
    else if(control<=5) { //per 5 volte cerco un pezzo casuale
        while (true) {
            int i = rand() % p;
            if (token[i]->GetOwner() == 1) {
                attacked = token[i];
                std::cout << "preso di mira: " << attacked->GetName() << " \n";
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
            attacker = token[l];
            std::cout << "\nPRESO IN CONSIDERAZIONE: " << attacker->GetName() << " \n";

            //scenta: dove muovere il token
            for (int t = 1; t <= attacker->GetRange(); t++) {
                int rx = -t;
                int ry = 0;
                std::cout << "il pezzo ha un raggio di: " <<t<< "\n";

                for (int f = 0; f <= t*4; f++) {
                    Pair src, dest;

                    if(control>5){ //nel caso non trovi nessuna pedina da attaccare il computer proverà a prendere il controllo di
                        destination[0].x = (rand() % 3) + 2 + rx; //una casella centrale. "Prendere" il centro è generalmente sempre
                        destination[0].y = (rand() % 2) + 2 + ry; //una buona mossa nei giochi di strategia come scacchi
                    }
                    else{
                        destination[0].x = attacked->GetPosX() + rx;
                        destination[0].y = attacked->GetPosY() + ry;
                    }

                    //std::cout << "prende in consideraztine (" <<rx<< " , " <<ry<< ") \n";
                    std::cout << "la destination sarebbe (" << destination[0].x << " - " << destination[0].y << ") \n";

                    if((destination[0].x > 6) || (destination[0].x < 0) || (destination[0].y > 5) || (destination[0].y < 0)){
                        std::cout << "ma uscirebbe dalla mappa \n";
                    }
                    else {
                        std::cout << "controllo fattibilita' del percorso \n";

                        aStarSearch(grid, src, dest);
                        UpdatePath();

                        if(/*path[0].x == -1 || path[0].y == -1*/false) { //TODO scrivere cosa succede se non trova il percorso
                            std::cout << "non è una via percorribile \n";
                        }
                        else{ //è stato trovato un percorso
                            distance=GetDistanza();
                            std::cout << "il pezzo si muove di' " << attacker->GetSpeed() << " e il percorso e' lungo:"
                                      << distance << "\n";

                            if (PositionCheck() && (distance <= attacker->GetSpeed())) {
                                std::cout << "il percorso va bene ed e': \n";

                                enemy = ENEMY::movement;

                                //esce dai vari loop
                                l = p;
                                t = attacker->GetRange() + 1;
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
        if((token[i]->GetPosX() != attacker->GetPosX()) || (token[i]->GetPosY() != attacker->GetPosY()))
            if(token[i]->GetPosX() == destination[0].x && token[i]->GetPosY() == destination[0].y)
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

void TurnSystem::UpdatePath(){
    //elenco caselle percorse
    for(int i=0; i <= distance; i++){
        std::cout<< "il percorso e' " << GetPercorso(i).x << " - "<< GetPercorso(i).y <<"\n";
        destination[i].x=GetPercorso(i).x;
        destination[i].y=GetPercorso(i).y;
    }
}