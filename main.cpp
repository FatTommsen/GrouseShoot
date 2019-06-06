/*****************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
#include "game.h"

#include "graphicmanager.h"

int main(void)
{

    GraphicManager gm;

    while(true){
        gm.updateScreen();
    }


    return 0;
}
