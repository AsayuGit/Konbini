#ifndef _TYPES_H
#define _TYPES_H

#include "category.h"
#include "text.h"

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
    unsigned int TVA;
    unsigned int Price;
    int Quantity;
}Article;

typedef struct{
    char* BuisnessName;
    char* BuisnessDetails;
    char* RCS;
}BuisnessInfo;

// Integer linked List
typedef struct IntList {
    int Data;
    struct IntList* next;
}IntList_t;

// String linked list
typedef struct StringList {
    char* Data;
    struct StringList* next;
}StringList_t;

// Article Linked list (Used for the cart)
typedef struct ArticleList {
    Article* Item;
    int Quantity;
    struct ArticleList* next;
}ArticleList_t;

typedef struct History {
    labelsID LabelID;
    char* Data1;
    char* Data2;
    struct History* next;
}History_t;

// Category binary tree
typedef struct IntTree {
    int Data;
    void* LeftChild;
    void* RightChild;
}IntTree_t;

#endif