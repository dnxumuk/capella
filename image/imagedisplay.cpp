#include "imagedisplay.h"

void ImageDisplay::initImage(size_t imageWidth, size_t imageHeight)
{
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    imageData = new float[ imageWidth*imageHeight*3 ];
}

void ImageDisplay::destroyImage()
{
    delete[] imageData;
}
