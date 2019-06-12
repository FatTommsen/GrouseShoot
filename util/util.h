/*
 * util.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <cstdio>

struct Point{
    size_t x;
    size_t y;

    bool operator==(const Point& p){
        return (this->x == p.x && this->y == p.y );
    }

    bool operator!=(const Point& p){
        return !(*this == p);
    }

    void operator=(const Point& p){
        this->x = p.x;
        this->y = p.y;
    }
};

struct Corners{
    Point lUp;
    Point rLow;

    bool operator==(const Corners& c){
        return (this->lUp == c.lUp && this->rLow == c.rLow );
    }

    bool operator!=(const Corners& c){
        return !(*this == c);
    }

    void operator=(const Corners& c){
        this->lUp = c.lUp;
        this->rLow = c.rLow;
    }
};

struct pixel{
    uint16_t* map;
    uint16_t* item;

    pixel():map(nullptr), item(nullptr){};
};

struct Settings{
    bool reload;
    bool mapViaGSensor;

    Settings(): reload(false), mapViaGSensor(true){};
};

inline size_t min( size_t x1, size_t x2 ){
    return x1 <= x2 ? x1 : x2;
}

inline size_t max( size_t x1, size_t x2 ){
    return x1 >= x2 ? x1 : x2;
}

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


#endif /* UTIL_H_ */
