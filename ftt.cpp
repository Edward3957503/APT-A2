#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <set>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>
#include "LinkedList.h"
#include "Coin.h"

// Main functions and the structure of the program are declared here

void displayMainMenu(); // Displays the main menu
void processOption(int option, LinkedList& itemList, CoinCollection& coinsList); // Processes the option selected from the main menu
void purchaseItem(LinkedList& itemList, CoinCollection& moneyList); // Handles the item purchase process
bool isValidDenomination(int cents); // Checks if the given cents are a valid denomination


int main(int argc, char **argv) {
    int option = 0; // Variable to store the selected option
    bool validInput = false; // Flag to check if the input is valid
    std::string input; // Stores the user input
    LinkedList itemList; // Linked list to store food items
    CoinCollection coinsList; // Coin collection to manage the coins

    itemList.loadFoodData(argv[1]); // Loads food data from the file provided as the first argument
    coinsList.loadCoinData(argv[2]); // Loads coin data from the file provided as the second argument

    // Main loop to display the menu and process options
    do {
        displayMainMenu();
        std::cout << "Select your option (1-7): ";
        std::getline(std::cin, input); // Reads input from the user

        if (std::cin.eof()) { // If EOF is encountered, exit the program
            exit(EXIT_SUCCESS);
        } 
        else if (input.empty()) { // If input is empty, show an error message
            std::cout << "Error in input. Please try again.\n";
        } 
        else {
            std::stringstream ss(input); // Convert the input to a stringstream
            if (!(ss >> option) || ss.peek() != EOF) { // Validate if the input is an integer and there are no extra characters
                std::cout << "Error in input. Please try again.\n";
                std::cin.clear();
                ss.clear();
            } else {
                validInput = true; // If valid, set the flag to true
            }
        }

        if (validInput) {
            processOption(option, itemList, coinsList); // Process the selected option
            validInput = false; // Reset the flag for the next input
        }

    } while (option != 7 && !std::cin.eof()); // Continue until the user selects the option to exit or an EOF is encountered
}

// Function to display the main menu
void displayMainMenu() {
    std::string whitespace = "   ";
    std::cout << "\nMain Menu:\n";
    std::cout << whitespace << "1. Display Meal Options\n";
    std::cout << whitespace << "2. Purchase Meal\n";
    std::cout << whitespace << "3. Save and Exit\n";
    std::cout << "Administrator-Only Menu:\n";
    std::cout << whitespace << "4. Add Food\n";
    std::cout << whitespace << "5. Remove Food\n";
    std::cout << whitespace << "6. Display Balance\n";
    std::cout << whitespace << "7. Abort Program\n";
}

// Function to process the selected option from the menu
void processOption(int option, LinkedList& itemList, CoinCollection& coinsList) {
    std::string foodFile = "./foods.dat"; // File to save food data
    std::string coinFile = "./coins.dat"; // File to save coin data

    if (option == 1) {
        itemList.displayItems(); // Display all food items
    } else if (option == 2) {
        purchaseItem(itemList, coinsList); // Handle item purchase
    } else if (option == 3) {
        itemList.saveDataAndExit(foodFile, coinFile, coinsList); // Save data and exit
    } else if (option == 4) {
        itemList.createFood(); // Add a new food item
    } else if (option == 5) {
        itemList.deleteFoodById(); // Remove a food item
    } else if (option == 6) {
        coinsList.displayBalance(); // Display coin balance
    } else if (option == 7) {
        exit(EXIT_SUCCESS); // Exit the program
    } else if (option == 123441) { // Special option to set all food stock to zero
        itemList.setAllFoodStockToZero();
        std::cout << "All food stock set to zero.\n";
    } else if (option == 123442) { // Special option to set all coin stock to zero
        coinsList.setAllCoinsToZero();
        std::cout << "All coin stock set to zero.\n";
    } else {
        std::cout << "Error: number was outside of range.\n";
    }
}

// Function to handle the purchase of an item
void purchaseItem(LinkedList& itemList, CoinCollection& coinsList) {
    std::string itemId;
    std::cout << "\nPurchase Meal\n";
    std::cout << "-------------\n";
    std::cout << "Please enter the id of the item you wish to purchase: ";
    
    if (!std::getline(std::cin, itemId)) {
        // If getline fails, likely due to EOF, the function returns
    }
    else if(itemId.empty()) {
        std::cout << "Purchase cancelled\n";
    }
    else {
        FoodItem* item = itemList.findItemById(itemId); // Find the item by ID
        bool transactionCancelled = false; // Flag to check if the transaction is cancelled
        std::map<int, int> addedCoins; // Map to store added coins

        if (!item) {
            std::cout << "Item not found.\n";
        } 
        else if (item->on_hand <= 0) {
            std::cout << "Item out of stock.\n";
        } 
        else {
            int totalCostCents = item->price.dollars * 100 + item->price.cents; // Calculate total cost in cents
            int totalPaidCents = 0; // Total amount paid by the user

            std::cout << "You have selected \"" << item->name << "\" - " << item->description << ". This will cost you $" << std::fixed << std::setprecision(2) << static_cast<double>(totalCostCents) / 100.0 << ".\n";
            std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
            std::cout << "Please enter ctrl-D or enter on a new line to cancel this purchase.\n";

            // Loop to handle the money input and calculate the change if necessary
            while (!transactionCancelled && totalPaidCents < totalCostCents) {
                std::string input;
                std::cout << "You still need to give us $" << std::fixed << std::setprecision(2) << static_cast<double>(totalCostCents - totalPaidCents) / 100.0 << ": ";
                if (!std::getline(std::cin, input)) {
                    transactionCancelled = true;
                }
                else if(input.empty()) {
                    std::cout << "Transaction cancelled. Refunding $" << std::fixed << std::setprecision(2) << static_cast<double>(totalPaidCents) / 100.0 << "\n";
                    transactionCancelled = true;
                } 
                else {
                    bool isNumeric = std::all_of(input.begin(), input.end(), ::isdigit);

                    if (!isNumeric) {
                        std::cout << "Error: input was not numeric.\n";
                    } else {
                        try {
                            int paymentCents = std::stoi(input); // Convert input to integer
                            if (!isValidDenomination(paymentCents)) {
                                std::cout << "Error: invalid denomination encountered.\n";
                            } else {
                                totalPaidCents += paymentCents;
                                coinsList.addCoins(paymentCents); // Add coins to the coin collection
                            }
                        } catch (const std::invalid_argument&) {
                            std::cout << "Error: input was not numeric.\n";
                        }
                    }
                }
            }

            if (!transactionCancelled && totalPaidCents >= totalCostCents) {
                int changeCents = totalPaidCents - totalCostCents;
                if (changeCents == 0 || coinsList.provideChange(changeCents)) {
                    std::cout << "Here is your " << item->name << ". Thank you!\n";
                    item->on_hand--; // Decrease the stock of the item
                } else {
                    std::cout << "Sorry, unable to provide the required change. Transaction cannot be completed.\n";
                    std::cout << "Refunding $" << std::fixed << std::setprecision(2) << static_cast<double>(totalPaidCents) / 100.0 << "\n";
                    for (const auto& pair : addedCoins) {
                        coinsList.removeCoins(pair.first, pair.second); // Remove coins if the transaction is not completed
                    }
                }
            }
        }
    }
}

// Function to check if the given cents are a valid denomination
bool isValidDenomination(int cents) {
    static const std::set<int> validDenominations = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000};
    return validDenominations.find(cents) != validDenominations.end();
}
