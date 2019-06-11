/*
 * menuitembase.h
 *
 *  Created on: 11.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_MENUITEMBASE_H_
#define GRAPHIC_MAPITEM_MENUITEMBASE_H_

#include <cstdio>
#include "itembase.h"
#include "../../util/util.h"

class MenuItemBase : public ItemBase{

protected:

public:
    MenuItemBase( const uint16_t image_x, const uint16_t image_y, const uint16_t* image, const uint16_t type_id )
    : ItemBase( image_x, image_y, image, type_id)
    {

    }

    virtual ~MenuItemBase(){

    }

    virtual void drawItem( uint16_t** view_cover ){

        size_t x_img = 0;
        size_t y_img = 0;
        for( size_t y = _corn->lUp.y; y < _corn->rLow.y; ++y ){
            for( size_t x = _corn->lUp.x; x < _corn->rLow.x; ++x ){
                uint16_t color = _image[y_img * _image_x + x_img];
                if( color != TRANSPARENT_COLOR ){
                    view_cover[y][x] = color;
                }
                ++x_img;
            }
            ++y_img;
            x_img = 0;
        }

    }

    virtual void update_position( const Point& p ) = 0;

    virtual void update_position(){

    }

    bool gotHit( const Point& p ){
        if( _corn->lUp.x <= p.x && _corn->rLow.x >= p.x && _corn->lUp.y <= p.y && _corn->rLow.y >= p.y ){
            return true;
        }
        return false;
    }
};




#endif /* GRAPHIC_MAPITEM_MENUITEMBASE_H_ */
