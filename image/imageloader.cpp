#include <QImage>
#include <QPixmap>
#include "headers/ImageLayer.h"
#include "headers/ImageLoader.h"



ImageLayer *ImageLoader::loadImage(char *filePath , int tileSize /*=0*/)
{
    QString qFilePath (filePath);
    return imageLoader(&qFilePath , tileSize );
}

ImageLayer *ImageLoader::loadImage(std::string *filePath, int tileSize /*=0*/ )
{
    QString qFilePath (filePath->c_str());
    return imageLoader(&qFilePath , tileSize );
}

ImageLayer *ImageLoader::loadImage(QString *filePath , int tileSize /*=0*/ )
{
    return imageLoader(filePath , tileSize );
}

ImageLayer *ImageLoader::imageLoader(QString *filePath , int tileSize )
{
    // Load QPixmap  >> QImage
    // Create Image object
    // Convert QImage.data to Layer.Data
    QPixmap i = QPixmap(*filePath);
    QImage pImg = QImage(i.toImage());


    //ImageLayer *image = new ImageLayer(pImg.width(),pImg.height(), , 1, tileSize );
    ImageLayer *image = new ImageLayer();

    //Colorspace &tmpCsps = Colorspace::getInstance();
    int xT = image->getXTilesCount();
    int yT = image->getYTilesCount();
    int channelsCount = 3;//tmpCsps.getChannelCount(image->getColorspaceLayer());
    int pixInLine = image->getWidthLayer() * channelsCount ;

    int currentXTile = 0;
    int currentYTile = 0;
    int currentYrow  = 0;

    int totalBytes = image->getHeightLayer() * image->getWidthLayer();

    int l=0;
    bool zeroXTile = false;

    for ( int readBytes = 0; readBytes < totalBytes;  )
    {
        if ( tileSize <= 0 )
            tileSize = max( image->getWidthLayer() , image->getHeightLayer() );

        int willReadPixels = tileSize;

        if ( currentXTile >= image->getXTilesCount()-1 )
        {
            // Goto next line into tile
            willReadPixels = image->getTileInfo( currentXTile, currentYTile ).xMax - image->getTileInfo( currentXTile, currentYTile ).xMin;
            zeroXTile = true;
        }
        if ( currentYrow >=  image->getTileSize() )
        {
            // Goto net tile's row
            currentYrow = 0;
            currentYTile++;
        }


       rgba32tofloat( pImg.bits() + readBytes*4,
                       image->getTilePointer( currentXTile, currentYTile )->getRowPointer( currentYrow ) ,
                       willReadPixels ,
                       1
                      );
        readBytes+=willReadPixels;
        if (zeroXTile)
        {
            currentXTile = 0;
            currentYrow++;
            zeroXTile = false;
        }
        else
            currentXTile++;
    }
    return image;
    //image->ToOpenGL();
}

void ImageLoader::rgba32tofloat( uchar *source, float *dest, uint width, uint height)
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


