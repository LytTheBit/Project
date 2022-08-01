//
// Created by franc on 06/05/2022.
//

#include "Game.h"

//--funzioni private--
void Game::inizializedTurnSystem() {
    turnSystem = make_unique<TurnSystem>(Start());
}
void Game::inizializedWindow() {
    //crea la finestra
    window = make_unique<sf::RenderWindow>(sf::VideoMode(864, 864), "Reisende: protect the castle");
    //imposta il frame-rate massimo
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}
void Game::inizializedClass() {
    screen = make_unique<Screen>();
}


//--costruttore e distruttore--
Game::Game() {
    inizializedTurnSystem();
    inizializedWindow();
    inizializedClass();
}
Game::~Game() {
}


//--Accesso--
void Game::run() {
    while(this->window->isOpen()){
        update();
        render();
    }
}


//--funzioni pubbliche--
void Game::update() {
    sf::Event event;
    while (window->pollEvent(event))//Chiude il gioco premendo sulla X
    {
        if (event.Event::type == sf::Event::Closed)
            window->close();
    }
    updateMouse();

    switch (this->fase) {
        case FASE::menu:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                fase=FASE::game;
            break;
        case FASE::game:
            cout<<"\nE";
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                Save();
            cout<<"\nF";
            updatePointer();
            updateTurnSystem();
            cout<<"\nG";

            break;
        case FASE::win:
            ClearSave();

            break;
        case FASE::lose:
            ClearSave();
            break;
    }
}
void Game::updateTurnSystem() {
    turnSystem->Update(mousePos);
}
void Game::updateMouse() {//Aggiorno la variabile contenente la posizione del mause
    mousePos = sf::Mouse::getPosition(*window);
}
void Game::updatePointer() {
    screen->update(mousePos);//passo la variabile contenente la posizione del mause al oggetto screen
}
void Game::renderToken() {
    turnSystem->Render(*window);
}
void Game::renderArena(int scope) {
    screen->render(*window, scope);
}
void Game::render() {
    window->clear();
    update();

    //spazio per disegnare il gioco
    switch (fase) {
        case FASE::menu:
            renderArena(0);
            break;

        case FASE::game:
            renderArena(3);
            renderToken();

            if(turnSystem->Winner()==1)
                fase=FASE::win;
            else if(turnSystem->Winner()==2)
                fase=FASE::lose;
            break;

        case FASE::win:
            renderArena(1);
            break;

        case FASE::lose:
            renderArena(2);
            break;
    }
    window->display();
}

int Game::Start() {
    ifstream MyReadFile("../Save.txt");
    int livello;
    cout<<"A";
    if (MyReadFile.peek() == ifstream::traits_type::eof()){
        cout<<"B";
        livello=1;
    }
    else{
        cout<<"C";
        MyReadFile >> livello;
    }
    cout<<"D";
    return livello;
    //cout<<turnSystem->GetLevel();
    //MyReadFile.close();
}

void Game::Save() {
    ofstream MyFile("../Save.txt");
    MyFile << turnSystem->GetLevel();
    MyFile.close();
}

void Game::ClearSave() {
    int status = remove("../Save.txt");
    if(status==0)
        cout<<"\nFile Deleted Successfully!";
    else
        cout<<"\nError Occurred!";
    cout<<endl;
}