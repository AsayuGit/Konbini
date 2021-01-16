#include "graphics.h"

#include <stdio.h>
#include <stdlib.h>
#include "globalFunctions.h"

void DrawBoxAt(int x, int y, int width, int height){
    int compt_lenght;
    int compt_height;

    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;

    SetCursorAt(x, y);
    printf("╔");
    
    for (compt_lenght = 2; compt_lenght < width; compt_lenght++){
        printf("═");
    }
    printf("╗");

    for (compt_height = 1; compt_height < height - 1; compt_height++){
        SetCursorAt(x, y+compt_height);
        printf("║");
        SetCursorAt(x+width-1, y+compt_height);
        printf("║");
    }

    SetCursorAt(x, y+compt_height);
    printf("╚");
    
    for (compt_lenght = 2; compt_lenght < width; compt_lenght++){
        printf("═");
    }
    printf("╝");
}
//╔═╗
//║║║
//╚═╝