#include "framedisplaygl.h"
#include "./core/profiler.h"
#include <QtTest/QTest>
#include <QThread>

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
    //i.loadImage("/home/xmk/programming/skeleton/test/images/interpolate.bmp", 1 );
    i.loadImage("/home/xmk/programming/skeleton/test/images/rgb.bmp", 1 );
    //i.loadImage("/home/xmk/programming/skeleton/test/images/m42.jpg", 1 );
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
    glRasterPos2d(0,currHeight);                  // нижний левый угол
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);        // выравнивание
    glPixelZoom(zoom,zoom);
      //QString msg = QString("Drawing image using OpenGL");
      //Profiler *timer = new Profiler(msg);
      //timer->start();
      ImageDisplay* displayedImage = &ImageDisplay::getInstance();

      glDrawPixels( displayedImage->getWidth(),
                    displayedImage->getHeight(),
                    GL_RGB,
                    GL_FLOAT,
                    displayedImage->getImage() );
      //timer->finish();
      //delete timer;
}

void FrameDisplayGL::redraw()
{
    updateGL();
}
