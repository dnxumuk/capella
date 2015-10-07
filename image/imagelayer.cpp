#include "math.h"
#include "imagelayer.h"

ImageLayer::ImageLayer()
{
    countTiles = 1;
    widthLayer = 0;
    heightLayer = 0;
    heightTile = 0;
    tiles = new std::vector<ImageTile*>(countTiles);
}

ImageLayer::ImageLayer( size_t widthLayer, size_t heightLayer, size_t channelCount, size_t tileRowsCount )
{
    this->widthLayer  = widthLayer;
    this->heightLayer = heightLayer;
    this->heightTile = tileRowsCount;
    size_t countTiles = (int) ceil(heightLayer/tileRowsCount) ;
    tiles = new std::vector<ImageTile*>(countTiles);
    for (size_t i=0 ; i < countTiles ; i++)
    {
        (*tiles)[i] = new ImageTile(widthLayer,heightTile,channelCount);
    }
}

ImageLayer::ImageLayer(const ImageLayer &source)
{
    this->widthLayer  = source.widthLayer;
    this->heightLayer = source.heightLayer;
    this->heightTile =  source.heightTile;
    this->countTiles =  source.countTiles;
    this->tiles = new std::vector<ImageTile*>(countTiles);
    for (size_t i=0 ; i < countTiles ; i++)
    {
        const ImageTile* sourceTilePtr = source.getTilePtr(i);
        (*tiles)[i] = new ImageTile(*sourceTilePtr);
    }
}

ImageTile *ImageLayer::getTilePtr(size_t tileNumber) const
{
    return (*tiles)[tileNumber];
}

