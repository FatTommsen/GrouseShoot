/*
 * interfacemapitem.h
 *
 *  Created on: 24.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_INTERFACEMAPITEM_H_
#define GRAPHIC_INTERFACEMAPITEM_H_

class InterfaceMapItem{

public:
    virtual bool cover_callback( size_t x, size_t y, uint16_t& color ) = 0;
    virtual void update_position() = 0;
    virtual ~InterfaceMapItem() = default;
};



#endif /* GRAPHIC_INTERFACEMAPITEM_H_ */
