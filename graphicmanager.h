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
    MapItemManager& _itemManager;
    Display* _display;

public:

    GraphicManager( MapItemManager& itemManager )
    : _itemManager(itemManager)
    {
        _map = new Map;
        _display = new Display;
        _itemManager.registerMapCorners( _map->getCorners() );
    }



    ~GraphicManager(){
        delete _map;
        delete _display;
    }

    //main graphic method
    void updateScreen(){
        _map->update();
        _itemManager.updateItemPositions();
        _itemManager.updateViewCover(TRANSPARENT_COLOR);

        uint16_t** map_view = _map->getCurrentView();
        uint16_t** view_cover = _itemManager.getCoverLayer();

        _display->drawTwoLayer( (const void**)map_view, (const void**)view_cover );
        _itemManager.deleteItemsOutOfMap();
    }

    void updateMenuScreen(){
        _itemManager.updateItemPositions();
        _itemManager.updateViewCover(MENU_BACKGROUND_COLOR);
        uint16_t** menu_view = _itemManager.getCoverLayer();
        _display->drawOneLayer((const void**)menu_view);
    }

    void resetMap(){
        _map->reset();
    }

    void toggleMapNavigation(){
        _map->toggleNavigation();
    }

};




#endif /* GRAPHICMANAGER_H_ */
