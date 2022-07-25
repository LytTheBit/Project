//
// Created by franc on 06/05/2022.
//

#include "Game.h"

//--funzioni private--
void Game::inizializedTurnSystem() {
    this->turnSystem= new TurnSystem();
}
void Game::inizializedWindow() {
    //crea la finestra
    this->window = new sf::RenderWindow(sf::VideoMode(864, 864), "SFML Application");
    //imposta il frame-rate massimo
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}
void Game::inizializedMusic() {
    //music.openFromFile("../Theme/Greenpath.ogg")
    //music.getLoopPoints();
}
void Game::inizializedClass() {
    menu=new Menu();
    arena=new Arena();
}


//--costruttore e distruttore--
Game::Game() {
    this->inizializedTurnSystem();
    this->inizializedWindow();
    //inizializedMusic();
    this->inizializedClass();
}
Game::~Game() {
    delete this->turnSystem;
    delete this->window;
    delete this->arena;
}


//--Accesso--
void Game::run() {
    while(this->window->isOpen()){
        this->update();
        this->render();
    }
}


//--funzioni pubbliche--
void Game::update() {
    sf::Event event;
    //music.play();
    while (this->window->pollEvent(event))//Chiude il gioco premendo sulla X
    {
        if (event.Event::type == sf::Event::Closed)
            this->window->close();
    }
    this->updateMouse();

    switch (this->fase) {
        case FASE::menu:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                fase=FASE::game;
            break;
        case FASE::game:
            this->updatePointer();
            this->updateTurnSystem();
            break;
        case FASE::win:

            break;
        case FASE::lose:

            break;
    }
}
void Game::updateTurnSystem() {
    this->turnSystem->Update(this->mousePos);
}
void Game::updateMouse() {//Aggiorno la variabile contenente la posizione del mause
    this->mousePos = sf::Mouse::getPosition(*this->window);
}
void Game::updatePointer() {
    this->arena->update(this->mousePos);//passo la variabile contenente la posizione del mause al oggetto arena
}

void Game::renderMenu(int scope) {
    this->menu->render(*this->window, scope);
}
void Game::renderToken() {
    this->turnSystem->Render(*this->window);
}
void Game::renderArena() {
    this->arena->render(*this->window);
}
void Game::render() {
    this->window->clear();
    this->update();

    //spazio per disegnare il gioco
    switch (this->fase) {
        case FASE::menu:
            renderMenu(0);
            break;

        case FASE::game:
            this->renderArena();
            this->renderToken();

            if(turnSystem->Winner()==1)
                fase=FASE::win;
            else if(turnSystem->Winner()==2)
                fase=FASE::lose;
            break;

        case FASE::win:
            renderMenu(1);
            break;

        case FASE::lose:
            renderMenu(2);
            break;
    }
    this->window->display();
}












