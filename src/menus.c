#include "menus.h"
#include "string.h"

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

IntTree_t* CategoryMenu(IntTree_t* CategoryPointer, char** DisplayLabel){
    int i;
    int userSelection;
    IntTree_t* DisplayTree;
    
    while (1){
        system(CLEAR);
        printf("%s\n\n", labels[CatalogueTile]);

        drawLine(23);
        DisplayTree = CategoryPointer;
        i = 0;
        while (DisplayTree != NULL){
            i++;
            printf("// %d) %s //\n", i, DisplayLabel[DisplayTree->Data]);
            DisplayTree = DisplayTree->LeftChild;
        }
        drawLine(23);
        
        printf("\n%s", labels[CatalogueSubCategorySelect]);
        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= i))){
            return GetItemInLeftTree(CategoryPointer, userSelection - 1);
            break;
        }else{
            clear();
        }
    }
}

void BuyMenu(int ItemToBuy){ // Billing Process

    system(CLEAR);
    printf("%s\n", labels[BuyMenuTitle]);

    printf("Selected Item : \n");
    printf("%d // %s %s //\n", ItemToBuy, Catalogue[ItemToBuy].MarketName, Catalogue[ItemToBuy].CommunName);
    while(1);
};

void* CatalogueMenu(){
    int i;
    int userSelection;

    IntTree_t* CategoryPointer;
    IntTree_t* SubCategoryPointer;

    ArticleList_t* DisplayList;

    CategoryPointer = CategoryMenu(CategorisedCatalogue, CategoryLabel);
    SubCategoryPointer = CategoryMenu(CategoryPointer->RightChild, SubCategoryLabel);

    while (1){
        system(CLEAR);
        printf("%s\n\n", labels[CatalogueTile]);
        //printf(">> %s / %s / ?\n\n", CategoryLabel[Category], SubCategoryLabel[SubCategory]);

        drawLine(89);
        printf("// N° // ArticleCode // Brand // Product // Serial Number // Relevent Date // Quantity //\n");
        DisplayList = (ArticleList_t*)(SubCategoryPointer->RightChild);
        i = 0;
        while (DisplayList != NULL){
            i++;
            printf("// %d) // %s // %s // %s %s // %s // %s // %d //\n", i, 
            DisplayList->Item->ArticleCode, DisplayList->Item->Brand, DisplayList->Item->CommunName,
            DisplayList->Item->MarketName, DisplayList->Item->SerialNumber, "DATE", DisplayList->Item->Quantity);

            DisplayList = DisplayList->next;
        }
        drawLine(89);
        
        printf("\n%s", labels[CatalogueItemSelect]);
        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= i))){
            DisplayList = GetItemFromArticleList((ArticleList_t*)(SubCategoryPointer->RightChild), userSelection - 1);
            break;
        }else{
            clear();
        }
    }

    if (getCartValue() + DisplayList->Item->Price <= CART_MAX_VALUE){
        if (DisplayList->Item->Quantity > 0){
            (DisplayList->Item->Quantity)--;
            AddArticleToCart(DisplayList->Item);
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

    mode = 0;
    while(1){

        // Display    
        system(CLEAR);
        printf("%s\n", labels[CartTile]);
        DisplayCartContent();
        printf("\n");


        switch (mode){
            case 0:
            for (i = CartMenuOptionsFirst; i <= CartMenuOptionsLast; i++){
                printf("%s\n", labels[i]);
            }
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
                printf("%s\n", labels[ModArticleSelect]);
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
                                if (getCartValue() > CART_MAX_VALUE){
                                    selectedItem->Quantity = PreviousQuantity;
                                    printf("\n%s\n", labels[CartValueMax]); 
                                    CrossSleep(1);
                                } else {
                                    // All clear
                                    (*CatalogueQuantity) -= (userSelection - PreviousQuantity);
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