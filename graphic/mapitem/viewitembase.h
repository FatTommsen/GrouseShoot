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
    virtual void drawItem( uint16_t** view_cover ) = 0;
};



#endif /* GRAPHIC_MAPITEM_VIEWITEMBASE_H_ */
