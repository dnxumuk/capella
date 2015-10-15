#ifndef IMAGE_H
#define IMAGE_H
#include "./core/colorspace.h"
#include "./imagelayer.h"


class Image
{
    std::vector< ImageLayer* > layers;
    Colorspace *colorspace;
    size_t width;
    size_t heigh;
    size_t tileCount;
public:
    Image();
    Image(size_t width, size_t height, size_t layerCount, size_t tileCount, Colorspace &colorType);
    ~Image();
    void getSmallImage( float scaleFactor );
};

#endif // IMAGE_H
