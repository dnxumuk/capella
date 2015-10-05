#ifndef IMAGELAYER_H
#define IMAGELAYER_H
#include "./imagetile.h"
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

};

#endif // IMAGELAYER_H
