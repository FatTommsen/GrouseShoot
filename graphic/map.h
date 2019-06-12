/*
 * map.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef GRAPHIC_MAP_H_
#define GRAPHIC_MAP_H_

#include "util/util.h"
#include "../periphery/gsensor.h"
#include "../periphery/joystick.h"

extern const size_t map_size_x;
extern const size_t map_size_y;
extern uint16_t image_map[82944];

class Map {

private:

    Corners* _corn;
    uint16_t **_view;
    GSensor& _gSen;
    Joystick& _joy;
    bool _useGSensor;

public:

    Map()
    : _gSen( GSensor::getInstance() ), _joy(Joystick::getInstance()), _useGSensor(true)
    {

        _view = new uint16_t*[DISPLAY_SIZE];
        _corn = new Corners;

        reset();

    }

    ~Map(){
        delete _corn;
        delete _view;
    }

    uint16_t** getCurrentView(){
        return _view;
    }

    void reset(){
        _corn->lUp.x = MAP_START_X;
        _corn->lUp.y = MAP_START_Y;

        _corn->rLow.x = _corn->lUp.x + DISPLAY_SIZE;
        _corn->rLow.y = _corn->lUp.y + DISPLAY_SIZE;

        updateView();
    }

    void update() {

        int x = 0;
        int y = 0;
        if(_useGSensor){
            _gSen.measure();
            x = _gSen.getAndResetX();
            y = _gSen.getAndResetY();
        }
        else{
            _joy.measure();
            x = _joy.getAndResetX();
            y = _joy.getAndResetY();
        }

        if( x != 0 || y != 0){
            moveViewH( y * MAP_SCROLL_SPEED );
            moveViewV( x * MAP_SCROLL_SPEED );
            updateView();
        }
    }

    const Corners& getCorners(){
        return *_corn;
    }

    void toggleNavigation(){
        _useGSensor = !_useGSensor;
    }

private:

    void updateView(){
        size_t lUp_y_absolute = _corn->lUp.y * map_size_x + _corn->lUp.x;
        _view[0] = &image_map[lUp_y_absolute];
        for( size_t i = 1; i < DISPLAY_SIZE; ++i ){
            _view[i] = _view[0] + i * map_size_x;
        }
    }

    void moveViewH( int rows ){
        if( rows == 0 ){
            //nothing to do here
            return;
        }
        else if( rows < 0 ){
            if( _corn->lUp.y <= 0 ){
                //already in top row
                return;
            }
            else{
                int move = _corn->lUp.y < (size_t)(rows * (-1)) ? _corn->lUp.y : rows * (-1);
                _corn->lUp.y -= move;
                _corn->rLow.y -= move;
            }
        }
        else{
            if( _corn->rLow.y >= map_size_y - 1 ){
                //already in button row
                return;
            }
            else{
                int move = map_size_y - _corn->rLow.y < (size_t)rows ? map_size_y - _corn->rLow.y : rows;
                _corn->lUp.y += move;
                _corn->rLow.y += move;
            }
        }
    }

    void moveViewV( int cols ){
        if( cols == 0 ){
            //nothing to do here
            return;
        }
        else if( cols < 0 ){
            if( _corn->lUp.x <= 0 ){
                //already in very left col
                return;
            }
            else{
                int move = _corn->lUp.x < (size_t)(cols * (-1)) ? _corn->lUp.x : cols * (-1);
                _corn->lUp.x -= move;
                _corn->rLow.x -= move;
            }
        }
        else{
            if( _corn->rLow.x >= map_size_x - 1 ){
                //already in very right col
                return;
            }
            else{
                int move = map_size_x - _corn->rLow.x < (size_t)cols ? map_size_x - _corn->rLow.x : cols;
                _corn->lUp.x += move;
                _corn->rLow.x += move;
            }
        }

    }

};



#endif /* GRAPHIC_MAP_H_ */
