#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(void) {
	printf("Content-Type:text/html\n\n");

	printf("<!DOCTYPE html><html lang=\"en-US\"><head><title>Blue Room</title><meta charset=\"utf-8\"><style>.right{float: right;margin-right: 40%%;}.left{float: left;margin-left: 40%%;}</style></head><body><h1 style=\"font-family: verdana; font-size: 200%%; text-align: center;\" >Welcome to the Blue Room</h1><p><img title=\"Room\" src=\"monster.jpg\" height=\"40%%\" width=\"40%%\" style=\"float: left;margin-left: 40px; margin-right: 40px\"><textarea readonly rows=\"18\" cols=\"80\">");

	char array[128];
  int length = atoi(getenv("CONTENT_LENGTH")) + 1;
  fgets(array, length, stdin);

  //parse input from player
  int i = 0, j = 0, playerManna, playerGold, playerHealth, monsterHealth;
  char command[16], number1[8], number2[8], number5[8], number6[8];
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
  for(; i < length && array[i] != '&'; i++, j++) {
    number2[j] = array[i];
  }
  number2[j] = '\0';
  playerGold = atoi(number2);

  j = 0;
  for(; i < length && array[i] != '='; i++);
  i++;
  for(; i < length && array[i] != '%'; i++, j++) {
    number5[j] = array[i];
  }
  number1[j] = '\0';
  playerHealth = atoi(number5);
  j = 0;
  i+=3;
  for(; i < length; i++, j++) {
    number6[j] = array[i];
  }
  number6[j] = '\0';
  monsterHealth = atoi(number6);

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

  time_t t;

  srand((unsigned) time(&t));


  int monsterHitNum = (rand() % 10);
	  int monsterWillHit;

	  if (monsterHitNum < 5) {
		  monsterWillHit = 0;
	  } else {
		  monsterWillHit = 1;
	  }

	int userHitNum = (rand() % 10);;
	  int userWillHit;

	  if (userHitNum < 3) {
		  userWillHit = 0;
	  } else {
		  userWillHit = 1;
	  }

  // Apply function based on commmand.


	if (strncasecmp(command, "quit", 4) == 0) {
		printf("I suppose we can't all be heroes. Come back when you feel more courageous.\n");
		printf("Type a command to continue.\n\nCommands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
	  printf("</textarea><form action=\"room.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center> <form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"North\"></form></center><span class=\"left\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"West\"></form></span><span class=\"right\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"East\"></form></span></br><center><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"South\"></form></center></body></html>", playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold);
	}
	else {
		if (strncasecmp(command, "sword", 5) == 0) {
			printf("You swing your mighty sword!\n");
			if(userWillHit == 1) {
				printf("Your sword strikes the Cavernthing and makes it shout!\n");
				monsterHealth--;
			} else {
				printf("With unexpected swiftness, the beast evades your attack.\n");
			}
			if (monsterWillHit == 1) {
				printf("Before you can brace yourself, the monster manages to land a blow.\n");
				playerHealth--;
			} else {
				printf("The monster lunges, but somehow it just misses you.\n");
			}
	    }
		else if (strncasecmp(command, "dodge", 5) == 0) {
			printf("The Cavernthing charges you, but with impressive grace you leap right over it!\n");
	    }
		else {
		    printf("Please enter a valid input\n");
	    }

  // Here we check to see if you won.
    if (monsterHealth == 0) {
      printf("\nYou slayed the beast! Take home your spoils and get some rest.\n");
      printf("This room has %d manna and %d gold.\nYou can select a total of 5 manna and gold combined.\nType how much manna you would like.\n", roomManna, roomGold);
      printf("</textarea><form action=\"gameGold.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"game\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center></body></html>", playerManna, playerGold, playerHealth, monsterHealth);
    }
    else if (playerHealth == 0) {
      printf("\nYou died! Shoot!\n");
      printf("Type a command to continue.\n\nCommands:\n  DROP n - drop n gold and get n/2 manna\n  PLAY - play game\n  EXIT - leave game\n  REFRESH - refresh page\n");
      printf("</textarea><form action=\"room.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center> <form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"North\"></form></center><span class=\"left\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"url\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"West\"></form></span><span class=\"right\"><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"East\"></form></span></br><center><form action=\"http://cs.mcgill.ca/~sbeard3/cgi-bin/transporter.py\" method=\"post\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"URL\" value=\"http://cgi.cs.mcgill.ca/~htu6/Room\"><input type=\"submit\" value=\"South\"></form></center></body></html>", playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold, playerManna, playerGold);
    } else {
		  printf("\nYou have %d health and the monster has %d health.\n", playerHealth, monsterHealth);
		  printf("\nQuickly! Either swing your SWORD or DODGE the beast's attack!\n");
		  printf("You can type QUIT at any time to flee.\n");
		  printf("</textarea><form action=\"game.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"%d,%d\"><input type=\"hidden\" name=\"game\" value=\"%d,%d\"><input type=\"submit\" value=\"Submit\"></form></p></br></br></br><center></body></html>", playerManna, playerGold, playerHealth, monsterHealth);
	   }
  }

	FILE *resources1 = fopen("resources.csv", "w");
	fprintf(resources1, "%d,%d,%d", roomManna, roomGold, 1);
	fclose(resources1);

  return 0;
}

