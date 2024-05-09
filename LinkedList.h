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

    /*
        * Save Data and Exit:
        This function saves all the data stored in the linked list to a file named "savedData.dat".
        It traverses the linked list, writes the data of each node to the file in the specified format,
        and deletes each node after writing its data to "savedData.dat" file. Finally, it closes the file and exits the program.
        If the file creation fails, it throws a runtime error.
    */
    void saveDataAndExit();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


