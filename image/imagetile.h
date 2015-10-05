#ifndef IMAGETILE_H
#define IMAGETILE_H

#define DEFAULT_WIDTH          0
#define DEFAULT_HEIGHT         0
#define DEFAULT_CHANNELS_COUNT 1
#include "../core/colorspace.h"
#include "cstddef"
#include <vector>

class ImageTile
{
private:
    size_t   widthTile;
    size_t   heightTile;
    size_t   channelsCount;
    std::vector<float>* dataTile;
    size_t  _tileSizeInBytes;
    size_t  _tileRowSizeInBytes;
    size_t  _tileRowPixelCount;
public:
    // Constructors && destructor
    ImageTile();
    ImageTile( size_t widthTile, size_t heightTile, size_t channelsCount );
    ImageTile( const ImageTile& sourceTile );
    ~ImageTile();
    // Accessprs
    bool    isEmptyData();
    int     getWidth()         const     { return widthTile; }
    int     getHeight()        const     { return heightTile; }
    int     getChannelsCount() const  { return channelsCount; }
    float*  getData()               { return dataTile->data(); }
    int     getTileSizeInBytes()    { return _tileSizeInBytes; }
    int     getTileRowPixelCount()  { return _tileRowPixelCount;       }

    int     getTileTotalPixelsCount() { return widthTile*heightTile; } // *Channel count
    int     getTileRowSizeInBytes()   { return _tileRowSizeInBytes; }

    void    setWidth ( int widthTile )              { this->widthTile = widthTile; }
    void    setHeight( int heightTile )             { this->heightTile = heightTile;}
    void    setChannelsCount( size_t channelsCount) { this->channelsCount = channelsCount;}
    void    setData  ( float *data )                { this->dataTile = dataTile; }

    void    updateTileCachedData();

    float*  getTileRowPointer  ( size_t row )     { return &dataTile->data()[row*_tileRowPixelCount]; }
    float*  getTilePixelPointer( size_t row, size_t column );

    bool    pointInTileArea ( size_t  x , size_t y );
};

#endif // IMAGETILE_H
