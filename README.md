# Advanced Programming Techniques: Assignment 02

### Group Members:
- **Name:** Esmatullah Akhtary | **Student ID:** s3941885
- **Name:** Edward Lim Padmajaya | **Student ID:** s3957503
- **Name:** Sandesh Mann Mangat | **Student ID:** s3945006

---

## Introduction
The Vending Machine System is a console-based application designed to facilitate the management of food items in a vending machine. This program, written in C++, helps keep track of all your food items. It lets you add new food items, remove existing food items, and see what's currently available. Additionally, this system is particularly useful for administrators who need to keep track of various food items, their descriptions, prices, and availability. It even handles the money side of things, making sure customers get the right change and keeping track of how much money is in the machine. Moreover, this system is designed to be easy to use, so even if you're not a tech expert, you can manage your food selection with ease.

---

## Requirements
- **C++14** 
- **A terminal or command-line interface**

---

## Building and Running the Project

### Using Makefile

1. **Build the project:**
   - Open your terminal.
   - Navigate to the project directory using `cd` command.
   - Run:
     ```sh
     make
     ```

2. **Run the project:**
   - After building the project, run the following command:
     ```sh
     ./ftt foods.dat coins.dat
     ```

---

## Main Menu Options:

1. **Display Items:** Lists all the food items in the menu.
2. **Purchase Meal:** Prompts for the ID of a food item and handles the purchase process.
3. **Save and Exit:** Saves the current food data and coin data to respective files and exits the program.
4. **Add Food Item:** Prompts for details of a new food item and adds it to the menu.
5. **Remove Food Item:** Prompts for the ID of a food item to delete it from the menu.
6. **Display Balance:** Displays the current balance of coins in the system.
7. **Abort Program:** Exits the program without saving any data.

---

## Test Cases

1. **invalid_input_main:** Testing invalid inputs on the main menu.
2. **invalid_input_purchase:** Testing invalid inputs on the purchase menu.
3. **invalid_add_food:** Testing cancellation in 'add food' and invalid inputs at each stage.
4. **empty_food_stock:** Testing the scenario where all food stock is set to 0 and a customer attempts to purchase an item.
   - **Note:** Uses `123441` as an input to set all food stock to 0.
5. **empty_coin_stock:** Testing the scenario where all coin stock is set to 0 and a customer attempts to purchase an item.
   - **Note:** Uses `123442` as an input to set all coin stock to 0.
6. **invalid_food_format:** Testing the behavior when `foods.dat` has an invalid format.
   - **Note:** This will need modification of the `foods.dat` file by inserting a random '|' separator in the middle, which could cause the `loadFoodData` function to read an invalid data type.
7. **invalid_input_remove:** Testing invalid inputs on the remove food menu.
8. **addFoodSE:** Create a new food item, save, and exit. The new food item should appear in `foods.dat`.
9. **coinBalanceSE:** Purchase food, save, and exit. Check if coin quantity changes in `coins.dat`.
10. **removeFoodSE:** Remove food, save, and exit. Check if the food item is no longer present in `foods.dat`.

---

