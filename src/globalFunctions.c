#include "globalFunctions.h"
#include "unistd.h"
#include "string.h"

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

void CrossSleep(int Seconds){
#ifdef _WIN32
    Sleep(Seconds * 1000);
#else
    sleep(Seconds);
#endif 
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

void PrintIntList(IntList_t* List){ // Mostly a debug function
    int i = 0;

    while (List != NULL){
        printf("Element %d : %d\n", i++, List->Data);
        List = List->next;
    }
}

IntList_t* SearchDataInList(IntList_t* List, int Data){
    while (List != NULL){
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

IntTree_t* GetItemInLeftTree(IntTree_t* Tree, int ID){
    int i;
    for (i = 0; i < ID; i++){
        Tree =Tree->LeftChild;
    }
    return Tree;
}

void FreeIntList(IntList_t* List){
    while (List != NULL){
        FreeIntList(List->next);
        free(List);
    }
}

void AddElementToStringList(StringList_t** List, char* Data){
    if (List != NULL){
        while ((*List) != NULL){ // Search for a free spot
            List = &((*List)->next);
        }
        (*List) = (StringList_t*)malloc(sizeof(StringList_t));
        (*List)->Data = (char*)malloc(sizeof(char)*(strlen(Data)+1));
        strcpy((*List)->Data, Data);
        (*List)->next = NULL;
    }
}

void FreeStringList(StringList_t** List){
    if ((*List) != NULL){
        FreeStringList(&((*List)->next));
        free((*List)->Data);
        free((*List));
    }

    (*List) = NULL;
}