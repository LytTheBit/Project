#include "gtest/gtest.h"

#include "../Token.h"

TEST(Token, DefaultConstructor) {
    Token c(10,10,10);
    ASSERT_EQ(10, c.GetHp());
    ASSERT_EQ(10, c.GetAtk());
    ASSERT_EQ(10, c.GetDef());
}


TEST(Token, TestPerVedereSeFunzionanoITest) {
    Token c(10,10,10);
    ASSERT_TRUE(c.GetHp());
}
