/*
 * interfacemapitem.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

/*
 * TypeIDs:
 * 1 = Crosshair
 * 2 = Cartridge
 * 3 = GrouseFly
 * 4 = GrouseFishing
 * 5 = GrouseRun
 */

#define TypeIdCrosshair     1
#define TypeIdCartridge     2
#define TypeIdGrouseFly     3
#define TypeIdGrouseFishing 4
#define TypeIdGrouseRun     5

#ifndef GRAPHIC_INTERFACEMAPITEM_H_
#define GRAPHIC_INTERFACEMAPITEM_H_

#include "../../util/util.h"

class ItemBase{

protected:

    Corners* _corn;
    const uint16_t _image_x;
    const uint16_t _image_y;
    const uint16_t* _image;
    const uint16_t _type_id;

public:

    virtual void update_position() = 0;

    ItemBase( const uint16_t image_x, const uint16_t image_y, const uint16_t* image, const uint16_t type_id )
    : _image_x(image_x), _image_y(image_y), _image(image), _type_id(type_id)
    {
        _corn = new Corners;
    }

    virtual ~ItemBase(){
        delete _corn;
    }

    const uint16_t getTypeId(){
        return _type_id;
    }

    const Corners& getCorners(){
        return *_corn;
    }
};



#endif /* GRAPHIC_INTERFACEMAPITEM_H_ */
