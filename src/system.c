#include "system.h"

ArticleList_t* Cart;

void init(){
    Cart = NULL;
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
    if (SearchRef = ArticleRef){ // If it's the first Item
        Cart = Cart->next;
        FreeArticlelistItem(SearchRef);
    } else {
        PrevRef = Cart;
        SearchRef = Cart->next;

        while (SearchRef != NULL){
            if (SearchRef = ArticleRef){
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