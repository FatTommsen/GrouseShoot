/*
 * crosshair.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_CROSSHAIR_H_
#define GRAPHIC_CROSSHAIR_H_

#include "../../periphery/joystick.h"
#include "../../util/util.h"
#include "viewitembase.h"

extern const uint8_t DISPLAY_SIZE;

extern const uint16_t crosshair_x;
extern const uint16_t crosshair_y;
extern const uint16_t image_crosshair[256];

extern const uint8_t CROSSHAIR_START_X;
extern const uint8_t CROSSHAIR_START_Y;
extern const uint8_t CROSSHAIR_SCROLL_SPEED;


class Crosshair : public ViewItemBase{

private:
    Joystick* _joy;

public:

    Crosshair( )
    : ViewItemBase( crosshair_x, crosshair_y, image_crosshair, 1 )
    {
        _corn->lUp.x = CROSSHAIR_START_X;
        _corn->lUp.y = CROSSHAIR_START_Y;

        _corn->rLow.x = _corn->lUp.x + crosshair_x;
        _corn->rLow.y = _corn->lUp.y + crosshair_y;

        _joy = new Joystick();

    }

    virtual ~Crosshair(){
        delete _joy;
    }

    void update_position() override{
        _joy->measure();
        int x = _joy->getAndResetX();
        int y = _joy->getAndResetY();

        moveCrosshairH( y * CROSSHAIR_SCROLL_SPEED);
        moveCrosshairV( x * CROSSHAIR_SCROLL_SPEED);

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
                int move = _corn->lUp.y < (uint8_t)(rows * (-1)) ? _corn->lUp.y : rows * (-1);
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
                int move = DISPLAY_SIZE - _corn->rLow.y < (uint8_t)rows ? DISPLAY_SIZE - _corn->rLow.y : rows;
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
                int move = _corn->lUp.x < (uint8_t)(cols * (-1)) ? _corn->lUp.x : cols * (-1);
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
                int move = DISPLAY_SIZE - _corn->rLow.x < (uint8_t)cols ? DISPLAY_SIZE - _corn->rLow.x : cols;
                _corn->lUp.x += move;
                _corn->rLow.x += move;
            }
        }
    }

};


#endif /* GRAPHIC_CROSSHAIR_H_ */
