#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PETS_PER_SPECIES 100
#define NUM_SHELTERS 3
#define ADMIN_PASSWORD "12345"
#define FILENAME "pet_data.txt"

struct Pet {
    char name[50];
    char species[20];
    char breed[20];
    char activity[20];
    char size[10];
    int age;
    int shelterNumber; // Added shelter number
};

struct Shelter {
    struct Pet pets[MAX_PETS_PER_SPECIES];
    int numPets;
};

void regularUserMenu(struct Shelter shelters[], int numShelters);
void adminMenu(struct Shelter shelters[], int numShelters);
void displayMatchingPets(struct Shelter shelters[], int numShelters);
void displayAllPets(struct Shelter shelters[], int numShelters);
void addPet(struct Shelter shelters[], int numShelters); // Updated function signature
void removePet(struct Shelter shelters[], int numShelters); // Updated function signature
void savePetData(struct Shelter shelters[], int numShelters);
void loadPetData(struct Shelter shelters[], int numShelters);
void clearInputBuffer();
void switchToUser(struct Shelter shelters[], int numShelters);
void strToLower(char *str);
void adoptPet(struct Shelter shelters[], int numShelters);

int main() {
    struct Shelter shelters[NUM_SHELTERS];

    loadPetData(shelters, NUM_SHELTERS);

    char userType;
    printf("Welcome to PetPair!\n");
    printf("Are you a regular user (U) or an admin (A)? ");
    scanf(" %c", &userType);

    if (userType == 'U' || userType == 'u') {
        regularUserMenu(shelters, NUM_SHELTERS);
    } else if (userType == 'A' || userType == 'a') {
        char password[20];
        printf("Enter password: ");
        scanf("%s", password);
        clearInputBuffer();
        if (strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("Correct password entered. Entering admin menu.\n");
            adminMenu(shelters, NUM_SHELTERS);
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }

    savePetData(shelters, NUM_SHELTERS);

    return 0;
}

void regularUserMenu(struct Shelter shelters[], int numShelters) {
    int choice;
    do {
        printf("\nRegular User Menu:\n");
        printf("1. Search for matching pets\n");
        printf("2. Display all available pets\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMatchingPets(shelters, numShelters);
                break;
            case 2:
                displayAllPets(shelters, numShelters);
                break;
            case 3:
                printf("Exiting regular user menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void displayMatchingPets(struct Shelter shelters[], int numShelters) {
    char selectedSpecies[20];
    char selectedBreed[20];
    char selectedActivity[20];
    char selectedSize[10];
    int selectedAge;

    printf("Choose a species (dog, cat, or rabbit): ");
    scanf("%s", selectedSpecies);
    printf("Choose a breed: ");
    scanf("%s", selectedBreed);
    printf("Choose an activity level: ");
    scanf("%s", selectedActivity);
    printf("Choose a size (small, medium, or large): ");
    scanf("%s", selectedSize);
    printf("Choose an age: ");
    scanf("%d", &selectedAge);

    strToLower(selectedSpecies);
    strToLower(selectedBreed);
    strToLower(selectedActivity);
    strToLower(selectedSize);

    int matchingPets = 0;
    int closestPets = 0;
    printf("Matching pets:\n");
    for (int i = 0; i < numShelters; i++) {
        for (int j = 0; j < shelters[i].numPets; j++) {
            struct Pet pet = shelters[i].pets[j];
            char petSpecies[20], petBreed[20], petActivity[20], petSize[10];
            strcpy(petSpecies, pet.species);
            strcpy(petBreed, pet.breed);
            strcpy(petActivity, pet.activity);
            strcpy(petSize, pet.size);
            strToLower(petSpecies);
            strToLower(petBreed);
            strToLower(petActivity);
            strToLower(petSize);
            if (strcmp(petSpecies, selectedSpecies) == 0 &&
                strcmp(petBreed, selectedBreed) == 0 &&
                strcmp(petActivity, selectedActivity) == 0 &&
                strcmp(petSize, selectedSize) == 0 &&
                pet.age == selectedAge) {
                printf("Shelter: %d, Name: %s, Species: %s, Breed: %s, Activity: %s, Size: %s, Age: %d\n",
                       i + 1, pet.name, pet.species, pet.breed, pet.activity, pet.size, pet.age);
                matchingPets++;
            }
            else if (strcmp(petSpecies, selectedSpecies) == 0 &&
                     strcmp(petActivity, selectedActivity) == 0) {
                printf("Closest match found:\n");
                printf("Shelter: %d, Name: %s, Species: %s, Breed: %s, Activity: %s, Size: %s, Age: %d\n",
                       i + 1, pet.name, pet.species, pet.breed, pet.activity, pet.size, pet.age);
                closestPets++;
            }
        }
    }
    if (matchingPets == 0 && closestPets == 0) {
        printf("No matching pets found.\n");
    } else {
        printf("Do you want to adopt a pet from the matching list? (Y/N): ");
        char adoptChoice;
        scanf(" %c", &adoptChoice);
        clearInputBuffer();
        if (adoptChoice == 'Y' || adoptChoice == 'y') {
            adoptPet(shelters, numShelters);
        } else {
            printf("Come back next time. Thank you!\n");
        }
    }
}

void adoptPet(struct Shelter shelters[], int numShelters) {
    char petName[50];
    printf("Enter the name of the pet you want to adopt: ");
    scanf("%s", petName);

    petName[0] = toupper(petName[0]);

    for (int i = 0; i < numShelters; i++) {
        for (int j = 0; j < shelters[i].numPets; j++) {
            char currentPetName[50];
            strcpy(currentPetName, shelters[i].pets[j].name);
            currentPetName[0] = toupper(currentPetName[0]);

            if (strcmp(currentPetName, petName) == 0) {
                printf("Thank you for adopting %s from Shelter %d!\n", shelters[i].pets[j].name, i + 1);
                for (int k = j; k < shelters[i].numPets - 1; k++) {
                    shelters[i].pets[k] = shelters[i].pets[k + 1];
                }
                shelters[i].numPets--;
                return;
            }
        }
    }
    printf("Pet not found in the database.\n");
}

void displayAllPets(struct Shelter shelters[], int numShelters) {
    printf("All available pets:\n");
    for (int i = 0; i < numShelters; i++) {
        printf("Shelter %d:\n", i + 1);
        for (int j = 0; j < shelters[i].numPets; j++) {
            struct Pet pet = shelters[i].pets[j];
            printf("Name: %s, Species: %s, Breed: %s, Activity: %s, Size: %s, Age: %d\n",
                   pet.name, pet.species, pet.breed, pet.activity, pet.size, pet.age);
        }
    }
}

void adminMenu(struct Shelter shelters[], int numShelters) {
    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. Add pet\n");
        printf("2. Remove pet\n");
        printf("3. Display all pets\n");
        printf("4. Switch to regular user\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPet(shelters, numShelters);
                break;
            case 2:
                removePet(shelters, numShelters);
                break;
            case 3:
                displayAllPets(shelters, numShelters);
                break;
            case 4:
                switchToUser(shelters, numShelters);
                break;
            case 5:
                printf("Exiting admin menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void addPet(struct Shelter shelters[], int numShelters) {
    if (numShelters == 0) {
        printf("No shelters available. Cannot add pet.\n");
        return;
    }

    printf("Choose a shelter number (1 to %d): ", numShelters);
    int shelterNumber;
    scanf("%d", &shelterNumber);
    if (shelterNumber < 1 || shelterNumber > numShelters) {
        printf("Invalid shelter number.\n");
        return;
    }

    if (shelters[shelterNumber - 1].numPets < MAX_PETS_PER_SPECIES) {
        printf("Enter name: ");
        scanf("%s", shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].name);
        printf("Enter species: ");
        scanf("%s", shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].species);
        printf("Enter breed: ");
        scanf("%s", shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].breed);
        printf("Enter activity: ");
        scanf("%s", shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].activity);
        printf("Enter size (small, medium, or large): ");
        scanf("%s", shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].size);
        printf("Enter age: ");
        scanf("%d", &shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].age);
        shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets].shelterNumber = shelterNumber;
        shelters[shelterNumber - 1].numPets++;
        printf("Pet added successfully to Shelter %d.\n", shelterNumber);
    } else {
        printf("Maximum number of pets reached for this shelter.\n");
    }
}

