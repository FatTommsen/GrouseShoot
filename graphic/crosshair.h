/*
 * crosshair.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_CROSSHAIR_H_
#define GRAPHIC_CROSSHAIR_H_

#include "util.h"
#include "interfacemapitem.h"
#include "../sensor/joystick.h"

extern const size_t view_size;
extern const uint16_t color_crosshair_full;
extern const uint16_t color_crosshair_trans;
extern const uint16_t image_crosshiar[256];

const size_t crosshair_lUp_x = 40;
const size_t crosshair_lUp_y = 40;
const size_t crosshair_scroll_per_tick = 5;


class Crosshair : public InterfaceMapItem{

private:
    Corners* _corn;
    Joystick* _joy;

public:

    Crosshair( )
    {
        _corn = new Corners();
        _corn->lUp.x = crosshair_lUp_x;
        _corn->lUp.y = crosshair_lUp_y;

        _corn->rLow.x = _corn->lUp.x + 16;
        _corn->rLow.y = _corn->lUp.y + 16;

        _joy = new Joystick();

    }

    virtual ~Crosshair(){
        delete _corn;
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

    virtual bool outOfMap() override{
        return false;
    }

private:

    void moveCrosshairH( int rows ){
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
            if( _corn->rLow.y >= view_size - 1 ){
                //already in button row
                return;
            }
            else{
                int move = view_size - _corn->rLow.y < (size_t)rows ? view_size - _corn->rLow.y : rows;
                _corn->lUp.y += move;
                _corn->rLow.y += move;
            }
        }
    }

    void moveCrosshairV( int cols ){
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
            if( _corn->rLow.x >= view_size - 1 ){
                //already in very right col
                return;
            }
            else{
                int move = view_size - _corn->rLow.x < (size_t)cols ? view_size - _corn->rLow.x : cols;
                _corn->lUp.x += move;
                _corn->rLow.x += move;
            }
        }
    }

};


#endif /* GRAPHIC_CROSSHAIR_H_ */
