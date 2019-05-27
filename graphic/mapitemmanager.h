/*
 * mapitemmanager.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEMMANAGER_H_
#define GRAPHIC_MAPITEMMANAGER_H_

#include "util.h"
#include "interfacemapitem.h"
#include "task.h"
#include "crosshair.h"
#include "grousefly.h"
#include "grouseflyreverse.h"
#include "grousefishing.h"

extern const size_t view_size;

class MapItemManager : public task{

private:
    static MapItemManager* instance;

public:

    static MapItemManager& getInstance(){
        if( MapItemManager::instance == nullptr ){
            MapItemManager::instance = new MapItemManager();
        }

        return *MapItemManager::instance;
    }

private:

    Point* _mapViewOffset;
    bool _taskMode;
    InterfaceMapItem* _topLevelItem;

    List<InterfaceMapItem>* _itemList;

    InterfaceMapItem* _grouseTest;
    Synchronizer* _sync;
    //MapItems



    MapItemManager()
    : task("MapItemManager task"), _mapViewOffset(nullptr), _taskMode(true), _sync(nullptr)
    {
        _topLevelItem = new Crosshair;
        _itemList = new List<InterfaceMapItem>;

        //Test
        _itemList->push_back( new GrouseFlyReverse( 190, 50) );
        _itemList->push_back( new GrouseFishing( 130, 120) );
    }


public:

    ~MapItemManager(){
        delete _topLevelItem;
        delete _itemList;
    }

    void registerMapViewOffset( Point* p){
        _mapViewOffset = p;
    }

    void registerSynchronizer( Synchronizer* sync ){
        _sync = sync;
    }

    bool coverCallback( size_t x, size_t y, uint16_t& color ){
        if( _topLevelItem->cover_callback( x, y, color ) ){
            return true;
        }
        size_t x_abs = x + _mapViewOffset->x;
        size_t y_abs = y + _mapViewOffset->y;

        List<InterfaceMapItem>::elem* it = _itemList->_head;
        while( it != nullptr ){
            if( it->_data->cover_callback(x_abs, y_abs, color)){
                return true;
            }
            else{
                it = it->_next;
            }
        }
        return false;


    }

    void turnOffTaskMode(){
        _taskMode = false;
    }

    void run() override{
        do{
            if( _taskMode && _sync != nullptr ){
                _sync->_mutex_crosshair->lock();
            }

            _topLevelItem->update_position();
            List<InterfaceMapItem>::elem* it = _itemList->_head;
            while( it != nullptr ){
                it->_data->update_position();
                it = it->_next;
            }

            if( _taskMode && _sync != nullptr ){
                _sync->_mutex_crosshair->unlock();
                yield();
            }

        }while(_taskMode);
    }

    void itemOutOfMap( InterfaceMapItem* item ){

    }
};


static bool mapItemCoverCallback( size_t x, size_t y, uint16_t& color ){
    return MapItemManager::getInstance().coverCallback(x, y, color);
}




#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
