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

    Map* _map;
    MapItemManager* _itemManager;
    Display* _display;

public:

    GraphicManager(){
        _map = new Map;
        _itemManager = new MapItemManager;
        _display = new Display;
    }



    ~GraphicManager(){
        delete _map;
        delete _itemManager;
        delete _display;
    }

    //main graphic method
    void updateScreen(){
        _map->update();
        _itemManager->updateItemPositions();
        _itemManager->updateViewCover( _map->getCorners() );

        uint16_t** map_view = _map->getCurrentView();
        uint16_t** view_cover = _itemManager->getCoverLayer();

        _display->drawTwoLayer( (const void**)map_view, (const void**)view_cover );
        _itemManager->deleteItemsOutOfMap();
    }

};




#endif /* GRAPHICMANAGER_H_ */
