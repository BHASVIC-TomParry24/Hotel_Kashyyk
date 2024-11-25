#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "project.h"


char* readTableBooking(char fileName[15], int line, char buffer[100]) {
    read(fileName, line, buffer);
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }

    return buffer;
}

int removeOldBookings() {
    int err = 0;
    int toBeRemoved = 0;

    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    char dateString[9];
    if (date.tm_yday > 99) {
        sprintf(dateString, "%02d-%02d", date.tm_yday,  date.tm_year + 1900);
    } else if (date.tm_yday > 9) {
        sprintf(dateString, "0%02d-%02d", date.tm_yday,  date.tm_year + 1900);
    } else if (date.tm_yday <= 9) {
        sprintf(dateString, "00%02d-%02d", date.tm_yday,  date.tm_year + 1900);
    } else {
        err = 1;
        printf("An error occurred in getting the date");
    }

    char fileDate[100];
    readTableBooking("..\\tableData.txt", 1, fileDate);

    if (err == 0 && strcmp(dateString, fileDate) == 0) {
        toBeRemoved = 0;
        //printf("all good\n");
    } else if (err == 0 && strcmp(dateString, fileDate) > 0) {
        toBeRemoved = 1;
        //printf("to be removed\n");
    } else {
        err = 1;
    }

    if (err == 0 && toBeRemoved == 1) {
        char* lines[8];
        lines[0] = dateString;
        for (int i = 1; i <= 6; i++) {
            lines[i] = "T";
        }

        for (int i = 0; i <= 6; i++) {
            //printf("%s", lines[i]);
            writeFile("..\\tableData.txt", i+1, lines[i]);
        }
    }

    return err;
}

int validateTableBooking() {
    int err = 1;
    int invalidBookingID = 1;
    char rooms[6][15] = {"room1.txt", "room2.txt", "room3.txt", "room4.txt", "room5.txt", "room6.txt"};
    char bookingID[100] = "Jim12345678900";
    char* board[100];
    char roomData[100];

    fflush(stdin);
    printf("Enter booking ID: ");
    scanf("%s", &bookingID);

    for (int i = 0; i <= 5; i++) {
        readTableBooking(rooms[i], 10, roomData);
        if (strcmp(bookingID, roomData) == 0) {
            invalidBookingID = 0;
            readTableBooking(rooms[i], 7, board);
            if (strcmp(board, "F") == 0 || strcmp(board, "H") == 0) {
                err = 0;
            } else {
                printf("Sorry, you are not allowed to book dinner tables with the bed and breakfast room type.\n");
            }
            break;
        }
    }

    if (invalidBookingID == 1) {
        printf("Invalid booking ID.\n");
    }

    return err;
}

int displayAvailableTables() {
    char* tableNames[3] = {"Ednoor  ", "Naboo   ", "Tatooine"};
    char tablesAvailable[3][2][100];
    readTableBooking("..\\tableData.txt", 2, tablesAvailable[0][0]);
    readTableBooking("..\\tableData.txt", 3, tablesAvailable[0][1]);
    readTableBooking("..\\tableData.txt", 4, tablesAvailable[1][0]);
    readTableBooking("..\\tableData.txt", 5, tablesAvailable[1][1]);
    readTableBooking("..\\tableData.txt", 6, tablesAvailable[2][0]);
    readTableBooking("..\\tableData.txt", 7, tablesAvailable[2][1]);

    int noTablesAvailable = 1;

    printf("Available bookings:\n");
    for (int i = 0; i < 3; i++) {
        if (strcmp(tablesAvailable[i][0], "T") == 0 || strcmp(tablesAvailable[i][1], "T") == 0) {
            printf("%s | 7pm - %s, 9pm - %s\n", tableNames[i], tablesAvailable[i][0], tablesAvailable[i][1]);
            noTablesAvailable = 0;
        }
    }

    if (noTablesAvailable) {
        printf("No options available\n");
    }

    return noTablesAvailable;
}

int chooseTableBooking() {
    int err = 0;
    char* tableNames[3] = {"Ednoor", "Naboo", "Tatooine"};
    int choiceTable;
    int choiceTime;
    int digiCount;
    char roomData[100];

    do {
        printf("\nWhich table would you like to book (enter 1 for Ednoor, 2 for Naboo, and 3 for Tatooine)? ");
        fflush(stdin);
        digiCount = scanf("%d", &choiceTable);
        if (digiCount != 1 || choiceTable < 1 || choiceTable > 3) {
            printf("\nInvalid table choice, please enter again.\n");
        }
    } while (digiCount != 1 || choiceTable < 1 || choiceTable > 3);

    do {
        printf("\nWhich time would you like to book (7 or 9 pm)? ");
        fflush(stdin);
        digiCount = scanf("%d", &choiceTime);
        if (digiCount != 1 || (choiceTime != 7 && choiceTime != 9)) {
            printf("\nInvalid time choice, please enter again.\n");
        }
    } while (digiCount != 1 || (choiceTime != 7 && choiceTime != 9));

    int lineNumber = 2*(choiceTable);

    if (choiceTime == 9) {
        lineNumber = lineNumber + 1;
    }

    readTableBooking("..\\tableData.txt", lineNumber, roomData);
    if (strcmp(roomData, "T") == 0) {
        err = 0;
        writeFile("..\\tableData.txt", lineNumber, "F");
        printf("Booking successful! You have booked the %s table at %d pm.\n", tableNames[choiceTable-1], choiceTime);
    } else {
        printf("Table already booked\n");
    }

    return err;
}

void bookTable() {
    int err = 1;
    int valid = 0;
    if (removeOldBookings() == err) {
        printf("Unfortunately you can't book a table right now (an error occurred)\n");
    } else {
        printf("--- Welcome to table booking ---\n");
        if (validateTableBooking() == valid) {
            if (displayAvailableTables() == valid) {
                chooseTableBooking();
            }
        }
    }

    printf("--- Concluded table booking ---\n");
}