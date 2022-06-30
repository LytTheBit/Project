//
// Created by franc on 10/05/2022.
//

#include "Token.h"
void Token::inizializedSprite(const sf::Image& image) {
    //A seconda della variabile "aspetto" del token, li carico una texture diversa
    this->textureSheet.loadFromImage(image);

    this->sprite.setTexture(this->textureSheet);

    this->sprite.setTextureRect(sf::IntRect(0,0,32,64));
    this->sprite.setScale(3.f,3.f);
    this->sprite.setPosition(startingPointX+PosX*96, (startingPointY-96)+PosY*96);
}

//Costruttore
Token::Token(const sf::Image& image, int InputHp, int InputAtk, int InputDef, int X, int Y) {
    Hp=InputHp; //punti vita inseriti alla creazione della pedina
    Atk=InputAtk; //attacco ...
    Def=InputDef; //difesa ...
    PosX=X; //posizione sulle X ...
    PosY=Y; //posizione sulle Y ...

    this->inizializedSprite(image);
}
//Distruttore
Token::~Token() {

}

//Combattimento
void Token::attached(int AttaccoSubito) {
    if(AttaccoSubito>=Def)
        Hp=Hp-(AttaccoSubito-Def);
}//funzione di prova di un possibile attacco subito

//Getter delle statistiche
int Token::GetHp() {
    return Hp;
}
int Token::GetAtk() {
    return Atk;
}
int Token::GetDef() {
    return Def;
}
int Token::GetPosX() {
    return PosX;
}
int Token::GetPosY() {
    return PosY;
}



//FUNZIONI
void Token::update(sf::Vector2i& mousePos){//aggiorna il token
    sf::Vector2i Pos=mousePos;
    this->updateMovement(Pos);
}
void Token::updateMovement(sf::Vector2i& mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        for(int i=0; i<=6; i++){
            for(int j=0; j<=5; j++) {
                if (mousePos.x > (startingPointX+(i * 32 * 3.f)) && mousePos.y > (startingPointY+(j * 32 * 3)) &&
                    mousePos.x < (startingPointX+((i + 1) * 32 * 3)) && mousePos.y < (startingPointY+((j + 1) * 32 * 3))) {
                    if((startingPointX+(i * 32 * 3.f))>this->sprite.getPosition().x){
                        this->sprite.move(1.f,0.f);
                    }
                    else if((startingPointX+(i * 32 * 3.f))<this->sprite.getPosition().x){
                        this->sprite.move(-1.f,0.f);
                    }

                    if((startingPointY+(j * 32 * 3))-96>this->sprite.getPosition().y){
                        this->sprite.move(0.f,1.f);
                    }
                    else if((startingPointY+(j * 32 * 3))-96<this->sprite.getPosition().y){
                        this->sprite.move(0.f,-1.f);
                    }
                }
            }
        }
    }//insegue la freccia
}
void Token::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}









