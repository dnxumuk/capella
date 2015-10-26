#ifndef TOOLCURVESDIALOG_H
#define TOOLCURVESDIALOG_H
#include <QDialog>
#include "toolcurvescurve.h"
#include "./image/imagedisplay.h"


namespace Ui
{
    class ToolCurvesDialog;
}

class ToolCurvesDialog : public QDialog
{
    Q_OBJECT
private:
    Ui::ToolCurvesDialog *ui;
    ToolCurvesCurve *curve;
    std::list<Point>::iterator selectedPoint;
    //Point                      *selectedPointPtr;
    ImageDisplay *img;
    /* Makeup parameters */
    size_t  border;
    float   grid_size;
    float   circle_size;
    size_t  width;
    size_t  height;
    /* Makeup accessors */
    void   setBorderSize(size_t size) { border = size; }
    size_t getBorderSize()            { return border;}
    void   setGridSize(float count) { grid_size = count;}
    float  getGridSize()            { return grid_size; }
    void   setCircleSize(size_t size) { circle_size = size; }
    size_t getCircleSize()            { return circle_size; }
    /* Pens pattern */
    QPen  *borderPen;
    QPen  *gridPen;
    QPen  *centerPen;
    QPen  *pointPen;
    QPen  *curvePen;
    QPen  *selectedPoinPen;

    void DrawGrid();
    void DrawBorder();
    void setDefaultValues();
    void drawPoints();
    void drawCurve();
    void redraw();
    Point getValues    (const Point& point);
    Point get255Values (const Point& point);
public:
    explicit ToolCurvesDialog (QWidget *pwgt = 0);
    virtual void resizeEvent ( QResizeEvent * event );
    void setImage(ImageDisplay &img);
    bool eventFilter( QObject *obj, QEvent *ev);
    void processingImage();
    //virtual void mouse
    ~ToolCurvesDialog();
signals:
    void MySetValueSignal(int);
};
#endif // TOOLCURVESDIALOG_H
