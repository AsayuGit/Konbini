#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "include.h"
#include "catalogue.h"

void init();

void AddArticleToCart(Article* ArticleRef);
void DeleteArticleFromCart(ArticleList_t* ArticleRef);

ArticleList_t* SearchArticleInCart(Article* ArticleRef);
ArticleList_t* GetItemFromCart(int ArticleID);
void DisplayCartContent();
int getCartValue();
int getNbItemInCart();
void FreeArticlelistItem(ArticleList_t* ArticleRef);
void FreeCart();

#endif