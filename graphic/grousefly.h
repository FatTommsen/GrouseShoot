/*
 * grouse_fly.h
 *
 *  Created on: 26.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_GROUSEFLY_H_
#define GRAPHIC_GROUSEFLY_H_

#include "interfacemapitem.h"
#include "util.h"

extern uint16_t grouse_fly_x;
extern uint16_t grouse_fly_y;
extern uint16_t grouse_fly_trans;

extern uint16_t image_grouse_fly_up[240];
extern uint16_t image_grouse_fly_mid[240];
extern uint16_t image_grouse_fly_low[240];

class GrouseFly : public InterfaceMapItem{

protected:

    size_t _actImg;
    int _imgCounter;
    const uint16_t* _imgOrder[4];
    Corners* _corn;
    Point * _path;

public:

    GrouseFly( uint16_t start_x, uint16_t start_y )
    : _actImg(0), _imgCounter(0)
    {
        _imgOrder[0] = &image_grouse_fly_up[0];
        _imgOrder[1] = &image_grouse_fly_mid[0];
        _imgOrder[2] = &image_grouse_fly_low[0];
        _imgOrder[3] = &image_grouse_fly_mid[0];
        _corn = new Corners;
        _corn->lUp.x = start_x;
        _corn->lUp.y = start_y;

        _corn->rLow.x = _corn->lUp.x + grouse_fly_x;
        _corn->rLow.y = _corn->lUp.y + grouse_fly_y;

        _path = new Point;
    }

    virtual ~GrouseFly(){
        delete _corn;
        delete _path;
    }

    virtual void update_position() override{

        move();

        if( _imgCounter < 1){
            ++_imgCounter;
        }
        else{
            _imgCounter = 0;
            ++_actImg;
            if( _actImg > 3 ){
                _actImg = 0;
            }
        }

    }

    virtual bool cover_callback( size_t x, size_t y, uint16_t& color ) override{

        if( x >= _corn->lUp.x && x < _corn->rLow.x && y >= _corn->lUp.y && y < _corn->rLow.y ){
            //size_t rel_x = x - _corn->lUp.x;
            //size_t rel_y = y - _corn->lUp.y;
            size_t index = (y-_corn->lUp.y) * grouse_fly_x + (x-_corn->lUp.x);

            if( _imgOrder[_actImg][index] != grouse_fly_trans ){
                color = _imgOrder[_actImg][index];
                return true;
            }
        }

        return false;
    }

    void setPath( Point& p ){
        _path->x = p.x;
        _path->y = p.y;
    }

private:

    void move(){

    }



};



#endif /* GRAPHIC_GROUSEFLY_H_ */
