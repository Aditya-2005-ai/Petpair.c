# Petpair.c
 A C program for managing pet adoption records and user interactions in an animal shelter system.
# PetPair

## Overview
PetPair is a C program designed to manage pet adoption records and user interactions in an animal shelter system. It provides functionalities for both regular users and administrators to search for pets, add or remove pets, and adopt pets. users can input the attributes they want in a pet and the program will return closest matches based on the user's input.

## Features
- **Regular User Menu:**
  - Search for matching pets based on various criteria through inputs from the user
  - Display all available pets
  - Adopt a pet from the list of matching pets 

- **Admin Menu:**
  - Add a new pet to the shelter's database
  - Remove a pet from the shelter's database
  - Display all pets in the shelter
  - Switch to regular user mode

## Files
- `main.c`: Contains the main function and menu logic for the program.
- `pet_data.txt`: Stores pet information persistently.

## How to Use
1. **Compile the Program:**
   Use a C compiler to compile the source code. For example, with `gcc`:
   ```sh
   gcc main.c -o PetPair
