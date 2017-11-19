#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
  printf("Content-Type:text/html\n\n");

  printf("<!DOCTYPE html><html lang=\"en-US\"><head><title>Blue Room</title><meta charset=\"utf-8\"><style>.right{float: right;margin-right: 40%%;}.left{float: left;margin-left: 40%%;}</style></head><body><h1 style=\"font-family: verdana; font-size: 200%%; text-align: center;\" >Welcome to the Blue Room</h1><p><img title=\"Room\" src=\"room.jpg\" height=\"40%%\" width=\"40%%\" style=\"float: left;margin-left: 40px; margin-right: 40px\"><textarea readonly rows=\"18\" cols=\"80\">");

  char array[128];
  int length = atoi(getenv("CONTENT_LENGTH")) + 1;
  fgets(array, length, stdin);

  //parse input from player
  int i = 0, j = 0, input, playerManna, playerGold;
  char number[8], number1[8], number2[8];
  for(; i < length && array[i] != '='; i++);
  i++;
  for(; i < length && array[i] != '&'; i++, j++) {
    number[j] = array[i];
  }
  number[j] = '\0';
  input = atoi(number);
  j = 0;
  for(; i < length && array[i] != '='; i++);
  i++;
  for(; i < length && array[i] != '%'; i++, j++) {
    number1[j] = array[i];
  }
  number1[j] = '\0';
  playerManna = atoi(number1);
  j = 0;
  i+=3;
  for(; i < length; i++, j++) {
    number2[j] = array[i];
  }
  number2[j] = '\0';
  playerGold = atoi(number2);

  //parse room resources
  char array1[16], number3[8], number4[8];
  int length1;
  int roomManna, roomGold;
  FILE *resources = fopen("resources.csv", "r");
  fscanf(resources, "%s", array1);
  length1 = sizeof(array1);
  i = j = 0;
  for(; i < length1 && array1[i] != ','; i++, j++) {
    number3[j] = array1[i];
  }
  number3[j] = '\0';
  roomManna = atoi(number3);
  j = 0;
  i++;
  for(; i < length1; i++, j++) {
    number4[j] = array1[i];
  }
  number4[j] = '\0';
  roomGold = atoi(number4);
  fclose(resources);

  //give player gold and manna

  if (roomManna + roomGold <= 5) { //if the room doesn't have enough resources, give the player what is left
    printf("This room does not have many resources. You can have what is left.\n");
    printf("You got %d manna and %d.\n", roomManna, roomGold);
    playerManna += roomManna;
    playerGold += roomGold;
    roomManna = 0;
    roomGold = 0;
  }
  else { //check that the room resources have enough to give
    if (input > roomManna) {
      if (input <= 5) {
        printf("Sorry the room does not have enough resources.\n");
        input = roomManna;
      }
      else {
        printf("Sorry you can't have that much manna.\n");
        input = 5;
      }
    }
    else if (5-input > roomGold && input >= 0) {
      printf("Sorry the room does not have enough resources.\n");
      input = 5 - roomGold;
    }

    if (input <= 5 && input >= 0){
      printf("You got %d manna and %d gold.\n", input, 5 - input);
      playerManna += input;
      playerGold += 5 - input;
      roomManna -= input;
      roomGold -= 5 - input;
      //give user manna and gold
    }
    else { //if user enters a number that isn't within the range, give them 5 manna and no gold
      printf("Your input is invalid.\n");
      printf("You got %d manna and %d gold.\n", 5, 0);
      roomManna -= 5;
      roomGold -= 0;
      //give user manna and gold
    }
  }

  printf("Type a command to continue.\n\nCommands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
  printf("</textarea><form action=\"room.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center> <form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"North\"></form></center><span class=\"left\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"West\"></form></span><span class=\"right\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"East\"></form></span></br><center><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"South\"></form></center></body></html>", playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold);

  FILE *resources1 = fopen("resources.csv", "w");
  fprintf(resources1, "%d,%d,%d", roomManna, roomGold, 1);
  fclose(resources1);

  return 0;
}

