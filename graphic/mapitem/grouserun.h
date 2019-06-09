/*
 * grouserun.h
 *
 *  Created on: 08.06.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAPITEM_GROUSERUN_H_
#define GRAPHIC_MAPITEM_GROUSERUN_H_

#include "mapitembase.h"
#include "../../util/random.h"

extern const uint16_t grouserun_x;
extern const uint16_t grouserun_y;

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
    size_t _moveCounter;
    bool _outOfMap;
    bool _leftTop;


public:

    GrouseRun()
    : MapItemBase(grouserun_x, grouserun_y, image_grouserun_1, TypeIdGrouseRun), _actImg(0), _imgCounter(0), _moveCounter(0), _outOfMap(false)
    {
        _imgOrder[0] = &image_grouserun_1[0];
        _imgOrder[1] = &image_grouserun_2[0];
        _imgOrder[2] = &image_grouserun_3[0];
        _imgOrder[3] = &image_grouserun_4[0];
        _imgOrder[4] = &image_grouserun_5[0];

        _path = new Point;
        Random rand = Random::getInstance();
        if( rand.next() > 0.5 ){
            //left to right
            _path->x = GROUSERUN_RIGHT_START_X;
            _path->y = GROUSERUN_RIGHT_START_Y;
            _img_reverse = false;
            if( rand.next() > 0.5 ){
                //left bottom
                _corn->lUp.x = GROUSERUN_LEFT_START_X_BOT;
                _corn->lUp.y = GROUSERUN_LEFT_START_Y_BOT;
                _leftTop = false;
            }
            else{
                //left top
                _corn->lUp.x = GROUSERUN_LEFT_START_X_TOP;
                _corn->lUp.y = GROUSERUN_LEFT_START_Y_TOP;
                _leftTop = true;
            }
        }
        else {
            //right to left
            _img_reverse = true;
            _corn->lUp.x = GROUSERUN_RIGHT_START_X;
            _corn->lUp.y = GROUSERUN_RIGHT_START_Y;
            if( rand.next() > 0.5 ){
                //left bottom
                _path->x = GROUSERUN_LEFT_START_X_BOT;
                _path->y = GROUSERUN_LEFT_START_Y_BOT;
                _leftTop = false;
            }
            else{
                //left top
                _path->x = GROUSERUN_LEFT_START_X_TOP;
                _path->y = GROUSERUN_LEFT_START_Y_TOP;
                _leftTop = true;
            }
        }

        _corn->rLow.x = _corn->lUp.x + grouserun_x;
        _corn->rLow.y = _corn->lUp.y + grouserun_y;

    }

    virtual ~GrouseRun(){
        if( _path ){
            delete _path;
        }
    }

    virtual void update_position() override{

        if( _path != nullptr ){
           move();
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
        return _outOfMap;
    }

private:
    void move(){
        if( _corn->lUp.x <= _path->x ){
            // left to right
            _corn->lUp.x += 2;
            if( _leftTop ){
                if( _moveCounter < 5 ){
                    ++_moveCounter;
                }
                else{
                    _moveCounter = 0;
                    _corn->lUp.y += 1;
                }
            }
            else{
                if(_moveCounter < 3){
                    ++_moveCounter;
                }
                else{
                    _moveCounter = 0;
                    _corn->lUp.y -= 1;
                }
            }
            if( _corn->lUp.x >= _path->x ){
                _outOfMap = true;
            }
        }
        else{
            // right to left
            _corn->lUp.x -= 2;
            if( _leftTop ){
                if( _moveCounter < 5 ){
                    ++_moveCounter;
                }
                else{
                    _moveCounter = 0;
                    _corn->lUp.y -= 1;
                }
            }
            else{
                if(_moveCounter < 3){
                    ++_moveCounter;
                }
                else{
                    _moveCounter = 0;
                    _corn->lUp.y += 1;
                }
            }
            if( _corn->lUp.x <= _path->x ){
                _outOfMap = true;
            }

        }

        _corn->rLow.x = _corn->lUp.x + grouserun_x;
        _corn->rLow.y = _corn->lUp.y + grouserun_y;
    }



};




#endif /* GRAPHIC_MAPITEM_GROUSERUN_H_ */
