//
// Created by Student on 2020-01-21.
//

#ifndef JONCECHAIN_HELPER_H
#define JONCECHAIN_HELPER_H

#include <string>
#include <iostream>

void printl(unsigned long long int a) {
    std::cout << a << std::endl;
}

void printl(int &a) {
    std::cout << a << std::endl;
}

void printl(std::string a) {
    std::cout << a << std::endl;
}

void print(unsigned long long int a) {
    std::cout << a << " ";
}

void print(int &a) {
    std::cout << a << " ";
}

void print(std::string a) {
    std::cout << a << " ";
}

template < typename T>
std::pair<bool, int > findInVector(const std::vector<T>  & vecOfElements, const T  & element)
{
    std::pair<bool, int > result;

    // Find given element in vector
    auto it = std::find(vecOfElements.begin(), vecOfElements.end(), element);

    if (it != vecOfElements.end())
    {
        result.second = distance(vecOfElements.begin(), it);
        result.first = true;
    }
    else
    {
        result.first = false;
        result.second = -1;
    }

    return result;
}

#endif //JONCECHAIN_HELPER_H
