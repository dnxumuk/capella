#include "toolcurvesdialog.h"
#include "ui_ToolCurvesDialog.h"
#include <QResizeEvent>
#include <QMouseEvent>
#include <math.h>
#include <QDebug>
//#include "omp.h"
#include <xmmintrin.h>


ToolCurvesDialog::ToolCurvesDialog (QWidget *pwgt/*=0*/) :
                QDialog (pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint), ui(new Ui::ToolCurvesDialog)
{
    ui->setupUi(this);
    // Init visual components
    border    = 5;
    grid_size = 8.;
    circle_size = 4.;
    borderPen  = new QPen(Qt::red);
    gridPen    = new QPen(Qt::lightGray);
    centerPen  = new QPen(Qt::darkGray);
    pointPen   = new QPen(Qt::gray);
    curvePen   = new QPen(Qt::darkBlue);
    curvePen->setWidth(2);
    // Init curve && scene
    curve                 = new ToolCurvesCurve();
    QGraphicsScene *scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->viewport()->setMouseTracking(1);
    ui->graphicsView->setMouseTracking(1);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->viewport()->installEventFilter(this);
}

void ToolCurvesDialog::resizeEvent(QResizeEvent *event)
{
    QSize newSize  = event->size();
    int newWidth  = event->size().width()  * ui->graphicsView->width () / event->oldSize().width() ;
    int newHeight = event->size().height() * ui->graphicsView->height() / event->oldSize().height() ;
    ui->graphicsView->resize(newWidth, newHeight );
    width  = ui->graphicsView->width();
    height = ui->graphicsView->height();
    redraw();
}

void ToolCurvesDialog::setImage(ImageDisplay &img)
{
    this->img = &img;
    ui->listWidget->clear();
    /*  Here we must to add items to item-box wich mapping image-channels
     *     like this:
        QListWidgetItem *currentItem = ui->listWidget->item(ui->listWidget->count()-1);
        currentItem->setFlags( currentItem->flags() | Qt::ItemIsUserCheckable );
        currentItem->setCheckState(Qt::Checked);
    */
}


bool ToolCurvesDialog::eventFilter(QObject *obj, QEvent *event)
{
    switch ( event->type() )
    {
        case QEvent::MouseButtonPress:
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton)
            {
                // LMB pressed. Add new point or select from existing &

                Point mouseCoord = get255Values( Point( mouseEvent->x(),mouseEvent->y() ) );
                Point radius     = get255Values( Point(10,10) );
                std::list<Point>::iterator xxx = curve->findPointByCoordinates(mouseCoord.x,mouseCoord.y, radius.x, radius.y);
                if (curve->pointExists(xxx))
                {
                    qDebug() << "     Nearest point ... " << xxx->x << xxx->y;
                    curve->selectPoint(xxx);
                }
                else
                {
                    QGraphicsScene *scene = ui->graphicsView->scene();
                    Point pt = get255Values( Point (mouseEvent->pos().x(),
                                                    mouseEvent->pos().y()) );
                    qDebug() << "Add" << pt.x << pt.y;
                    curve->addPoint(pt.x,pt.y);
                    redraw();
                }
            }
            else if (mouseEvent->buttons() & Qt::RightButton)
            {
                qDebug() << "Right click detected";
            }
            return true;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if ( (mouseEvent->buttons() & Qt::LeftButton) && curve->pointExists(selectedPoint))
            {
                Point newCoord = get255Values( Point(mouseEvent->x(),mouseEvent->y()) );
                curve->selectedPoint->x = newCoord.x;
                curve->selectedPoint->y = newCoord.y;
                redraw();
            }
                return true;
        }
        case QEvent::MouseButtonRelease:
        {
            processingImage();
            qDebug() << "Emitting";
            emit MySetValueSignal(1);
            return true;
        }
        case QEvent::KeyPress:
        {
            return true;
        }
        default :
        {
            return false;
        }
    }
}

inline int FastToInt( float f )
{
    return _mm_cvtss_si32( _mm_load_ss( &f ) );
}


inline float getSuperPrecisionValue(float x, float x0, float x1, float y0,float y1)
{
    float  dy  = y1-y0;
    float  dx0 = x - x0;
    float  dx1 = x1 - x;
    float  dy1 = dy*dx0/dx1;
    return dy1 + y0;
}

