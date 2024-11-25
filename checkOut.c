#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

void checkOut(){
  char roomNumberString[100];
  char roomCostString[100];
  int roomCosts[6] = {100, 100, 85, 75, 75, 50};
  int boardRates[3] = {20, 15, 5};
  char firstName[100];
  char lastName[100];
  int bookingIdFound = 0;
  char bookingId[30];
  char roomFileName[10];
  char currentBookingId[100];
  float totalRoomCost;
  int lengthOfStay;
  char lengthOfStayString[100];
  int roomNumber;
  int age;
  char ageString[100];
  char board[100];
  float boardPrice;
  float totalBoardPrice;
  int numberOfChildren;
  char numberOfChildrenString[100];
  int numberOfAdults;
  char numberOfAdultsString[100];
  char newspaperString[100];
  int hadNewspaper = 0;
  float totalCost;

  printf("Enter booking ID: ");
  scanf("%s", bookingId);

  for(int i = 1; i <= 6; i++) {
    sprintf(roomFileName, "room%d.txt", i);
    read(roomFileName, 10, currentBookingId);
    if (currentBookingId[strlen(currentBookingId) - 1] == '\n') {
      currentBookingId[strlen(currentBookingId) - 1] = '\0';
    }

    if (strcmp(currentBookingId, bookingId) == 0) {
      roomNumber = i;
      bookingIdFound = 1;
      break;
    };
  }
  if (bookingIdFound == 0) {
    printf("Your booking ID could not be found in our system");
  }

  read(roomFileName, 8, lengthOfStayString);
  sscanf(lengthOfStayString, "%d", &lengthOfStay);
  totalRoomCost = roomCosts[roomNumber - 1];
  totalRoomCost = totalRoomCost * lengthOfStay;
  read(roomFileName, 4, ageString);
  sscanf(ageString, "%d", &age);
  if (age > 65) {
    totalRoomCost = totalRoomCost * 0.9;
  }

  read(roomFileName, 7, board);
  if (board[strlen(board) - 1] == '\n') {
    board[strlen(board) - 1] = '\0';
  }
  if (strcmp(board, "F") == 0) {
    boardPrice = boardRates[0];
  }
  else if (strcmp(board, "H") == 0) {
    boardPrice = boardRates[1];
  }
  else {
    boardPrice = boardRates[2];
  }

  read(roomFileName, 5, numberOfAdultsString);
  read(roomFileName, 6, numberOfChildrenString);
  sscanf(numberOfAdultsString, "%d", &numberOfAdults);
  sscanf(numberOfChildrenString, "%d", &numberOfChildren);
  totalBoardPrice = (numberOfChildren * boardPrice * 0.5) + (numberOfAdults * boardPrice);

  totalCost = totalRoomCost + totalBoardPrice;

  read(roomFileName, 9, newspaperString);
  if (newspaperString[strlen(newspaperString) - 1] == '\n') {
    newspaperString[strlen(newspaperString) - 1] = '\0';
  }
  if (strcmp(newspaperString, "T") == 0) {
    totalCost = totalCost + 5.5;
    hadNewspaper = 1;
  }

  read(roomFileName, 2, firstName);
  if (firstName[strlen(firstName) - 1] == '\n') {
    firstName[strlen(firstName) - 1] = '\0';
  }
  read(roomFileName, 3, lastName);
  if (lastName[strlen(lastName) - 1] == '\n') {
    lastName[strlen(lastName) - 1] = '\0';
  }

  printf("%s %s\t\t\t\tBookingID: %s\n", firstName, lastName, currentBookingId);
  printf("Your total room cost was %f pounds for %d days stay\n", totalRoomCost, lengthOfStay);
  printf("Your total board cost was %f pounds for your %d guests\n", totalBoardPrice, numberOfAdults + numberOfChildren);
  if (hadNewspaper == 1) {
    printf("You had a newspaper costing 5.5 pounds\n");
  }
  printf("Your total bill comes to %f pounds\n", totalCost);
  printf("Hope you enjoyed your stay!");

  sprintf(roomNumberString, "%d", roomNumber);
  sprintf(roomCostString, "%d", roomCosts[roomNumber - 1]);

  writeFile(roomFileName, 1, roomNumberString);
  writeFile(roomFileName, 2, "NULL");
  writeFile(roomFileName, 3, "NULL");
  writeFile(roomFileName, 4, "NULL");
  writeFile(roomFileName, 5, "NULL");
  writeFile(roomFileName, 6, "NULL");
  writeFile(roomFileName, 7, "NULL");
  writeFile(roomFileName, 8, "NULL");
  writeFile(roomFileName, 9, "NULL");
  writeFile(roomFileName, 10, "NULL");
  writeFile(roomFileName, 11, roomCostString);
}