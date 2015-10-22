#include <QImage>
#include <QPixmap>
//#include "headers/Image.h"
//#include "headers/ImageLoader.h"
#include "imageloader.h"



Image *ImageLoader::loadImage(const char *filePath , int tileSize /*=0*/)
{
    QString qFilePath (filePath);
    //return ;
    imageLoader(&qFilePath , tileSize );
}

Image *ImageLoader::loadImage(const std::string *filePath, int tileSize /*=0*/ )
{
    QString qFilePath (filePath->c_str());
    //return
    imageLoader(&qFilePath , tileSize );
}

Image *ImageLoader::loadImage( const QString *filePath , int tileSize /*=0*/ )
{
    //return
    imageLoader(filePath , tileSize );
}

void ImageLoader::imageLoader( const QString *filePath , int tileSize )
{
    // Load QPixmap  >> QImage
    // Create Image object
    // Convert QImage.data to Layer.Data
    QPixmap imagePixmap    = QPixmap(*filePath);
    QImage  imageSourcePtr = QImage (imagePixmap.toImage());

    ImageDisplay* imagePtr = &(ImageDisplay::getInstance());
    imagePtr->initImage( imageSourcePtr.width() , imageSourcePtr.height() );

    rgba32tofloat( imageSourcePtr.bits(),
                   imagePtr->getImage()  ,
                   imageSourcePtr.width(),
                   imageSourcePtr.height()
                  );
    //return image;
}

void ImageLoader::rgba32tofloat( const uchar *source, float *dest, size_t width, size_t height)
{
    const float maxRGBValue = 255.;
    const float revCoef = 1/maxRGBValue;
    int srcShift = 0;
    int dstShift = 0;

    for (uint row=0; row < height; row++ )
        for ( uint col=0; col < width; col++ )
        {
            dest[ dstShift ]    = source[ srcShift + 2] * revCoef;
            dest[ dstShift +1 ] = source[ srcShift + 1] * revCoef;
            dest[ dstShift +2 ] = source[ srcShift    ] * revCoef;
            srcShift+=4;
            dstShift+=3;
        }

}

ImageLoader::ImageLoader()
{

}


