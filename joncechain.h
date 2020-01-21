//
// Created by Student on 2020-01-11.
//

#ifndef JONCECHAIN_JONCECHAIN_H
#define JONCECHAIN_JONCECHAIN_H

#include <vector>
#include "Block.h"

class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain() {

    }

    std::vector<Block> getChain() {
        return chain;
    }

    Block getLastBlock() const {
        return chain.back();
    }

    std::string getLastBlockHash() {
        if(chain.empty()) return "0"; // genesis
        else return chain.back().getHash();
    }

    /*bool getInfo(const std::vector<Transaction>& transactions) { // BS
        for(auto i : transactions) i.getInfo(i);
        return true;
    }*/


    bool validateBlock(const Block& newBlock) {

        return true;
    }

    void addBlock(const Block& newBlock) {
        chain.push_back(newBlock);
    }

    bool isChainValid() {

        return true;
    }

    size_t size(){
        return chain.size();
    }

    std::string add_strings(std::string &one, std::string &two){
        std::stringstream s;
        s<<one<<two;
        return s.str();
    }

    std::string calculateMerkleRoot(std::vector<Transaction> &transactions){

        std::vector<std::string> merkleTree;

        for (Transaction t : transactions) {
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



#endif //JONCECHAIN_JONCECHAIN_H
