/*****************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
#include "graphic/map.h"
#include "graphic/mapitem/crosshair.h"
#include "periphery/display.h"
#include "task_monitor.h"
#include "game.h"

#include "graphicmanager.h"

int main(void)
{

//    Map map;
//    Display display(map );
//    MapItemManager& manager = MapItemManager::getInstance();
//    Game& game = Game::getInstance();
//
//
//    while(true){
//        map.run();
//        manager.run();
//        display.run();
//        game.run();
//    }

    GraphicManager gm;

    while(true){
        gm.updateScreen();
    }

    return 0;
}
