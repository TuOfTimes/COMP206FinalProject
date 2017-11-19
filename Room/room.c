#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void refresh() {
  printf("Hi there! Welcome to the Blue Room! Type a command to get started.\n\nCommands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
}

void play() {
  printf("This room contains a monster known as the Delirious Cavernthing. It has %d health and you have %d health.\n\n", 5, 3);
  printf("You have two actions:\n\n  SWORD will swing your sword,\n  DODGE will allow you to evade the monster's attacks.\n\n");
  printf("You can type QUIT at any time to flee.\n");
}

int main(void) { //takes a player's inventory and command as input
  printf("Content-Type:text/html\n\n");

  printf("<!DOCTYPE html><html lang=\"en-US\"><head><title>Blue Room</title><meta charset=\"utf-8\"><style>.right{float: right;margin-right: 40%%;}.left{float: left;margin-left: 40%%;}</style></head><body><h1 style=\"font-family: verdana; font-size: 200%%; text-align: center;\" >Welcome to the Blue Room</h1><p><img title=\"Room\" src=\"room.jpg\" height=\"40%%\" width=\"40%%\" style=\"float: left;margin-left: 40px; margin-right: 40px\"><textarea readonly rows=\"18\" cols=\"80\">");

  char array[128];
  int length = atoi(getenv("CONTENT_LENGTH")) + 1;
  fgets(array, length, stdin);

  //parse input from player
  int i = 0, j = 0, playerManna, playerGold;
  char command[16], number1[8], number2[8];
  for(; i < length && array[i] != '='; i++);
  i++;
  for(; i < length && array[i] != '&'; i++, j++) {
    command[j] = array[i];
  }
  command[j] = '\0';
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

  //execute function based on command
  int occupied = 1;

  if (playerGold >= 100) { //display you win page
    printf("You have reached 100 gold. You win!");
    occupied = 0;
    printf("</textarea><form action=\"win.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center></body></html>", playerManna, playerGold);
  }
  else if (playerManna <= 0) { //display you are dead page
    printf("You have 0 manna. You lost!");
    roomGold += playerGold;
    playerGold = 0;
    occupied = 0;
    printf("</textarea><form action=\"dead.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center></body></html>", playerManna, playerGold);
  }
  else if (strncasecmp(command, "exit", 4) == 0) {//do something for exit
    printf("Sorry to see you go!");
    roomGold += playerGold;
    roomManna += playerManna;
    playerGold = 0;
    playerManna = 0;
    occupied = 0;
    printf("</textarea><form action=\"dead.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center></body></html>", playerManna, playerGold);
  }
  else if (strncasecmp(command, "play", 4) == 0) {
    play();
    printf("</textarea><form action=\"game.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"game\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center></body></html>", playerManna, playerGold, 3, 5);
  }
  else {
    if (strncasecmp(command, "drop", 4) == 0) {
      int goldDrop, m=5, n=0;
      char dropped[16];
      for (; m < sizeof(command); m++, n++) {
        dropped[n] = command[m];
      }
      goldDrop = atoi(dropped);

      if (playerGold >= goldDrop) {
        playerGold -= goldDrop;
        playerManna += goldDrop/2;
        roomGold += goldDrop;
        printf("You dropped %d gold and you got %d manna.\n\n", goldDrop, goldDrop/2);
        printf("Type a command to continue.\n\nCommands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
      }
      else  {
        printf("You don't have that much gold! Please try again.\n\n");
        printf("Type a command to continue.\n\nCommands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
      }
    }
    else if (strncasecmp(command, "refresh", 7) == 0) {//do something for refresh
      refresh();
    }
    else {
      printf("Please enter a valid command!\n\n");
      printf("Commands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
    }
    //this following printf is okay. remember to change the actions of the buttons to transporter.py of other rooms

    printf("</textarea><form action=\"room.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center> <form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"North\"></form></center><span class=\"left\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"West\"></form></span><span class=\"right\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"East\"></form></span></br><center><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"South\"></form></center></body></html>", playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold);
  }

  FILE *resources1 = fopen("resources.csv", "w");
  fprintf(resources1, "%d,%d,%d", roomManna, roomGold, occupied);
  fclose(resources1);

  return 0;
}

