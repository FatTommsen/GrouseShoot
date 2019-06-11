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

    __enable_irq();
    Game game;
    game.loadMenu();
    game.runMenu();

/*
    __enable_irq();
    UartLogger logger = UartLogger::getInstance();
    logger.log("start\n");
    Timer t;
    logger.log("start timer\n");
    t.delay(500000);
    logger.log("timer end\n");
*/
    return 0;

}
