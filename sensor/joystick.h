/*
 * joystick.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef SENSOR_JOYSTICK_H_
#define SENSOR_JOYSTICK_H_

#include "adc14_msp432.h"

const int joystick_trigger = 200;

class Joystick{

private:
    adc14_msp432_channel* _joyX;
    adc14_msp432_channel* _joyY;

    int _moveX;
    int _moveY;

    uint16_t _offset;
public:

    Joystick()
    : _moveX(0), _moveY(0)
    {
        _joyX = new adc14_msp432_channel(15);
        _joyX->adcMode(ADC::ADC_10_BIT);

        _joyY = new adc14_msp432_channel(9);
        _joyY->adcMode(ADC::ADC_10_BIT);

        _offset = _joyX->adcReadRaw();
    }

    ~Joystick(){
        delete _joyX;
        delete _joyY;
    }

    void measure(){
        int x = _joyX->adcReadRaw() - _offset;
        int y = _joyY->adcReadRaw() - _offset;

        if( x < joystick_trigger * (-1)){
            _moveX = -1;
        }
        else if( x > joystick_trigger ){
            _moveX = 1;
        }
        else{
            _moveX = 0;
        }

        if( y < joystick_trigger * (-1) ){
            _moveY = 1;
        }
        else if( y > joystick_trigger ){
            _moveY = -1;
        }
        else{
            _moveY = 0;
        }
    }

    int getAndResetX(){
        int x = _moveX;
        _moveX = 0;
        return x;
    }

    int getAndResetY(){
        int y = _moveY;
        _moveY = 0;
        return y;
    }
};



#endif /* SENSOR_JOYSTICK_H_ */
