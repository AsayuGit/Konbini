#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <wchar.h>
#endif

#include "globalFunctions.h"

void DrawBoxAt(int x, int y, int width, int height){
    int compt_lenght;
    int compt_height;

    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;

    SetCursorAt(x, y);
    wprintf(BOX_TOPLEFT);

    for (compt_lenght = 2; compt_lenght < width; compt_lenght++){
        wprintf(BOX_HLINE);
    }
    wprintf(BOX_TOPRIGHT);

    for (compt_height = 1; compt_height < height - 1; compt_height++){
        SetCursorAt(x, y+compt_height);
        wprintf(BOX_VLINE);
        SetCursorAt(x+width-1, y+compt_height);
        wprintf(BOX_VLINE);
    }

    SetCursorAt(x, y+compt_height);
    wprintf(BOX_BOTTOMLEFT);
    
    for (compt_lenght = 2; compt_lenght < width; compt_lenght++){
        wprintf(BOX_HLINE);
    }
    wprintf(BOX_BOTTOMRIGHT);
}

void DrawStringBoxAt(int x, int y, StringList_t* List, int* returnWidth, int* returnHeight){
    int nbOfLines;
    int textX, textY;
    int maxWidth, newWidth;

    textX = x + 2;
    textY = y + 2;
    nbOfLines = 0;
    maxWidth = 0;
    while (List != NULL){
        SetCursorAt(textX, textY);
        printf("%s\n", List->Data);
        newWidth = strlen(List->Data);
        if (newWidth > maxWidth){
            maxWidth = newWidth;
        }
        List = List->next;
        nbOfLines++;
        textY++;
    }
    maxWidth += 4;
    nbOfLines += 4;
    DrawBoxAt(x, y, maxWidth, nbOfLines);

    if (returnWidth)
        (*returnWidth) = maxWidth;

    if (returnHeight)
        (*returnHeight) = nbOfLines;
}