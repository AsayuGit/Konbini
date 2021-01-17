#include <string.h>
#include "system.h"

ArticleList_t* Cart;
BuisnessInfo Buisness = {
    "Guud Goods", // Buisness Name
    "72  Faubourg Saint Honoré 75116", // Buisness Details
    "RCS PARIS A 818547863"  // RCS
};
History_t* ActionsHistory;

IntTree_t** AddNodeToIntTree(IntTree_t** Tree, int Data){
    while ((*Tree) != NULL){ // Search through the OptimisedDatabase
        if ((*Tree)->Data == Data){ // If the category already exists
            break; // then we stop searching
        }
        // Else we continue searching
        Tree = (IntTree_t**)&((*Tree)->LeftChild);
    }

    if ((*Tree) == NULL){ // If the category doesn't exists yet
        // We create it
        (*Tree) = (IntTree_t*)malloc(sizeof(IntTree_t));
        (*Tree)->Data = Data;
        (*Tree)->LeftChild = NULL;
        (*Tree)->RightChild = NULL;
    }
    return Tree;
}

ArticleList_t** AddItemToArticleList(ArticleList_t** ArticleList, Article* Item){
    while ((*ArticleList) != NULL){ // Search for a free spot
        ArticleList = &((*ArticleList)->next);
    }
    (*ArticleList) = (ArticleList_t*)malloc(sizeof(ArticleList_t));
    (*ArticleList)->Item = Item;
    (*ArticleList)->Quantity = Item->Quantity; // Ajustements needed
    (*ArticleList)->next = NULL;

    return ArticleList;
}

void InitCatalogue(IntTree_t** OptimizedDatabase, Article* Database){
    int i;
    IntTree_t** MainCategoryPointer;
    IntTree_t** SubCategoryPointer;

    for (i = 0; i < CATALOGUE_SIZE; i++){ // For each article in the database
        
        // If the category doesn't exists -> Create it
        MainCategoryPointer = AddNodeToIntTree(OptimizedDatabase, Catalogue[i].MainCategory);
        // If the sub category doesn't exists -> Cteate it
        SubCategoryPointer = AddNodeToIntTree((IntTree_t**)&((*MainCategoryPointer)->RightChild), Catalogue[i].SubCategory);

        // Then we add it to the corresponding article list
        AddItemToArticleList((ArticleList_t**)&((*SubCategoryPointer)->RightChild), &(Catalogue[i]));
    }
}

void init(){ // Init Cart and Init Categorry list
    Cart = NULL;
    CategorisedCatalogue = NULL;
    ActionsHistory = NULL;

    InitCatalogue(&CategorisedCatalogue, Catalogue);
}

ArticleList_t* GetItemFromArticleList(ArticleList_t* List, int ArticleID){
    int i;

    for (i = 0; i < ArticleID; i++){
        if (List == NULL){
            break;
        }else{
            List = List->next;
        }
    }

    return List;
}

ArticleList_t* SearchArticleInCart(Article* ArticleRef){
    ArticleList_t* CartRef;

    CartRef = Cart;
    while (CartRef != NULL){ // Search for a free spot
        if (CartRef->Item == ArticleRef){
            return CartRef;
        }else{
            CartRef = CartRef->next;
        }
    }
    return NULL;
}

ArticleList_t* GetItemFromCart(int ArticleID){
    ArticleList_t* CartRef;
    int i;

    CartRef = Cart;
    for (i = 0; i < ArticleID; i++){
        if (CartRef == NULL){
            break;
        }else{
            CartRef = CartRef->next;
        }
    }
    
    return CartRef;
}

void AddArticleToCart(Article* ArticleRef){
    ArticleList_t** CartRef;
    ArticleList_t* SearchRef;

    CartRef = &Cart;

    SearchRef = SearchArticleInCart(ArticleRef);
    if (SearchRef != NULL){
        SearchRef->Quantity++;
    }else{
        // If the Item doesn't exists in the list
        while ((*CartRef) != NULL){ // Search for a free spot
            CartRef = &((*CartRef)->next);
        }
        (*CartRef) = (ArticleList_t*)malloc(sizeof(ArticleList_t));
        (*CartRef)->Item = ArticleRef;
        (*CartRef)->Quantity = 1;
        (*CartRef)->next = NULL;
    }
}

