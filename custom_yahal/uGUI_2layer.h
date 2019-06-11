/*
 * uGUI_2d.h
 *
 *  Created on: 22.05.2019
 *      Author: student
 */

#ifndef UGUI_2D_H_
#define UGUI_2D_H_

#include "uGUI.h"
#include "pixel_stream_2layer.h"

class uGUI_2layer : public uGUI{

private:
    lcd_interface & _lcd;

public:
    uGUI_2layer(lcd_interface & lcd )
        : uGUI(lcd), _lcd(lcd)
    {

    };

    struct BMP_2layer
    {
        const void** background;
        const void** cover;
        uint16_t trans_color;
        uint16_t _screen_size;
        uint8_t bpp;
        uint8_t colors;
    };

    void DrawBMP_2layer(int16_t xp, int16_t yp, BMP_2layer* bmp)
    {
        if (bmp->background == nullptr)
            return;

        /* Only support 16 BPP so far */
        if ((bmp->bpp != BMP_BPP_16) || (bmp->colors != BMP_RGB565))
            return;

        if( bmp->cover == nullptr ){
            pixel_stream_2layer ps((const uint16_t**) bmp->background, bmp->_screen_size, bmp->trans_color );
            _lcd.drawArea(xp, yp, xp + bmp->_screen_size - 1, yp + bmp->_screen_size - 1, ps);
        }
        else{
            pixel_stream_2layer ps((const uint16_t**) bmp->background, (const uint16_t**) bmp->cover, bmp->_screen_size, bmp->trans_color );
            _lcd.drawArea(xp, yp, xp + bmp->_screen_size - 1, yp + bmp->_screen_size - 1, ps);
        }

    }

};

#endif /* UGUI_2D_H_ */
