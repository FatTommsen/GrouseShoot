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

extern const uint8_t GROUSE_FISHING_START_X;
extern const uint8_t GROUSE_FISHING_START_Y;

class GrouseFishing : public MapItemBase{

public:

    GrouseFishing()
    : MapItemBase( grouse_fishing_x, grouse_fishing_y, image_grouse_fishing )
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
        return;
    }

    virtual bool outOfMap() override{
        //fishing grouse can no be out of map
        return false;
    }

};



#endif /* GRAPHIC_GROUSEFISHING_H_ */
