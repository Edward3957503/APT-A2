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
void processOption(int option);

void loadFoodData(const char* filename, LinkedList& itemList);


int main(int argc, char **argv) {
    int option;
    LinkedList itemList;
    CoinCollection coinsList;
    loadFoodData(argv[1], itemList);
    coinsList.loadCoinData(argv[2]);

    do {
        displayMainMenu();
        std::cout << "Select your option (1-7): ";
        std::cin >> option;
        processOption(option);
    } while (option != 7);

    return EXIT_SUCCESS;
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

void processOption(int option) {
    if (option == 1) {
        // Display Items
        std::cout << "\nDisplaying all items:\n";
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

void loadFoodData(const char* filename, LinkedList& itemList){


    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }
    std::string line;

    while (std::getline(file, line)) {
        //std::cout << "Processing line: " << line << std::endl;
        std::istringstream iss(line);
        std::string id, name, description, temp;
        unsigned dollars, cents, on_hand;

        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        std::getline(iss, description, '|');
        std::getline(iss, temp, '|');
        dollars = std::stoi(temp.substr(0, temp.find('.')));
        cents = std::stoi(temp.substr(temp.find('.') + 1));
        std::getline(iss, temp, '|');
        on_hand = std::stoi(temp);

        FoodItem item;
        item.id = id;
        item.name = name;
        item.description = description;
        item.price.dollars = dollars;
        item.price.cents = cents;
        item.on_hand = on_hand;

        itemList.addFoodItem(item);
        //std::cout << "Added item: " << item.name << " with price $" << item.price.dollars << "." << item.price.cents << std::endl; // Test if added to system
    }
}