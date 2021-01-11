#ifndef _CATEGORY_H
#define _CATEGORY_H

typedef enum{
    CAT_Computers = 0,
    CAT_Clothes,
    CAT_Stationery,
    CAT_Hygiene,
    CAT_Decoration,
    CAT_Food,
    CAT_Entertainement,
    CAT_Culture,
    NbOfCategories
}CategoryID;

typedef enum{
    SBCAT_Shoe = 0,
    SBCAT_Shirt,
    SBCAT_Coat,
    SBCAT_Pen,
    SBCAT_Paper,
    SBCAT_Ink,
    SBCAT_Soap,
    SBCAT_Shampoo,
    SBCAT_Toothpaste,
    SBCAT_Poster,
    SBCAT_Picture,
    SBCAT_Figurine,
    SBCAT_Fruit,
    SBCAT_Vegetables,
    SBCAT_Meat,
    SBCAT_BoardGames,
    SBCAT_VideoGames,
    SBCAT_MusicalInstruments,
    SBCAT_Book,
    SBCAT_Music,
    SBCAT_Movie,
    SBCAT_Computers,
    SBCAT_Keyboard,
    SBCAT_ComputerMouse,
    NbOfSubCategories
}SubCategoryID;

extern char* CategoryLabel[NbOfCategories];
extern char* SubCategoryLabel[NbOfSubCategories];


#endif