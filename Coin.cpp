#include "Coin.h"
#include <fstream>
#include <sstream>
#include <iostream>


Coin::Coin(Denomination denom, unsigned count) : denom(denom), count(count) {}

void CoinCollection::loadCoinData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int value;
        unsigned count;

        char delim; // Assuming a comma delimiter
        iss >> value >> delim >> count;

        Denomination denom = static_cast<Denomination>(value);
        coins.emplace_back(denom, count);
    }
}
