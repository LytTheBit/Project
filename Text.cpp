//
// Created by franc on 30/07/2022.
//

#include "Text.h"

Text::Text(){
    if (!font.loadFromFile("../Font/Ancient.ttf"))
    {
        std::cout<<"error";
    }
}
Text::~Text() {

}
void Text::SetLevel(int level){
    levelText.setFont(font);
    std::string text="Livello: ";
    text += std::to_string(level);
    levelText.setString(text);
    levelText.setFillColor(sf::Color::White);
    levelText.setCharacterSize(48);
    //text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    levelText.setPosition(350,0);
}
void Text::SetUnitText(std::string name, int life, int attack, int defance, int speed, int range) {
    //stampa il nome del unità
    unitNameText.setFont(font);
    unitNameText.setString(name);
    unitNameText.setFillColor(sf::Color::White);
    unitNameText.setCharacterSize(24);
    unitNameText.setStyle(sf::Text::Underlined);
    unitNameText.setPosition(0,0);
    //stampa le statistiche del unità
    std::string text = "Hp: "+std::to_string(life)+" Atk: "+std::to_string(attack)+ " Def: "+std::to_string(defance)+"\nSpeed: "+std::to_string(speed)+" Ragne: "+std::to_string(range);
    unitStatText.setFont(font);
    unitStatText.setString(text);
    unitStatText.setFillColor(sf::Color::White);
    unitStatText.setCharacterSize(18);
    unitStatText.setPosition(0,24);

}

void Text::SetActionText(std::string testo) {
    actionText.setFont(font);
    actionText.setString(testo);
    actionText.setFillColor(sf::Color::White);
    actionText.setCharacterSize(24);
    actionText.setPosition(300,825);
}

void Text::GetText(sf::RenderTarget& target){
    target.draw(levelText);
    target.draw(unitNameText);
    target.draw(unitStatText);
    target.draw(actionText);
    //target.draw(unitStatText);
}




