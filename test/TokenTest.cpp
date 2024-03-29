#include "gtest/gtest.h"

#include "../Token.h"

TEST(Token, DefaultConstructor) {
    sf::Image image;
    image.loadFromFile("Sprites/null.png");
    Token c("Test-Man",image,1,5,5,5,5, 5,5,5);
    ASSERT_EQ(1, c.GetOwner());
    ASSERT_EQ(5, c.GetHp());
    ASSERT_EQ(5, c.GetAtk());
    ASSERT_EQ(5, c.GetDef());
    ASSERT_EQ(5, c.GetSpeed());
    ASSERT_EQ(5, c.GetRange());
    ASSERT_EQ(5, c.GetPosX());
    ASSERT_EQ(5, c.GetPosY());
}