void removePet(struct Shelter shelters[], int numShelters) {
    if (numShelters == 0) {
        printf("No shelters available. Cannot remove pet.\n");
        return;
    }

    printf("Choose a shelter number (1 to %d): ", numShelters);
    int shelterNumber;
    scanf("%d", &shelterNumber);
    if (shelterNumber < 1 || shelterNumber > numShelters) {
        printf("Invalid shelter number.\n");
        return;
    }

    if (shelters[shelterNumber - 1].numPets > 0) {
        char nameToRemove[50];
        printf("Enter the name of the pet to remove: ");
        scanf("%s", nameToRemove);
        for (int i = 0; i < shelters[shelterNumber - 1].numPets; i++) {
            if (strcmp(shelters[shelterNumber - 1].pets[i].name, nameToRemove) == 0) {
                for (int j = i; j < shelters[shelterNumber - 1].numPets - 1; j++) {
                    shelters[shelterNumber - 1].pets[j] = shelters[shelterNumber - 1].pets[j + 1];
                }
                shelters[shelterNumber - 1].numPets--;
                printf("Pet removed successfully from Shelter %d.\n", shelterNumber);
                return;
            }
        }
        printf("Pet not found in Shelter %d.\n", shelterNumber);
    } else {
        printf("No pets to remove from Shelter %d.\n", shelterNumber);
    }
}

