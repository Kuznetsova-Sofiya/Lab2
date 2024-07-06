#include "pch.h"
#include "Header.h"

TEST(Validator, validate_login) {
	Validator v;
	EXPECT_TRUE(v.validLogin(std::string("privet1234")));
	EXPECT_FALSE(v.validLogin(std::string("!Poka1234")));
}
TEST(Validator, validate_pass) {
	Validator vo;
	EXPECT_TRUE(vo.validPassword(std::string("Vk123456")));
	EXPECT_FALSE(vo.validPassword(std::string("1234")));
}