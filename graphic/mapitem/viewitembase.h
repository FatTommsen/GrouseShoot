/*
 * interfaceviewitem.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_VIEWITEMBASE_H_
#define GRAPHIC_MAPITEM_VIEWITEMBASE_H_

#include "itembase.h"

class ViewItemBase : public ItemBase{

public:

    ViewItemBase( const uint16_t image_x, const uint16_t image_y, const uint16_t* image, const uint16_t type_id )
    : ItemBase( image_x, image_y, image, type_id )
    {

    }

    void drawItem( uint16_t** view_cover ){

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
};



#endif /* GRAPHIC_MAPITEM_VIEWITEMBASE_H_ */
