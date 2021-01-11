#include "globalFunctions.h"

void SetCursorAt(int X, int Y){
    printf("\033[%d;%dH", Y, X);
}

void clear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void drawLine(int Length){
    int i;

    for (i = 0; i < Length; i++){
        printf("/");
    }
    printf("\n");
}

void AddElementToIntList(IntList_t** List, int Data){
    if (List != NULL){
        while ((*List) != NULL){ // Search for a free spot
            List = &((*List)->next);
        }
        (*List) = (IntList_t*)malloc(sizeof(IntList_t));
        (*List)->Data = Data;
        (*List)->next = NULL;
    }
}

void PrintIntList(IntList_t* List){
    int i = 0;

    while (List != NULL){
        printf("Element %d : %d\n", i++, List->Data);
        List = List->next;
    }
}

IntList_t* SearchDataInList(IntList_t* List, int Data){
    while (List != NULL){ // Search for a free spot
        if (List->Data == Data){
            return List;
        }else{
            List = List->next;
        }
    }
    return NULL;
}

IntList_t* GetItemInList(IntList_t* List, int ID){
    int i;
    for (i = 0; i < ID; i++){
        List = List->next;
    }
    return List;
}

void FreeIntList(IntList_t* List){
    while (List != NULL){
        FreeIntList(List->next);
    }
    if (List){
        free(List);
    }
}