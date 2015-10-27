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

ImageLayer::~ImageLayer()
{
    for (auto iter = tiles->begin(); iter != tiles->end(); iter++ )
    {
        delete *iter;
    }
    delete tiles;
}

ImageTile *ImageLayer::getTilePtr(size_t tileNumber) const
{
    return (*tiles)[tileNumber];
}

float *ImageLayer::getRowPtr(size_t rowNumber) const
{
    size_t tileNumber      = rowNumber / heightTile;
    size_t rowNumberInTile = rowNumber % heightTile;
    if ( rowNumber > heightLayer  || tileNumber > tiles->size() || rowNumberInTile > (*tiles)[tileNumber]->getHeight() )
        return nullptr;
    return (*tiles)[tileNumber]->getTileRowPointer(rowNumberInTile);
}

float *ImageLayer::getPointPtr(size_t row, size_t column) const
{
    size_t tileNumber      = row / heightTile;
    size_t rowNumberInTile = row % heightTile;
    if ( row > heightLayer  || tileNumber > tiles->size() || rowNumberInTile > (*tiles)[tileNumber]->getHeight() )
        return nullptr;
    return (*tiles)[tileNumber]->getTilePixelPointer( rowNumberInTile , column );
}

float *ImageLayer::getPixelPtr(size_t row, size_t column, size_t channel) const
{
    float* pointPointer = getPointPtr( row, column );
    if ( pointPointer == nullptr )
        return nullptr;
    return pointPointer + channel;
}

ImageTile &ImageLayer::extractTile(size_t tileNumber)
{
    if ( tileNumber > tiles->size() )
        throw 'ImageLayer::extractTile -> wrong tileNumber';
    ImageTile*  copiedTile = (*tiles)[tileNumber];
    return *(new ImageTile(*copiedTile) );
}
/*
Image &ImageLayer::extractRow(size_t rowNumber)
{
        throw 'ImageLayer::extractRow -> wrong tileNumber';

}

Image &ImageLayer::extractArea(size_t rowFrom, size_t columnFrom, size_t rowCount, size_t columnCount)
{

}
*/