void ToolCurvesDialog::processingImage()
{
    if (curve->curvePoints->size() < 5)
        return;
    ImageDisplay &img = *(this->img);
    // Make array coefs
    const unsigned long  size_of = 256;
    float coef[size_of];
    for (uint i=0 ; i< size_of; i++)
    {
        for (auto iterCurvePoint = curve->curvePoints->begin(); iterCurvePoint != curve->curvePoints->end(); iterCurvePoint++)
        {
            if ( i/(size_of/1.-1.) <= iterCurvePoint->x )
            {
                auto next = iterCurvePoint;
                ++next;
                coef[i] = 1 - getSuperPrecisionValue( i/(size_of/1.-1.), iterCurvePoint->x, next->x,
                                                                         iterCurvePoint->y, next->y );
                //qDebug() << "Coef " << i << " is " << coef[i];
                break;
            }
        }
    }
    //
    bool channelProcessing[4] = { false, false, false, false };

    float* tmp = img.getImage();
    for (uint j=0 ; j< img.getWidth()*img.getHeight(); j++ )
    {
        *(tmp)   = channelProcessing[0] ? coef[FastToInt(*(tmp  )*(size_of-1))]    :  *(tmp)   ;
        *(tmp+1) = channelProcessing[1] ? coef[FastToInt(*(tmp+1)*(size_of-1))]:  *(tmp+1)   ;
        *(tmp+2) = channelProcessing[2] ? coef[FastToInt(*(tmp+2)*(size_of-1))]:  *(tmp+2)   ;
          tmp+=3;
    }
}

ToolCurvesDialog :: ~ToolCurvesDialog()
{
    delete ui;
}

void ToolCurvesDialog::DrawGrid()
{
    QGraphicsScene *scene = ui->graphicsView->scene();
    //QPen line (Qt::gray);

    int _width =  this->width - 2*border;
    int _height = this->height- 2*border;
    for (uint i=1 ; i < grid_size; i++)
    {
        int x = round( (i/grid_size-0.5)*_width  );
        int y = round( (i/grid_size-0.5)*_height );
        if ( abs( i-grid_size/2 ) < 1. )
        {
            scene->addLine( x , -_height/2 , x, _height/2, *centerPen);
            scene->addLine( -_width/2 , y  , _width/2,  y, *centerPen);
        }
        else
        {
            scene->addLine( x , -_height/2 , x, _height/2, *gridPen);
            scene->addLine( -_width/2 ,  y , _width/2,  y, *gridPen);
        }
    }
}

// Ok
void ToolCurvesDialog::DrawBorder()
{
    QGraphicsScene *scene = ui->graphicsView->scene();
    int x0 =  border   - width/2 ;
    int x1 =  width/2  - border;
    int y0 =  border   - height/2 ;
    int y1 =  height/2 - border;
    scene->addLine( x0, y0, x1, y0, *borderPen);
    scene->addLine( x1, y0, x1, y1, *borderPen);
    scene->addLine( x1, y1, x0, y1, *borderPen);
    scene->addLine( x0, y1, x0, y0, *borderPen);
}

void ToolCurvesDialog::setDefaultValues()
{

}

void ToolCurvesDialog::drawPoints()
{
    QGraphicsScene *scene = ui->graphicsView->scene();
    float zerox = border -  width/2. ;
    float zeroy = border -  height/2. ;
    float circleCorrection = -circle_size/2.;

    for  ( uint i=0; i < curve->rootPoints->size(); i++ )
    {
        // Graphic scene w/h witout borders
        int dx = width -2*(int)border;
        int dy = height-2*(int)border;

        float x = curve->getRealX( dx,i);
        float y = curve->getRealY( dy,i);

        float dd = zerox + x + circleCorrection;
        float dl = zeroy + y + circleCorrection;


        scene->addEllipse( zerox + x + circleCorrection  ,
                             zeroy + y + circleCorrection ,
                             circle_size, circle_size, *pointPen );

    }
}

void ToolCurvesDialog::drawCurve()
{
    QGraphicsScene *scene = ui->graphicsView->scene();
    float zerox =  border - width/2. ;
    float zeroy =  border - height/2.;
    float areaSizeX =  width   -2*border;
    float areaSizeY =  height  -2*border;

    float *curveXCoords = new float[curve->curvePoints->size()];
    float *curveYCoords = new float[curve->curvePoints->size()];
    int  j = 0;
    for  ( auto iterCurvePoint  = curve->curvePoints->begin();
                iterCurvePoint != curve->curvePoints->end() ;
           iterCurvePoint++, j++ )
    {
        curveXCoords[j] = areaSizeX*iterCurvePoint->x + zeroy;
        curveYCoords[j] = areaSizeY*iterCurvePoint->y + zeroy;
    }
    if  (this->curve->curvePoints->size() > 1)
        for  ( int i=0; i < this->curve->curvePoints->size() - 1 ; i++ )
            scene->addLine( curveXCoords[i],   curveYCoords[i],
                            curveXCoords[i+1], curveYCoords[i+1],
                           *curvePen );
    delete curveXCoords, curveYCoords;
}

void ToolCurvesDialog::redraw()
{
    // This constant is inverse of value how precisely bezier-curve will be computed ( 1 / (ticksCount) )
    const float redrawBezierCurveStepX = 1/256. ;
    curve->curvePoints->clear();
    curve->calculateCurve(redrawBezierCurveStepX);
    ui->graphicsView->scene()->clear();
    DrawBorder();
    DrawGrid();
    drawPoints();
    drawCurve();
}
/*
 *  Returning relation coordiantes of point relates of area inside border
 */
Point ToolCurvesDialog::get255Values(const Point &pt)
{
    return Point ( (float)(pt.x - border) / (width  - 2*border) ,
                   (float)(pt.y - border) / (height - 2*border)
                 );
}

