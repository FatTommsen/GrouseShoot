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
#include "String.h"


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
        _display->writeToView(98, 37, to_String(stat.flyCount).fill_left(3) + "x", view);
        _display->writeToView(15, 47, "Run     ( 5):", view );
        _display->writeToView(98, 47, to_String(stat.runCount).fill_left(3) + "x", view);
        _display->writeToView(15, 57, "Fishing ( 2):", view );
        _display->writeToView(98, 57, to_String(stat.fishCount).fill_left(3) + "x", view);
        _display->writeToView(15, 67, "Shots   (-1):", view );
        _display->writeToView(98, 67, to_String(stat.shotCount).fill_left(3) + "x", view);

        int points = stat.getPoints();

        _display->putScoreStringToView(80, 87, view, to_String(points).fill_left(4));

        _itemManager.updateItemPositions();
        _itemManager.updateViewCover(MENU_BACKGROUND_COLOR, false);
        _display->drawOneLayer( (const void**)view);
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
            int points = high.stat_first->getPoints();
            _display->writeToView(25, 45, "1.  " + to_String(points).fill_left(4), view, marked );

        }
        if( high.stat_second ){
            bool marked = _itemManager.processHit() == TypeIdHitboxTwo;
            int points = high.stat_second->getPoints();
            _display->writeToView(25, 60, "2.  " + to_String(points).fill_left(4), view, marked );
        }
        if( high.stat_third ){
            bool marked = _itemManager.processHit() == TypeIdHitboxThree;
            int points = high.stat_third->getPoints();
            _display->writeToView(25, 75, "3.  " + to_String(points).fill_left(4), view, marked );
        }

        _itemManager.updateItemPositions();
        _itemManager.updateViewCover(MENU_BACKGROUND_COLOR, false);
        _display->drawOneLayer( (const void**)view);
    }
};




#endif /* GRAPHICMANAGER_H_ */
