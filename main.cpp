/*****************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "settings.h"
#include "msp.h"
#include "game.h"

#include "util/timer.h"
#include "util/uartlogger.h"

int main(void)
{
    Game game;
    game.loadMenu();
    game.runMenu();


    return 0;

}

