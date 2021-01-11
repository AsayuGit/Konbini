#include "system.h"

ArticleList_t* Cart;

Article Catalogue[CATALOGUE_SIZE] = {
    {
        "00000",
        "Colgate",
        "Dentifrice",
        CAT_Hygiene,
        SBCAT_Toothpaste,
        "Colgate",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00001",
        "Adidas",
        "Chaussure",
        CAT_Clothes,
        SBCAT_Shoe,
        "Adidas",
        ""
        "",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00002",
        "Bic",
        "Stylos",
        CAT_Stationery,
        SBCAT_Pen,
        "Bic",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00003",
        "Charral",
        "Beuf",
        CAT_Food,
        SBCAT_Meat,
        "Charral",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00004",
        "Monoprix",
        "Carottes",
        CAT_Food,
        SBCAT_Vegetables,
        "Monoprix",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00005",
        "Harry Potter And the Chamber of Secrets",
        "Livre",
        CAT_Culture,
        SBCAT_Book,
        "Hachette",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00006",
        "Acer",
        "Ordinateur",
        CAT_Computers,
        SBCAT_Computers,
        "Acer",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00007",
        "Displate",
        "Poster",
        CAT_Decoration,
        SBCAT_Poster,
        "Displate",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00008",
        "Razer",
        "Clavier",
        CAT_Computers,
        SBCAT_Keyboard,
        "Razer",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    },
    {
        "00009",
        "Supreme",
        "T Shirt",
        CAT_Clothes,
        SBCAT_Shirt,
        "Supreme",
        "",
        "NA",
        {0, 0, 0},
        0.0,
        10.0,
        50
    }
};

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

void DisplayCartContent(){
    int i = 0;
    ArticleList_t* CartRef;

    drawLine(89);
    printf("// N° // ArticleCode // Brand // Product // Serial Number // Relevent Date // Quantity //\n");
    
    CartRef = Cart;
    while (CartRef != NULL){
        printf("// %d) // %s // %s // %s %s // %s // %s // %s //\n", i, 
        CartRef->Item->ArticleCode, CartRef->Item->Brand, CartRef->Item->CommunName,
        CartRef->Item->MarketName, CartRef->Item->SerialNumber, "DATE", "XXX");
        CartRef = CartRef->next;
    }
    
    drawLine(89);
}

void FreeCart(){
    while (Cart != NULL){
        FreeCart(Cart->next);
    }
    if (Cart){
        free(Cart);
    }
}