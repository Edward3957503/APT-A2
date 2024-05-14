#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <limits>

LinkedList::LinkedList() : head(nullptr), count(0) {
    // Constructor body
    // Initialize any needed fields, such as the head pointer and count
}
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;  // Node's destructor will delete the FoodItem object
        current = next;
    }

    // Set the count to 0
    count = 0;
}

void LinkedList::addFoodData(const FoodItem& item) {
    Node* newNode = new Node();
    newNode->data = new FoodItem(item);
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode; 
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

void LinkedList::displayItems() const {
    std::cout << "\nFood Menu\n";
    std::cout << std::string(9, '-') << std::endl;
    Node* current = head;
    if (current != nullptr) {
        std::cout << std::left << std::setw(6) << "ID" << "|"
                  << std::setw(20) << "Name" << "|"
                  << "Length" << std::endl;
        std::cout << std::string(37, '-') << std::endl;

        while (current != nullptr) {
            FoodItem* item = current->data;
            std::cout << std::left << std::setw(6) << item->id << "|"
                      << std::setw(20) << item->name << "|"
                      << "$" << std::setw(6) << std::fixed << std::setprecision(2) << item->price.dollars + item->price.cents / 100.0 << std::endl;
            current = current->next;
        }
    } else {
        std::cout << "No items to display.\n";
    }
}

void LinkedList::loadFoodData(const char* filename) {
    std::ifstream file(filename);
    bool fileOpenedSuccessfully = file.is_open();
    std::string line;

    if (!fileOpenedSuccessfully) {
        std::cerr << "Failed to open " << filename << std::endl;
    } else {
        while (std::getline(file, line)) {
        //std::cout << "Processing line: " << line << std::endl;
        std::istringstream iss(line);
        std::string id, name, description, temp, onHandStr;
        unsigned dollars = 0, cents = 0, on_hand = DEFAULT_FOOD_STOCK_LEVEL;

        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        std::getline(iss, description, '|');
        std::getline(iss, temp, '|');
        dollars = std::stoi(temp.substr(0, temp.find('.')));
        cents = std::stoi(temp.substr(temp.find('.') + 1));
        std::getline(iss, onHandStr, '|');
        // Parse on-hand stock if available
        if (!onHandStr.empty()) {
            on_hand = std::stoi(onHandStr);
        }

        FoodItem item;
        item.id = id;
        item.name = name;
        item.description = description;
        item.price.dollars = dollars;
        item.price.cents = cents;
        item.on_hand = on_hand;

        addFoodData(item);
        //std::cout << "Added item: " << item.name << " with price $" << item.price.dollars << "." << item.price.cents << std::endl; // Test if added to system
        }
    }

    // Close reading file to avoid memory leack
    file.close();
    
}

FoodItem* LinkedList::findItemById(const std::string& id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->id == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}


void LinkedList::saveDataAndExit(const std::string& foodFilename, const std::string& coinFilename, const CoinCollection& coinsList) {
    // Saving Food Items
    std::ofstream foodFile(foodFilename);
    Node* current = head;
    if (!foodFile) {
        throw std::runtime_error("Failed to create expected_output.dat file.");
    }
    while (current != nullptr) {
        foodFile << current->data->id << "|" << current->data->name << "|" << 
        current->data->description << "|" << current->data->price.dollars << "." << 
        current->data->price.cents << "|"<< current->data->on_hand  << std::endl;

        // Storing the next node
        Node* nextNode = current->next;

        // Deleting the current node
        delete current;
        // Moving to the next node in the linkedList.
        current = nextNode;
    }

    // Assign the head pointer to nullptr to avoid memory leack.
    head = nullptr;
    foodFile.close();

    // Saving Coin Data
    std::ofstream coinFile(coinFilename);
    if (!coinFile) {
        std::cerr << "Failed to open " << coinFilename << " for writing.\n";
        exit(EXIT_FAILURE);
    }

    for (const auto& coin : coinsList.coins) {
        coinFile << static_cast<int>(coin.denom) << "," << coin.count << "\n";
    }
    coinFile.close();

    std::cout << "All data saved successfully. Exiting program.\n";
    exit(EXIT_SUCCESS);
}


void LinkedList::createFood(){
    std::string id, name, description, tempStrCents;
    unsigned dollars, cents;
    char dot;

    // Determine the next available food item id
    std::ostringstream nextId;
    nextId << "F" << std::setw(4) << std::setfill('0') << (count + 1);
    // set width to 4 
    // make sure there is always 4 numbers after 'F' = 5 characters long
    // current number of food(count) + 1
    id = nextId.str(); // convert stream to string 

    // Prompt the user for food details
    std::cout << "This new meal item will have the Item id of " << id << "." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore line from input 4 (ftt.cpp)
    
    std::cout << "Enter the item name: ";
    std::getline(std::cin, name);
    if(checkForInvalidValues(name) == true){return;}
    
    std::cout << "Enter the item description:";
    std::getline(std::cin, description);
    if(checkForInvalidValues(description) == true){return;}

    bool valid_price = false;
    while (!valid_price) { // check for valid input
        std::string price_input;
        std::cout << "Enter the price for this item (in dollars.cents format): ";
        std::getline(std::cin, price_input); 
        if(checkForInvalidValues(price_input) == true){return;} // invalid values returns to main menu

        std::istringstream iss(price_input); 

        iss >> dollars >> dot >> cents;
        tempStrCents = std::to_string(cents); // to check if there are 2 numbers after dot 

        if (dollars && dot == '.' && (cents < 100 && cents % 5 == 0) && tempStrCents.size() == 2) { 
            valid_price = true;
        }
        else if (price_input.find('.') == std::string::npos){
            std::cout << "Error: money is not formatted properly" << std::endl;
        }
        else if(!(tempStrCents.size() == 2)){
            std::cout << "Error: there are not two digits for cents." << std::endl;
        }
        else if(cents % 5 != 0){
            std::cout << "Error: price is not a valid denomination." << std::endl;
        }
    }
    // add the food item to the program
    FoodItem item;
    item.id = id;
    item.name = name;
    item.description = description;
    item.price.dollars = dollars;
    item.price.cents = cents;
    item.on_hand = DEFAULT_FOOD_STOCK_LEVEL; // Set value to 20

    addFoodData(item);

    std::cout << "This item \"" << name << " - " << description << ".\" has now been added to the food menu" << std::endl;
}

bool LinkedList::checkForInvalidValues(std::string name){
    if(name.empty()){
        std::cout << "Option cancelled, returning to menu." << std::endl;
        return true;
        }
    else{
        return false;
        }
}

void LinkedList::deleteFoodById() {
    Node* current = head;
    Node* prev = nullptr;
    bool quit = false;
    std::string id = "";
    std::cout << "Enter the food id of the food to remove from the menu: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!std::getline(std::cin, id) || id.empty() || std::cin.eof()){
        quit = true;
    }

    if(current == nullptr && !quit) {
        std::cout << "Food list is emtpy. Food with (" << id << ") cannot be found." << std::endl;
        delete current;
        quit = true;
    }    

    while (current != nullptr && !quit) {
        if (current->data->id == id) {
            std::cout << "“" << id << " - " << current->data->name << " - " << current->data->description << "”"<< " has been removed from the system." << std::endl;
            if (prev == nullptr) {
                // If the node to delete is the head
                head = current->next;
            } 
            else {
                prev->next = current->next;
            }
            
            // Creating a temprary node to store the current.next;
            Node* temp = current->next;
            // Deleting the current node;
            delete current;
            
            // assigning the current node to temp node.
            current = temp;
            // Set the quit to true.
            quit = true;
        }
        else if (current->data->id != id) {
            std::cout << "Food with id (" << id << ") was not found." << std::endl;
            quit = true;
        }
        prev = current;
        current = current->next;
        
    } 
}
