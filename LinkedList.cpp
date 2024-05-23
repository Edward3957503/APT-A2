#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <limits>

LinkedList::LinkedList() : head(nullptr), count(0) {
}
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    count = 0;
}

void LinkedList::addFoodData(const FoodItem& item) {
    Node* newNode = new Node();
    newNode->data = new FoodItem(item);
    newNode->next = nullptr;

    if (head == nullptr || head->data->name.compare(item.name) > 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data->name.compare(item.name) < 0) {
            current = current->next;
        }
        newNode->next = current->next;
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
                  << std::setw(49) << "Name" << "|"
                  << "Length" << std::endl;
        std::cout << std::string(66, '-') << std::endl;

        while (current != nullptr) {
            FoodItem* item = current->data;
            std::cout << std::left << std::setw(6) << item->id << "|"
                      << std::setw(49) << item->name << "|"
                      << "$" << std::setw(6) << std::fixed << std::setprecision(2) << item->price.dollars + item->price.cents / 100.0 << std::endl;
            current = current->next;
        }
    } else {
        std::cout << "No items to display.\n";
    }
}

void LinkedList::loadFoodData(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, description, priceStr, onHandStr;
        unsigned dollars = 0, cents = 0, on_hand = DEFAULT_FOOD_STOCK_LEVEL;

        if (!std::getline(iss, id, '|') ||
            !std::getline(iss, name, '|') ||
            !std::getline(iss, description, '|') ||
            !std::getline(iss, priceStr, '|')) {
            std::cerr << "Error parsing line, skipping: " << line << std::endl;
        }

        try {
            size_t pos = priceStr.find('.');
            if (pos != std::string::npos) {
                dollars = std::stoi(priceStr.substr(0, pos));
                cents = std::stoi(priceStr.substr(pos + 1));
            } else {
                throw std::invalid_argument("Invalid price format");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing data for item: " << id << ", Error: " << e.what() << std::endl;
        }

        FoodItem item;
        item.id = id;
        item.name = name;
        item.description = description;
        item.price.dollars = dollars;
        item.price.cents = cents;
        item.on_hand = on_hand;

        addFoodData(item);
    }

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
    std::ofstream foodFile(foodFilename);
    Node* current = head;
    if (!foodFile) {
        throw std::runtime_error("Failed to create expected_output.dat file.");
    }
    while (current != nullptr) {
        foodFile << current->data->id << "|" << current->data->name << "|" << 
        current->data->description << "|" << current->data->price.dollars << "." << 
        current->data->price.cents << std::endl;
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    foodFile.close();
    std::ofstream coinFile(coinFilename);
    if (!coinFile) {
        std::cerr << "Failed to open " << coinFilename << " for writing.\n";
    }
    else {
        for (const auto& coin : coinsList.coins) {
            coinFile << static_cast<int>(coin.denom) << "," << coin.count << "\n";
        }
        coinFile.close();

        std::cout << "All data saved successfully. Exiting program.\n";
    }
    exit(EXIT_SUCCESS);
}

void LinkedList::createFood() {
    std::string id, name, description, price_input;
    unsigned dollars, cents;
    char dot;
    bool cancel = false, eof_encountered = false;
    std::ostringstream nextId;
    nextId << "F" << std::setw(4) << std::setfill('0') << (count + 1);
    id = nextId.str();

    std::cout << "This new meal item will have the Item id of " << id << "." << std::endl;
    std::cout << "Enter the item name: ";
    std::getline(std::cin, name);
    if (std::cin.eof()) {
        eof_encountered = true;
    }
    else if (name.empty()) {
        cancel = true;
    } else {
        capitalizeFirstLetter(name);
    }
    
    if (!cancel && !eof_encountered) {
        std::cout << "Enter the item description: ";
        std::getline(std::cin, description);
        if (std::cin.eof()) {
            eof_encountered = true;
        }
        else if (description.empty()) {
            cancel = true;
        } else {
            capitalizeFirstLetter(description);
        }
    }

    if (!cancel && !eof_encountered) {
        bool valid_price = false;
        std::cout << "Enter the item price (in cents): ";
        while (!valid_price && !cancel) {
            std::getline(std::cin, price_input);
            if (std::cin.eof()) {
                eof_encountered = true;
            }
            if (price_input.empty()) {
                cancel = true;
            } else {
                std::istringstream iss(price_input);
                if (!(iss >> dollars >> dot >> cents)) {
                    if (price_input.find('.') == std::string::npos) {
                        std::cout << "Error: money is not formatted properly.\n";
                    } else {
                        std::cout << "Error: there are not two digits for cents.\n";
                    }
                    std::cout << "Enter the item price (in dollars.cents format): ";
                } else if (dot != '.' || cents >= 100 || !iss.eof()) {
                    std::cout << "Error: money is not formatted properly.\n";
                    std::cout << "Enter the item price (in dollars.cents format): ";
                } else if (cents % 5 != 0) {
                    std::cout << "Error: price is not a valid denomination.\n";
                    std::cout << "Enter the item price (in dollars.cents format): ";
                } else {
                    valid_price = true;
                }
            }
        }
    }

    if (!cancel && !eof_encountered) {
        FoodItem item;
        item.id = id;
        item.name = name;
        item.description = description;
        item.price.dollars = dollars;
        item.price.cents = cents;
        item.on_hand = DEFAULT_FOOD_STOCK_LEVEL;

        addFoodData(item);
        std::cout << "This item \"" << name << " - " << description << "\" has now been added to the food menu\n";
    } else if (cancel && !eof_encountered) {
        std::cout << "Option cancelled, returning to menu.\n";
    }

    if (eof_encountered) {
        exit(EXIT_SUCCESS);
    }
}



void LinkedList::deleteFoodById() {
    Node* current = head;
    Node* prev = nullptr;
    bool quit = false;
    std::string id = "";
    std::cout << "Please enter the ID of the food to remove from the menu: ";

    if (!std::getline(std::cin, id) || id.empty() || std::cin.eof()){
        quit = true;
    }

    if(current == nullptr && !quit) {
        std::cout << "Food list is emtpy. Food with (" << id << ") cannot be found." << std::endl;
        delete current;
        quit = true;
    }    
    bool found = false;
    while (current != nullptr && !quit) {
        if (current->data->id == id) {
            std::cout << "\"" << id << " - " << current->data->name << " - " << current->data->description << "\" has been removed from the system.\n";
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
            found = true;
        }
            prev = current;
            current = current->next;
    } 
    if (!found && !quit) {
            std::cout << "Food with id (" << id << ") was not found." << std::endl;
            quit = true;
    }
}

void LinkedList::capitalizeFirstLetter(std::string& str) {
    if (!str.empty() && std::islower(str[0])) {
        str[0] = std::toupper(str[0]);
    }
}

void LinkedList::setAllFoodStockToZero() {
    Node* current = head;
    while (current != nullptr) {
        current->data->on_hand = 0;
        current = current->next;
    }
}


