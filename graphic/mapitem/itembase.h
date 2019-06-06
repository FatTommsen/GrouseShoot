/*
 * interfacemapitem.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_INTERFACEMAPITEM_H_
#define GRAPHIC_INTERFACEMAPITEM_H_

#include "../../util/util.h"

class ItemBase{

protected:

    Corners* _corn;

public:

    virtual void update_position() = 0;

    ItemBase(){
        _corn = new Corners;
    }

    virtual ~ItemBase(){
        delete _corn;
    }

};



#endif /* GRAPHIC_INTERFACEMAPITEM_H_ */
