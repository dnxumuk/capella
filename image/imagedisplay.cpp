#include "imagedisplay.h"

ImageDisplay::ImageDisplay(size_t imageWidth, size_t imageHeight, size_t channelsCount)
{
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    imageData = new float[ imageWidth*imageHeight*3 ];
}

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

ImageDisplay &ImageDisplay::operator=(const ImageDisplay &source)
{
    this->imageWidth = source.imageWidth;
    this->imageHeight = source.imageHeight;
    imageData = new float[ imageWidth*imageHeight*3 ];
    memcpy(imageData, source.getImage(),imageWidth*imageHeight*3*sizeof(float));
}

ImageDisplay::ImageDisplay(const ImageDisplay &source)
{
    this->imageWidth = source.imageWidth;
    this->imageHeight = source.imageHeight;
    imageData = new float[ imageWidth*imageHeight*3 ];
    memcpy(imageData, source.getImage(),imageWidth*imageHeight*3*sizeof(float));
}
