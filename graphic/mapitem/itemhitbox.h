/*
 * itemhitbox.h
 *
 *  Created on: 17.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_ITEMHITBOX_H_
#define GRAPHIC_MAPITEM_ITEMHITBOX_H_

#include "menuitembase.h"

class ItemHitBox : public MenuItemBase{

private:


public:
    ItemHitBox( int type_id)
    : MenuItemBase(0, 0, nullptr, type_id )
    {
        if( type_id == TypeIdHitboxOne ){
            _corn->lUp.x = 25;
            _corn->lUp.y = 45;
        }
        else if( type_id == TypeIdHitboxTwo ){
            _corn->lUp.x = 25;
            _corn->lUp.y = 60;
        }
        else if( type_id == TypeIdHitboxThree ){
            _corn->lUp.x = 25;
            _corn->lUp.y = 75;
        }

        _corn->rLow.x = _corn->lUp.x + 72;
        _corn->rLow.y = _corn->lUp.y + 6;
    }

    virtual void drawItem( uint16_t** view_cover ){
        return;
    }

    virtual void update_position(){
        return;
    }

    virtual void update_position( const Point& p ){
        return;
    }
};




#endif /* GRAPHIC_MAPITEM_ITEMHITBOX_H_ */
