#ifndef _GLOBALFUNCTION_H
#define _GLOBALFUNCTION_H

#include "include.h"

void SetCursorAt(int X, int Y);
void clear();
void drawLine(int Length);

void CrossSleep(int Seconds);

// Linked list
void AddElementToIntList(IntList_t** List, int Data);
void PrintIntList(IntList_t* List);

IntList_t* SearchDataInList(IntList_t* List, int Data);
IntList_t* GetItemInList(IntList_t* List, int ID);
void FreeIntList(IntList_t* List);

IntTree_t* GetItemInLeftTree(IntTree_t* Tree, int ID);

void AddElementToStringList(StringList_t** List, char* Data);
void FreeStringList(StringList_t** List);

#endif