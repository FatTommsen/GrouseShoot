/*
 * mapitemmanager.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEMMANAGER_H_
#define GRAPHIC_MAPITEMMANAGER_H_

#include "mapitem/crosshair.h"
#include "mapitem/grousefly.h"
#include "mapitem/grousefishing.h"
#include "../util/list.h"
#include "mapitem/mapitembase.h"
#include "mapitem/viewitembase.h"

extern const size_t map_size_x;
extern const size_t map_size_y;
extern const uint8_t DISPLAY_SIZE;
extern const uint16_t TRANSPARENT_COLOR;

class MapItemManager {


private:

    ViewItemBase* _topLevelItem;
    uint16_t** _view_cover;
    List<MapItemBase>* _itemList;

public:

    MapItemManager() {
        _topLevelItem = new Crosshair;
        _view_cover = new uint16_t*[DISPLAY_SIZE];
        for( size_t i = 0; i < DISPLAY_SIZE; ++i ){
            _view_cover[i] = new uint16_t[DISPLAY_SIZE];
        }

        _itemList = new List<MapItemBase>;

        //Test
        _itemList->push_back( new GrouseFly() );
        _itemList->push_back( new GrouseFishing() );


    }


    ~MapItemManager(){
        delete _topLevelItem;
        for( size_t i = 0; i < DISPLAY_SIZE; ++i ){
            delete _view_cover[i];
        }
        delete _view_cover;
        delete _itemList;
    }


    void updateItemPositions(){
        _topLevelItem->update_position();
        List<MapItemBase>::elem* it = _itemList->_head;
        while(it != nullptr){
            it->_data->update_position();
            it = it->_next;
        }
        //Test:
        if( _itemList->_size <= 4 ){
            _itemList->push_back(new GrouseFly);
        }
    }

    void updateViewCover( const Corners& map_corn ){
        for(size_t x = 0; x < DISPLAY_SIZE; ++x ){
            for(size_t y = 0; y < DISPLAY_SIZE; ++y ){
                _view_cover[x][y] = TRANSPARENT_COLOR;
            }
        }

        //backgrounditems
        List<MapItemBase>::elem* it = _itemList->_head;
        while(it != nullptr){
            it->_data->drawItem(_view_cover, map_corn);
            it = it->_next;
        }

        //toplevelitems
        _topLevelItem->drawItem(_view_cover);
    }

    void deleteItemsOutOfMap(){
        List<MapItemBase>::elem* it = _itemList->_head;
        while(it != nullptr){
            if( it->_data->outOfMap() ){
                _itemList->remove(it->_data);
                deleteItemsOutOfMap();
                return;
            }
            it = it->_next;
        }
    }

    uint16_t** getCoverLayer(){
        return _view_cover;
    }

};





#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
