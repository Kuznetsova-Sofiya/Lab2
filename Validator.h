#ifndef VALIDATOR_H
#define VALIDATOR_H
#include <iostream>
#include <QRegularExpression>

using namespace std;

class validator {
public:
    validator(){};
    ~validator(){};

    bool validpassword(const QString password);
    bool validlogin(const QString login);
};

bool validator::validpassword(const QString password){
    QRegularExpression passwordregex ("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8}$$");
    QRegularExpressionMatch match = passwordregex.match(password);
    return match.hasMatch();
}

bool validator::validlogin(const QString login){
    QRegularExpression loginregex ("^[a-zA-Z0-9_]{5,15}$");
    QRegularExpressionMatch match = loginregex.match(login);
    return match.hasMatch();
}

#endif // VALIDATOR_H
