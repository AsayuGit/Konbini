#ifndef _TEXT_H
#define _TEXT_H

extern const char errorMsg[][50];

typedef enum {
    MainMenuTitle,
    MainMenuOptionsFirst,
    MainMenuOptionsLast = MainMenuOptionsFirst + 3,
    CatalogueTile,
    CatalogueCategorySelect,
    CatalogueSubCategorySelect,
    CatalogueItemSelect,
    CatalogueGreetings,
    CartTile,
    BuyMenuTitle,
    ToMainMenu,
    CartValueMax,
    CartMenuOptionsFirst,
    CartMenuOptionsLast = CartMenuOptionsFirst + 2,
    EmptyCart,
    ModArticleSelect,
    ArticleNotFound,
    NotEnoughStock,
    CartTotal,
    BILLFrom,
    BILLTo,
    BILLDate,
    ThanksBuy,
    BILLNb,
    ADDItemToCart,
    DELItemFromCart,
    MODItemQuantity,
    NOHistory,
    MenuSelect,
    NBOfLabels
}labelsID;

extern const char labels[NBOfLabels][100];

#endif