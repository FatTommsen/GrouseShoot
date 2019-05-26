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
    InterfaceMapItem* _grouseTest;
    Synchronizer* _sync;
    //MapItems



    MapItemManager()
    : task("MapItemManager task"), _mapViewOffset(nullptr), _taskMode(true), _sync(nullptr)
    {
        _topLevelItem = new Crosshair();
        _grouseTest = new GrouseFly( 130, 50);
    }


public:

    ~MapItemManager(){

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
        return _grouseTest->cover_callback(x_abs, y_abs, color);
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
            _grouseTest->update_position();

            if( _taskMode && _sync != nullptr ){
                _sync->_mutex_crosshair->unlock();
                yield();
            }

        }while(_taskMode);
    }
};


static bool mapItemCoverCallback( size_t x, size_t y, uint16_t& color ){
    return MapItemManager::getInstance().coverCallback(x, y, color);
}




#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
