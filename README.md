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
1. addFood_SE - Creates a new food and save and exit --> SHOULD APPEAR IN foods.dat
2. coinBalance_SE - Purchase for food and save and exit --> Check if coin quantity changes in coins.dat
3. removeFood_SE - Removes food and save and exit --> Check in foods.dat if food item is no longer there 