void DeleteArticleFromCart(ArticleList_t* ArticleRef){
    ArticleList_t* PrevRef;
    ArticleList_t* SearchRef;
    
    SearchRef = Cart;
    if (SearchRef == ArticleRef){ // If it's the first Item
        Cart = Cart->next;
        FreeArticlelistItem(SearchRef);
    } else {
        PrevRef = Cart;
        SearchRef = Cart->next;

        while (SearchRef != NULL){
            if (SearchRef == ArticleRef){
                break;
            }
            PrevRef = SearchRef;
            SearchRef = SearchRef->next;
        }

        PrevRef->next = SearchRef->next;
        FreeArticlelistItem(SearchRef);
    }
}

int DisplayArticleListContent(int x, int y, ArticleList_t* List, char CartMode, int* returnWidth, int* returnHeight){
    int i;
    int textX, textY;
    int CurrentPrice;
    double Total;
    char Buffer[100];
    int TempX;
    
    StringList_t* NumberStringList;
    StringList_t* ArticleCodeStringList;
    StringList_t* BrandStringList;
    StringList_t* ProductStringList;
    StringList_t* SerialStringList;
    StringList_t* DateStringList;
    StringList_t* QuantityStringList;
    StringList_t* PriceStringList;
    
    NumberStringList = NULL;
    ArticleCodeStringList = NULL;
    BrandStringList = NULL;
    ProductStringList = NULL;
    SerialStringList = NULL;
    DateStringList = NULL;
    QuantityStringList = NULL;
    PriceStringList = NULL;

    AddElementToStringList(&NumberStringList, "N°");
    AddElementToStringList(&NumberStringList, "");

    AddElementToStringList(&ArticleCodeStringList, "Article Code");
    AddElementToStringList(&ArticleCodeStringList, "");

    AddElementToStringList(&BrandStringList, "Brand");
    AddElementToStringList(&BrandStringList, "");

    AddElementToStringList(&ProductStringList, "Product");
    AddElementToStringList(&ProductStringList, "");

    AddElementToStringList(&SerialStringList, "Serial Number");
    AddElementToStringList(&SerialStringList, "");
    
    AddElementToStringList(&DateStringList, "Relevent Date");
    AddElementToStringList(&DateStringList, "");
    
    AddElementToStringList(&QuantityStringList, "Quantity");
    AddElementToStringList(&QuantityStringList, "");
    
    AddElementToStringList(&PriceStringList, "Price");
    AddElementToStringList(&PriceStringList, "");

    i = 1;
    while (List != NULL){
        snprintf(Buffer, 100, "%d)", i);
        AddElementToStringList(&NumberStringList, Buffer);
        AddElementToStringList(&ArticleCodeStringList, List->Item->ArticleCode);
        AddElementToStringList(&BrandStringList, List->Item->Brand);
        snprintf(Buffer, 100, "%s %s", List->Item->CommunName, List->Item->MarketName);
        AddElementToStringList(&ProductStringList, Buffer);
        AddElementToStringList(&SerialStringList, List->Item->SerialNumber);
        snprintf(Buffer, 100, "%02d/%02d/%04d", List->Item->ManifacturingDate.Day, List->Item->ManifacturingDate.Month, List->Item->ManifacturingDate.Year);
        AddElementToStringList(&DateStringList, Buffer);
        if (CartMode){
            snprintf(Buffer, 100, "%d", List->Quantity);
        } else {
            snprintf(Buffer, 100, "%d", List->Item->Quantity);
        }
        
        AddElementToStringList(&QuantityStringList, Buffer);
        
        if (CartMode){
            CurrentPrice = List->Item->Price * List->Quantity;
            snprintf(Buffer, 100, "%.2lf $", CurrentPrice / 100.0);
            Total += CurrentPrice  + (CurrentPrice * List->Item->TVA / 100.0) / 100.0;
        } else {
            snprintf(Buffer, 100, "%.2lf $", List->Item->Price / 100.0);
        }
        
        AddElementToStringList(&PriceStringList, Buffer);
        List = List->next;
        i++;
    }
    DrawStringBoxAt(x, y, NumberStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, ArticleCodeStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, BrandStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, ProductStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, SerialStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, DateStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, QuantityStringList, &TempX, NULL); x+= TempX - 1;
    DrawStringBoxAt(x, y, PriceStringList, &TempX, returnHeight); x+= TempX - 1;

    FreeStringList(&NumberStringList);
    FreeStringList(&ArticleCodeStringList);
    FreeStringList(&BrandStringList);
    FreeStringList(&ProductStringList);
    FreeStringList(&SerialStringList);
    FreeStringList(&DateStringList);
    FreeStringList(&QuantityStringList);
    FreeStringList(&PriceStringList);

    if (CartMode)
        printf("\n\n%s%.2lf $ TTC\n", labels[CartTotal], (double)(Total / 100.0));

    if (returnWidth)
        (*returnWidth) = x + 2;

    return i - 1;
}


