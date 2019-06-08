/*
 * grouserun.h
 *
 *  Created on: 08.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_GROUSERUN_H_
#define GRAPHIC_MAPITEM_GROUSERUN_H_

#include "mapitembase.h"

extern const uint8_t GROUSERUN_ANIMATION_SPEED;

extern const uint16_t grouserun_x;
extern const uint16_t grouserun_y;

extern const uint16_t GROUSERUN_RIGHT_START_X;
extern const uint16_t GROUSERUN_RIGHT_START_Y;
extern const uint16_t GROUSERUN_LEFT_START_X;
extern const uint16_t GROUSERUN_LEFT_START_Y;

extern const uint16_t image_grouserun_1[644];
extern const uint16_t image_grouserun_2[644];
extern const uint16_t image_grouserun_3[644];
extern const uint16_t image_grouserun_4[644];
extern const uint16_t image_grouserun_5[644];

class GrouseRun : public MapItemBase{

private:

    size_t _actImg;
    int _imgCounter;
    const uint16_t* _imgOrder[5];
    Point * _path;
    bool _outOfMap;

public:

    GrouseRun()
    : MapItemBase(grouserun_x, grouserun_y, image_grouserun_1, 5), _actImg(0), _imgCounter(0), _outOfMap(false)
    {
        _imgOrder[0] = &image_grouserun_1[0];
        _imgOrder[1] = &image_grouserun_2[0];
        _imgOrder[2] = &image_grouserun_3[0];
        _imgOrder[3] = &image_grouserun_4[0];
        _imgOrder[4] = &image_grouserun_5[0];

        //Point start = getRandomBorderPoint();

        //_corn->lUp.x = start.x;
        //_corn->lUp.y = start.x;
        _corn->lUp.x = GROUSERUN_RIGHT_START_X - grouserun_x;
        _corn->lUp.y = GROUSERUN_RIGHT_START_Y;

        _corn->rLow.x = _corn->lUp.x + grouserun_x;
        _corn->rLow.y = _corn->lUp.y + grouserun_y;

        _path = nullptr;
        //_path = new Point;
        //Point end = getPathPoint(start);
        //*_path = end;
        /*
        if( start.x < end.x ){
            _img_reverse = true;
        }
        */
        _img_reverse = true;
    }

    virtual ~GrouseRun(){
        if( _path ){
            delete _path;
        }
    }

    virtual void update_position() override{

        if( _path != nullptr ){
          // move();
        }


        if( _imgCounter < GROUSERUN_ANIMATION_SPEED){
            ++_imgCounter;
        }
        else{
            _imgCounter = 0;
            ++_actImg;
            if( _actImg > 4 ){
                _actImg = 0;
            }
            _image = _imgOrder[_actImg];
        }

    }

    virtual bool outOfMap(){
        return false;
    }

};




#endif /* GRAPHIC_MAPITEM_GROUSERUN_H_ */
