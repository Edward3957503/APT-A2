#include "Coin.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>

// Constructor for the Coin class
Coin::Coin(Denomination denom, unsigned count) : denom(denom), count(count) {}

// Function to load coin data from a file
void CoinCollection::loadCoinData(const std::string& filename) {
    std::ifstream file(filename); // Open the file
    if (!file) { // Check if the file opened successfully
        throw std::runtime_error("Failed to open " + filename);
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
        std::istringstream iss(line); // Convert the line to a stringstream
        int value;
        unsigned count;
        char delim;
        iss >> value >> delim >> count; // Extract value and count separated by a delimiter

        // Convert the value to a Denomination and add to the coins vector
        Denomination denom = static_cast<Denomination>(value);
        coins.emplace_back(denom, count);
    }

    file.close(); // Close the file
}

// Function to add a coin to the collection
void CoinCollection::addCoins(int denom) {
    // Find the coin in the collection and increment its count
    for (auto& coin : coins) {
        if (coin.denom == denom) {
            coin.count += 1;
            return;
        }
    }
}

// Function to provide change for a given amount
bool CoinCollection::provideChange(int amount) {
    int changeRemaining = amount; // Remaining amount of change to provide
    std::multiset<int> changeDenominations; // Set to store the denominations used for change
    bool changeGiven = false; // Flag to indicate if change was given

    // Iterate over the coins to provide change
    for (auto& coin : coins) {
        int coinValue = static_cast<int>(coin.denom);
        while (coin.count > 0 && changeRemaining >= coinValue) {
            changeRemaining -= coinValue;
            coin.count--;
            changeDenominations.insert(coinValue); // Add the coin value to the change denominations
            changeGiven = true;
        }
    }

    // Check if exact change was provided
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

    // Return whether the exact change was provided
    return changeRemaining == 0 && changeGiven;
}

// Function to remove a specified count of coins of a given denomination
void CoinCollection::removeCoins(int denom, int count) {
    for (auto& coin : coins) {
        if (coin.denom == denom) {
            coin.count -= count;
            if (coin.count < 0) coin.count = 0; // Ensure count does not go below zero
            return;
        }
    }
}

// Function to display the balance of all coins
void CoinCollection::displayBalance() {
    std::cout << std::endl;
    std::cout << "Balance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denom | Quantity | Value" << std::endl;
    for(int i = 0; i < 28; ++i){
        std::cout << "-";
    }
    std::cout << std::endl;
                  
    double total = 0.00;
    // Iterate over the coins in reverse order to display higher denominations first
    for (int i = coins.size() - 1; i >= 0; --i){
        int denomination = static_cast<int>(coins[i].denom);
        int count = coins[i].count;
        double value = denomination * count / 100.0; 
        total += value; // Add to total value

        // Print the denomination, quantity, and total value for each type of coin
        std::cout << std::setw(5) << denomination << " | "
                  << std::setw(8) << count << " | $ "
                  << std::setw(7) << std::fixed << std::setprecision(2) << value << std::endl;
    }

    for(int i = 0; i < 28; ++i){
        std::cout << "-";
    }

    std::cout << std::endl;
    std::cout << std::setw(20) << "$" << "  " << total << std::endl; // Display the total value
}

// Function to set the count of all coins to zero
void CoinCollection::setAllCoinsToZero() {
    for (auto& coin : coins) {
        coin.count = 0; // Set each coin's count to zero
    }
}
