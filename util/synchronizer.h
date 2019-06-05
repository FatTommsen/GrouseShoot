/*
 * synchronizer.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef UTIL_SYNCHRONIZER_H_
#define UTIL_SYNCHRONIZER_H_

#include "mutex.h"

class Synchronizer{

public:
    mutex_interface* _mutex_map;
    mutex_interface* _mutex_crosshair;

    Synchronizer(){
        _mutex_map = new mutex<lock_base_msp432>();
        _mutex_crosshair = new mutex<lock_base_msp432>();
    }
};


#endif /* UTIL_SYNCHRONIZER_H_ */
