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
#include "mapitem/grouseflyreverse.h"
#include "mapitem/grousefishing.h"
#include "mapitem/interfacemapitem.h"
#include "mapitem/interfaceviewitem.h"
#include "../custom_yahal/uGUI_2layer.h"

extern const unsigned int map_size_x;
extern const unsigned int map_size_y;
extern const size_t view_size;

class MapItemManager {


private:

    InterfaceViewItem* _topLevelItem;
//    List<InterfaceMapItem>* _itemList;

public:

    MapItemManager() {
        _topLevelItem = new Crosshair;
 //       _itemList = new List<InterfaceItem>;

        //Test
        //_itemList->push_back( new GrouseFlyReverse( 190, 50) );
        //_itemList->push_back( new GrouseFishing( 130, 120) );


    }


    ~MapItemManager(){
//        delete _topLevelItem;
//        delete _itemList;
    }

//    bool coverCallback( size_t x, size_t y, uint16_t& color ){
//        if( _topLevelItem->cover_callback( x, y, color ) ){
//            return true;
//        }
//        size_t x_abs = x + _mapViewOffset->x;
//        size_t y_abs = y + _mapViewOffset->y;
//
//        List<InterfaceItem>::elem* it = _itemList->_head;
//        while( it != nullptr ){
//            if( it->_data->cover_callback(x_abs, y_abs, color)){
//                return true;
//            }
//            else{
//                it = it->_next;
//            }
//        }
//        return false;
//
//
//    }

    void run() {
/*
        if( _itemList->_size <= 4 ){
            createGrouseFly();
        }
*/
//        _topLevelItem->update_position();
//        List<InterfaceItem>::elem* it = _itemList->_head;
//        while( it != nullptr ){
//            it->_data->update_position();
//            it = it->_next;
//        }

    }

//    void createGrouseFly(){
//
//        Point start = getRandomBorderPoint();
//        Point path = getPathPoint( start );
//
//        if( start.x > path.x ){
//            GrouseFly* f = new GrouseFly(start.x, start.y);
//            f->setPath(path);
//            _itemList->push_back(f);
//        }
//        else {
//            GrouseFlyReverse* f = new GrouseFlyReverse(start.x, start.y);
//            f->setPath(path);
//            _itemList->push_back(f);
//        }
//    }


//    void createGrouseFishing(){
//
//    }
//
//    void deleteItemsOutOfMap(){
//        List<InterfaceItem>::elem* it = _itemList->_head;
//        while(it != nullptr){
//            if( it->_data->outOfMap() ){
//                _itemList->remove(it->_data);
//                deleteItemsOutOfMap();
//                return;
//            }
//            it = it->_next;
//        }
//    }


    void updateItemPositions(){
        _topLevelItem->update_position();
    }

    void updateScreenPositions(uGUI_2layer& gui){
        _topLevelItem->drawItem(gui);
    }





};





#endif /* GRAPHIC_MAPITEMMANAGER_H_ */
