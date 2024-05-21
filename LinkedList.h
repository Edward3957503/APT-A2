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
    void createFood();
    bool checkForInvalidValues(std::string);
    void capitalizeFirstLetter(std::string& str);
    void setAllFoodStockToZero();

    /*
        * Save Data and Exit:
        This function saves all the data stored in the linked list to a file named "savedData.dat".
        It traverses the linked list, writes the data of each node to the file in the specified format,
        and deletes each node after writing its data to "savedData.dat" file. Finally, it closes the file and exits the program.
        If the file creation fails, it throws a runtime error.
    */
    void saveDataAndExit(const std::string& foodFilename, const std::string& coinFilename, const CoinCollection& coinsList);

    /*
        This function allows the administrator to remove a food item from the menu by specifying its unique ID.
        The function prompts the user to enter the ID of the food item to be removed.
        If user presses enter without providing andy input, the function returns the user to main menu.
        If an id of food is provided but the food list is empty, it will show a message to user that food list is emtpy and it will return user to main menu.
        If food list is not empty then iterates through the linked list of food items to find the item with the specified ID.
        If the item is found, it is removed from the list, and a confirmation message is displayed.
        If the specified ID is not found in the list, a message indicating that the food item was not found is displayed.
    */
    void deleteFoodById();
private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


