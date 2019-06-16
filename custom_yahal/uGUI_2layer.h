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


    void PutStringToView(int16_t x, int16_t y, const char* str, uint16_t** view, bool opaque = false)
    {
        int16_t xp, yp;
        char chr;

        xp = x;
        yp = y;

        while (*str != 0)
        {
            chr = *str;
            if (chr == '\n')
            {
                xp = _x_dim;
                str++;
                continue;
            }
            // skip UTF8 prefix chars
            if ((chr == 0xC2) || (chr == 0xC3))
            {
                str++;
                continue;
            }

            if (xp + _font.char_width > _x_dim - 1)
            {
                xp = x;
                yp += _font.char_height + _font.char_v_space;
            }

            PutCharToView(chr, xp, yp, _fore_color, _back_color, view, opaque);

            xp += _font.char_width + _font.char_h_space;
            str++;
        }
    }

    void PutCharToView(const char chr, int16_t x, int16_t y, UG_COLOR fc, UG_COLOR bc, uint16_t** view, bool opaque=true)
    {
        uint16_t i, j, k, xo, yo, c, bn;
        uint8_t b, bt;
        unsigned char* p;

        bt = (uint8_t) chr;

        switch (bt)
        {
        case 0xB6:
            bt = 0x94;
            break; // ö
        case 0x96:
            bt = 0x99;
            break; // Ö
        case 0xBC:
            bt = 0x81;
            break; // ü
        case 0x9C:
            bt = 0x9A;
            break; // Ü
        case 0xA4:
            bt = 0x84;
            break; // ä
        case 0x84:
            bt = 0x8E;
            break; // Ä
        case 0xB5:
            bt = 0xE6;
            break; // µ
        case 0xB0:
            bt = 0xF8;
            break; // °
        }

        yo = y;
        bn = _font.char_width;
        if (!bn)
            return;
        bn >>= 3;
        if (_font.char_width % 8)
            bn++;
        p = _font.p;
        p += bt * _font.char_height * bn;

        for (j = 0; j < _font.char_height; j++)
        {
            xo = x;
            c = _font.char_width;
            for (i = 0; i < bn; i++)
            {
                b = *p++;
                for (k = 0; (k < 8) && c; k++)
                {
                    if (b & 0x01)
                    {
                        view[yo][xo] = fc;
                    }
                    else
                    {
                        if (opaque) view[yo][xo] = bc;
                    }
                    b >>= 1;
                    xo++;
                    c--;
                }
            }
            yo++;
        }
    }
};

#endif /* UGUI_2D_H_ */
