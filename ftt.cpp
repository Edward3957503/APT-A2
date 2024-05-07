#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <set>
#include <vector>
#include <limits>
#include "LinkedList.h"
#include "Coin.h"
/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void displayMainMenu();
void processOption(int option, LinkedList& itemList, CoinCollection& coinsList);
void loadFoodData(const char* filename, LinkedList& itemList);


int main(int argc, char **argv) {
    int option;
    LinkedList itemList;
    CoinCollection coinsList;
    itemList.loadFoodData(argv[1]);
    coinsList.loadCoinData(argv[2]);

    do {
        displayMainMenu();
        std::cout << "Select your option (1-7): ";
        std::cin >> option;
        processOption(option, itemList, coinsList);
    } while (option != 7);

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
    } else if (option == 2) {
        // Purchase Items
    } else if (option == 3) {
        // Save and Exit
        // Potentially save state or perform cleanup
    } else if (option == 4) {
        // Add Item
        // Implement as needed
    } else if (option == 5) {
        // Remove Item
        // Implement as needed
    } else if (option == 6) {
        // Display Balance
        // Code to display balance
    } else if (option == 7) {
        // Abort Program
        std::cout << "Exiting program.\n";
    } else {
        // Handle invalid option
        std::cout << "Invalid option. Please enter a number between 1 and 7.\n";
    }
}