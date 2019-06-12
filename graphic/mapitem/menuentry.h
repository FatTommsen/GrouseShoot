/*
 * menuentry.h
 *
 *  Created on: 11.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_MENUENTRY_H_
#define GRAPHIC_MAPITEM_MENUENTRY_H_

#include "menuitembase.h"

extern const uint16_t image_menu_combi_x;
extern const uint16_t image_menu_combi_y;

extern const uint8_t image_menu_flag_start;
extern const uint8_t image_menu_flag_settings;
extern const uint8_t image_menu_flag_highscore;
extern const uint8_t image_menu_flag_autoreload;
extern const uint8_t image_menu_flag_ok;
extern const uint8_t image_menu_flag_navigation;
extern const uint8_t image_menu_flag_crosshair;


extern const uint8_t image_menu_combi[1050];

class MenuEntry : public MenuItemBase{

private:
    bool _marked;
    bool _markable;

public:
    MenuEntry(uint8_t type_id)
    : MenuItemBase( image_menu_combi_x, image_menu_combi_y, nullptr, type_id), _marked(false), _markable(true)
    {
        _corn->lUp.x = MENU_ENTRY_X;
        if( type_id == TypeIdMenuEntryStart ){
            _corn->lUp.y = MENU_ENTRY_Y_START;
        }
        else if( type_id == TypeIdMenuEntrySettings ){
            _corn->lUp.y = MENU_ENTRY_Y_SETTINGS;
        }
        else if( type_id == TypeIdMenuEntryHighscore ){
            _corn->lUp.y = MENU_ENTRY_Y_HIGHSCORE;
        }
        else if( type_id == TypeIdMenuEntryAutoreload ){
            _corn->lUp.x = MENU_ENTRY_X_AUTO;
            _corn->lUp.y = MENU_ENTRY_Y_AUTO;
            _markable = false;
        }
        else if( type_id == TypeIdMenuEntryOk ){
            _corn->lUp.x = MENU_ENTRY_X_OK;
            _corn->lUp.y = MENU_ENTRY_Y_OK;
        }
        else if( type_id == TypeIdMenuEntryNavigation ){
            _corn->lUp.x = MENU_ENTRY_X_AUTO;
            _corn->lUp.y = MENU_ENTRY_Y_NAVIGATION;
            _markable = false;
        }
        else if( type_id == TypeIdMenuEntryCrosshair ){
            _corn->lUp.x = MENU_ENTRY_X_AUTO;
            _corn->lUp.y = MENU_ENTRY_Y_CROSSHAIR;
            _markable = false;
        }

        _corn->rLow.x = _corn->lUp.x + image_menu_combi_x;
        _corn->rLow.y = _corn->lUp.y + image_menu_combi_y;
    }

    virtual void update_position( const Point& p ){
        if(_markable){
            if(gotHit(p)){
                _marked = true;
            }
            else{
                _marked = false;
            }
        }
    }

    virtual void drawItem( uint16_t** view_cover ){
        uint8_t flag = 0;
        if( _type_id == TypeIdMenuEntryStart ){
            flag = image_menu_flag_start;
        }
        else if( _type_id == TypeIdMenuEntrySettings ){
            flag = image_menu_flag_settings;
        }
        else if( _type_id == TypeIdMenuEntryHighscore ){
            flag = image_menu_flag_highscore;
        }
        else if( _type_id == TypeIdMenuEntryAutoreload ){
            flag = image_menu_flag_autoreload;
        }
        else if( _type_id == TypeIdMenuEntryOk ){
            flag = image_menu_flag_ok;
        }
        else if( _type_id == TypeIdMenuEntryNavigation ){
            flag = image_menu_flag_navigation;
        }
        else if( _type_id == TypeIdMenuEntryCrosshair ){
            flag = image_menu_flag_crosshair;
        }

        size_t x_img = 0;
        size_t y_img = 0;
        for( size_t y = _corn->lUp.y; y < _corn->rLow.y; ++y ){
            for( size_t x = _corn->lUp.x; x < _corn->rLow.x; ++x ){
                uint8_t color = image_menu_combi[y_img * _image_x + x_img];
                if( color & flag ){
                    if(_marked){
                        view_cover[y][x] = MENU_FONT_MARKED;
                    }
                    else{
                        view_cover[y][x] = MENU_FONT_UNMARKED;
                    }
                }
                ++x_img;
            }
            ++y_img;
            x_img = 0;
        }

    }
};





#endif /* GRAPHIC_MAPITEM_MENUENTRY_H_ */
