/*
 * grouseflyreverse.h
 *
 *  Created on: 27.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_GROUSEFLYREVERSE_H_
#define GRAPHIC_GROUSEFLYREVERSE_H_

//#include "grousefly.h"
//
//class GrouseFlyReverse : public GrouseFly{
//
//private:
//
//
//public:
//
//    GrouseFlyReverse(size_t x, size_t y)
//    : GrouseFly( x, y)
//    {
//
//    }
//
//
//    virtual bool cover_callback( size_t x, size_t y, uint16_t& color ) override{
//
//        if( x >= _corn->lUp.x && x < _corn->rLow.x && y >= _corn->lUp.y && y < _corn->rLow.y ){
//            //size_t rel_x = x - _corn->lUp.x;
//            //size_t rel_y = y - _corn->lUp.y;
//            size_t index = (y-_corn->lUp.y) * grouse_fly_x + (_corn->lUp.x + grouse_fly_x -1 - x);
//
//            if( _imgOrder[_actImg][index] != grouse_fly_trans ){
//                color = _imgOrder[_actImg][index];
//                return true;
//            }
//        }
//
//        return false;
//    }
//
//
//};




#endif /* GRAPHIC_GROUSEFLYREVERSE_H_ */
