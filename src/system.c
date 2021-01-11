#include "system.h"

Article Catalogue[CATALOGUE_SIZE] = {
    {
        "00000",
        "Colgate",
        "Dentifrice",
        CAT_Hygiene,
        SBCAT_Toothpaste,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00001",
        "Adidas",
        "Chaussure",
        CAT_Clothes,
        SBCAT_Shoe,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00002",
        "Bic",
        "Stylos",
        CAT_Stationery,
        SBCAT_Pen,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00003",
        "Charral",
        "Beuf",
        CAT_Food,
        SBCAT_Meat,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00004",
        "Monoprix",
        "Carottes",
        CAT_Food,
        SBCAT_Vegetables,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00005",
        "Harry Potter And the Chamber of Secrets",
        "Livre",
        CAT_Culture,
        SBCAT_Book,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00006",
        "Acer",
        "Ordinateur",
        CAT_Computers,
        SBCAT_Computers,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00007",
        "Displate",
        "Poster",
        CAT_Decoration,
        SBCAT_Poster,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00008",
        "Razer",
        "Clavier",
        CAT_Computers,
        SBCAT_Keyboard,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    },
    {
        "00009",
        "Supreme",
        "T Shirt",
        CAT_Clothes,
        SBCAT_Shirt,
        NULL,
        "",
        "",
        {0, 0, 0},
        0.0,
        0
    }
};

void init(){

}