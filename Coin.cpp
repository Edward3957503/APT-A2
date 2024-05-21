#include "Coin.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>

Coin::Coin(Denomination denom, unsigned count) : denom(denom), count(count) {}

void CoinCollection::loadCoinData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int value;
        unsigned count;

        char delim;
        iss >> value >> delim >> count;

        Denomination denom = static_cast<Denomination>(value);
        coins.emplace_back(denom, count);
    }

    // closing reading file.
    file.close();
}



void CoinCollection::addCoins(int denom) {
    for (auto& coin : coins) {
        if (coin.denom == denom) {
            coin.count += 1;
            //std::cout << "Coin: " << denom << ". Count: " << coin.count << "\n";
            return;
        }
    }
}

bool CoinCollection::provideChange(int amount) {
    int changeRemaining = amount;
    std::multiset<int> changeDenominations;
    bool changeGiven = false;

    for (auto& coin : coins) {
        int coinValue = static_cast<int>(coin.denom);
        while (coin.count > 0 && changeRemaining >= coinValue) {
            changeRemaining -= coinValue;
            coin.count--;
            changeDenominations.insert(coinValue);
            changeGiven = true;
        }
    }

    if (changeRemaining > 0) {
        std::cout << "Unable to provide exact change. Missing: " << changeRemaining << " cents.\n";
    } else if (changeGiven) {
        std::cout << "Your change is: ";
        for (int denom : changeDenominations) {
            std::string denominationOutput;
            if (denom < 100) {
                denominationOutput = std::to_string(denom) + "c";
            } else {
                if (denom % 100 == 0) {
                    denominationOutput = "$" + std::to_string(denom / 100);
                } else {
                    double dollarValue = denom / 100.0;
                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(2) << dollarValue;
                    denominationOutput = "$" + stream.str();
                }
            }
            std::cout << denominationOutput << " ";
        }
        std::cout << "\n";
    }

    // Single return statement that evaluates if the change was successfully given
    return changeRemaining == 0 && changeGiven;
}



void CoinCollection::removeCoins(int denom, int count) {
    for (auto& coin : coins) {
        if (coin.denom == denom) {
            coin.count -= count;
            if (coin.count < 0) coin.count = 0;
            return;
        }
    }
}



void CoinCollection::displayBalance() {
    std::cout << std::endl;
    std::cout << "Balance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denom | Quantity | Value" << std::endl;
    for(int i=0; i < 28; ++i){
        std::cout << "-";
    }
    std::cout << std::endl;
                  
    double total = 0.00;
    for (int i=coins.size()-1; i >= 0  ; --i){
        
        int denomination = static_cast<int>(coins[i].denom);
        int count = coins[i].count;
        double value = denomination * count / 100.0; 

        total += value;

        // Print the (coin type) | (amount) | (total value)
        std::cout << std::setw(5) << denomination << " | "
                  << std::setw(8) << count << " | $ "
                  << std::setw(7) << std::fixed << std::setprecision(2) << value << std::endl;
}
    for(int i=0; i < 28; ++i){
        std::cout << "-";
    }

    std::cout << std::endl;
    std::cout << std::setw(20) << "$" << "  " << total << std::endl;
}

