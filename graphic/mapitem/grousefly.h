/*
 * grouse_fly.h
 *
 *  Created on: 26.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_GROUSEFLY_H_
#define GRAPHIC_GROUSEFLY_H_

#include "../../util/util.h"
#include "mapitembase.h"

extern uint16_t grouse_fly_x;
extern uint16_t grouse_fly_y;

extern uint16_t image_grouse_fly_up[240];
extern uint16_t image_grouse_fly_mid[240];
extern uint16_t image_grouse_fly_low[240];

extern const uint8_t GROUSE_FLY_SPEED;
extern const uint8_t GROUSEFLY_ANIMATION_SPEED;

class GrouseFly : public MapItemBase{

private:

    size_t _actImg;
    int _imgCounter;
    const uint16_t* _imgOrder[4];
    Point * _path;
    bool _outOfMap;

public:

    GrouseFly()
    : MapItemBase(grouse_fly_x, grouse_fly_y, image_grouse_fly_up, 3), _actImg(0), _imgCounter(0), _outOfMap(false)
    {
        _imgOrder[0] = &image_grouse_fly_up[0];
        _imgOrder[1] = &image_grouse_fly_mid[0];
        _imgOrder[2] = &image_grouse_fly_low[0];
        _imgOrder[3] = &image_grouse_fly_mid[0];

        Point start = getRandomBorderPoint();

        _corn->lUp.x = start.x;
        _corn->lUp.y = start.y;

        _corn->rLow.x = _corn->lUp.x + grouse_fly_x;
        _corn->rLow.y = _corn->lUp.y + grouse_fly_y;

        _path = new Point;
        Point end = getPathPoint(start);
        *_path = end;

        if( start.x < end.x ){
            _img_reverse = true;
        }
    }

    virtual ~GrouseFly(){
        delete _path;
    }

    virtual void update_position() override{

        if( _path != nullptr ){
           move();
        }


        if( _imgCounter < GROUSEFLY_ANIMATION_SPEED){
            ++_imgCounter;
        }
        else{
            _imgCounter = 0;
            ++_actImg;
            if( _actImg > 3 ){
                _actImg = 0;
            }
            _image = _imgOrder[_actImg];
        }

    }

    virtual bool outOfMap() override{
        return _outOfMap;
    }

private:

    void move(){
        if( _corn->lUp.x <= _path->x ){
            //left to right
            if( _path->x - _corn->lUp.x > GROUSE_FLY_SPEED ){
                double m = (double)(_corn->lUp.y - _path->y) / (double)(_corn->lUp.x - _path->x);
                _corn->lUp.x += GROUSE_FLY_SPEED;
                _corn->lUp.y += round( m * (double)GROUSE_FLY_SPEED );
            }
            else{
                //item out of map
                _outOfMap = true;
            }

        }
        else{
            //right to left
            if( _corn->rLow.x - _path->x > GROUSE_FLY_SPEED ){
                double m = (double)(_corn->lUp.y - _path->y) / (double)(_corn->rLow.x - _path->x);
                _corn->lUp.x -= GROUSE_FLY_SPEED;
                _corn->lUp.y -= round( m * (double)GROUSE_FLY_SPEED );
            }
            else{
                //item out of map
                _outOfMap = true;
            }
        }
        _corn->rLow.x = _corn->lUp.x + grouse_fly_x;
        _corn->rLow.y = _corn->lUp.y + grouse_fly_y;
    }



};



#endif /* GRAPHIC_GROUSEFLY_H_ */
