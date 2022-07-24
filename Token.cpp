//
// Created by franc on 10/05/2022.
//

#include "Token.h"

void Token::inizializedSprite(const sf::Image& image) {
    //A seconda della variabile "aspetto" del token, li carico una textureMenu diversa
    this->textureSheet.loadFromImage(image);

    this->sprite.setTexture(this->textureSheet);

    this->sprite.setTextureRect(sf::IntRect(0,0,32,32));
    this->sprite.setScale(3.f,3.f);
    this->sprite.setPosition(startingPointX+PosX*96, (startingPointY)+PosY*96);
}

//Costruttore
Token::Token(std::string inputName, const sf::Image& image, int owner, int InputHp, int InputAtk, int InputDef, int ImputSpeed, int InputRange, int X, int Y) {
    name=inputName; //nome della pedina
    Hp=InputHp; //punti vita inseriti alla creazione della pedina
    Atk=InputAtk; //attacco ...
    Def=InputDef; //difesa ...
    Speed=ImputSpeed; //Quadretti percorribili ...
    range=InputRange; //raggio d'attacco
    PosX=X; //posizione sulle X ...
    PosY=Y; //posizione sulle Y ...
    Owner=owner; //è un nemico o un amico

    this->inizializedSprite(image);
}
//Distruttore
Token::~Token() {

}

//Combattimento
void Token::attached(int AttaccoSubito) {
    if(AttaccoSubito>=Def)
        Hp=Hp-(AttaccoSubito-Def);
}//funzione di turnSystem di un possibile attacco subito

//Getter delle pedine
std::string Token::GetName() {
    return name;
}
int Token::GetHp() {
    return Hp;
}
int Token::GetAtk() {
    return Atk;
}
int Token::GetDef() {
    return Def;
}
int Token::GetSpeed() {
    return Speed;
}
int Token::GetRange() {
    return range;
}
int Token::GetPosX() {
    return PosX;
}
int Token::GetPosY() {
    return PosY;
}
int Token::GetOwner() {
    return Owner;
}




//FUNZIONI
void Token::update(sf::Vector2i& mousePos){//aggiorna il token
    sf::Vector2i Pos=mousePos;
    this->updateMovement(Pos);
}


void Token::updateMovement(sf::Vector2i& mousePos) {
    //sposto il Token vero il "bersaglio"
    if((startingPointX+(mousePos.x * 32 * 3))>this->sprite.getPosition().x){
        this->sprite.move(1.f,0.f);
    }
    else if((startingPointX+(mousePos.x * 32 * 3.f))<this->sprite.getPosition().x){
        this->sprite.move(-1.f,0.f);
    }
    if((startingPointY+(mousePos.y * 32 * 3))>this->sprite.getPosition().y){
        this->sprite.move(0.f,1.f);
    }
    else if((startingPointY+(mousePos.y * 32 * 3))<this->sprite.getPosition().y){
        this->sprite.move(0.f,-1.f);
    }

    //il Token è arrivato a destination
    if((startingPointX+(mousePos.x * 32 * 3))==this->sprite.getPosition().x)
        PosX=mousePos.x;
    if((startingPointY+(mousePos.y * 32 * 3))==this->sprite.getPosition().y)
        PosY=mousePos.y;
}

void Token::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}















