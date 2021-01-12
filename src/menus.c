#include "menus.h"
#include "string.h"
#include "unistd.h"

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
        if (SearchDataInList(CategoryList, Catalogue[i].MainCategory) == NULL){
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
        if (Catalogue[i].MainCategory == CategoryID) {
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
            printf("// %d) // %s // %s // %s %s // %s // %s // %s //\n", i, 
            Catalogue[DisplayList->Data].ArticleCode, Catalogue[DisplayList->Data].Brand, Catalogue[DisplayList->Data].CommunName,
            Catalogue[DisplayList->Data].MarketName, Catalogue[DisplayList->Data].SerialNumber, "DATE", "XXX");

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
    } else {
        printf("%s\n", labels[CartValueMax]);
        #ifdef _WIN32
            Sleep(3000);
        #else
            sleep(3);
        #endif 
    }

    return MainMenu;
}

void* CartMenu(){
    system(CLEAR);
    printf("%s\n", labels[CartTile]);

    DisplayCartContent();
    
    printf("\n%s\n", labels[ToMainMenu]);

    getchar(); // Pause
    getchar();
    
    return MainMenu;
}