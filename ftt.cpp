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


int main(int argc, char **argv) {
    int option = 0;
    bool validInput = false;
    std::string input;
    LinkedList itemList;
    CoinCollection coinsList;

    itemList.loadFoodData(argv[1]);
    coinsList.loadCoinData(argv[2]);

    do {
        displayMainMenu();
        std::cout << "Select your option (1-7): ";
        std::getline(std::cin, input);

        if (std::cin.eof()) {
            exit(EXIT_SUCCESS);
        } 
        else if (input.empty()) {
            std::cout << "Error in input. Please try again.\n";
            
        } 
        else {
            std::stringstream ss(input);
            if (!(ss >> option) || ss.peek() != EOF) {
                std::cout << "Error in input. Please try again.\n";
                std::cin.clear();
                ss.clear();
            } else if (option < 1 || option > 7) {
                std::cout << "Error: number was outside of range.\n";
            } else {
                validInput = true;
            }
        }

        if (validInput) {
            processOption(option, itemList, coinsList);
            validInput = false; // Reset for next input
        }

    } while (option != 7 && !std::cin.eof());
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
    std::string foodFile = "./foods.dat";
    std::string coinFile = "./coins.dat";
    if (option == 1) {
        itemList.displayItems();
    } else if (option == 2) {
        purchaseItem(itemList, coinsList);
    } else if (option == 3) {
        itemList.saveDataAndExit(foodFile, coinFile, coinsList);
    } else if (option == 4) {
        itemList.createFood();
    } else if (option == 5) {
        itemList.deleteFoodById();
    } else if (option == 6) {
        coinsList.displayBalance();
    } else if (option == 7) {
        exit(EXIT_SUCCESS);
    }
}

void purchaseItem(LinkedList& itemList, CoinCollection& coinsList) {
    std::string itemId;
    std::cout << "\nPurchase Meal\n";
    std::cout << "-------------\n";
    std::cout << "Please enter the id of the item you wish to purchase: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (!std::getline(std::cin, itemId) || itemId.empty()) {
        if (itemId.empty()) {
            std::cout << "Purchase cancelled\n";
        }
        return;
    }
    FoodItem* item = itemList.findItemById(itemId);
    bool transactionCancelled = false;
    std::map<int, int> addedCoins; 

    if (!item) {
        std::cout << "Item not found.\n";
    } else if (item->on_hand <= 0) {
        std::cout << "Item out of stock.\n";
    } else {
        int totalCostCents = item->price.dollars * 100 + item->price.cents;
        int totalPaidCents = 0;

        std::cout << "You have selected \"" << item->name << "\" - " << item->description << ". This will cost you $" << std::fixed << std::setprecision(2) << static_cast<double>(totalCostCents) / 100.0 << ".\n";
        std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
        std::cout << "Enter on a new line to cancel this purchase.\n";

        while (!transactionCancelled && totalPaidCents < totalCostCents) {
            std::string input;
            std::cout << "You still need to give us $" << std::fixed << std::setprecision(2) << static_cast<double>(totalCostCents - totalPaidCents) / 100.0 << ": ";
            if (!std::getline(std::cin, input) || input.empty()) {
                std::cout << "Transaction cancelled. Refunding $" << std::fixed << std::setprecision(2) << static_cast<double>(totalPaidCents) / 100.0 << "\n";
                transactionCancelled = true;
            } else {
                try {
                    int paymentCents = std::stoi(input);
                    if (isValidDenomination(paymentCents)) {
                        totalPaidCents += paymentCents;
                        coinsList.addCoins(paymentCents);
                    } else {
                        std::cout << "Error: invalid denomination encountered.\n";
                    }
                } catch (...) {
                    std::cout << "Invalid input. Please enter numeric value.\n";
                }
            }
        }

        if (!transactionCancelled && totalPaidCents >= totalCostCents) {
            int changeCents = totalPaidCents - totalCostCents;
            if (changeCents == 0 || coinsList.provideChange(changeCents)) {
                std::cout << "Here is your " << item->name << ". Thank you!\n";
                item->on_hand--;
            } else {
                std::cout << "Sorry, unable to provide the required change. Transaction cannot be completed.\n";
                std::cout << "Refunding $" << std::fixed << std::setprecision(2) << static_cast<double>(totalPaidCents) / 100.0 << "\n";
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
