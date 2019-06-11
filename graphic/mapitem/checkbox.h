/*
 * checkbox.h
 *
 *  Created on: 11.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_CHECKBOX_H_
#define GRAPHIC_MAPITEM_CHECKBOX_H_

#include "menuitembase.h"

extern const uint8_t image_symbols_x;
extern const uint8_t image_Symbols_y;
extern const uint8_t image_symbols_flag_box;
extern const uint8_t image_symbols_flag_haken;

extern const uint8_t image_symbols[572];

class CheckBox : public MenuItemBase{

private:

    bool _set;
    bool _marked;

public:

    CheckBox()
    : MenuItemBase( image_symbols_x, image_Symbols_y, nullptr, TypeIdMenuEntryCheckbox), _set(true), _marked(false)
    {
        _corn->lUp.x = MENU_ENTRY_CHECKBOX_X;
        _corn->lUp.y = MENU_ENTRY_CHECKBOX_Y;

        _corn->rLow.x = _corn->lUp.x + image_symbols_x;
        _corn->rLow.y = _corn->lUp.y + image_Symbols_y;
    }

    virtual ~CheckBox(){

    }

    virtual void update_position( const Point& p ){
        if(gotHit(p)){
            _marked = true;
        }
        else{
            _marked = false;
        }
    }

    virtual void drawItem( uint16_t** view_cover ){

        size_t x_img = 0;
        size_t y_img = 0;
        for( size_t y = _corn->lUp.y; y < _corn->rLow.y; ++y ){
            for( size_t x = _corn->lUp.x; x < _corn->rLow.x; ++x ){
                uint8_t color = image_symbols[y_img * _image_x + x_img];
                if( color ){
                    if(color & image_symbols_flag_box){
                        if(_marked){
                            view_cover[y][x] = MENU_FONT_MARKED;
                        }
                        else{
                            view_cover[y][x] = MENU_FONT_UNMARKED;
                        }
                    }
                    if(_set && (color & image_symbols_flag_haken)){
                        view_cover[y][x] = MENU_CHECKBOX_CHECK;
                    }

                }

                ++x_img;
            }
            ++y_img;
            x_img = 0;
        }
    }

    void toggle(){
        _set = (!_set);
    }
};





#endif /* GRAPHIC_MAPITEM_CHECKBOX_H_ */
