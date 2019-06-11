/*
 * grousestart.h
 *
 *  Created on: 11.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_GROUSESTART_H_
#define GRAPHIC_MAPITEM_GROUSESTART_H_

#include "menuitembase.h"

extern const uint16_t image_grouse_start_x;
extern const uint16_t image_grouse_start_y;

extern const uint16_t image_grouse_start_1[1650];
extern const uint16_t image_grouse_start_2[1650];
extern const uint16_t image_grouse_start_3[1650];

class GrouseStart : public MenuItemBase{

private:
    uint8_t _imageCounter;
    const uint16_t* _imgOrder[3];

public:

    GrouseStart()
    : MenuItemBase( image_grouse_start_x, image_grouse_start_y, image_grouse_start_1, TypeIdGrouseStart), _imageCounter(0)
    {
        _corn->lUp.x = GROUSE_START_X;
        _corn->lUp.y = GROUSE_START_Y;

        _corn->rLow.x = _corn->lUp.x + image_grouse_start_x;
        _corn->rLow.y = _corn->lUp.y + image_grouse_start_y;

        _imgOrder[0] = &image_grouse_start_1[0];
        _imgOrder[1] = &image_grouse_start_2[0];
        _imgOrder[2] = &image_grouse_start_3[0];
    }

    ~GrouseStart(){

    }

    virtual void update_position( const Point& p ){
        if( gotHit(p)){
            if(_imageCounter < 5){
                ++_imageCounter;
            }
        }
        else{
            if(_imageCounter > 0 ){
                --_imageCounter;
            }
        }

        _image = _imgOrder[_imageCounter / 2];
    }
};




#endif /* GRAPHIC_MAPITEM_GROUSESTART_H_ */
