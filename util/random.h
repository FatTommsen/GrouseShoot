/*
 * random.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef UTIL_RANDOM_H_
#define UTIL_RANDOM_H_

#include "../periphery/optsensor.h"

class Random{

private:
    static Random* instance;

public:

    static Random& getInstance(){
        if( Random::instance == nullptr ){
            Random::instance = new Random();
        }
        return *instance;
    }

private:

    int _seed;

    Random(){
        OptSensor optSen;
        _seed = optSen.measure();
        if( _seed < 0 ){
            _seed *= (-1);
        }
        _seed = _seed & 0x1F;
    }

public:

    ~Random(){

    }

    double next(){
        _seed = ( 5 * _seed + 1237) % 1237;
        double random = ((double)_seed) / 1237.;
        return random;
    }
};



#endif /* UTIL_RANDOM_H_ */
