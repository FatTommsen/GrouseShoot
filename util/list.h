/*
 * list.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef UTIL_LIST_H_
#define UTIL_LIST_H_

#include <cstdio>

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
            _tail = e;
            ++_size;
        }
    }

    bool remove( T* data ){
        elem* it = _head;

        while( it != nullptr ){
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
            it = it->_next;
        }
        return false;
    }

};



#endif /* UTIL_LIST_H_ */
