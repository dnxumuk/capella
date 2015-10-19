#ifndef FRAMEDISPLAYGL_H
#define FRAMEDISPLAYGL_H
#include <QtOpenGL/QGLWidget>
#include <QDebug>
#include "./image/imageloader.h"


//class QDebug;
class FrameDisplayGL : public QGLWidget
{
    Q_OBJECT
  private:
         GLfloat ratio;
         GLint   viewport[4];
         /*My types*/
         size_t currWidth;
         size_t currHeight;
         float zoom = 100;
  protected:
       void initGL();
       void resizeGL(int newWidth, int newHeight);
       void paintGL();
  public:
       FrameDisplayGL(QWidget* parent = 0);
       ~FrameDisplayGL();
       void dumpSize();
       //ImageLayer *image;
  public slots:
       void redraw();
};

#endif // FRAMEDISPLAYGL_H
