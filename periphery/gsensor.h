/*
 * gsensor.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef PERIPHERY_GSENSOR_H_
#define PERIPHERY_GSENSOR_H_

#include "adc14_msp432.h"
#include "gpio_msp432.h"
#include "../settings.h"

class GSensor {

private:

    static GSensor* instance;

    adc14_msp432_channel* _sensorX;
    adc14_msp432_channel* _sensorY;
    adc14_msp432_channel* _sensorZ;

    int _offset;

    int _moveX;
    int _moveY;

    GSensor()
    : _offset(8192), _moveX(0), _moveY(0) {
        _sensorX = new adc14_msp432_channel(14);
        _sensorY = new adc14_msp432_channel(13);
        _sensorZ = new adc14_msp432_channel(11);

        _sensorX->adcMode(ADC::ADC_14_BIT);
        _sensorY->adcMode(ADC::ADC_14_BIT);
        _sensorZ->adcMode(ADC::ADC_14_BIT);
    }

public:

    static GSensor& getInstance(){
        if( GSensor::instance == nullptr ){
            GSensor::instance = new GSensor;
        }
        return *instance;
    }


    ~GSensor(){
        delete _sensorX;
        delete _sensorY;
        delete _sensorZ;
    }

    void measure(){
        int x = _sensorX->adcReadRaw() - _offset;
        int y = _sensorY->adcReadRaw() - _offset;

        // Analyze X-Movement
        if( x > SENSOR_TRIGGER_G ){
            _moveX = 1;
        }
        else if ( x < (-1) * SENSOR_TRIGGER_G ){
            _moveX = -1;
        }
        else{
            _moveX = 0;
        }

        // Analyze Y-Movement
        if( y > SENSOR_TRIGGER_G ){
            _moveY = -1;
        }
        else if ( y < (-1) * SENSOR_TRIGGER_G ){
            _moveY = 1;
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

    int getZ(){
        int z = _sensorZ->adcReadRaw();
        if( z < 0 ){
            z *= (-1);
        }
        return z;
    }

};



#endif /* PERIPHERY_GSENSOR_H_ */
