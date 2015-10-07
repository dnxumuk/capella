#ifndef IMAGELAYER_H
#define IMAGELAYER_H
#include "./imagetile.h"
#include "./image.h"
#include <vector>
#include "cstddef"

class ImageLayer
{
private:
    std::vector<ImageTile*> *tiles;
    size_t countTiles;
    size_t widthLayer;
    size_t heightLayer;
    size_t heightTile;

public:
    ImageLayer();
    ImageLayer( size_t widthLayer, size_t heightLayer, size_t channelCount, size_t tileRowsCount );
    ImageLayer( const ImageLayer& source );
    ~ImageLayer();
    // Accessors
    ImageTile* getTilePtr( size_t tileNumber ) const;
    float* getRowPtr( size_t rowNumber ) const;
    float* getPointPtr( size_t row, size_t column) const;
    float* getPixelPtr( size_t row, size_t column, size_t channel ) const;
    //
    ImageTile& extractTile( size_t tileNumber );
    Image& extractRow ( size_t rowNumber );
    Image& extractArea( size_t rowFrom, size_t columnFrom, size_t rowCount, size_t columnCount);

};

#endif // IMAGELAYER_H
