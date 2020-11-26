#include "globalFunctions.h"

void SetCursorAt(int X, int Y){
    printf("\033[%d;%dH", Y, X);
}

void clear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}