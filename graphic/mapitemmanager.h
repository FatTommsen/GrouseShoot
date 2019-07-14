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
#include "mapitem/grousestart.h"
#include "mapitem/menuentry.h"
#include "mapitem/checkbox.h"
#include "mapitem/symbol.h"
#include "mapitem/itemhitbox.h"

#include "mapitem/mapitembase.h"
#include "mapitem/viewitembase.h"
#include "mapitem/menuitembase.h"

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
    List<MenuItemBase>* _menuItems;


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
        _menuItems = new List<MenuItemBase>;

        //_itemList->push_back(new GrouseFishing);
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

        List<MapItemBase>::elem* itMapItem = _itemList->_head;
        while(itMapItem != nullptr){
            itMapItem->_data->update_position();
            itMapItem = itMapItem->_next;
        }

        Point p;
        const Corners& crosshairCorners = _topLevelItem->getCorners();
        p.x = crosshairCorners.lUp.x + 8;
        p.y = crosshairCorners.lUp.y + 8;
        List<MenuItemBase>::elem* itMenuItem = _menuItems->_head;
        while( itMenuItem != nullptr ){
            itMenuItem->_data->update_position(p);
            itMenuItem = itMenuItem->_next;
        }

    }

    void fillViewWithColor( uint16_t color ){
        for(size_t x = 0; x < DISPLAY_SIZE; ++x ){
            for(size_t y = 0; y < DISPLAY_SIZE; ++y ){
                _view_cover[x][y] = color;
            }
        }
    }

    //void updateViewCover( uint16_t backgroundColor, bool showTopLevelItem = true ){
    void updateViewCover( uint16_t backgroundColor, bool fillViewFirst = true ){
        if( fillViewFirst ){
            fillViewWithColor( backgroundColor );
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

        //menu items
        List<MenuItemBase>::elem* it_menu = _menuItems->_head;
        while( it_menu != nullptr ){
            it_menu->_data->drawItem(_view_cover);
            it_menu = it_menu->_next;
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

    void spawnGrouseRun(){
        _itemList->push_back(new GrouseRun);
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

    int processHit(){
        const Corners& crosshairCorners = _topLevelItem->getCorners();
        if( getCartridgeCount() > 0 ){
            Point p;
            p.x = ((double)( crosshairCorners.rLow.x - crosshairCorners.lUp.x ) / 2 ) + _mapCorners->lUp.x + crosshairCorners.lUp.x;
            p.y = ((double)( crosshairCorners.rLow.y - crosshairCorners.lUp.y ) / 2 ) + _mapCorners->lUp.y + crosshairCorners.lUp.y;


            if(_singleItem != nullptr ){
                if( _singleItem->gotHit(p)){
                    return _singleItem->getTypeId();
                }
            }

            List<MapItemBase>::elem* itMapItem = _itemList->_head;
            while( itMapItem != nullptr ){
                if( itMapItem->_data->gotHit(p) ){
                    return itMapItem->_data->getTypeId();
                }
                itMapItem = itMapItem->_next;
            }
        }
        Point p;
        p.x = crosshairCorners.lUp.x + 8;
        p.y = crosshairCorners.lUp.y + 8;

        List<MenuItemBase>::elem* itMenuItem = _menuItems->_head;
        while(itMenuItem != nullptr){
            if( itMenuItem->_data->gotHit(p) ){
                return itMenuItem->_data->getTypeId();
            }
            itMenuItem = itMenuItem->_next;
        }

        return 0;
    }

    void registerMapCorners( const Corners& corn ){
        _mapCorners = &corn;
    }


    void clearItems(){
        if(_singleItem != nullptr){
            delete _singleItem;
            _singleItem = nullptr;
        }

        for( size_t i = _magazine->_size; i > 0 ; --i ){
            _magazine->remove(_magazine->_tail->_data);
        }

        for( size_t i = _itemList->_size; i > 0 ; --i ){
            _itemList->remove(_itemList->_tail->_data);
        }

        for( size_t i = _menuItems->_size; i > 0 ; --i ){
            _menuItems->remove(_menuItems->_tail->_data);
        }

    }

    void buildStartScreen(bool includeHighscore){
        clearItems();
        _menuItems->push_back(new GrouseStart);
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntryStart));
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntrySettings));
        if( includeHighscore ){
            _menuItems->push_back(new MenuEntry(TypeIdMenuEntryHighscore));
        }
    }

    void buildGameScreen(){
        clearItems();
        _itemList->push_back(new GrouseFishing);
        _itemList->push_back(new GrouseFly);
        _itemList->push_back(new GrouseRun);
    }

    void updateStartScreen(){

    }

    void buildSettingsScreen(const Settings& settings){
        clearItems();
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntryAutoreload));
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntryOk));
        _menuItems->push_back(new CheckBox (settings.reload));
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntryNavigation));
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntryCrosshair));
        _menuItems->push_back(new Symbol(TypeIdSymbolNavigation, settings.mapViaGSensor));
        _menuItems->push_back(new Symbol(TypeIdSymbolCrosshair, settings.mapViaGSensor));
        _menuItems->push_back(new Symbol(TypeIdSymbolSwitch, false));
    }

    void buildStatHighScreen(){
        clearItems();
        _menuItems->push_back(new MenuEntry(TypeIdMenuEntryOk));
    }

    void buildHighscoreHitboxes( uint8_t amount ){
        if(amount >= 1 ){
            _menuItems->push_back( new ItemHitBox(TypeIdHitboxOne));
        }
        if(amount >= 2 ){
            _menuItems->push_back( new ItemHitBox(TypeIdHitboxTwo));
        }
        if(amount >= 3 ){
            _menuItems->push_back( new ItemHitBox(TypeIdHitboxThree));
        }
    }

    void toggleAllCheckboxes(){
        List<MenuItemBase>::elem* it = _menuItems->_head;
        while( it != nullptr ){
            if( it->_data->getTypeId() == TypeIdMenuEntryCheckbox ){
                (static_cast<CheckBox*>(it->_data))->toggle();
            }
            it = it->_next;
        }
    }

    void toggleSettingSymbols(){
        List<MenuItemBase>::elem* it = _menuItems->_head;
        while( it != nullptr ){
            if( it->_data->getTypeId() == TypeIdSymbolCrosshair || it->_data->getTypeId() == TypeIdSymbolNavigation ){
                (static_cast<Symbol*>(it->_data))->toggle();
            }
            it = it->_next;
        }
    }

    void toggleTopLevelNavigation(){
        (static_cast<Crosshair*>(_topLevelItem))->toggleNavigation();
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
