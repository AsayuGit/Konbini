#ifndef _TEXT_H
#define _TEXT_H

extern const char errorMsg[][50];

typedef enum {
    MainMenuTitle,
    MainMenuOptionsFirst,
    MainMenuOptionsLast = MainMenuOptionsFirst + 2,
    CatalogueTile,
    CatalogueGreetings,
    CartTile,
    NBOfLabels
}labelsID;

extern const char labels[NBOfLabels][50];

#endif