void savePetData(struct Shelter shelters[], int numShelters) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < numShelters; i++) {
        for (int j = 0; j < shelters[i].numPets; j++) {
            fprintf(file, "%s %s %s %s %s %d %d\n", shelters[i].pets[j].name, shelters[i].pets[j].species,
                    shelters[i].pets[j].breed, shelters[i].pets[j].activity, shelters[i].pets[j].size,
                    shelters[i].pets[j].age, shelters[i].pets[j].shelterNumber); // Added shelter number
        }
    }
    fclose(file);
}

void loadPetData(struct Shelter shelters[], int numShelters) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No existing pet data found.\n");
        return;
    }
    for (int i = 0; i < numShelters; i++) {
        shelters[i].numPets = 0;
    }
    while (!feof(file)) {
        char name[50], species[20], breed[20], activity[20], size[10];
        int age, shelterNumber; // Added shelter number
        if (fscanf(file, "%s %s %s %s %s %d %d\n", name, species, breed, activity, size, &age, &shelterNumber) != EOF) {
            struct Pet pet;
            strcpy(pet.name, name);
            strcpy(pet.species, species);
            strcpy(pet.breed, breed);
            strcpy(pet.activity, activity);
            strcpy(pet.size, size);
            pet.age = age;
            pet.shelterNumber = shelterNumber; // Added shelter number
            shelters[shelterNumber - 1].pets[shelters[shelterNumber - 1].numPets++] = pet;
        }
    }
    fclose(file);
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

void switchToUser(struct Shelter shelters[], int numShelters) {
    char choice;
    printf("Are you sure you want to switch to regular user mode? (Y/N): ");
    scanf(" %c", &choice);
    clearInputBuffer();
    if (choice == 'Y' || choice == 'y') {
        regularUserMenu(shelters, numShelters);
    }
}

void strToLower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}
