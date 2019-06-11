/*
 * timer.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef UTIL_TIMER_H_
#define UTIL_TIMER_H_

#include "timer_msp432.h"

class Timer{

private:
    bool _param;

public:

    static void setTrue( void * arg ){
        bool* b = (static_cast<bool *>(arg));
        *b = true;
    }

    static void setFalse( void * arg ){
        bool* b = (static_cast<bool *>(arg));
        *b = false;
    }


    void delay( unsigned int us ){
        _param = false;
        timer_msp432 timer2(TIMER32_2);
        timer2.setPeriod(us, TIMER::ONE_SHOT);
        timer2.setCallback( Timer::setTrue, &_param);
        timer2.start();

        while(!_param) ;
    }

    void startGame( unsigned int s, bool* param ){
        *param = false;
        timer_msp432 timer2(TIMER32_2);
        uint32_t period = 1000000 * s;
        timer2.setPeriod(period, TIMER::ONE_SHOT);
        timer2.setCallback( Timer::setTrue, param );
        timer2.start();
    }


};

#endif /* UTIL_TIMER_H_ */
