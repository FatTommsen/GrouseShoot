/*
 * mapitemmanager.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEMMANAGER_H_
#define GRAPHIC_MAPITEMMANAGER_H_

#include "../periphery/gsensor.h"
#include "../periphery/optsensor.h"
#include "util.h"
#include "mapitem/interfacemapitem.h"
#include "mapitem/crosshair.h"
#include "mapitem/grousefly.h"
#include "mapitem/grouseflyreverse.h"
#include "mapitem/grousefishing.h"

extern const unsigned int map_size_x;
extern const unsigned int map_size_y;
extern const size_t view_size;

class MapItemManager {

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

    Random* _rand;
    Point* _mapViewOffset;
    InterfaceMapItem* _topLevelItem;

    List<InterfaceMapItem>* _itemList;

    InterfaceMapItem* _grouseTest;



    MapItemManager()
    : _mapViewOffset(nullptr)
    {
        _topLevelItem = new Crosshair;
        _itemList = new List<InterfaceMapItem>;

        //Test
        //_itemList->push_back( new GrouseFlyReverse( 190, 50) );
        //_itemList->push_back( new GrouseFishing( 130, 120) );

        GSensor gSen;
        OptSensor optSen;

        _rand = new Random( gSen.getZ() * optSen.measure() );
    }


public:

    ~MapItemManager(){
        delete _topLevelItem;
        delete _itemList;
    }

    void registerMapViewOffset( Point* p){
        _mapViewOffset = p;
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

    void run() {
/*
        if( _itemList->_size <= 4 ){
            createGrouseFly();
        }
*/
        _topLevelItem->update_position();
        List<InterfaceMapItem>::elem* it = _itemList->_head;
        while( it != nullptr ){
            it->_data->update_position();
            it = it->_next;
        }

    }

    void createGrouseFly(){

        Point start = getRandomBorderPoint();
        Point path = getPathPoint( start );

        if( start.x > path.x ){
            GrouseFly* f = new GrouseFly(start.x, start.y);
            f->setPath(path);
            _itemList->push_back(f);
        }
        else {
            GrouseFlyReverse* f = new GrouseFlyReverse(start.x, start.y);
            f->setPath(path);
            _itemList->push_back(f);
        }
    }


    void createGrouseFishing(){

    }

    void deleteItemsOutOfMap(){
        List<InterfaceMapItem>::elem* it = _itemList->_head;
        while(it != nullptr){
            if( it->_data->outOfMap() ){
                _itemList->remove(it->_data);
                deleteItemsOutOfMap();
                return;
            }
            it = it->_next;
        }
    }

private:

    Point getRandomBorderPoint(){
        Point p;
        double dmap_size_x = map_size_x;
        double dmap_size_y = map_size_y;
        size_t index = _rand->next() * ( dmap_size_x + dmap_size_y);
        if( index < 0.5 * dmap_size_y ){
            //left site
            p.x = 0;
            p.y = 0.5 * dmap_size_y - index;
        }
        else if( index < 0.5 * dmap_size_y + dmap_size_x ){
            p.x = index - dmap_size_y * 0.5;
            p.y = 0;
        }
        else{
            p.x = dmap_size_x;
            p.y = index - dmap_size_y * 0.5 - dmap_size_x;
        }

        return p;
    }

    Point getPathPoint( Point& start ){
        Point p;
        double dmap_size_x = map_size_x;
        double dmap_size_y = map_size_y;
        if( start.x == 0 ){
            size_t index = _rand->next() * (dmap_size_x + 0.5 * dmap_size_y);
            if( index < dmap_size_x ){
                p.x = index;
                p.y = 0;
            }
            else{
                p.x = index - dmap_size_x;
            }
        }
        else if( start.x == dmap_size_x ){
            size_t index = _rand->next() * (dmap_size_x + 0.5 * dmap_size_y);
            if( index <= 0.5 * dmap_size_y ){
                p.x = 0;
                p.y = dmap_size_y - index;
            }
            else{
                p.x = index - dmap_size_y;
                p.y = 0;
            }
        }
        else{
            size_t index = _rand->next() * dmap_size_y;
            if( index < 0.5 * dmap_size_y ){
                p.x = 0;
                p.y = 0.5 * dmap_size_y - index;
            }
            else{
                p.x = dmap_size_x;
                p.y = index - 0.5 * dmap_size_y;
            }
        }
        return p;
    }




};


static bool mapItemCoverCallback( size_t x, size_t y, uint16_t& color ){
    return MapItemManager::getInstance().coverCallback(x, y, color);
}




#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
