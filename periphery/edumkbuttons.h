/*
 * edumkbuttons.h
 *
 *  Created on: 07.06.2019
 *      Author: student
 */

#ifndef PERIPHERY_EDUMKBUTTONS_H_
#define PERIPHERY_EDUMKBUTTONS_H_

#include "gpio_msp432.h"

class EdumkIIButtons{

private:

    gpio_msp432_pin* _topButton;
    bool _topPushed;
    gpio_msp432_pin* _lowButton;
    bool _lowPushed;

public:

    EdumkIIButtons()
    : _topButton(false), _lowButton(false)
    {
        _topButton = new gpio_msp432_pin(PORT_PIN(5, 1));
        _lowButton = new gpio_msp432_pin(PORT_PIN(3, 5));

        _topButton->gpioMode(GPIO::INPUT | GPIO::PULLUP);
        _lowButton->gpioMode(GPIO::INPUT | GPIO::PULLUP);
    }

    ~EdumkIIButtons(){
        delete _topButton;
        delete _lowButton;
    }

    bool topButtonPushed(){
        if( _topPushed ){
            _topPushed = false;
        }
        return !_topButton->gpioRead();
    }

    bool lowButtonPushed(){
        return !_lowButton->gpioRead();
    }

};




#endif /* PERIPHERY_EDUMKBUTTONS_H_ */
