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

int CategoryMenu(){
    int i;
    int userSelection;
    IntList_t* CategoryList;
    IntList_t* DisplayList;
    
    CategoryList = NULL;

    // We build a list of every category with available Items
    for (i = 0; i < CATALOGUE_SIZE; i++){
        if ((SearchDataInList(CategoryList, Catalogue[i].MainCategory) == NULL) && (Catalogue[i].Quantity > 0)){
            AddElementToIntList(&CategoryList, Catalogue[i].MainCategory);
        }
    }
    if (!CategoryList){ // If No Item available
        return -1;
    }

    while (1){
        system(CLEAR);
        printf("%s\n", labels[CatalogueTile]);
        printf(">> ?\n\n");

        drawLine(23);
        DisplayList = CategoryList;
        i = 0;
        while (DisplayList != NULL){
            printf("// %d) %s //\n", i + 1, CategoryLabel[DisplayList->Data]);
            DisplayList = DisplayList->next;
            i++;
        }
        drawLine(23);
        
        printf("\n%s", labels[CatalogueCategorySelect]);

        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= NbOfCategories))){
            DisplayList = GetItemInList(CategoryList, userSelection - 1);
            userSelection = DisplayList->Data;
            free(CategoryList);
            return userSelection;
            break;
        }else{
            clear();
        }
    }

    return 0;
}

int SubCategoryMenu(CategoryID CategoryID){
    int i;
    int userSelection;
    IntList_t* SubCategoryList;
    IntList_t* DisplayList;

    SubCategoryList = NULL;

    // We build a list of every item meeting the main category
    for (i = 0; i < CATALOGUE_SIZE; i++){
        if ((Catalogue[i].MainCategory == CategoryID) && (Catalogue[i].Quantity > 0)) {
            if (SearchDataInList(SubCategoryList, Catalogue[i].SubCategory) == NULL){
                AddElementToIntList(&SubCategoryList, Catalogue[i].SubCategory);
            }
        }
    }
    if (!SubCategoryList){ // If No item match the sub category
        return -1;
    }
    
    while (1){
        system(CLEAR);
        printf("%s\n", labels[CatalogueTile]);
        printf(">> %s / ?\n\n", CategoryLabel[CategoryID]);

        drawLine(23);
        DisplayList = SubCategoryList;
        i = 0;
        while (DisplayList != NULL){
            i++;
            printf("// %d) %s //\n", i, SubCategoryLabel[DisplayList->Data]);
            DisplayList = DisplayList->next;
        }
        drawLine(23);
        
        printf("\n%s", labels[CatalogueSubCategorySelect]);
        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= i))){
            DisplayList = GetItemInList(SubCategoryList, userSelection - 1);
            userSelection = DisplayList->Data;
            free(SubCategoryList);
            return userSelection;
            break;
        }else{
            clear();
        }
    }
}

void BuyMenu(int ItemToBuy){

    system(CLEAR);
    printf("%s\n", labels[BuyMenuTitle]);

    printf("Selected Item : \n");
    printf("%d // %s %s //\n", ItemToBuy, Catalogue[ItemToBuy].MarketName, Catalogue[ItemToBuy].CommunName);
    while(1);
};

void* CatalogueMenu(){
    int i;
    int userSelection;

    int Category;
    int SubCategory;

    IntList_t* SelectedItemList;
    IntList_t* DisplayList;

    Category = CategoryMenu();
    if (CategoryMenu){
        SubCategory = SubCategoryMenu(Category);
    }

    // We build a list of every item meeting the main and secondary category
    SelectedItemList = NULL;
    for (i = 0; i < CATALOGUE_SIZE; i++){
        if ((Catalogue[i].MainCategory == Category) && (Catalogue[i].SubCategory == SubCategory)){
            AddElementToIntList(&SelectedItemList, i);
        }
    }
    if (!SelectedItemList){ // If No item match
        return MainMenu;
    }

    while (1){
        system(CLEAR);
        printf("%s\n", labels[CatalogueTile]);
        printf(">> %s / %s / ?\n\n", CategoryLabel[Category], SubCategoryLabel[SubCategory]);

        drawLine(89);
        printf("// N° // ArticleCode // Brand // Product // Serial Number // Relevent Date // Quantity //\n");
        DisplayList = SelectedItemList;
        i = 0;
        while (DisplayList != NULL){
            i++;
            printf("// %d) // %s // %s // %s %s // %s // %s // %d //\n", i, 
            Catalogue[DisplayList->Data].ArticleCode, Catalogue[DisplayList->Data].Brand, Catalogue[DisplayList->Data].CommunName,
            Catalogue[DisplayList->Data].MarketName, Catalogue[DisplayList->Data].SerialNumber, "DATE", Catalogue[DisplayList->Data].Quantity);

            DisplayList = DisplayList->next;
        }
        drawLine(89);
        
        printf("\n%s", labels[CatalogueItemSelect]);
        // SecureInput
        if ((scanf("%d", &userSelection) == 1) && ((userSelection >= 1) && (userSelection <= i))){
            DisplayList = GetItemInList(SelectedItemList, userSelection - 1);
            userSelection = DisplayList->Data;
            free(SelectedItemList);
            break;
        }else{
            clear();
        }
    }

    if (getCartValue() + Catalogue[userSelection].Price <= CART_MAX_VALUE){
        AddArticleToCart(&(Catalogue[userSelection]));
        Catalogue[userSelection].Quantity--;
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