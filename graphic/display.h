/*
 * display.h
 *
 *  Created on: 23.05.2019
 *      Author: student
 */

#ifndef CUSTOM_YAHAL_DISPLAY_H_
#define CUSTOM_YAHAL_DISPLAY_H_

#include "gpio_msp432.h"
#include "spi_msp432.h"
#include "st7735s_drv.h"
#include "../custom_yahal/uGUI_2layer.h"
#include "task.h"
#include "map.h"
#include "crosshair.h"

extern const size_t view_size = 128;

class Display : public task{

private:

    gpio_msp432_pin* _lcd_backlight;
    gpio_msp432_pin* _lcd_cs;
    spi_msp432* _spi;
    gpio_msp432_pin* _lcd_rst;
    gpio_msp432_pin* _lcd_dc;
    st7735s_drv* _lcd;
    uGUI_2layer* _gui;
    uGUI_2layer::BMP_2layer* _bmp;

    Map& _map;
    Synchronizer& _sync;
    bool _taskMode;
public:

    Display(Map& map, Synchronizer& sync, bool taskMode = true )
    : task( "display task"), _map(map), _sync(sync), _taskMode(taskMode)
    {
        _lcd_backlight = new gpio_msp432_pin (PORT_PIN(2, 6));
        _lcd_cs = new gpio_msp432_pin (PORT_PIN(5, 0));
        _spi = new spi_msp432(EUSCI_B0_SPI, *_lcd_cs);
        //_spi->setSpeed(2400000000);
        _lcd_rst = new gpio_msp432_pin(PORT_PIN(5, 7));
        _lcd_dc = new gpio_msp432_pin(PORT_PIN(3, 7));
        _lcd = new st7735s_drv(*_spi, *_lcd_rst, *_lcd_dc, st7735s_drv::Crystalfontz_128x128);
        _gui = new uGUI_2layer(*_lcd);

        _bmp = new uGUI_2layer::BMP_2layer();
        _bmp->_screen_size = view_size;
        _bmp->bpp = 16;
        _bmp->colors = BMP_RGB565;
        _bmp->_layer_callback = mapItemCoverCallback;
    }

    ~Display(){
        delete _lcd_backlight;
        delete _lcd_cs;
        delete _spi;
        delete _lcd_rst;
        delete _lcd_dc;
        delete _lcd;
        delete _gui;
        delete _bmp;
    }

    void run() override{
        do{
            _bmp->p = (const void**) _map.getCurrentView();
            if(_taskMode){
                _sync._mutex_map->lock();
                _sync._mutex_crosshair->lock();
            }
            _gui->DrawBMP_2layer(0, 0, _bmp);
            if(_taskMode){
                _sync._mutex_map->unlock();
                _sync._mutex_crosshair->unlock();
                yield();
            }
        }
        while(_taskMode);
    }
};


#endif /* CUSTOM_YAHAL_DISPLAY_H_ */
