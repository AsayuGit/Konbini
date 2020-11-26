#include <include.h>
#include "menus.h"

int main (int argc, char* argv[]){

    void* (*NextMenu)() = MainMenu;
    while (NextMenu != NULL){
        NextMenu = NextMenu();
    }

    return 0;
}