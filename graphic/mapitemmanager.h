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
    Synchronizer* _sync;
    //MapItems



    MapItemManager()
    : task("MapItemManager task"), _mapViewOffset(nullptr), _taskMode(true), _sync(nullptr)
    {
        _topLevelItem = new Crosshair();
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

    bool coverCallback( size_t x, size_t y, uint16_t* color ){
        return _topLevelItem->cover_callback( x, y, color );
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

            if( _taskMode && _sync != nullptr ){
                _sync->_mutex_crosshair->unlock();
                yield();
            }

        }while(_taskMode);
    }
};


static bool mapItemCoverCallback( size_t x, size_t y, uint16_t* color ){
    return MapItemManager::getInstance().coverCallback(x, y, color);
}




#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
