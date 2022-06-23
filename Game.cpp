//
// Created by franc on 06/05/2022.
//

#include "Game.h"

//--funzioni private--
void Game::inizializedToken() {
    this->prova= new Token();
}
void Game::inizializedWindow() {
    //crea la finestra
    this->window = new sf::RenderWindow(sf::VideoMode(864, 864), "SFML Application");
    //imposta il frame-rate massimo
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}
void Game::inizializedArena() {
    this->arena = new Arena();
}


//--costruttore e distruttore--
Game::Game() {
    this->inizializedToken();
    this->inizializedWindow();
    this->inizializedArena();
}
Game::~Game() {
    delete this->prova;
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
    while (this->window->pollEvent(event))//Chiude il gioco premendo sulla X
    {
        if (event.Event::type == sf::Event::Closed)
            this->window->close();
    }
    this->updateMouse();
    this->updateViola();
    this->updateToken();
}
void Game::updateToken() {
    //this->prova->updateMovement();
    this->prova->update(this->mousePos);
}
void Game::updateMouse() {//Aggiorno la variabile contenente la posizione del mause
    this->mousePos = sf::Mouse::getPosition(*this->window);
}
void Game::updateViola() {
    this->arena->update(this->mousePos);//passo la variabile contenente la posizione del mause al oggetto arena
}
void Game::renderToken() {
    this->prova->render(*this->window);
}
void Game::renderArena() {
    this->arena->render(*this->window);
}
void Game::render() {
    this->window->clear();
    this->update();

    //spazio per disegnare il gioco
    this->renderArena();
    this->renderToken();
    this->window->display();
}










