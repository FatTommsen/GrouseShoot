/*
 * grousefishing.h
 *
 *  Created on: 28.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_GROUSEFISHING_H_
#define GRAPHIC_GROUSEFISHING_H_

#include "interfacemapitem.h"
#include "util.h"

extern const uint16_t grouse_fishing_x;
extern const uint16_t grouse_fishing_y;
extern const uint16_t grouse_fishing_trans;
extern const uint16_t image_grouse_fishing[1400];

class GrouseFishing : public InterfaceMapItem{

protected:

    Corners* _corn;

public:

    GrouseFishing( uint16_t start_x, uint16_t start_y ){
        _corn = new Corners;
        _corn->lUp.x = start_x;
        _corn->lUp.y = start_y;

        _corn->rLow.x = _corn->lUp.x + grouse_fishing_x;
        _corn->rLow.y = _corn->lUp.y + grouse_fishing_y;

    }

    virtual ~GrouseFishing(){
        delete _corn;
    }

    virtual void update_position() override{

    }

    virtual bool cover_callback( size_t x, size_t y, uint16_t& color ) override{

        if( x >= _corn->lUp.x && x < _corn->rLow.x && y >= _corn->lUp.y && y < _corn->rLow.y ){
            //size_t rel_x = x - _corn->lUp.x;
            //size_t rel_y = y - _corn->lUp.y;
            size_t index = (y-_corn->lUp.y) * grouse_fishing_x + (x-_corn->lUp.x);

            if( image_grouse_fishing[index] != grouse_fishing_trans ){
                color = image_grouse_fishing[index];
                return true;
            }
        }

        return false;
    }

};



#endif /* GRAPHIC_GROUSEFISHING_H_ */
