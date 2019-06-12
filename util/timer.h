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
    timer_msp432* timer;

public:

    Timer(){
        timer = new timer_msp432(TIMER32_2);
    }

    ~Timer(){
        delete timer;
    }

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
        timer->setPeriod(us, TIMER::ONE_SHOT);
        timer->setCallback( Timer::setTrue, &_param);
        timer->start();

        while(!_param) ;
    }

    void startGame( unsigned int s, bool* param ){
        *param = true;
        uint32_t period = 1000000 * s;
        timer->setPeriod(period, TIMER::ONE_SHOT);
        timer->setCallback( Timer::setFalse, param );
        timer->start();
    }


};

#endif /* UTIL_TIMER_H_ */
