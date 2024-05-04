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

void LinkedList::addFoodItem(const FoodItem& item) {
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