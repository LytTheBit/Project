//
// Created by franc on 30/07/2022.
//

#ifndef TURNSYSTEM_CPP_TEXT_H
#define TURNSYSTEM_CPP_TEXT_H

#include "Librerie.h"
#include "Token.h"


class Text {
private:
    sf::Texture bachecaTexture;
    sf::Sprite bachecaSprite;

    sf::Font font;
    sf::Text levelText;
    sf::Text unitNameText;
    sf::Text unitStatText;
    sf::Text actionText;
public:
    Text();
    ~Text();
    void SetLevel(int level);
    void SetUnitText(std::string name, int life, int attack, int defance, int speed, int range);
    void SetActionText(std::string testo);
    void GetText(sf::RenderTarget& target);
    void SetBacheca();
};


#endif //TURNSYSTEM_CPP_TEXT_H
