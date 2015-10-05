#include "imagetile.h"
#include "cstring"

ImageTile::ImageTile()
{
    setWidth ( DEFAULT_WIDTH );
    setHeight( DEFAULT_HEIGHT );
    channelsCount = DEFAULT_CHANNELS_COUNT;
    setData ( NULL );
    updateTileCachedData();
 }

ImageTile::ImageTile( size_t widthTile, size_t heightTile, size_t channelsCount )
{
    setWidth ( widthTile );
    setHeight( heightTile );
    this->channelsCount = channelsCount;
    this->dataTile = new std::vector<float>( widthTile * heightTile * channelsCount );
    updateTileCachedData();
}

ImageTile::ImageTile( const ImageTile &source )
{
    setWidth ( source.getWidth()  );
    setHeight( source.getHeight() );
    this->channelsCount = source.getChannelsCount();
    this->dataTile = new std::vector<float>( widthTile * heightTile * channelsCount );
    updateTileCachedData();
}

ImageTile::~ImageTile()
{
    delete     dataTile;
}

bool ImageTile::isEmptyData()
{
    return (dataTile) ? true : false;
}

float* ImageTile::getTilePixelPointer( size_t row, size_t column )
{
    return &dataTile->at( channelsCount*(row + column) );
}

bool ImageTile::pointInTileArea ( size_t  x , size_t y )
{
    return  ( x < widthTile && y < heightTile ) ? true : false;
}


void ImageTile::updateTileCachedData()
{
    _tileSizeInBytes    = dataTile->size()*sizeof(*dataTile->begin());
    _tileRowSizeInBytes = widthTile*channelsCount*sizeof(*dataTile->begin());
    _tileRowPixelCount  = widthTile*channelsCount;
}
