#include "lcd_interface.h"
#include "pixel_stream_rgb565.h"
#include <cstdlib>

class pixel_stream_2layer : public pixel_stream_rgb565{

private:

    const uint16_t ** _data;
    size_t            _screen_size;
    size_t            _index;
    bool(*_layer_callback)( size_t, size_t, uint16_t& color);

public:

    pixel_stream_2layer( const uint16_t **data, size_t screen_size )
    : pixel_stream_rgb565(nullptr, 0), _data(data), _screen_size(screen_size), _index(0),
      _layer_callback(nullptr)
    {

    }

    virtual ~pixel_stream_2layer() { }

    inline color_t getNext() override {
        // calculate next pixel in 2d array
        size_t x = (_index) / _screen_size;
        size_t y = (_index) % _screen_size;
        ++_index;

        // determine whether pixel is overwritten with top layer
        uint16_t color_cover;
        if( _layer_callback != nullptr && _layer_callback(x, y, color_cover) ){
            return color_cover | LCD::COLORTYPE_RGB565;
        }

        return _data[x][y] | LCD::COLORTYPE_RGB565;
    }

    void setLayerCallback( bool(*layer_callback)( size_t, size_t, uint16_t& color) ){
        _layer_callback = layer_callback;
    }

};
