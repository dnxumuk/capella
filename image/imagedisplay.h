#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H
#include <string.h>


class ImageDisplay
{
public:
        static ImageDisplay& getInstance()
        {
                static ImageDisplay theSingleInstance;
                return theSingleInstance;
        }
        void initImage( size_t imageWidth, size_t imageHeight );
        void destroyImage ();
        float* getImage () { return imageData;   };
        size_t getWidth()  { return imageWidth;  };
        size_t getHeight() { return imageHeight; };
private:
        ImageDisplay(){}
        ImageDisplay(const ImageDisplay& source);
        ImageDisplay& operator=(const ImageDisplay&);
        float *imageData;
        size_t imageWidth;
        size_t imageHeight;
};
#endif // IMAGEDISPLAY_H
