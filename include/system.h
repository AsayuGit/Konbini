#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "include.h"
#include "catalogue.h"

void init();

void AddArticleToCart(Article* ArticleRef);
ArticleList_t* SearchArticleInCart(Article* ArticleRef);
void DisplayCartContent();
int getCartValue();
void FreeCart();

#endif