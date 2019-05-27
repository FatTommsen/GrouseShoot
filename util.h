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

struct Path{
    Point from;
    Point to;
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


template<typename T>
class List{

public:

    struct elem{
      elem* _next;
      elem* _prev;
      T* _data;

      elem( T* data ){
          _data = data;
      }

      ~elem(){
          delete _data;
      }
    };

    elem* _head;
    elem* _tail;
    size_t _size;

    List()
    : _head(nullptr), _tail(nullptr), _size(0)
    {
    }

    ~List(){
        elem* it = _head;
        elem* next;
        while( it != nullptr ){
            next = it->_next;
            delete it;
            it = next;
        }
    }

    void push_back( T* data ){
        elem* e = new elem( data );
        if( _head == nullptr ){
            e->_next = nullptr;
            e->_prev = nullptr;
            _head = e;
            _tail = e;
            ++_size;
        }
        else{
            e->_next = nullptr;
            e->_prev = _tail;
            _tail->_next = e;
            ++_size;
        }
    }

    bool remove( T* data ){
        elem* it = _head;
        for( size_t index = 0; index < _size; ++index){
            if( it->_data == data ){
                if( it == _head || it == _tail ){
                    if( it == _head ){
                        _head = it->_next;
                        _head->_prev = nullptr;
                    }
                    if( it == _tail ){
                        _tail = it->_prev;
                        _tail->_next = nullptr;
                    }
                }
                else{
                    it->_next->_prev = it->_prev;
                    it->_prev->_next = it->_next;
                }
                --_size;
                delete it;
                return true;
            }
        }
        return false;
    }

};






#endif /* UTIL_H_ */
