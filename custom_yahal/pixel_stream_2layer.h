#include "lcd_interface.h"
#include "pixel_stream_rgb565.h"
#include <cstdlib>

class pixel_stream_2layer : public pixel_stream_rgb565{

private:

    const uint16_t ** _data;
    const uint16_t ** _data_cover;
    size_t            _screen_size;
    size_t            _index;
    uint16_t          _trans_color;

public:

    pixel_stream_2layer( const uint16_t **data, const uint16_t **data_cover, size_t screen_size, uint16_t trans_color )
    : pixel_stream_rgb565(nullptr, 0), _data(data), _data_cover(data_cover), _screen_size(screen_size), _index(0), _trans_color(trans_color)
    {

    }

    virtual ~pixel_stream_2layer() { }

    inline color_t getNext() override {
        // calculate next pixel in 2d array
        size_t y = (_index) / _screen_size;
        size_t x = (_index) % _screen_size;
        ++_index;

        if( _data_cover[y][x] != _trans_color ){
            return _data_cover[y][x] | LCD::COLORTYPE_RGB565;
        }

        // writes columns from top to down
        return _data[y][x] | LCD::COLORTYPE_RGB565;
    }

};
