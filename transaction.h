//
// Created by Student on 2020-01-11.
//

#ifndef JONCECHAIN_TRANSACTION_H
#define JONCECHAIN_TRANSACTION_H

#include <string>
#include <sstream>
#include <vector>
#include "sha256.h"
#include "user.h"

class Transaction {
    std::string t_hash;
    double amount;
    std::string senderKey;
    std::string receiverKey;
    time_t timestamp;

public:

    Transaction(double amt, time_t time, std::string sender, std::string receiver) {
        amount = amt;
        timestamp = time;
        senderKey = sender;
        receiverKey = receiver;
        t_hash = genHash(amt, time, sender, receiver);
    }

    std::string genHash(double amt, time_t time, const std::string& sender, const std::string& receiver) {

        std::stringstream s;
        s<<amt<<time<<sender<<receiver;
        std::string hash = sha256(s.str());

        return hash;
    }

    std::string genHash(time_t time, std::string& prevHash) { //experiment
        std::stringstream s;
        s<<time<<prevHash;
        std::string hash = sha256(s.str());

        return hash;
    }

    std::string genHash(std::stringstream s) {
        std::string hash = sha256(s.str());

        return hash;
    }

    std::string getInfo() {
        std::string result;

        result = "amount: " + std::to_string(this->getAmount()) + " sender: " + this->getSenderKey() + " receiver: " + this->getReceiverKey() + " \n" ;
        return result;
    }

    bool transactionIsValid(double balance){
        std::string hash = genHash(this->getAmount(), this->getTimestamp(), this->getSenderKey(), this->getReceiverKey());
        return this->t_hash == hash && this->getAmount() <= balance; //hash and balance
    }

    bool commitTransaction(User s, User g) {
        double amt = this->getAmount();

        s.setBalance(s.getBalance()-amt);
        g.setBalance(g.getBalance()+amt);

        return true;
    }


    std::string getT_Hash() const {
        return t_hash;
    }

    double getAmount() {
        return amount;
    }

    void setAmount(double sAmount) {
        this->amount = sAmount;
    }

    const std::string &getSenderKey() const {
        return senderKey;
    }

    void setSenderKey(const std::string &ssenderKey) {
        this->senderKey = ssenderKey;
    }

    const std::string &getReceiverKey() const {
        return receiverKey;
    }

    void setReceiverKey(const std::string &sreceiverKey) {
        this->receiverKey = sreceiverKey;
    }

    time_t getTimestamp() const {
        return timestamp;
    }

    void setTimestamp(time_t stimestamp) {
        this->timestamp = stimestamp;
    }




};


#endif //JONCECHAIN_TRANSACTION_H
