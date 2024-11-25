#include <stdio.h>
#include "project.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void checkIn() {
    const int fullBoardRate = 20;
    const int halfBoardRate = 15;
    const int BandBRate = 5;
    char firstName[30];
    char lastName[30];
    int lastNameLength = 0;
    char numberOfAdults[5];
    char numberOfChildren[5];
    char boardType[2] = {'\0', '\0'};
    char lengthOfStay[5];
    char newspaper[2] = {'\0', '\0'};
    char bookingId[30];
    int randomNumber;
    char randomNumberList[5];
    char age[5];
    char roomAvailable[6] = "FFFFFF";
    int chosenRoom;
    char* nullString = "NULL\n";
    const char false[1] = "F";

    for (int i = 0; i < 30; i++) {
        lastName[i] = 0;
        bookingId[i] = '\0';
        firstName[i] = '\0';
        lastName[i] = '\0';
        numberOfAdults[i] = '\0';
        numberOfChildren[i] = '\0';
        lengthOfStay[i] = '\0';
        boardType[i] = '\0';
    }

    printf("Enter your first name: ");
    scanf("%s",firstName);
    fflush(stdin);
    printf("Enter your last name: ");
    scanf("%s",lastName);
    fflush(stdin);
    do {
        printf("Enter number of adults: ");
        scanf("%s",&numberOfAdults);
        fflush(stdin);
        if (isdigit(numberOfAdults[0]) == 0 || (numberOfAdults[1] != '\0' && isdigit(numberOfAdults[1]) == 0) || (isdigit(numberOfAdults[2]) == 0 && numberOfAdults[2] != '\0')) {
            printf("Please enter a number\n");
        }
        if (numberOfAdults[2] != '\0' && isdigit(numberOfAdults[2]) != 0) {
            printf("Please enter a number less than 100\n");
        }
    } while(isdigit(numberOfAdults[0]) == 0 || (numberOfAdults[1] != '\0' && isdigit(numberOfAdults[1]) == 0) || (numberOfAdults[2] != '\0' && isdigit(numberOfAdults[2]) != 0) || isdigit(numberOfAdults[2]) == 0 && numberOfAdults[2] != '\0');
    do {
        printf("Enter number of children: ");
        scanf("%s",&numberOfChildren);
        fflush(stdin);
        if (isdigit(numberOfChildren[0]) == 0 || (numberOfChildren[1] != '\0' && isdigit(numberOfChildren[1]) == 0) || (isdigit(numberOfChildren[2]) == 0 && numberOfChildren[2] != '\0')) {
            printf("Please enter a number\n");
        }
        if (numberOfChildren[2] != '\0' && isdigit(numberOfChildren[2]) != 0) {
            printf("Please enter a number less than 100\n");
        }
    } while(isdigit(numberOfChildren[0]) == 0 || (numberOfChildren[1] != '\0' && isdigit(numberOfChildren[1]) == 0) || (numberOfChildren[2] != '\0' && isdigit(numberOfChildren[2]) != 0) || isdigit(numberOfChildren[2]) == 0 && numberOfChildren[2] != '\0');
    do {
        printf("Enter the length of your stay in days: ");
        scanf("%s",&lengthOfStay);
        fflush(stdin);
        if (isdigit(lengthOfStay[0]) == 0 || (lengthOfStay[1] != '\0' && isdigit(lengthOfStay[1]) == 0) || (isdigit(lengthOfStay[2]) == 0 && lengthOfStay[2] != '\0')) {
            printf("Please enter a number\n");
        }
        if (lengthOfStay[2] != '\0' && isdigit(lengthOfStay[2]) != 0) {
            printf("Please enter a number less than 100\n");
        }
    } while(isdigit(lengthOfStay[0]) == 0 || (lengthOfStay[1] != '\0' && isdigit(lengthOfStay[1]) == 0) || (lengthOfStay[2] != '\0' && isdigit(lengthOfStay[2]) != 0) || isdigit(lengthOfStay[2]) == 0 && lengthOfStay[2] != '\0');
    do {
        printf("Enter the board you want: Full(F) - %d, Half(H) - %d or Bed and Breakfast(B) - %d: ", fullBoardRate, halfBoardRate, BandBRate);
        scanf("%s",&boardType);
        fflush(stdin);
        if ((strcmp(boardType, "F") != 0) && (strcmp(boardType, "H") != 0) && (strcmp(boardType, "B") != 0) || boardType[1] != '\0') {
            printf("Please enter either F, H or B\n");
        }
    } while((strcmp(boardType, "F") != 0) && (strcmp(boardType, "H") != 0) && (strcmp(boardType, "B") != 0) || boardType[1] != '\0');
    do {
        printf("Would you like a newspaper? (T for yes, F for no): ");
        scanf("%s",&newspaper);
        fflush(stdin);
        if ((strcmp(newspaper, "T") != 0) && (strcmp(newspaper, "F") != 0) || newspaper[1] != '\0') {
            printf("Please enter either T or F\n");
        }
    } while((strcmp(newspaper, "T") != 0) && (strcmp(newspaper, "F") != 0) || newspaper[1] != '\0');
    do {
        printf("Enter your age: ");
        scanf("%s",&age);
        fflush(stdin);
        if (isdigit(age[0]) == 0 || (age[1] != '\0' && isdigit(age[1]) == 0) || (isdigit(age[2]) == 0 && age[2] != '\0')) {
            printf("Please enter a number\n");
        }
        if (age[2] != '\0' && isdigit(age[2]) != 0) {
            printf("Please enter a number less than 100\n");
        }
    } while(isdigit(age[0]) == 0 || (age[1] != '\0' && isdigit(age[1]) == 0) || (age[2] != '\0' && isdigit(age[2]) != 0) || isdigit(age[2]) == 0 && age[2] != '\0');

    printf("Available Rooms: \n");
    for(int i = 1; i <= 6; i++) {
        char roomFileName[10];
        sprintf(roomFileName, "room%d.txt", i);
        char fileLineContent[100];
        read(roomFileName, 10, fileLineContent);
        if (strcmp(fileLineContent, nullString) == 0) {
            roomAvailable[i - 1] = 84;
            char price[100];
            printf("Room Number %d (%s pounds)\n", i, read(roomFileName, 11, price));
        }
        else {
            roomAvailable[i - 1] = 70;
        }
    }

    do {
        printf("Enter the room number you choose: ");
        fflush(stdin);
        scanf("%d",&chosenRoom);
        if (roomAvailable[chosenRoom - 1] == false[0] || chosenRoom > 6 || chosenRoom < 1) {
            printf("Please choose an available room\n");
        }
    }
    while (roomAvailable[chosenRoom - 1] == false[0] || chosenRoom > 6 || chosenRoom < 1);

    srand(time(NULL));
    randomNumber = rand() % (9999 - 1000 + 1) + 1000;
    int digit1 = randomNumber / 1000;
    int digit2 = (randomNumber / 100) % 10;
    int digit3 = (randomNumber / 10) % 10;
    int digit4 = randomNumber % 10;
    randomNumberList[0] = '0' + digit1;
    randomNumberList[1] = '0' + digit2;
    randomNumberList[2] = '0' + digit3;
    randomNumberList[3] = '0' + digit4;
    randomNumberList[4] = '\0';
    for (int i = 0; i < 30; i++) {
        if (lastName[i] != 0) {
            bookingId[i] = lastName[i];
            lastNameLength++;
        }
    }

    for (int i = 0; i < 4; i++) {
        bookingId[i + lastNameLength] = randomNumberList[i];
    }

    char roomFileName[10];
    sprintf(roomFileName, "room%d.txt", chosenRoom);

    writeFile(roomFileName, 2, firstName);
    writeFile(roomFileName, 3, lastName);
    writeFile(roomFileName, 4, age);
    writeFile(roomFileName, 5, numberOfAdults);
    writeFile(roomFileName, 6, numberOfChildren);
    writeFile(roomFileName, 7, boardType);
    writeFile(roomFileName, 8 , lengthOfStay);
    writeFile(roomFileName, 9, newspaper);
    writeFile(roomFileName, 10, bookingId);

    printf("Your booking id is %s\n", bookingId);
}