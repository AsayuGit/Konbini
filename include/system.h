#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "include.h"

#define CATALOGUE_SIZE 10

extern Article Catalogue[CATALOGUE_SIZE];

void init();

void AddArticleToCart(Article* ArticleRef);
ArticleList_t* SearchArticleInCart(Article* ArticleRef);
void DisplayCartContent();
void FreeCart();

#endif