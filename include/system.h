#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "include.h"
#include "catalogue.h"

extern BuisnessInfo Buisness;

void init();
ArticleList_t* GetItemFromArticleList(ArticleList_t* List, int ArticleID);

void AddArticleToCart(Article* ArticleRef);
void DeleteArticleFromCart(ArticleList_t* ArticleRef);

ArticleList_t* SearchArticleInCart(Article* ArticleRef);
ArticleList_t* GetItemFromCart(int ArticleID);
int DisplayArticleListContent(int x, int y, ArticleList_t* List, char CartMode, int* returnWith, int* returnHeight);
int DisplayCartContent(int x, int y, int* returnWith, int* returnHeight);
int GetTTCArticleListPrice(ArticleList_t* CartRef);
int GetTTCCartPrice();
int getNbItemInCart();
void FreeArticlelistItem(ArticleList_t* ArticleRef);
void FreeCart();

History_t** AddActionToHistory(labelsID Message, char* Arg1, char* Arg2);
void DisplayHistory(int x, int y, int start, int end);
void FreeHistory();

#endif