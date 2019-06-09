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
#include "mapitem/grouserun.h"

#include "mapitem/mapitembase.h"
#include "mapitem/viewitembase.h"

#include "../util/uartlogger.h"

extern const unsigned int map_size_x;
extern const unsigned int map_size_y;

class MapItemManager {


private:

    uint16_t** _view_cover;
    ViewItemBase* _topLevelItem;
    List<ViewItemBase>* _magazine;
    List<MapItemBase>* _itemList;
    MapItemBase* _singleItem;


    const Corners* _mapCorners;
public:

    MapItemManager()
    : _singleItem(nullptr)
    {
        _topLevelItem = new Crosshair;
        _view_cover = new uint16_t*[DISPLAY_SIZE];
        for( size_t i = 0; i < DISPLAY_SIZE; ++i ){
            _view_cover[i] = new uint16_t[DISPLAY_SIZE];
        }

        _itemList = new List<MapItemBase>;
        _magazine = new List<ViewItemBase>;

        //Test
        _itemList->push_back( new GrouseFly() );
        _itemList->push_back( new GrouseFishing() );
        _itemList->push_back( new GrouseRun() );

    }


    ~MapItemManager(){
        delete _topLevelItem;
        for( size_t i = 0; i < DISPLAY_SIZE; ++i ){
            delete _view_cover[i];
        }
        delete _view_cover;
        delete _itemList;
        delete _magazine;
        if(_singleItem){
            delete _singleItem;
        }
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
        if( !hasActiveGrouseRun() ){
            _itemList->push_back(new GrouseRun);
        }
    }

    void updateViewCover(){
        for(size_t x = 0; x < DISPLAY_SIZE; ++x ){
            for(size_t y = 0; y < DISPLAY_SIZE; ++y ){
                _view_cover[x][y] = TRANSPARENT_COLOR;
            }
        }

        //dynamic items
        List<MapItemBase>::elem* it_map = _itemList->_head;
        while(it_map != nullptr){
            it_map->_data->drawItem(_view_cover, *_mapCorners);
            it_map = it_map->_next;
        }

        if( _singleItem ){
            _singleItem->drawItem(_view_cover, *_mapCorners);
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
        _itemList->push_back(new GrouseFly);
    }

    void spawnGrouseFishing(){
        if(!_singleItem){
            _singleItem = new GrouseFishing();
        }
    }

    bool hasActiveGrouseFishing(){
        return _singleItem == nullptr;
    }

    bool hasActiveGrouseRun(){
        return getTypeCount( TypeIdGrouseRun );
    }

    int getItemCount(){
        return _itemList->_size;
    }

    int getCartridgeCount(){
        return _magazine->_size;
    }

    int processShot(){
        if( getCartridgeCount() > 0 ){
            const Corners& crosshairCorners = _topLevelItem->getCorners();
            Point p;
            p.x = ((double)( crosshairCorners.rLow.x - crosshairCorners.lUp.x ) / 2 ) + _mapCorners->lUp.x + crosshairCorners.lUp.x;
            p.y = ((double)( crosshairCorners.rLow.y - crosshairCorners.lUp.y ) / 2 ) + _mapCorners->lUp.y + crosshairCorners.lUp.y;

            if(_singleItem != nullptr ){
                if( _singleItem->gotHit(p)){
                    delete _singleItem;
                    _singleItem = nullptr;
                    return 1;
                }
            }

            List<MapItemBase>::elem* it = _itemList->_head;
            while( it != nullptr ){
                if( it->_data->gotHit(p) ){
                    _itemList->remove(it->_data);
                    // return points
                    return 1;
                }
                it = it->_next;
            }
        }
        return 0;
    }

    void registerMapCorners( const Corners& corn ){
        _mapCorners = &corn;
    }


private:

    int getTypeCount( int typeId ){
        int ret = 0;
        List<MapItemBase>::elem* it = _itemList->_head;
        while( it != nullptr ){
            if( it->_data->getTypeId() == typeId ){
                ++ret;
            }
            it = it->_next;
        }
        return ret;
    }


};
#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
