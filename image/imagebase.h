#ifndef IMAGEBASE_H
#define IMAGEBASE_H


class ImageBase
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
    ImageTile( size_t widthTile, size_t heightTile, size_t channelsCount, const Colorspace& );
    ImageTile( const ImageTile& sourceTile );
    ~ImageTile();
    // Accessprs
    bool    isEmptyData();
    int     getWidth()         const     { return widthTile; }
    int     getHeight()        const     { return heightTile; }
    int     getChannelsCount() const  { return channelsCount; }
    float*  getData()               { return dataTile; }
    int     getTileSizeInBytes()    { return _tileSizeInBytes; }
    int     getTileRowPixelCount()  { return _tileRowPixelCount;       }

    int     getTileTotalPixelsCount() { return widthTile*heightTile; } // *Channel count
    int     getTileRowSizeInBytes()   { return _tileRowSizeInBytes; }

    void    setWidth ( int widthTile )              { this->widthTile = widthTile; }
    void    setHeight( int heightTile )             { this->heightTile = heightTile;}
    void    setData  ( float *data )                { this->dataTile = dataTile; }

    void    updateTileCachedData();

    float*  getTileRowPointer  ( size_t row )     { return &dataTile[row*_tileRowPixelCount]; }
    float*  getTilePixelPointer( size_t row, size_t column );

    bool    pointInTileArea ( size_t  x , size_t y );
};

#endif // IMAGEBASE_H
