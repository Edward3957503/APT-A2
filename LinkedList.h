#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void addFoodData(const FoodItem& item);
    void displayItems() const;
    void loadFoodData(const char* filename);
    FoodItem* findItemById(const std::string& id);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


