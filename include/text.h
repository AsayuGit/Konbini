#ifndef _TEXT_H
#define _TEXT_H

extern const char errorMsg[][50];

typedef enum {
    MainMenuTitle,
    MainMenuOptionsFirst,
    MainMenuOptionsLast = MainMenuOptionsFirst + 2,
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
    NBOfLabels
}labelsID;

extern const char labels[NBOfLabels][100];

#endif