//
// Created by franc on 30/07/2022.
//

#ifndef TURNSYSTEM_CPP_TEXT_H
#define TURNSYSTEM_CPP_TEXT_H

#include "Librerie.h"

class Text {
private:
    sf::Font font;
    sf::Text levelText;
    sf::Text unitNameText;
    sf::Text unitStatText;
public:
    Text();
    ~Text();
    void SetLevel(int level);
    void SetUnitName(std::string testo);
    void SetUnitStat(std::string testo);
    void GetText(sf::RenderTarget& target);
};


#endif //TURNSYSTEM_CPP_TEXT_H
