/*
 * cartridge.h
 *
 *  Created on: 07.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_CARTRIDGE_H_
#define GRAPHIC_MAPITEM_CARTRIDGE_H_

#include "viewitembase.h"

extern const uint8_t DISPLAY_SIZE;

extern const uint8_t cartridge_x;
extern const uint8_t cartridge_y;
extern const uint16_t image_cartridge[144];

class Cartridge : public ViewItemBase{

private:


public:

    Cartridge( uint8_t offset )
    : ViewItemBase( cartridge_x, cartridge_y, image_cartridge, 2 )
    {
        _corn->lUp.y = DISPLAY_SIZE - (cartridge_y + 3);
        _corn->lUp.x = DISPLAY_SIZE - cartridge_x - offset * ( cartridge_x - 1 ) - 2;

        _corn->rLow.x = _corn->lUp.x + cartridge_x;
        _corn->rLow.y = _corn->lUp.y + cartridge_y;
    }

    ~Cartridge(){

    }

    virtual void update_position(){
        //catridge do not move
        return;
    }

};



#endif /* GRAPHIC_MAPITEM_CARTRIDGE_H_ */
