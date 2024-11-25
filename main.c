#include "project.h"
#include <stdio.h>

int main(void) {
    int mainOption;
    while (1) {
        printf("\nWelcome to Hotel Kashyyyk! Please choose an option:\n");
        printf("1. Check In\n2. Check Out\n3. Book a Table\n4. Quit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &mainOption);
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
    };
    return 0;
}