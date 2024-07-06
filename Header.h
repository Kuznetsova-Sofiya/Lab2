#pragma once
#include <iostream>
#include <string>
#include <regex>

class Validator {
public:
    Validator() {};
    ~Validator() {};

    bool validPassword(const std::string& password);
    bool validLogin(const std::string& login);
};

bool Validator::validPassword(const std::string& password) {
    std::regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    return std::regex_match(password, passwordRegex);
}

bool Validator::validLogin(const std::string& login) {
    std::regex loginRegex("^[a-zA-Z0-9_]{5,15}$");
    return std::regex_match(login, loginRegex);
}
