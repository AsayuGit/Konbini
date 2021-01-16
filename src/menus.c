#include "menus.h"
#include "string.h"
#include "time.h"

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
        
        printf("\n%s", labels[MenuSelect]);
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
                return HistoryMenu;
                break;

            case 4:
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

IntTree_t* CategoryMenu(IntTree_t* CategoryPointer, char** DisplayLabel, labelsID Question){
    int i;
    int userSelection;
    IntTree_t* DisplayTree;
    int textX, textY;
    int maxWidth, newWidth;
    char Buffer[100];

    while (1){
        textX = 3;
        textY = 5;
        maxWidth = 0;

        system(CLEAR);
        printf("%s\n\n", labels[CatalogueTile]);

        DisplayTree = CategoryPointer;
        i = 0;
        while (DisplayTree != NULL){
            i++;
            SetCursorAt(textX, textY);
            snprintf(Buffer, 100, "%d) %s\n", i, DisplayLabel[DisplayTree->Data]);
            printf("%s\n", Buffer);
            newWidth = strlen(Buffer);
            if (newWidth > maxWidth){
                maxWidth = newWidth;
            }
            DisplayTree = DisplayTree->LeftChild;
            textY++;
        }
        DrawBoxAt(0, 3, maxWidth + 4, i + 4);
        
        printf("\n\n%s", labels[Question]);
        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= i))){
            return GetItemInLeftTree(CategoryPointer, userSelection - 1);
            break;
        }else{
            clear();
        }
    }
}

void* BuyMenu(){ // Billing Process
    int userSelection;
    
    char NOM[50];
    char Prenom[50];

    char UserDetails[100];

    int maxWidth, maxHeight;
    char printNb = 0;

    time_t currentTime = time(NULL);
    srand(currentTime);
    struct tm tm = *localtime(&currentTime);

    while (1){
        system(CLEAR);
        printf(">> Veuillez entrer votre NOM et Prenom : ");

        if (scanf("%s %s", NOM, Prenom) == 2) {
            break;
        }else{
            clear();
        }
    }

    while (1){
        system(CLEAR);
        printf(">> Veuillez entrer vos coordonées : ");

        clear();
        if (fgets(UserDetails, 100, stdin) != NULL) {
            break;
        }else{
            clear();
        }
    }

    while (1){
        system(CLEAR);
        printf("%s\n", labels[BuyMenuTitle]);

        DisplayCartContent(1, 12, &maxWidth, &maxHeight);

        // Date
        SetCursorAt(maxWidth - (strlen(labels[BILLDate]) + 11), 3);
        printf("%s%02d/%02d/%02d\n", labels[BILLDate], tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

        if (printNb){
            SetCursorAt(maxWidth - (strlen(labels[BILLNb]) + 10), 4);
            printf("%s%010d", labels[BILLNb], rand());
        }

        // Buisness Side
        SetCursorAt(1, 6);
        printf("%s\n\n", labels[BILLFrom]);
        printf("%s\n%s\n%s", Buisness.BuisnessName, Buisness.BuisnessDetails, Buisness.RCS);

        // Client Side
        SetCursorAt(maxWidth - strlen(labels[BILLTo]), 6);
        printf("%s\n\n", labels[BILLTo]);
        SetCursorAt(maxWidth - (strlen(NOM) + strlen(Prenom) + 1), 8);
        printf("%s %s\n", NOM, Prenom);
        SetCursorAt(maxWidth - strlen(UserDetails), 9);
        printf("%s\n", UserDetails);

        SetCursorAt(1, 14 + maxHeight);
        printf("\n>> Est ce que tout est en ordre ?\n\n1) Oui (Procéder au paiement)\n2) Non (Retourner au menu principal)\n\n");

        if (printNb){
            printf("\n%s\n", labels[ThanksBuy]);
            CrossSleep(5);
            FreeCart();
            FreeHistory();
            return MainMenu;
        }

        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= 2))){
            switch (userSelection)
            {
            case 1:
                printNb = 1;
                break;

            case 2:
                return MainMenu;
                break;
            }
        }else{
            clear();
        }
    }
};

void* CatalogueMenu(){
    int i;
    int userSelection;

    IntTree_t* CategoryPointer;
    IntTree_t* SubCategoryPointer;

    ArticleList_t* DisplayList;

    CategoryPointer = CategoryMenu(CategorisedCatalogue, CategoryLabel, CatalogueCategorySelect);
    SubCategoryPointer = CategoryMenu(CategoryPointer->RightChild, SubCategoryLabel, CatalogueSubCategorySelect);

    while (1){
        system(CLEAR);
        printf("%s\n\n", labels[CatalogueTile]);
        //printf(">> %s / %s / ?\n\n", CategoryLabel[Category], SubCategoryLabel[SubCategory]);

        DisplayList = (ArticleList_t*)(SubCategoryPointer->RightChild);
        i = DisplayArticleListContent(1, 3, DisplayList, 0, NULL, NULL);
        
        printf("\n\n%s", labels[CatalogueItemSelect]);
        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= i))){
            DisplayList = GetItemFromArticleList((ArticleList_t*)(SubCategoryPointer->RightChild), userSelection - 1);
            break;
        }else{
            clear();
        }
    }

    if (GetTTCCartPrice() + DisplayList->Item->Price <= CART_MAX_VALUE){
        if (DisplayList->Item->Quantity > 0){
            (DisplayList->Item->Quantity)--;
            AddArticleToCart(DisplayList->Item);
            AddActionToHistory(ADDItemToCart, DisplayList->Item->MarketName, NULL);
        } else {
            printf("\n%s\n", labels[NotEnoughStock]);
            CrossSleep(1);
        }
    } else {
        printf("\n%s\n", labels[CartValueMax]);
        CrossSleep(1);
    }

    return MainMenu;
}

