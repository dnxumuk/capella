#include "mainwindow.h"
#include <QApplication>
#include "./core/profiler.h"
#include "./image/imagetile.h"
#include "./image/imagelayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.resize(w.width()-50,w.height()-50);
    QString x = QString("Fucking");
    Profiler *prf = new Profiler(x);
    prf->start();
    double b=0.0;
    for (int i = 0 ; i<7000000; i++)
    {
        b += i*(2.345);
    }
    prf->finish();
    //
    ImageTile *img = new ImageTile(10,10,1);
    qDebug() << "Vector size:" << img->getTileSizeInBytes()
             << "Row size in bytes:" << img->getTileRowSizeInBytes()
             << "Row pixels count:" << img->getTileRowPixelCount()
             << "Total tile pixels count:" << img->getTileTotalPixelsCount() <<
                sizeof(float);
    delete img;
    ImageLayer *lr = new ImageLayer(100,100,3,10);
    delete lr;
    return a.exec();
}
