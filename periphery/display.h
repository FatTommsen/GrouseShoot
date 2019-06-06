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

extern const uint16_t TRANSPARENT_COLOR;

class Display {

private:

    gpio_msp432_pin* _lcd_backlight;
    gpio_msp432_pin* _lcd_cs;
    spi_msp432* _spi;
    gpio_msp432_pin* _lcd_rst;
    gpio_msp432_pin* _lcd_dc;
    st7735s_drv* _lcd;
    uGUI_2layer* _gui;
    uGUI_2layer::BMP_2layer* _bmp_map;

public:

    Display(){

        _lcd_backlight = new gpio_msp432_pin (PORT_PIN(2, 6));
        _lcd_cs = new gpio_msp432_pin (PORT_PIN(5, 0));
        _spi = new spi_msp432(EUSCI_B0_SPI, *_lcd_cs);
        _spi->setSpeed(2500000000);
        _lcd_rst = new gpio_msp432_pin(PORT_PIN(5, 7));
        _lcd_dc = new gpio_msp432_pin(PORT_PIN(3, 7));
        _lcd = new st7735s_drv(*_spi, *_lcd_rst, *_lcd_dc, st7735s_drv::Crystalfontz_128x128);
        _gui = new uGUI_2layer(*_lcd);

        _bmp_map = new uGUI_2layer::BMP_2layer();
        _bmp_map->_screen_size = DISPLAY_SIZE;
        _bmp_map->bpp = 16;
        _bmp_map->colors = BMP_RGB565;
        _bmp_map->trans_color = TRANSPARENT_COLOR;
    }

    ~Display(){
        delete _lcd_backlight;
        delete _lcd_cs;
        delete _spi;
        delete _lcd_rst;
        delete _lcd_dc;
        delete _lcd;
        delete _gui;
        delete _bmp_map;
    }


    void drawTwoLayer( const void** map_view, const void** view_cover ){
        _bmp_map->background = map_view;
        _bmp_map->cover = view_cover;
        _gui->DrawBMP_2layer(0, 0, _bmp_map);
    }

};


#endif /* CUSTOM_YAHAL_DISPLAY_H_ */
