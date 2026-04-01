#ifndef UI_H
#define UI_H
#include "game.h"
#include "evaluate.h"
//colors
#define BLUE "\033[34m" 
#define GRAY "\033[90m" 
#define YELLOW "\e[0;33m" //Chips
#define DARKBLUE "\033[0;36m"
//bot names
#define CYAN "\e[0;36m"    //0
#define MAGENTA "\e[0;35m" //1
#define GREEN "\e[0;32m"   //2
#define RED "\e[0;31m"     //3
#define BYELLOW "\e[0;93m" //4
//format
#define RESET "\033[0m"
#define ITALIC "\033[1;34;3m" 

void gotoxy(int x, int y);
void sizeDemo();
void showdownScreen();
void botWindow(int xCord, int yCord, char* botName, int chips, int bet, int colIndex, int foldedStatus, int activeStatus);
void cardPrint(int xCord,int yCord, int rank, int suit);
void drawFrame(GAME *g);
#endif