int DisplayCartContent(int x, int y, int* returnWith, int* returnHeight){
    return DisplayArticleListContent(x, y, Cart, 1, returnWith, returnHeight);
}

int GetTTCArticleListPrice(ArticleList_t* CartRef){
    double CurrentPrice;
    int Total;
    
    Total = 0;
    CartRef = Cart;
    while (CartRef != NULL){
        CurrentPrice = CartRef->Item->Price * CartRef->Quantity;
        Total += CurrentPrice  + (CurrentPrice * CartRef->Item->TVA / 100.0) / 100.0;
        CartRef = CartRef->next;
    }
    return Total;
}

int GetTTCCartPrice(){
    return GetTTCArticleListPrice(Cart);
}

int getNbItemInCart(){
    int NbOfItems;
    ArticleList_t* CartRef;

    NbOfItems = 0;
    CartRef = Cart;
    while (CartRef != NULL){
        NbOfItems++;
        CartRef = CartRef->next;
    }

    return NbOfItems;
}

void FreeArticlelistItem(ArticleList_t* ArticleRef){ // Just in case
    free(ArticleRef);
}

void FreeArticleList(ArticleList_t* ArticleList){
    if (ArticleList != NULL){
        FreeArticleList(ArticleList->next);
        free(ArticleList);
    }
}

void FreeCart(){
    FreeArticleList(Cart);
    Cart = NULL;
}

// History Management

History_t** AddActionToHistory(labelsID Message, char* Arg1, char* Arg2){
    History_t** HistoryRef;

    HistoryRef = &ActionsHistory;
    while ((*HistoryRef) != NULL){ // Search for a free spot in the history linked list
        HistoryRef = &((*HistoryRef)->next);
    }

    (*HistoryRef) = (History_t*)malloc(sizeof(History_t)); // We allocate memory for a new element;
    (*HistoryRef)->LabelID = Message;

    if (Arg1){
        (*HistoryRef)->Data1 = (char*)malloc(sizeof(char)*(strlen(Arg1)+1));
        strcpy((*HistoryRef)->Data1, Arg1);
    } else {
        (*HistoryRef)->Data1 = NULL;
    }

    if (Arg2){
        (*HistoryRef)->Data2 = (char*)malloc(sizeof(char)*(strlen(Arg2)+1));
        strcpy((*HistoryRef)->Data2, Arg2);
    } else {
        (*HistoryRef)->Data2 = NULL;
    }

    return HistoryRef;
}

History_t* GetHistoryElementByIndex(int index){
    int i;
    History_t* HistoryRef;

    HistoryRef = ActionsHistory;
    for (i = 0; i < index; i++){
        HistoryRef = HistoryRef->next;
    }
    
    return HistoryRef;
}

void DisplayHistory(int x, int y, int start, int end){
    History_t* HistoryRef;
    int i;
    int maxWidth, newWidth;
    int textX, textY;
    char Buffer[100];
    
    maxWidth = 0;
    textX = x + 2;
    textY = y + 2;
    HistoryRef = GetHistoryElementByIndex(start);

    for (i = start; i < end; i++){
        if (HistoryRef == NULL){
            break;
        }
        SetCursorAt(textX, textY);
        snprintf(Buffer, 100, labels[HistoryRef->LabelID], HistoryRef->Data1, HistoryRef->Data2);
        printf("%s\n", Buffer);
        newWidth = strlen(Buffer);
        if (newWidth > maxWidth){
            maxWidth = newWidth;
        }
        HistoryRef = HistoryRef->next;
        textY++;
    }
    if (i == start){ // If the history is empty
        SetCursorAt(textX, textY);
        snprintf(Buffer, 100, labels[NOHistory]);
        maxWidth = strlen(Buffer);
        printf("%s\n", Buffer);
        i++;
    }
    DrawBoxAt(x, y, maxWidth + 4, i - start + 4);
}

void FreeHistoryObject(History_t* HistoryObject){
    if (HistoryObject != NULL){
        FreeHistoryObject(HistoryObject->next);
        if (HistoryObject->Data1){
            free(HistoryObject->Data1);
        }
        if (HistoryObject->Data2){
            free(HistoryObject->Data2);
        }
        free(HistoryObject);
    }
}

void FreeHistory(){
    FreeHistoryObject(ActionsHistory);
    ActionsHistory = NULL;
}