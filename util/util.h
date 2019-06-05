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



#endif /* UTIL_H_ */
