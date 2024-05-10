#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
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
        count--;
    }
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
    Node* current = head;
    if (current != nullptr) {
        std::cout << std::left << std::setw(6) << "ID" << "|"
                  << std::setw(20) << "Name" << "|"
                  << "Length" << std::endl;
        std::cout << std::string(37, '-') << std::endl;  // Separator line

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

        addFoodData(item);
        //std::cout << "Added item: " << item.name << " with price $" << item.price.dollars << "." << item.price.cents << std::endl; // Test if added to system
        }
    }
    
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


void LinkedList::saveDataAndExit() {
    std::ofstream savedData ("./savedData.dat");
    Node* current = head;
    if (!savedData) {
        throw std::runtime_error("Failed to create saveData.dat file.");
    }
    while (current != nullptr) {
        savedData << current->data->id << "|" << current->data->name << "|" << 
        current->data->description << "|" << current->data->price.dollars << "." << current->data->price.cents << std::endl;

        // Storing the next node
        Node* nextNode = current->next;
        // Deleting the current node
        delete current;
        // Moving to the next node in the linkedList.
        current = nextNode;
    }

    // Assign the head pointer to nullptr to avoid memory leack.
    head = nullptr;

    // Close the file
    savedData.close();

    // Exit out of program
    exit(EXIT_SUCCESS); 
}

void LinkedList::createFood(){
    std::string id, name, description;
    unsigned dollars, cents;

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
    
    std::cout << "Enter the item description:";
    std::getline(std::cin, description);

    bool valid_price = false;
    while (!valid_price) { // check for valid input
        std::string price_input;
        std::cout << "Enter the price for this item (in dollars.cents format): ";
        std::getline(std::cin, price_input); //store the entire line in price_input
        std::istringstream iss(price_input); //store price_input into istringstream

        char dot;
        // store value into dollars
        // store dot and check if it is the right character
        // store cents and check if its less then 100 coins

        if (iss >> dollars && (iss >> dot && dot == '.') && (iss >> cents && cents < 100) ) { 
            valid_price = true;
        } 
        else {
            std::cout << "Invalid input. The price entered for an item must have a dollars and a cents component\n";
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