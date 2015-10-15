#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <math.h>
#include <string.h>
#include <QString>
#include "./image.h"
// This is 8-bit RGB image-map. Using for direct show
//

class ImageLoader
{
private:
    Image*    imageLoader   ( const QString *filePath, int tileSize = 0 );
    void      rgba32tofloat ( const uchar *src, float *dest, size_t width, size_t height);
    void      allocateImage ();
public:
    ImageLoader();
    Image* loadImage (const char *filePath, int tileSize = 0 );
    Image* loadImage (const std::string *filePath, int tileSize = 0 );
    Image* loadImage (const QString *filePath, int tileSize = 0 );
};




#endif // IMAGELOADER_H
