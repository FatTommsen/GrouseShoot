/*
 * uartlogger.h
 *
 *  Created on: 05.06.2019
 *      Author: student
 */

#ifndef UTIL_UARTLOGGER_H_
#define UTIL_UARTLOGGER_H_

#include "uart_msp432.h"
#include "std_io.h"
#include "String.h"
#include <cstdio>

class UartLogger{

private:

    uart_msp432* _uart;
    static UartLogger* instance;

    UartLogger(){
        _uart = new uart_msp432;
        std_io::inst.redirect_stdout( *_uart );
    }

public:

    static UartLogger& getInstance(){
        if( UartLogger::instance == nullptr ){
            UartLogger::instance = new UartLogger();
        }
        return *UartLogger::instance;
    }


    ~UartLogger(){
        delete _uart;
    }

    UartLogger& log( String msg ){
        printf(msg);
        fflush( stdout );
        return (*this);
    }

    UartLogger& log( double d ){
        int vk = (int)d;
        int nk = (int)(d * 10000);
        nk = nk % 10000;
        printf("%d,%04d" , vk, nk);
        fflush( stdout );
        return (*this);
    }

    UartLogger& log( int i ){
        printf("%d" , i);
        fflush( stdout );
        return (*this);
    }

};



#endif /* UTIL_UARTLOGGER_H_ */
