/*
 * crosshair.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_CROSSHAIR_H_
#define GRAPHIC_CROSSHAIR_H_

#include "../../periphery/joystick.h"
#include "interfaceviewitem.h"
#include "../../util/util.h"
#include "../../custom_yahal/uGUI_2layer.h"

extern const size_t DISPLAY_SIZE;
extern const uint16_t color_crosshair_full;
extern const uint16_t color_crosshair_trans;
extern const uint16_t image_crosshiar[256];

extern const size_t crosshair_lUp_x;
extern const size_t crosshair_lUp_y;
extern const size_t crosshair_scroll_per_tick;


class Crosshair : public InterfaceViewItem{

private:
    Joystick* _joy;

public:

    Crosshair( )
    {
        _corn->lUp.x = crosshair_lUp_x;
        _corn->lUp.y = crosshair_lUp_y;

        _corn->rLow.x = _corn->lUp.x + 16;
        _corn->rLow.y = _corn->lUp.y + 16;

        _joy = new Joystick();

    }

    virtual ~Crosshair(){
        delete _joy;
    }

    void update_position() override{
        _joy->measure();
        int x = _joy->getAndResetX();
        int y = _joy->getAndResetY();

        moveCrosshairH( y * crosshair_scroll_per_tick);
        moveCrosshairV( x * crosshair_scroll_per_tick);

    }

    bool cover_callback( size_t x, size_t y, uint16_t& color ) override{
        if( x >= _corn->lUp.x && x < _corn->rLow.x && y >= _corn->lUp.y && y < _corn->rLow.y ){
            size_t rel_x = x - _corn->lUp.x;
            size_t rel_y = y - _corn->lUp.y;

            if( image_crosshiar[ rel_y * 16 + rel_x] == color_crosshair_full ){
                color = color_crosshair_full;
                return true;
            }
        }

        return false;
    }


private:

    void moveCrosshairH( int rows ){
        _oldCorn->lUp.y = _corn->lUp.y;
        _oldCorn->rLow.y = _corn->rLow.y;
        if( rows == 0 ){
            //nothing to do here
            return;
        }
        else if( rows < 0 ){
            if( _corn->lUp.y <= 0 ){
                //already in top row
                return;
            }
            else{
                int move = _corn->lUp.y < (size_t)(rows * (-1)) ? _corn->lUp.y : rows * (-1);
                _corn->lUp.y -= move;
                _corn->rLow.y -= move;
            }
        }
        else{
            if( _corn->rLow.y >= DISPLAY_SIZE - 1 ){
                //already in button row
                return;
            }
            else{
                int move = DISPLAY_SIZE - _corn->rLow.y < (size_t)rows ? DISPLAY_SIZE - _corn->rLow.y : rows;
                _corn->lUp.y += move;
                _corn->rLow.y += move;
            }
        }
    }

    void moveCrosshairV( int cols ){
        _oldCorn->lUp.x = _corn->lUp.x;
        _oldCorn->rLow.x = _corn->rLow.x;
        if( cols == 0 ){
            //nothing to do here
            return;
        }
        else if( cols < 0 ){
            if( _corn->lUp.x <= 0 ){
                //already in very left col
                return;
            }
            else{
                int move = _corn->lUp.x < (size_t)(cols * (-1)) ? _corn->lUp.x : cols * (-1);
                _corn->lUp.x -= move;
                _corn->rLow.x -= move;
            }
        }
        else{
            if( _corn->rLow.x >= DISPLAY_SIZE - 1 ){
                //already in very right col
                return;
            }
            else{
                int move = DISPLAY_SIZE - _corn->rLow.x < (size_t)cols ? DISPLAY_SIZE - _corn->rLow.x : cols;
                _corn->lUp.x += move;
                _corn->rLow.x += move;
            }
        }
    }

    void drawItem( uGUI_2layer& gui ){
        if( *_oldCorn != *_corn ){
            gui.removeItemFromMap( *_oldCorn );
            *_oldCorn = *_corn;
        }
        size_t x_img = 0;
        size_t y_img = 0;
        for( size_t y = _corn->lUp.y; y < _corn->rLow.y; ++y ){
            for( size_t x = _corn->lUp.x; x < _corn->rLow.x; ++x ){
                uint16_t color = image_crosshiar[y_img * 16 + x_img];
                if( color != color_crosshair_trans ){
                    gui.DrawPixel(x, y, color| LCD::COLORTYPE_RGB565);
                }
                ++x_img;
            }
            ++y_img;
            x_img = 0;
        }
    }

};


#endif /* GRAPHIC_CROSSHAIR_H_ */