void* CartMenu(){
    int mode;
    ArticleList_t* selectedItem;
    int* CatalogueQuantity;
    int userSelection;
    int PreviousQuantity;
    int i;
    char buffer[10];

    mode = 0;
    while(1){

        // Display    
        system(CLEAR);
        printf("%s\n", labels[CartTile]);
        DisplayCartContent(1, 3, NULL, NULL);
        printf("\n");


        switch (mode){
            case 0:
            for (i = CartMenuOptionsFirst; i <= CartMenuOptionsLast; i++){
                printf("%s\n", labels[i]);
            }

            printf("\n%s", labels[MenuSelect]);
            // SecureInput
            if (scanf("%d", &userSelection) == 1){
                // Selection logic
                switch (userSelection)
                {
                case 1: // Mod Article
                    if (getNbItemInCart() > 0){
                        mode = 1;
                    } else {
                        printf("\n%s\n", labels[EmptyCart]);
                        CrossSleep(1);
                    }
                    break;

                case 2: // Checkout
                    if (getNbItemInCart() > 0){
                        return BuyMenu;
                    } else {
                        printf("\n%s\n", labels[EmptyCart]);
                        CrossSleep(1);
                    }
                    break;

                case 3:
                    return MainMenu;
                    break;
                }
            } else {
                clear();
            }
            break;
            
            case 1:
                printf("%s", labels[ModArticleSelect]);
                if ((scanf("%d", &userSelection) == 1) && (userSelection > 0)){
                    userSelection--;
                    if ((selectedItem = GetItemFromCart(userSelection)) == NULL){
                        printf("\n%s\n", labels[ArticleNotFound]);
                        CrossSleep(1);
                    } else {
                        mode = 2;
                    }
                }else{
                    clear();
                }
                break;
            
            case 2:
                printf("Actuellement votre panier contient %d %s\nVeuiller entrer la nouvelle quantité (0 pour supprimer l'article) : ", selectedItem->Quantity, selectedItem->Item->MarketName);
                if ((scanf("%d", &userSelection) == 1) && (userSelection >= 0)){
                    CatalogueQuantity = &(selectedItem->Item->Quantity);
                    if (userSelection == 0){ // delete article
                        (*CatalogueQuantity) += selectedItem->Quantity;
                        AddActionToHistory(DELItemFromCart, selectedItem->Item->MarketName, NULL);
                        DeleteArticleFromCart(selectedItem);
                    } else {
                        // Over stock protection
                        if (userSelection > selectedItem->Quantity){
                            if ((*CatalogueQuantity) - (userSelection - selectedItem->Quantity) < 0){
                                printf("\n%s\n", labels[NotEnoughStock]);
                                CrossSleep(1);
                            }else{
                                // Over Value protection
                                PreviousQuantity = selectedItem->Quantity;
                                selectedItem->Quantity = userSelection;
                                if (GetTTCCartPrice() > CART_MAX_VALUE){
                                    selectedItem->Quantity = PreviousQuantity;
                                    printf("\n%s\n", labels[CartValueMax]); 
                                    CrossSleep(1);
                                } else {
                                    // All clear
                                    (*CatalogueQuantity) -= (userSelection - PreviousQuantity);
                                    snprintf(buffer, 10, "%d", userSelection);
                                    AddActionToHistory(MODItemQuantity, selectedItem->Item->MarketName, buffer);
                                }
                            }
                        } else if (userSelection < selectedItem->Quantity){
                            (*CatalogueQuantity) += (selectedItem->Quantity - userSelection);
                            selectedItem->Quantity = userSelection;
                        }
                        // There's no need to do anything if the the userSelection is the same as the current selectedItem->Quantity
                    }
                    mode = 0; // return to "Main menu"
                } else {
                    clear();
                }
                break;
        }
    }
    
    return MainMenu;
}

void* HistoryMenu(){
    while (1){
        system(CLEAR);
        printf("-- History Menu --\n\n");
        
        DisplayHistory(2, 3, 0, 999);
        printf("\n\n%s", labels[ToMainMenu]);
        clear();
        getchar();

        return MainMenu;
    }
}