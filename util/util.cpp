/*
 * util.cpp
 *
 *  Created on: 29.05.2019
 *      Author: student
 */

#include "util.h"
#include "uartlogger.h"
#include "random.h"

UartLogger* UartLogger::instance = nullptr;
Random* Random::instance = nullptr;


inline int round( double d ){
    int i = (int) (d * 10);
    i = i % 10;
    if( i < 5 ){
        return (int)d;
    }
    else if( i < 0 ){
        return (int)(d - 1);
    }
    return (int)(d + 1);
}
