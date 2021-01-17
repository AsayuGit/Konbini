#include "include.h"
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "menus.h"

int main (int argc, char* argv[]){

    setlocale (LC_ALL,"");
    init(); // Init System

    void* (*NextMenu)() = MainMenu;
    while (NextMenu != NULL){
        NextMenu = NextMenu();
    }

    return 0;
}