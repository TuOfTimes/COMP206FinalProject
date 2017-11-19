#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) { //page when player wins
  printf("Content-Type:text/html\n\n");

  printf("<!DOCTYPE html><html lang=\"en-US\"><head><title>Blue Room</title><meta charset=\"utf-8\"><style>.right{float: right;margin-right: 40%%;}.left{float: left;margin-left: 40%%;}</style></head><body><h1 style=\"font-family: verdana; font-size: 200%%; text-align: center;\" >Welcome to the Blue Room</h1><p><img title=\"Room\" src=\"room.jpg\" height=\"40%%\" width=\"40%%\" style=\"float: left;margin-left: 40px; margin-right: 40px\"><textarea readonly rows=\"18\" cols=\"80\">");

  printf("Congratulation! You Won!\n");

  printf("</textarea><form action=\"win.cgi\" method=\"post\"><input type=\"text\" name=\"command\" style=\"width: 523px; align: center\"><input type=\"hidden\" name=\"inventory\" value=\"0,0\"><input type=\"submit\" value=\"Submit\"></form></p></br></br><center></body></html>");

  return 0;
}

