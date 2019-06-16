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

struct Statistic{
    uint8_t flyCount;
    uint8_t runCount;
    uint8_t fishCount;
    uint8_t shotCount;

    Statistic()
    : flyCount(0), runCount(0), fishCount(0), shotCount(0)
    {

    }

    int getPoints() const{
        return flyCount * 10 + runCount * 5 + fishCount * 2 - shotCount;
    }
};

struct Highscore{
    Statistic* stat_first;
    Statistic* stat_second;
    Statistic* stat_third;

    Highscore() : stat_first(nullptr), stat_second(nullptr), stat_third(nullptr){};

    ~Highscore(){
        if( stat_first ){
            delete stat_first;
        }
        if( stat_second ){
            delete stat_second;
        }
        if( stat_third ){
            delete stat_third;
        }
    }

    bool hasStatistic(){
        if( stat_first != nullptr ){
            return true;
        }
        return false;
    }

    void add( Statistic stat ){
        if( !stat_first ){
            stat_first = new Statistic;
            stat_first->shotCount = 255;
        }
        else if( !stat_second ){
            stat_second = new Statistic;
            stat_second->shotCount = 255;
        }
        else if( !stat_third ){
            stat_third = new Statistic;
            stat_third->shotCount = 255;
        }

        if( stat_first && stat.getPoints() > stat_first->getPoints() ){
            change( stat, *stat_first );
        }

        if( stat_second && stat.getPoints() > stat_second->getPoints() ){
            change( stat, *stat_second );
        }

        if( stat_third && stat.getPoints() > stat_third->getPoints() ){
            change(stat, *stat_third);
        }

    }

    void change( Statistic& stat1, Statistic& stat2 ){
        int tmp = 0;
        tmp = stat1.flyCount;
        stat1.flyCount = stat2.flyCount;
        stat2.flyCount = tmp;

        tmp = stat1.runCount;
        stat1.runCount = stat2.runCount;
        stat2.runCount = tmp;


        tmp = stat1.fishCount;
        stat1.fishCount = stat2.fishCount;
        stat2.fishCount = tmp;


        tmp = stat1.shotCount;
        stat1.shotCount = stat2.shotCount;
        stat2.shotCount = tmp;
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
