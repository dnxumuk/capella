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
    QString x("/home/xmk/programming/capella/test/images/m51.jpg");
    image = i.imageLoader( &x, 0 );

    //i.loadImage("/home/xmk/programming/skeleton/test/images/m42.jpg", 1 );
    timer.finish();
}

FrameDisplayGL ::~FrameDisplayGL()
{
    delete image;
}



void FrameDisplayGL ::initGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LINES);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPixelZoom(zoom,zoom);
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
    ImageDisplay* displayedImage = image;
    glRasterPos2d(0,currHeight);                  // нижний левый угол
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);        // выравнивание
    glPixelZoom( 1 , 1 );
    glDrawPixels( displayedImage->getWidth(),
                  displayedImage->getHeight(),
                  GL_RGB,
                  GL_FLOAT,
                  displayedImage->getImage() );
}

void FrameDisplayGL::redraw()
{
    updateGL();
}
