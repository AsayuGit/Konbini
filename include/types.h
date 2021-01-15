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
    char BarCode[14];
    char SerialNumber[7];
    Date ManifacturingDate;
    double TVA;
    unsigned int Price;
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

// Category binary trees
/*
typedef struct SubCategoryList {
    int SubCagegory;
    ArticleList_t* AList;
    struct SubCategoryList* next;
}SubCategoryList_t;

typedef struct CategoryList {
    int Category;
    struct SubCategoryList* SubCategoryList;
    struct CategoryList* next;
}CategoryList_t;*/

typedef struct IntTree {
    int Data;
    void* LeftChild;
    void* RightChild;
}IntTree_t;

#endif