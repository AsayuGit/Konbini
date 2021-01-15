#include "system.h"

ArticleList_t* Cart;

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

void DisplayCartContent(){
    int i = 1;
    double CurrentPrice;
    double Total;
    ArticleList_t* CartRef;

    printf("\n");
    drawLine(89);
    printf("// N° // ArticleCode // Brand // Product // Serial Number // Relevent Date // Quantity // Price //\n");
    
    Total = 0.0;
    CartRef = Cart;
    while (CartRef != NULL){
        CurrentPrice = CartRef->Item->Price * CartRef->Quantity;
        printf("// %d) // %s // %s // %s %s // %s // %d/%d/%d // %d // %.2lf $ //\n", i, 
        CartRef->Item->ArticleCode, CartRef->Item->Brand, CartRef->Item->CommunName,
        CartRef->Item->MarketName, CartRef->Item->SerialNumber, CartRef->Item->ManifacturingDate.Day, CartRef->Item->ManifacturingDate.Month, CartRef->Item->ManifacturingDate.Year, CartRef->Quantity, CurrentPrice / 100);
        Total += CurrentPrice;
        CartRef = CartRef->next;
        i++;
    }

    drawLine(89);
    printf("\nYour cart total is : %.2lf $ HT\n", Total / 100);
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

int getCartValue(){
    int Total;
    ArticleList_t* CartRef;

    Total = 0;
    CartRef = Cart;
    while (CartRef != NULL){
        Total += CartRef->Item->Price * CartRef->Quantity;
        CartRef = CartRef->next;
    }

    return Total;
}

void FreeArticlelistItem(ArticleList_t* ArticleRef){ // Just in case
    free(ArticleRef);
}

void FreeCart(){
    while (Cart != NULL){
        FreeCart(Cart->next);
    }
    if (Cart){
        free(Cart);
    }
}