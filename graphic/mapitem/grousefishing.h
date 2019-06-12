/*
 * grousefishing.h
 *
 *  Created on: 28.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_GROUSEFISHING_H_
#define GRAPHIC_GROUSEFISHING_H_

#include "../../util/util.h"
#include "mapitembase.h"

extern const uint16_t grouse_fishing_x;
extern const uint16_t grouse_fishing_y;
extern const uint16_t image_grouse_fishing[1400];
extern const uint8_t image_symbols_flag_2;


class GrouseFishing : public MapItemBase{

public:

    GrouseFishing()
    : MapItemBase( grouse_fishing_x, grouse_fishing_y, image_grouse_fishing, TypeIdGrouseFishing, image_symbols_flag_2 )
    {
        _corn->lUp.x = GROUSE_FISHING_START_X;
        _corn->lUp.y = GROUSE_FISHING_START_Y;

        _corn->rLow.x = _corn->lUp.x + grouse_fishing_x;
        _corn->rLow.y = _corn->lUp.y + grouse_fishing_y;

    }

    virtual ~GrouseFishing(){

    }

    virtual void update_position() override{
        //fishing grouse can not be moved
        if(!_alive){
            if(_pointCounter < 7){
                ++_pointCounter;
                _corn->lUp.y -= 1;
                _corn->rLow.y -= 1;
            }
            else{
                _outOfMap = true;
            }
        }
        return;
    }

    virtual bool outOfMap() override{
        //fishing grouse can no be out of map
        return _outOfMap;
    }

};



#endif /* GRAPHIC_GROUSEFISHING_H_ */
