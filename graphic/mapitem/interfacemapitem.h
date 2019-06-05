/*
 * interfacemapitem.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_INTERFACEMAPITEM_H_
#define GRAPHIC_MAPITEM_INTERFACEMAPITEM_H_

#include "interfaceitem.h"
#include "../../util/random.h"

extern const size_t map_size_x;
extern const size_t map_size_y;

class InterfaceMapItem : public InterfaceItem{

public:

    virtual bool outOfMap() = 0;
    virtual bool isInView() = 0;

private:

    Point getRandomBorderPoint(){
        Point p;
        Random& rand = Random::getInstance();
        double dmap_size_x = map_size_x;
        double dmap_size_y = map_size_y;
        size_t index = rand.next() * ( dmap_size_x + dmap_size_y);
        if( index < 0.5 * dmap_size_y ){
            //left site
            p.x = 0;
            p.y = 0.5 * dmap_size_y - index;
        }
        else if( index < 0.5 * dmap_size_y + dmap_size_x ){
            p.x = index - dmap_size_y * 0.5;
            p.y = 0;
        }
        else{
            p.x = dmap_size_x;
            p.y = index - dmap_size_y * 0.5 - dmap_size_x;
        }

        return p;
    }

    Point getPathPoint( Point& start ){
        Point p;
        Random& rand = Random::getInstance();
        double dmap_size_x = map_size_x;
        double dmap_size_y = map_size_y;
        if( start.x == 0 ){
            size_t index = rand.next() * (dmap_size_x + 0.5 * dmap_size_y);
            if( index < dmap_size_x ){
                p.x = index;
                p.y = 0;
            }
            else{
                p.x = index - dmap_size_x;
            }
        }
        else if( start.x == dmap_size_x ){
            size_t index = rand.next() * (dmap_size_x + 0.5 * dmap_size_y);
            if( index <= 0.5 * dmap_size_y ){
                p.x = 0;
                p.y = dmap_size_y - index;
            }
            else{
                p.x = index - dmap_size_y;
                p.y = 0;
            }
        }
        else{
            size_t index = rand.next() * dmap_size_y;
            if( index < 0.5 * dmap_size_y ){
                p.x = 0;
                p.y = 0.5 * dmap_size_y - index;
            }
            else{
                p.x = dmap_size_x;
                p.y = index - 0.5 * dmap_size_y;
            }
        }
        return p;
    }
};


#endif /* GRAPHIC_MAPITEM_INTERFACEMAPITEM_H_ */
