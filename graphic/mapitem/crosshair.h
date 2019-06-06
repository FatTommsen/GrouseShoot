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
extern const uint16_t TRANSPARENT_COLOR;
extern const uint16_t image_crosshair[256];

extern const uint8_t CROSSHAIR_START_X;
extern const uint8_t CROSSHAIR_START_Y;
extern const uint8_t CROSSHAIR_SCROLL_SPEED;


class Crosshair : public ViewItemBase{

private:
    Joystick* _joy;

public:

    Crosshair( )
    {
        _corn->lUp.x = CROSSHAIR_START_X;
        _corn->lUp.y = CROSSHAIR_START_Y;

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

    void drawItem( uint16_t** view_cover ){

        size_t x_img = 0;
        size_t y_img = 0;
        for( size_t y = _corn->lUp.y; y < _corn->rLow.y; ++y ){
            for( size_t x = _corn->lUp.x; x < _corn->rLow.x; ++x ){
                uint16_t color = image_crosshair[y_img * 16 + x_img];
                if( color != TRANSPARENT_COLOR ){
                    view_cover[y][x] = color;
                }
                ++x_img;
            }
            ++y_img;
            x_img = 0;
        }

    }

};


#endif /* GRAPHIC_CROSSHAIR_H_ */
