/*
 * mapitemmanager.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEMMANAGER_H_
#define GRAPHIC_MAPITEMMANAGER_H_

#include "../util/list.h"

#include "mapitem/cartridge.h"
#include "mapitem/crosshair.h"
#include "mapitem/grousefly.h"
#include "mapitem/grousefishing.h"

#include "mapitem/mapitembase.h"
#include "mapitem/viewitembase.h"

extern const size_t map_size_x;
extern const size_t map_size_y;
extern const uint8_t DISPLAY_SIZE;
extern const uint16_t TRANSPARENT_COLOR;
extern const uint8_t MAGAZINE_SIZE;

class MapItemManager {


private:

    ViewItemBase* _topLevelItem;
    List<ViewItemBase>* _magazine;
    uint16_t** _view_cover;
    List<MapItemBase>* _dynamicItemList;

public:

    MapItemManager() {
        _topLevelItem = new Crosshair;
        _view_cover = new uint16_t*[DISPLAY_SIZE];
        for( size_t i = 0; i < DISPLAY_SIZE; ++i ){
            _view_cover[i] = new uint16_t[DISPLAY_SIZE];
        }

        _dynamicItemList = new List<MapItemBase>;
        _magazine = new List<ViewItemBase>;

        //Test
        _dynamicItemList->push_back( new GrouseFly() );
        _dynamicItemList->push_back( new GrouseFishing() );

    }


    ~MapItemManager(){
        delete _topLevelItem;
        for( size_t i = 0; i < DISPLAY_SIZE; ++i ){
            delete _view_cover[i];
        }
        delete _view_cover;
        delete _dynamicItemList;
        delete _magazine;
    }


    void updateItemPositions(){
        _topLevelItem->update_position();
        List<MapItemBase>::elem* it = _dynamicItemList->_head;
        while(it != nullptr){
            it->_data->update_position();
            it = it->_next;
        }
        //Test:
        if( _dynamicItemList->_size <= 4 ){
            _dynamicItemList->push_back(new GrouseFly);
        }
    }

    void updateViewCover( const Corners& map_corn ){
        for(size_t x = 0; x < DISPLAY_SIZE; ++x ){
            for(size_t y = 0; y < DISPLAY_SIZE; ++y ){
                _view_cover[x][y] = TRANSPARENT_COLOR;
            }
        }

        //dynamic items
        List<MapItemBase>::elem* it_map = _dynamicItemList->_head;
        while(it_map != nullptr){
            it_map->_data->drawItem(_view_cover, map_corn);
            it_map = it_map->_next;
        }

        //static items
        List<ViewItemBase>::elem* it_view = _magazine->_head;
        while(it_view != nullptr){
            it_view->_data->drawItem(_view_cover );
            it_view = it_view->_next;
        }

        //toplevelitems
        _topLevelItem->drawItem(_view_cover);
    }

    void deleteItemsOutOfMap(){
        List<MapItemBase>::elem* it = _dynamicItemList->_head;
        while(it != nullptr){
            if( it->_data->outOfMap() ){
                _dynamicItemList->remove(it->_data);
                deleteItemsOutOfMap();
                return;
            }
            it = it->_next;
        }
    }

    uint16_t** getCoverLayer(){
        return _view_cover;
    }

    // game controll
    void deleteOneCartridge(){
        if( _magazine->_size > 0 ){
            _magazine->remove(_magazine->_tail->_data);
        }
    }

    void reloadMagazine(){
        while( _magazine->_size < MAGAZINE_SIZE ){
            _magazine->push_back(new Cartridge(_magazine->_size));
        }
    }

    void spawnGrouseFly(){
        _dynamicItemList->push_back(new GrouseFly);
    }

    void spawnGrouseFishing(){
        if(!hasActiveGrouseFishing()){
            _dynamicItemList->push_back(new GrouseFishing);
        }
    }

    bool hasActiveGrouseFishing(){
        List<MapItemBase>::elem* it = _dynamicItemList->_head;
        while(it != nullptr){
            if( it->_data->getTypeId() == 4 ){
                return true;
            }
            it = it->_next;
        }
        return false;
    }

};





#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
