/*****************************************************************************
*
* MSP432 empty main.c template
*
******************************************************************************/

#include "msp.h"
#include "graphic/map.h"
#include "graphic/crosshair.h"
#include "task.h"
#include "graphic/display.h"
#include "task_monitor.h"
#include "util.h"

int main(void)
{

/*
    Synchronizer sync;
    Map task_map(128, sync);
    Display task_display(task_map, sync);
    Crosshair task_crosshair( 128, sync);

    theCrosshair = &task_crosshair;

    task_map.start();
    task_display.start();
    task_crosshair.start();

//    task_monitor monitor;
//    monitor.start();


    task::start_scheduler();
*/

    Synchronizer sync;
    Map task_map( sync, false);
    Display task_display(task_map, sync, false);
    MapItemManager& task_manager = MapItemManager::getInstance();
    task_manager.turnOffTaskMode();



    while(true){
        task_map.run();
        task_manager.run();
        task_display.run();
    }

    return 0;
}
