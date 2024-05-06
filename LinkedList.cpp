#include "LinkedList.h"
#include <iostream>
#include <iomanip>
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
    if (current == nullptr) {
        std::cout << "No items to display.\n";
        return;
    }
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
}