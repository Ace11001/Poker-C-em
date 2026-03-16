#ifndef TEXTCOLOR_H
#define TEXTCOLOR_H

#define BLUE "\033[34m" // 0
#define RED "\e[0;31m" // 1
#define RESET "\033[0m"

void ColorfulPrintf(char* str,int colorChoice);

#endif