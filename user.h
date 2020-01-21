//
// Created by Student on 2020-01-12.
//

#ifndef JONCECHAIN_USER_H
#define JONCECHAIN_USER_H

#include "User.h"
#include "sha256.h"

#include <string>
#include <map>

class User {
private:
    std::string name;
    std::string publicKey;
    double jonceCoin;
public:
    User(std::string name, int balance) {
        User::name = name;
        User::jonceCoin = balance;
        User::publicKey = sha256(name + std::to_string(balance) + std::to_string(rand()));
    }


    const std::string &getName() const {
        return name;
    }

    void setName(const std::string name) {
        User::name = name;
    }

    const std::string getPublicKey() const {
        return publicKey;
    }

    std::string getPublicKeyID(std::map<User, std::string> users, size_t index){
        auto iter = users.begin();
        std::advance(iter, index);
        return iter->second;
    }

    double getBalance() const {
        return jonceCoin;
    }

    void setBalance(double balance) {
        jonceCoin = balance;
    }




};

#endif //JONCECHAIN_USER_H
