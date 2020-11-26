#include "menus.h"

void* MainMenu(){
    int i;
    int userSelection;

    while(1){

        // Display
        system(CLEAR);
        printf("%s\n\n", labels[MainMenuTitle]);
        for (i = MainMenuOptionsFirst; i <= MainMenuOptionsLast; i++){
            printf("%s\n", labels[i]);
        }
        
        // SecureInput
        if (scanf("%d", &userSelection) == 1){
            // Selection logic
            switch (userSelection)
            {
            case 1:
                return CatalogueMenu;
                break;

            case 2:
                return CartMenu;
                break;

            case 3:
                return NULL;
                break;
            
            default:
                break;
            }
        }else{
            clear();
        }
    }
}

void* CatalogueMenu(){
    system(CLEAR);
    printf("%s\n\n%s\n", labels[CatalogueTile], labels[CatalogueGreetings]);
    return NULL;
}

void* CartMenu(){
    system(CLEAR);
    printf("%s\n", labels[CartTile]);
    return NULL;
}

