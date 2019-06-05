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
    bool param;

    static void setTrue( void * arg ){
        (*static_cast<bool *>(arg)) = true;
    }

public:
    void delay( unsigned int us ){
        param = false;
        timer_msp432 timer2(TIMER32_2);
        timer2.setPeriod(us, TIMER::ONE_SHOT);
        timer2.setCallback( Timer::setTrue, &param);
        timer2.start();

        while(!param) ;
    }

};

#endif /* UTIL_TIMER_H_ */
