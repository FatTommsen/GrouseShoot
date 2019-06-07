/*
 * interfacemapitem.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_MAPITEMBASE_H_
#define GRAPHIC_MAPITEM_MAPITEMBASE_H_

#include "../../util/random.h"
#include "../../util/util.h"
#include "itembase.h"

extern const size_t map_size_x;
extern const size_t map_size_y;

class MapItemBase : public ItemBase{

public:

    virtual bool outOfMap() = 0;

    MapItemBase( const uint16_t image_x, const uint16_t image_y, const uint16_t* image, const uint16_t type_id )
    : ItemBase( image_x, image_y, image, type_id ), _img_reverse(false)
    {

    }

    virtual ~MapItemBase() = default;

protected:

    bool _img_reverse;

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

public:

    virtual bool isInRegion( const Corners& map_corn ){
        //lUp
        if( _corn->lUp.x >= map_corn.lUp.x && _corn->lUp.x <= map_corn.rLow.x
                && _corn->lUp.y >= map_corn.lUp.y && _corn->lUp.y <= map_corn.rLow.y )
        {
            return true;
        }
        //lLow
        if( _corn->lUp.x >= map_corn.lUp.x && _corn->lUp.x <= map_corn.rLow.x
                && _corn->rLow.y >= map_corn.lUp.y && _corn->rLow.y <= map_corn.rLow.y )
        {
            return true;
        }
        //rUp
        if( _corn->rLow.x >= map_corn.lUp.x && _corn->rLow.x <= map_corn.rLow.x
                && _corn->lUp.y >= map_corn.lUp.y && _corn->lUp.y <= map_corn.rLow.y )
        {
            return true;
        }
        //rLow
        if( _corn->rLow.x >= map_corn.lUp.x && _corn->rLow.x <= map_corn.rLow.x
                && _corn->rLow.y >= map_corn.lUp.y && _corn->rLow.y <= map_corn.rLow.y )
        {
            return true;
        }
        return false;
    }

    virtual void drawItem( uint16_t** view_cover, const Corners& map_corn ) {
        if( isInRegion( map_corn )){
            size_t x_img = 0;
            size_t y_img = 0;
            for(size_t y_abs = max( map_corn.lUp.y ,_corn->lUp.y); y_abs < min( map_corn.rLow.y, _corn->rLow.y); ++ y_abs ){
                for(size_t x_abs = max( map_corn.lUp.x ,_corn->lUp.x); x_abs < min( map_corn.rLow.x, _corn->rLow.x); ++ x_abs ){
                    y_img = y_abs - _corn->lUp.y;
                    x_img = x_abs - _corn->lUp.x;
                    if( _img_reverse ){
                        x_img = _image_x - x_img;
                    }
                    view_cover[y_abs - map_corn.lUp.y][x_abs - map_corn.lUp.x] = _image[ y_img * _image_x + x_img];
                }
            }
        }
    }

};


#endif /* GRAPHIC_MAPITEM_MAPITEMBASE_H_ */
