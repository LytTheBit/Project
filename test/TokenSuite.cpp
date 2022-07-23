#include "gtest/gtest.h"

#include "../Token.h"
#include "../Librerie.h"


class TokenSuite : public ::testing::Test{
public:
    TokenSuite() {
        sf::Image image;
        image.loadFromFile("../Sprites/Null.png");
        Token t("null",image,1,10,10,5,5, 0,0);
    }
};

TEST_F(TokenSuite, TestAattached) {
    sf::Image image;
    image.loadFromFile("../Sprites/Null.png");
    Token t("null",image,1,10,10,6,5, 0,0);

    t.attached(16); //l'attacco che riceverà il personaggio sarà 16

    ASSERT_EQ(0, t.GetHp())<< "test 1"; //con un attacco di 16 - una difesa da 10, il personaggio rimarra a 6 Hp
}
