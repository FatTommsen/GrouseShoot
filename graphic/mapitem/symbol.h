/*
 * symbol.h
 *
 *  Created on: 12.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_SYMBOL_H_
#define GRAPHIC_MAPITEM_SYMBOL_H_

#include "menuitembase.h"


extern const uint8_t image_symbols_x;
extern const uint8_t image_symbols_y;
extern const uint8_t image_symbols_flag_gsensor;
extern const uint8_t image_symbols_flag_joystick;
extern const uint8_t image_symbols_flag_change;

extern const uint8_t image_symbols[572];

class Symbol : public MenuItemBase{

private:

    bool _marked;
    bool _markable;
    uint8_t _image_flag;

public:

    Symbol( uint8_t type_id, bool mapViaGSensor )
    : MenuItemBase( image_symbols_x, image_symbols_y, nullptr, type_id ), _marked(false), _markable(true)
    {
        _corn->lUp.x = MENU_SYMBOL_X;
        if( type_id == TypeIdSymbolNavigation ){
            _corn->lUp.y = MENU_SYMBOL_NAVIGATION_Y;
            if( mapViaGSensor ) {
                _image_flag = image_symbols_flag_gsensor;
            }
            else{
                _image_flag = image_symbols_flag_joystick;
            }
            _markable = false;
        }
        else if ( type_id == TypeIdSymbolCrosshair ){
            _corn->lUp.y = MENU_SYMBOL_CROSSHAIR_Y;
            _image_flag = image_symbols_flag_joystick;
            _markable = false;
            if( !mapViaGSensor ) {
                _image_flag = image_symbols_flag_gsensor;
            }
            else{
                _image_flag = image_symbols_flag_joystick;
            }
        }
        else if( type_id == TypeIdSymbolSwitch ){
            _corn->lUp.y = MENU_SYMBOL_SWITCH_Y;
            _corn->lUp.x = MENU_SYMBOL_SWITCH_X;
            _image_flag = image_symbols_flag_change;
        }

        _corn->rLow.x = _corn->lUp.x + image_symbols_x;
        _corn->rLow.y = _corn->lUp.y + image_symbols_y;
    }

    ~Symbol(){

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

        size_t x_img = 0;
        size_t y_img = 0;
        for( size_t y = _corn->lUp.y; y < _corn->rLow.y; ++y ){
            for( size_t x = _corn->lUp.x; x < _corn->rLow.x; ++x ){
                uint8_t color = image_symbols[y_img * _image_x + x_img];

                if(color & _image_flag){
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

    void toggle(){
        if(getTypeId() == TypeIdSymbolCrosshair || getTypeId() == TypeIdSymbolNavigation ){
            if(_image_flag == image_symbols_flag_gsensor){
                _image_flag = image_symbols_flag_joystick;
            }
            else if( _image_flag == image_symbols_flag_joystick ){
                _image_flag = image_symbols_flag_gsensor;
            }
        }
    }

};




#endif /* GRAPHIC_MAPITEM_SYMBOL_H_ */
