#include "gtest/gtest.h"

#include "../Token.h"



class TokenSuite : public ::testing::Test{
protected:
    virtual void SetUp() {
        Token c(10,10,10);
    }
    Token c;
};

TEST_F(TokenSuite, TestAattached) {
    c.attached(14); //l'attacco che riceverà il personaggio sarà 16

    ASSERT_EQ(6, c.GetHp())<< "test 1"; //con un attacco di 14 - una difesa da 10, il personaggio rimarra a 6 Hp
}
