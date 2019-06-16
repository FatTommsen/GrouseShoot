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
        _itemManager.fillViewWithColor( MENU_BACKGROUND_COLOR);
        uint16_t** view = _itemManager.getCoverLayer();
        _display->initStatScreen();
        drawHLineToView(28, 7, 71, MENU_FONT_UNMARKED, view);
        drawHLineToView(82, 57, 121, MENU_FONT_UNMARKED, view);
        _display->writeHeadlineToView(10, 10, view, "Score:");
        _display->writeToView(15, 37, "Fly     (10):", view );
        _display->writeToView(15, 47, "Run     ( 5):", view );
        _display->writeToView(15, 57, "Fishing ( 2):", view );
        _display->writeToView(15, 67, "Shots   (-1):", view );


        _display->putCharToView( 98, 37, view, getChar((stat.flyCount/100)%100, true) );
        _display->putCharToView(104, 37, view, getChar((stat.flyCount/10)%10, true) );
        _display->putCharToView(110, 37, view, getChar(stat.flyCount) );
        _display->putCharToView(117, 37, view, 'x' );

        _display->putCharToView( 98, 47, view, getChar((stat.flyCount/100)%100, true) );
        _display->putCharToView(104, 47, view, getChar((stat.runCount/10)%10, true) );
        _display->putCharToView(110, 47, view, getChar(stat.runCount) );
        _display->putCharToView(117, 47, view, 'x' );

        _display->putCharToView( 98, 57, view, getChar((stat.flyCount/100)%100, true) );
        _display->putCharToView(104, 57, view, getChar((stat.fishCount/10)%10, true) );
        _display->putCharToView(110, 57, view, getChar(stat.fishCount) );
        _display->putCharToView(117, 57, view, 'x' );

        _display->putCharToView( 98, 67, view, getChar((stat.flyCount/100)%100, true) );
        _display->putCharToView(104, 67, view, getChar((stat.shotCount/10)%10, true) );
        _display->putCharToView(110, 67, view, getChar(stat.shotCount) );
        _display->putCharToView(117, 67, view, 'x' );

        int points = stat.getPoints();

        char vz = ' ';

        if(points < 0 ){
            points *= (-1);
            vz = '-';
        }

        char hun = getChar((points%1000)/1000, true);
        char ten = getChar((points%100)/10, (hun == 32) );
        char one = getChar((points%10));

        _display->putScoreCharToView(63, 87, view, vz);
        _display->putScoreCharToView(75, 87, view, hun);
        _display->putScoreCharToView(87, 87, view, ten);
        _display->putScoreCharToView(99, 87, view, one);
        _itemManager.updateItemPositions();
        _itemManager.updateViewCover(MENU_BACKGROUND_COLOR, false);
        _display->drawOneLayer( (const void**)view);
    }

    char getChar( uint8_t num, bool first = false ){
        num = num % 10;
        if( num == 0 && first ){
            return (char)32;
        }
        return (char)(num + 48);
    }

    void drawHLineToView( uint8_t y, uint8_t xStart, uint8_t xEnd, uint16_t color, uint16_t** view ){
        for( size_t x = xStart; x <= xEnd; ++x ){
            view[y][x] = color;
        }
    }

    void printHighscore( const Highscore& high){
        _itemManager.fillViewWithColor( MENU_BACKGROUND_COLOR);
        uint16_t** view = _itemManager.getCoverLayer();
        _display->initStatScreen();
        _display->writeHeadlineToView(10, 10, view, "Highscore:");
        drawHLineToView(28, 7, 103, MENU_FONT_UNMARKED, view);

        if( high.stat_first ){
            bool marked = _itemManager.processHit() == TypeIdHitboxOne;
            _display->writeToView(25, 45, "1.", view, marked );
            int points = high.stat_first->getPoints();
            char vz = ' ';
            if(points < 0 ){
                points *= (-1);
                vz = '-';
            }
            char hun = getChar((points%1000)/1000, true);
            char ten = getChar((points%100)/10, (hun == 32) );
            char one = getChar((points%10));
            if( hun != 32 ){
                _display->putCharToView(40, 45, view, vz, marked);
                _display->putCharToView(48, 45, view, hun, marked);
            }
            else{
                _display->putCharToView(48, 45, view, vz, marked);
            }
            _display->putCharToView(56, 45, view, ten, marked);
            _display->putCharToView(64, 45, view, one, marked);
        }
        if( high.stat_second ){
            bool marked = _itemManager.processHit() == TypeIdHitboxTwo;
            _display->writeToView(25, 60, "2.", view, marked );
            int points = high.stat_second->getPoints();
            char vz = ' ';
            if(points < 0 ){
                points *= (-1);
                vz = '-';
            }
            char hun = getChar((points%1000)/1000, true);
            char ten = getChar((points%100)/10, (hun == 32) );
            char one = getChar((points%10));

            if( hun != 32 ){
                _display->putCharToView(40, 60, view, vz, marked);
                _display->putCharToView(48, 60, view, hun, marked);
            }
            else{
                _display->putCharToView(48, 60, view, vz, marked);
            }

            _display->putCharToView(56, 60, view, ten, marked);
            _display->putCharToView(64, 60, view, one, marked);
        }
        if( high.stat_third ){
            bool marked = _itemManager.processHit() == TypeIdHitboxThree;
            _display->writeToView(25, 75, "3.", view, marked );
            int points = high.stat_third->getPoints();
            char vz = ' ';
            if(points < 0 ){
                points *= (-1);
                vz = '-';
            }
            char hun = getChar((points%1000)/1000, true);
            char ten = getChar((points%100)/10, (hun == 32) );
            char one = getChar((points%10));

            if( hun != 32 ){
                _display->putCharToView(40, 75, view, vz, marked);
                _display->putCharToView(48, 75, view, hun, marked);
            }
            else{
                _display->putCharToView(48, 75, view, vz, marked);
            }
            _display->putCharToView(56, 75, view, ten, marked);
            _display->putCharToView(64, 75, view, one, marked);
        }

        _itemManager.updateItemPositions();
        _itemManager.updateViewCover(MENU_BACKGROUND_COLOR, false);
        _display->drawOneLayer( (const void**)view);
    }
};




#endif /* GRAPHICMANAGER_H_ */
