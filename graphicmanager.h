/*
 * graphicmanager.h
 *
 *  Created on: 04.06.2019
 *      Author: student
 */

#ifndef GRAPHICMANAGER_H_
#define GRAPHICMANAGER_H_

#include "graphic/map.h"
#include "graphic/mapitemmanager.h"

#include "periphery/display.h"

class GraphicManager{

private:

    static GraphicManager* instance;

public:

    static GraphicManager& getInstance(){
        if( GraphicManager::instance == nullptr ){
            GraphicManager::instance = new GraphicManager();
        }
        return *instance;
    }


    Map* _map;
    MapItemManager* _itemManager;
    Display* _display;

    GraphicManager(){
        _map = new Map;
        _itemManager = new MapItemManager;
        _display = new Display;
    }

public:

    ~GraphicManager(){
        delete _map;
        delete _itemManager;
        delete _display;
    }

    //main graphic method
    void updateScreen(){
        _itemManager->updateItemPositions();
        if( _map->update() ){
            uint16_t** map_view = _map->getCurrentView();
            _display->quickDrawMap( (const void**)map_view );
            _itemManager->updateScreenPositions(_display->getGui());


            // alle Items neu zweichnen
        }
        else{
            _itemManager->updateScreenPositions(_display->getGui());
        }

        //_itemManager->deleteItemsOutOfMap();
    }

};




#endif /* GRAPHICMANAGER_H_ */
