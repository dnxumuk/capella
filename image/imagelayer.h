#ifndef IMAGELAYER_H
#define IMAGELAYER_H
#include "./imagetile.h"
#include "./image.h"
#include <vector>
#include "cstddef"

class ImageLayer
{
private:
    std::vector<ImageLayer*> *tiles;
    size_t countTiles;
    size_t widthLayer;
    size_t heightLayer;
    size_t heightTile;

public:
    ImageLayer();
    ImageLayer( size_t widthLayer, size_t heightLayer, size_t channelCount, size_t countTiles );
    ImageLayer( const ImageLayer& source );
    ~ImageLayer();
    // Accessors
    ImageTile* getTilePtr( size_t tileNumber );
    float* getRowPtr( size_t rowNumber );
    float* getPointPtr( size_t row, size_t column);
    float* getPixelPtr( size_t row, size_t column, size_t channel );
    //
    ImageTile& extractTile( size_t tileNumber );
    Image& extractRow ( size_t rowNumber );
    Image& extractArea( size_t rowFrom, size_t columnFrom, size_t rowCount, size_t columnCount);

};

#endif // IMAGELAYER_H
