//
// Created by Student on 2020-01-11.
//

#ifndef JONCECHAIN_BLOCK_H
#define JONCECHAIN_BLOCK_H


#include <string>
#include "transaction.h"
#include "sha256.h"
#include "user.h"
#include <ctime>
#include <vector>
#include <map>


//HEAD prev hash, timestamp, version, merkle root, nonce, difficulty target || BODY transactions

class Block {
private:
    std::string hash;
    std::string prevHash;
    double version = 1.0;
    std::string merkleRootHash;
    time_t timestamp;
    int nonce;
    int id;
    int difficultyTarget = 3;
    std::vector<Transaction> transactionData;
public:

    Block(std::string prHash, std::vector<Transaction> &data) {
        prevHash = std::move(prHash);
        transactionData = data;
        merkleRootHash = calculateMerkleRoot();
        timestamp = time(nullptr);
    }

    Block(std::string &prHash){
        prevHash = std::move(prHash);
        timestamp = time(nullptr);
    }

    Block(std::vector<Transaction> &data){
        transactionData = data;
        merkleRootHash = calculateMerkleRoot();
        timestamp = time(nullptr);
    }

    std::vector<Transaction> getTransactions() {
        return transactionData;
    }
    void setTrasactions( std::vector<Transaction> set) {
        transactionData=set;
    }
    std::string getInfo() {
        std::string result;
        result.append("hash: " + getHash() + " prev: " + getPrevHash()
        + "\n Merkle: " + getMerkle() + "\n");
        for(auto i : transactionData) {
            result.append(i.getInfo() + "\n");
        }
        return result;
    }

    void setDifficulty(int &target) {
        difficultyTarget = target;
    }

    int getDifficulty() {
        return difficultyTarget;
    }

    void setHash(std::string hsh) {
        hash = hsh;
    }

    std::string getHash() {
        return hash;
    }

    std::string getPrevHash() {
        return prevHash;
    }

    int getNonce(){
        return nonce;
    }

    void setNonce(int &n){
        nonce = n;
    }

    void incrementNonce() {
        nonce++;
    }



    std::string genHash() {
        std::stringstream s;
        s<<prevHash<<merkleRootHash<<nonce;
        std::string hash = sha256(s.str());
        return hash;
    }

    std::string genHash(int nonce) {
        std::stringstream s;
        s<<prevHash<<merkleRootHash<<nonce;
        std::string hash = sha256(s.str());
        return hash;
    }

    bool checkTargetDiff() {

        std::string str;
        for(auto i = 0; i < difficultyTarget; i++) str=str+"0";

        return str.compare(0, difficultyTarget, hash, 0, difficultyTarget) == 0;
    }

    bool checkTargetDiff(std::string &hsh) {

        std::string str;
        for(auto i = 0; i < difficultyTarget; i++) str=str+"0";

        return str.compare(0, difficultyTarget, hsh, 0, difficultyTarget) == 0;
    }

    void calcMerkle() {
        merkleRootHash = calculateMerkleRoot();
    }

    std::string getMerkle() {
        return merkleRootHash;
    }

    std::string add_strings(std::string &one, std::string &two){
        std::stringstream s;
        s<<one<<two;
        return s.str();
    }

    std::string calculateMerkleRoot(){

        std::vector<std::string> merkleTree;

        for (Transaction t : transactionData) {
            merkleTree.push_back(t.getT_Hash()); // transakciju hashai
            //std::cout  << "merkleTree.size() " << merkleTree.size() << std::endl;
            //std::cout  << "t.getT_Hash() " << t.getT_Hash() << std::endl;
            //std::cout  << "t.getT_Hash() " << t.get << std::endl;
        }

        while (merkleTree.size() > 1){
            if (merkleTree.size()%2 != 0) merkleTree.push_back(merkleTree.back()); // reikia kad lyginis lapu skaicius butu

            std::vector<std::string> newMerkleTree;

            for (unsigned long long i = 0; i < merkleTree.size(); i += 2){
                std::string firstHalf = merkleTree.at(i);
                std::string secondHalf = merkleTree.at(i+1);
                std::string hash_this =  add_strings(firstHalf, secondHalf);

                newMerkleTree.push_back(sha256(hash_this));
            }
            merkleTree = newMerkleTree;

        }
        return merkleTree.at(0);
    }


};








#endif //JONCECHAIN_BLOCK_H


