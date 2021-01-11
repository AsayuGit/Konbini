#ifndef _TYPES_H
#define _TYPES_H

#include "category.h"

typedef struct{
    int Day;
    int Month;
    int Year;
}Date;

// Article Description
typedef struct{
    char ArticleCode[5];
    char* MarketName;
    char* CommunName;
    CategoryID MainCategory;
    SubCategoryID SubCategory;
    char* Brand;
    char BarCode[13];
    char SerialNumber[6];
    Date ManifacturingDate;
    double TVA;
    double Price;
    int Quantity;
}Article;

// Integer linked List
typedef struct IntList {
    int Data;
    struct IntList* next;
}IntList_t;

// Article Linked list (Used for the cart)
typedef struct ArticleList {
    Article* Item;
    int Quantity;
    struct ArticleList* next;
}ArticleList_t;

#endif