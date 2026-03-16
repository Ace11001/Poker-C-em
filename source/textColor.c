#include <stdio.h>
#define BLUE "\033[34m" //0
#define RED "\e[0;31m" //1
#define RESET "\033[0m"

void ColorfulPrintf(char* str,int colorChoice){
    switch(colorChoice){
        case 0:
            printf(BLUE"%s",str);
            printf(RESET);        
            break;
        case 1:
            printf(RED"%s",str);
            printf(RESET);        
            break;
        //more colors to be added
        default:
            printf("%s",str);
    }
}