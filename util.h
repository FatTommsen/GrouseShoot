/*
 * util.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <cstdio>
#include "timer_msp432.h"
#include "mutex.h"
#include "lock_base_msp432.h"

struct Point{
    size_t x;
    size_t y;
};

struct Corners{
    Point lUp;
    Point rLow;
};


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


class Synchronizer{

public:
    mutex_interface* _mutex_map;
    mutex_interface* _mutex_crosshair;

    Synchronizer(){
        _mutex_map = new mutex<lock_base_msp432>();
        _mutex_crosshair = new mutex<lock_base_msp432>();
    }
};






#endif /* UTIL_H_ */
