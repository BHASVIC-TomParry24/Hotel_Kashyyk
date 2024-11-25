#include "project.h"
#include <stdio.h>
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char input[10];  // Buffer to hold user input
    int mainOption;

    while (1) {
        printf("\nWelcome to Hotel Kashyyyk! Please choose an option:\n");
        printf("1. Check In\n2. Check Out\n3. Book a Table\n4. Quit Program\n");
        printf("Enter your choice: ");

        // Read the entire input line
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle EOF or input error gracefully
            printf("\nError reading input. Exiting.\n");
            break;
        }

        // Remove trailing newline character if present
        input[strcspn(input, "\n")] = '\0';

        // Check if the input is empty
        if (strlen(input) == 0) {
            printf("No input detected. Please enter a valid choice.\n");
            continue;  // Re-prompt the user
        }

        // Convert input to integer and handle invalid input
        char *endptr;
        mainOption = strtol(input, &endptr, 10);
        if (*endptr != '\0') {
            printf("Invalid input. Please enter a number between 1 and 4.\n");
            continue;  // Re-prompt the user
        }

        // Process valid input
        switch (mainOption) {
            case 1:
                checkIn();
            break;
            case 2:
                checkOut();
            break;
            case 3:
                bookTable();
            break;
            case 4:
                printf("Exiting the program. Thank you for using Hotel Kashyyyk!\n");
            return 0;
            default:
                printf("Invalid option. Please choose a number between 1 and 4.\n");
            break;
        }
    }
    return 0;
}