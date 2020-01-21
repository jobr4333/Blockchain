#include <iostream>
#include <vector>
#include <algorithm>
#include "transaction.h"
#include "user.h"
#include "joncechain.h"
#include "helper.h"
#include <map>
#include <omp.h>


int main() {

    //daugiau mineriu
    //tikrinti ar nera double spending

    int usersSum = 1000, transSum = 10000, blocksSum = usersSum / 100;

    std::vector<User> usersV;
    std::map<std::string, User> users;
    std::vector<Transaction> transPool;
    Blockchain JonceChain = Blockchain();

    //1 generate users
    for (int i = 0; i < usersSum; i++) { // gen users

        User u("Jonas" + std::to_string(i), 8000 + i);
        //std::cout << u.getName() << " " << u.getPublicKey() << std::endl;

        usersV.push_back(u);
        users.emplace(u.getPublicKey(), u);
        //std::cout << users[i].getName() + " " + users[i].getPublicKey() << " " << std::endl;

    }

    //___________________________
    //2 generate transactions


    transPool.reserve(transSum);

    for (int i = 0; i < transSum; i++) { // gen transactions
        int id1 = rand() % usersSum;
        int id2 = rand() % usersSum;

        std::string key1 = usersV[id1].getPublicKey();
        std::string key2 = usersV[id2].getPublicKey();

        Transaction t(i, time(nullptr), key1, key2);
        transPool.push_back(t);
    }

    //___________________________
    //3 generate candidate blocks
    while(!transPool.empty()) {
        std::vector<Block> candidateBlocks;

        int miners = 3;
        int transPerBlock = 100;

        for (auto m = 0; m < miners; m++) {
            std::vector<Transaction> transForBlock;
            while (transForBlock.size() < transPerBlock) {
                auto userId = rand() % usersSum;
                auto transId = rand() % transPool.size();
                auto id = rand() % transPool.size();
                auto t = transPool[transId];
                std::string senderKey = t.getSenderKey();

                if(t.transactionIsValid(users.find(senderKey)->second.getBalance()) &&
                   t.getSenderKey() != t.getReceiverKey()) {
                    transForBlock.push_back(transPool[id]);
                }

                else transPool.erase(transPool.begin()+id);
            }

            Block tempBlock(JonceChain.getLastBlockHash(), transForBlock);
            candidateBlocks.push_back(tempBlock);
        }

        //4 MINING + validation

        //std::map<std::string, User> users;

        int nonce_max = 1000, nonce = 0, winner = 0;
        std::vector<Transaction> txValidated;
        bool mined = false;
        while (!mined) {
            for (auto i : candidateBlocks) {

                for (auto u : i.getTransactions()) {
                    std::string senderKey = u.getSenderKey();
                    std::string receiverKey = u.getReceiverKey();
                    auto balance = users.find(senderKey)->second.getBalance();

                    auto sender = users.find(senderKey)->second;
                    auto receiver = users.find(receiverKey)->second;

                    if (u.transactionIsValid(balance)) {
                        txValidated.push_back(u);
                    }
                }

                i.setTrasactions(txValidated);

                while (nonce < nonce_max && !mined) {
                    std::string tempHash = i.genHash(nonce);
                    if (i.checkTargetDiff(tempHash)) {

                        printl("the winner is miner number " + std::to_string(winner));

                        for (auto u : txValidated) {
                            std::string senderKey = u.getSenderKey();
                            std::string receiverKey = u.getReceiverKey();
                            auto sender = users.find(senderKey)->second;
                            auto receiver = users.find(receiverKey)->second;

                            //std::cout << "pries commit : siuntejas " << sender.getName() <<  " skaikaitos likutis:  " << sender.getBalance() << " siuncia " << u.getAmount() << " || gavejas  " << receiver.getName() << " turi " << receiver.getBalance() << " pinigu. " << std::endl;

                            double amt = u.getAmount();
                            sender.setBalance(sender.getBalance()-amt);
                            receiver.setBalance(receiver.getBalance()+amt);
                            auto hash = u.getT_Hash();

                            auto it = find_if(transPool.begin(), transPool.end(), [&hash](const Transaction& obj) {return obj.getT_Hash() == hash;}); //neveik

                            if (it != transPool.end())
                            {
                                transPool.erase(it);
                                //print("transpool size:");
                                //printl(transPool.size());
                            }

                            //std::cout << "po    commit : siuntejas " << sender.getName() << " skaikaitos likutis:  " << sender.getBalance() << " || O gavejas " << receiver.getName() << " dabar turi " << receiver.getBalance() << " pinigu. " << std::endl;

                        }
                        i.setNonce(nonce);
                        i.calcMerkle();
                        i.setHash(tempHash);
                        JonceChain.addBlock(i);
                        mined = true;
                        break;
                    }

                    nonce++;
                }
                nonce = 0;
                winner++;
            }
            winner = 0;
            nonce_max *= 2;
        }

        print("JonceChain.size(): ");
        printl(JonceChain.size());
        print("Prev Hash: ");
        printl(JonceChain.getLastBlock().getPrevHash());
        print("Hash: ");
        printl(JonceChain.getLastBlock().getHash());
        print("Nonce: ");
        printl(JonceChain.getLastBlock().getNonce());
        print("Merkle: ");
        printl(JonceChain.getLastBlock().getMerkle());
        printl("");
    }



    return 0;
}