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
void Text::SetUnitName(std::string testo) {
    unitNameText.setFont(font);
    unitNameText.setString(testo);
    unitNameText.setFillColor(sf::Color::White);
    unitNameText.setCharacterSize(24);
    unitNameText.setStyle(sf::Text::Underlined);
    unitNameText.setPosition(0,0);
}

void Text::SetUnitStat(std::string testo) {

}

void Text::GetText(sf::RenderTarget& target){
    target.draw(levelText);
    target.draw(unitNameText);
    //target.draw(unitStatText);
}




