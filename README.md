# Adnvaced Programming Technique
                                Assignment 02

            Name: Esmatullah Akhtary        Student ID: s3941885
            Name: Edward Lim Padmajaya      Student ID: s3957503
            Name: Sandesh Mann Mangat       Student ID: s3945006

## Introduction
The Vending Machine System is a console-based application designed to facilitate the management of food items in a vending machine. This program, written in C++, helps keep track of all your food items.  It lets you add new food items, remove exist food items, and see what's currently available. Additionally, this system is particularly useful for administrators who need to keep track of various food items, their descriptions, prices, and availability. It even handles the money side of things, making sure customers get the right change and keeping track of how much money is in the machine. Moreover, this system is designed to be easy to use, so even if you're not a tech expert, you can manage your food selection with ease.


## Requirements

- C++14 
- A terminal or command-line interface


### Using Makefile

1. **Build the project**
   
   Open your terminal, navigate to the project directory using cd command and run:
   make

   The type the following command:
   ./ftt foods.dat coins.dat


## Main Menu Options:
1. Display Items: Lists all the food items in the menu.
2. Add Food Item: Prompts for details of a new food item and adds it to the menu.
3. Delete Food Item: Prompts for the ID of a food item to delete it from the menu.
4. Load Food Data: Loads food data from a specified file.
5. Save Data and Exit: Saves the current food data to a file and exits the program.
6. Display Coin Balance: Displays the current balance of coins in the system.
7. Abort: Exit out of the program. 


## Test Cases
1. test-1 : Testing invalid inputs on main menu.
2. test-2 : Testing invalid inputs on purchase menu.
3. test-3 : Testing cancellation in 'add food' and invalid inputs menu on each stage.
4. test-4 : Testing what happens when the all food stock is 0 and a customer wants to purchase an item.
   Note : Uses 123441 as an input to make the food stock to 0.
5. test-5 : Testing what happens when the all the coin stock is 0 and a customer wants to purchase an item.
   Note : Uses 123442 as an input to make the coin stock to 0.
6. test-6 : Testing what happens when foods.dat has an invalid format.
   Note : This will need modification on the foods.dat file where someone puts a random '|' seperator somewhere in the middle, which could make `loadFoodData` function read an invalid data type.
7. test-7 : Testing invalid inputs on remove food menu.
8. test-8 : Create a new food and save and exit --> SHOULD APPEAR IN foods.dat
9. test-9 : Purchase for food and save and exit --> Check if coin quantity changes in coins.dat
3. test-10 : Remove food and save and exit --> Check in foods.dat if food item is no longer there 
