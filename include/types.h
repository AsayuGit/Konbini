#ifndef _TYPES_H
#define _TYPES_H


typedef struct{
    int Day;
    int Month;
    int Year;
}Date;

typedef struct{
    char ArticleCode[5];
    char* MarketName;
    char* CommunName;
    char* MainCategory;
    char* SubCategory;
    char* Brand;
    char BarCode[13];
    char SerialNumber[6];
    Date ManifacturingDate;
    double TVA;
    int Quantity;
}Article;

typedef struct SubCategory SubCategory;
typedef struct MainCategory MainCategory;
typedef struct Catalogue Catalogue;

#endif