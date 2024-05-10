#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <set>
#include <vector>
#include <limits>
#include <map>
#include "LinkedList.h"
#include "Coin.h"
/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void displayMainMenu();
void processOption(int option, LinkedList& itemList, CoinCollection& coinsList);
void purchaseItem(LinkedList& itemList, CoinCollection& moneyList);
bool isValidDenomination(int cents);
void loadFoodData(const char* filename, LinkedList& itemList);


int main(int argc, char **argv) {
    int option;
    bool quit = false;
    LinkedList itemList;
    CoinCollection coinsList;
    itemList.loadFoodData(argv[1]);
    coinsList.loadCoinData(argv[2]);

    do {
        displayMainMenu();
        std::cout << "Select your option (1-7): ";
        std::cin >> option;
        
        if (std::cin.fail() || std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            quit = true;
        }
        else if (!quit) {
            processOption(option, itemList, coinsList);
        }
    } while (option != 7 && !std::cin.eof() && !quit);

}

void displayMainMenu() {
    std::cout << "\nMain Menu:\n";
    std::cout << "1. Display Items\n";
    std::cout << "2. Purchase Items\n";
    std::cout << "3. Save and Exit\n";
    std::cout << "Administrator-Only Menu:\n";
    std::cout << "4. Add Food\n";
    std::cout << "5. Remove Food\n";
    std::cout << "6. Display Balance\n";
    std::cout << "7. Abort\n";

}

void processOption(int option, LinkedList& itemList, CoinCollection& coinsList) {
    if (option == 1) {
        // Display Items
        std::cout << "\nDisplaying all items:\n";
        itemList.displayItems();
    } else if (option == 2) {// Purchase Items
        purchaseItem(itemList, coinsList);

    } else if (option == 3) { // Save and Exit
        itemList.saveDataAndExit();
    } else if (option == 4) { // add food item
        itemList.createFood();

    } else if (option == 5) {
        // Remove Item
        // Implement as needed
    } else if (option == 6) {
        // Display Balance
        // Code to display balance
        coinsList.displayBalance();
    } else if (option == 7) {
        // Abort Program
        std::cout << "Exiting program.\n";
    } else {
        // Handle invalid option
        std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
    }
}

void purchaseItem(LinkedList& itemList, CoinCollection& coinsList) {
    std::string itemId;
    std::cout << "\nPurchase Meal\n";
    std::cout << "-------------\n";
    std::cout << "Please enter the id of the item you wish to purchase: ";
    std::cin >> itemId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    FoodItem* item = itemList.findItemById(itemId);
    if (!item) {
        std::cout << "Item not found.\n";
    } else if (item->on_hand <= 0) {
        std::cout << "Item out of stock.\n";
    } else {
        double totalCost = item->price.dollars + (item->price.cents / 100.0);
        std::cout << "You have selected \"" << item->name << "\" - " << item->description
                  << ". This will cost you $" << std::fixed << std::setprecision(2) << totalCost << ".\n";

        double totalPaid = 0.0;
        bool transactionCancelled = false;
        std::map<int, int> addedCoins; // Track coins added during this transaction

        std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
        std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase.\n";
        while (!transactionCancelled && totalPaid < totalCost) {
            std::string input;
            std::cout << "You still need to give us $" << std::fixed << std::setprecision(2) << (totalCost - totalPaid) << ": ";

            if (!std::getline(std::cin, input) || input.empty()) {
                std::cout << "Transaction cancelled. Refunding $" << std::fixed << std::setprecision(2) << totalPaid << "\n";
                std::cin.clear();
                transactionCancelled = true;
            } 
            else {
                try {
                    int paymentCents = std::stoi(input);
                    if (isValidDenomination(paymentCents)) {
                        totalPaid += paymentCents / 100.0;
                        coinsList.addCoins(paymentCents);
                        addedCoins[paymentCents]++;
                    } else {
                        std::cout << "Error: invalid denomination encountered.\n";
                    }
                } catch (...) {
                    std::cout << "Invalid input. Please enter numeric value.\n";
                }
            }
        }

        if (transactionCancelled) {
            for (const auto& pair : addedCoins) {
                coinsList.removeCoins(pair.first, pair.second);
            }
        } else if (totalPaid >= totalCost) {
            int change = static_cast<int>((totalPaid - totalCost) * 100);
            if (coinsList.canProvideChange(change)) {
                coinsList.provideChange(change);
                std::cout << "Here is your " << item->name << ". Thank you!\n";
                item->on_hand--;
            } else {
                std::cout << "Sorry, unable to provide the required change. Transaction cannot be completed.\n";
                std::cout << "Refunding $" << std::fixed << std::setprecision(2) << totalPaid << "\n";
                // Roll back added coins
                for (const auto& pair : addedCoins) {
                    coinsList.removeCoins(pair.first, pair.second);
                }
            }
        }
    }
}

bool isValidDenomination(int cents) {
    static const std::set<int> validDenominations = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000};
    return validDenominations.find(cents) != validDenominations.end();
}
