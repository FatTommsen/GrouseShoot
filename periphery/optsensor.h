/*
 * optsensor.h
 *
 *  Created on: 28.05.2019
 *      Author: student
 */

#ifndef PERIPHERY_OPTSENSOR_H_
#define PERIPHERY_OPTSENSOR_H_

#include "i2c_msp432.h"

class OptSensor{

private:
    i2c_msp432* _light;
    uint8_t * _rxbuf;
    uint8_t * _txbuf;
public:

    OptSensor(){
        _light = new i2c_msp432( EUSCI_B1 );

        // Buffers needed for i2c communication
        _rxbuf = new uint8_t[2];
        _txbuf = new uint8_t [3];

        // Write the 'Configuration'
        // (default is 0xc819)
        _txbuf[0] = 0x01;
        _txbuf[1] = 0xce; // MSB
        _txbuf[2] = 0x00; // LSB
        _light->i2cWrite(0x44, _txbuf, 3);
    }

    ~OptSensor(){

    }

    uint16_t measure(){
        // Set the configuration register
        _txbuf[0] = 0x01;
        _light->i2cWrite(0x44, _txbuf, 1);

        // Wait until conversion is ready
        while(1) {
            _light->i2cRead(0x44, _rxbuf, 2);
            if (_rxbuf[1] & 0x80)
                break;
        }

        // Set the result register
        _txbuf[0] = 0x00;
        _light->i2cWrite(0x44, _txbuf, 1);

        // Read the raw light value
        _light->i2cRead(0x44, _rxbuf, 2);

        // Calculate raw value from both bytes
        uint16_t val = _rxbuf[0] * 256 + _rxbuf[1];
        return val;
    }
};



#endif /* PERIPHERY_OPTSENSOR_H_ */
