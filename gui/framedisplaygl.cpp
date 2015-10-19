#include "framedisplaygl.h"
#include "./core/profiler.h"

#define ZOOM_FACTOR 0.5

FrameDisplayGL ::FrameDisplayGL(QWidget *parent)
{
    QGLFormat frmt;
    setFormat(frmt);

    currWidth =visibleRegion().boundingRect().width();
    currHeight=visibleRegion().boundingRect().height();
    QString msg = QString("Loading image into QImage");
    Profiler timer(msg);
    timer.start();
    ImageLoader i;
    i.loadImage("/home/xmk/programming/skeleton/test/images/interpolate.bmp", 1 );
    //  i.loadImage("/home/xmk/programming/skeleton/test/images/m51.jpg", 1 );
    timer.finish();
}

FrameDisplayGL ::~FrameDisplayGL()
{
    //delete image;
}



void FrameDisplayGL ::initGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LINES);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void FrameDisplayGL ::resizeGL(int newWidth, int newHeight)
{
    currWidth =visibleRegion().boundingRect().width();
    currHeight=visibleRegion().boundingRect().height();

    glViewport( 0,0,newWidth,newHeight );
    glMatrixMode( GL_PROJECTION );
         glLoadIdentity();
         glOrtho( 0, newWidth, newHeight, 0, 0, 1 );
    glMatrixMode(GL_MODELVIEW);
}




void FrameDisplayGL::paintGL()
{

    glRasterPos2d(10,10);               // нижний левый угол
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);         // выравнивание
    glPixelZoom(zoom,zoom);
      //zoom+=0.01;

      QString msg = QString("Drawing image using OpenGL");
      Profiler *timer = new Profiler(msg);
      timer->start();
      ImageDisplay* displayedImage = &ImageDisplay::getInstance();

      glDrawPixels( displayedImage->getWidth(),
                    displayedImage->getHeight(),
                    GL_RGB,
                    GL_FLOAT,
                    displayedImage->getImage() );
      timer->finish();
      delete timer;
/*
      for ( int currentYTile = 0 ; currentYTile < image->getYTilesCount() ; currentYTile++ )
      {
          for ( int currentXTile = 0 ; currentXTile < image->getXTilesCount() ; currentXTile++ )
          {
              ImageData *displayedTile = image->getTilePointer( currentXTile, currentYTile );
              float  shiftX = ZOOM_FACTOR*image->getTileInfo( currentXTile, currentYTile).xMin ;
              float  shiftY = ZOOM_FACTOR*image->getTileInfo( currentXTile, currentYTile).yMin;
              //float deltaX = ZOOM_FACTOR*image->getTileInfo( currentXTile, currentYTile).xMin ;
              //deltaX -= floor(deltaX);
              //deltaX = round(deltaX);
              glRasterPos2d( shiftX , currentHeight - shiftY );
              glDrawPixels( displayedTile->getWidth(), displayedTile->getHeight(),
                            GL_RGB, GL_FLOAT, displayedTile->getData() );
          }
      }
*/
      //ImageReflector *ref = image->constructReflection();

      //ImageReflector *ref = image->constructReflection( 0, 0, 150, 150 );

      /*
      for ( int i = 0 ; i < 5; i++ )
      {
          qDebug() << "[" << 100+i << "] = (" << ref->getData()[ 3*i ]
                   << ref->getData()[ 3*i+1 ] << ref->getData()[ 3*i+2 ] << ")";
      }
      qDebug() << "---------------------------------------------------------\n" ;
*/
      /*glDrawPixels( ref->getWidth(), ref->getHeight(),
                    GL_RGB, GL_UNSIGNED_BYTE, ref->getData() );*/

      //delete ref;
      //delete screen;
      //qDebug() << "Drawing picture .... " << image->getWidth() << image->getHeight();
}

void FrameDisplayGL::redraw()
{
    updateGL();
}
