/*
 * interfacemapitem.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_INTERFACEMAPITEM_H_
#define GRAPHIC_INTERFACEMAPITEM_H_

#include "../../util/util.h"
#include "../../custom_yahal/uGUI_2layer.h"

class InterfaceItem{

protected:

    Corners* _corn;
    Corners* _oldCorn;

public:
    virtual bool cover_callback( size_t x, size_t y, uint16_t& color ) = 0;
    virtual void update_position() = 0;

    InterfaceItem(){
        _corn = new Corners;
        _oldCorn = new Corners;
    }

    virtual ~InterfaceItem(){
        delete _corn;
        delete _oldCorn;
    }

    virtual void drawItem( uGUI_2layer& gui ) = 0;
};



#endif /* GRAPHIC_INTERFACEMAPITEM_H_ */
