#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H
#include <string.h>


class ImageDisplay
{
private:
    float *imageData;
    size_t imageWidth;
    size_t imageHeight;
public:
    ImageDisplay(){};
    ImageDisplay( size_t imageWidth, size_t imageHeight, size_t channelsCount = 3 );
    ~ImageDisplay() { delete[] imageData; };

    void initImage( size_t imageWidth, size_t imageHeight );
    void destroyImage ();
    float* getImage () const { return imageData;   };
    size_t getWidth()  { return imageWidth;  };
    size_t getHeight() { return imageHeight; };
    ImageDisplay& operator=(const ImageDisplay&);
    ImageDisplay(const ImageDisplay& source);
};
#endif // IMAGEDISPLAY_H
