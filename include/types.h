#ifndef _TYPES_H
#define _TYPES_H

#include "category.h"

typedef struct{
    int Day;
    int Month;
    int Year;
}Date;

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
    int Quantity;
}Article;

typedef struct IntList {
    int Data;
    struct IntList* next;
}IntList_t;

//typedef struct SubCategory SubCategory;
//typedef struct MainCategory MainCategory;
//typedef struct Catalogue Catalogue;

#endif