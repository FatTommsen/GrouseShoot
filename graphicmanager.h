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
#include "util/timer.h"


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

    void printStatistic( const Statistic& stat ){
        _display->initStatScreen();
        _display->writeHeadline(10, 10, "Score:");
        _display->write(15, 37, "Fly     (10):" );
        _display->write(15, 47, "Run     ( 5):" );
        _display->write(15, 57, "Fishing ( 2):" );
        _display->write(15, 67, "Shots   (-1):" );


        _display->putChar( 98, 37, getChar((stat.flyCount/100)%100, true) );
        _display->putChar(104, 37, getChar((stat.flyCount/10)%10, true) );
        _display->putChar(110, 37, getChar(stat.flyCount) );
        _display->putChar(117, 37, 'x' );

        _display->putChar( 98, 47, getChar((stat.flyCount/100)%100, true) );
        _display->putChar(104, 47, getChar((stat.runCount/10)%10, true) );
        _display->putChar(110, 47, getChar(stat.runCount) );
        _display->putChar(117, 47, 'x' );

        _display->putChar( 98, 57, getChar((stat.flyCount/100)%100, true) );
        _display->putChar(104, 57, getChar((stat.fishCount/10)%10, true) );
        _display->putChar(110, 57, getChar(stat.fishCount) );
        _display->putChar(117, 57, 'x' );

        _display->putChar( 98, 67, getChar((stat.flyCount/100)%100, true) );
        _display->putChar(104, 67, getChar((stat.shotCount/10)%10, true) );
        _display->putChar(110, 67, getChar(stat.shotCount) );
        _display->putChar(117, 67, 'x' );

        int points = (10*stat.flyCount + 5*stat.runCount + 2*stat.fishCount - stat.shotCount);

        char vz = ' ';

        if(points < 0 ){
            points *= (-1);
            vz = '-';
        }

        char hun = getChar((points%1000)/1000, true);
        char ten = getChar((points%100)/10, (hun == 32) );
        char one = getChar((points%10));

        _display->putScoreChar(63, 87, vz);
        _display->putScoreChar(75, 87, hun);
        _display->putScoreChar(87, 87, ten);
        _display->putScoreChar(99, 87, one);
    }

    char getChar( uint8_t num, bool first = false ){
        num = num % 10;
        if( num == 0 && first ){
            return (char)32;
        }
        return (char)(num + 48);
    }


};




#endif /* GRAPHICMANAGER_H_ */
