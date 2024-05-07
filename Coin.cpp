#include "Coin.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <set>


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
}

bool CoinCollection::canProvideChange(int amount) {
    int changeRemaining = amount;
    for (auto& coin : coins) {
        int coinValue = static_cast<int>(coin.denom);
        int totalCoinValue = coin.count * coinValue;
        changeRemaining -= totalCoinValue;
    }
    return changeRemaining <= 0;
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

void CoinCollection::provideChange(int amount) {
    int changeRemaining = amount;
    std::multiset<int> changeDenominations; // Set to store and sort coin denominations used.

    for (auto& coin : coins) {
        int coinValue = static_cast<int>(coin.denom);
        while (coin.count > 0 && changeRemaining >= coinValue && changeRemaining != 0) {
            changeRemaining -= coinValue;
            coin.count--;
            changeDenominations.insert(coinValue);
        }
    }

    if (changeRemaining > 0) {
        std::cout << "Unable to provide exact change. Missing: " << changeRemaining << " cents.\n";
    } else {
        std::cout << "Your change is: ";
        for (int denom : changeDenominations) {
            std::string denominationOutput;
            if (denom < 100) {
                denominationOutput = std::to_string(denom) + "c";
            } else {
                if (denom % 100 == 0) {
                    denominationOutput = std::to_string(denom / 100) + "$";
                } else {
                    double dollarValue = denom / 100.0;
                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(2) << dollarValue;
                    denominationOutput = stream.str() + "$";
                }
            }
            std::cout << denominationOutput << " ";
        }
        std::cout << "\n";
    }
}

void CoinCollection::removeCoins(int denom, int count) {
    for (auto& coin : coins) {
        if (coin.denom == denom) {
            coin.count -= count;
            if (coin.count < 0) coin.count = 0; // Prevent negative counts
            return;
        }
    }
}
