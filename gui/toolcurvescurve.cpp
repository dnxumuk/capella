#include "toolcurvescurve.h"
#include <QDebug>
#include <limits>
#include <math.h>

ToolCurvesCurve::ToolCurvesCurve()
{
    rootPoints   = new std::list<Point>();
    curvePoints  = new std::list<Point>();
    areaLimit    = new Rectangle();
    xAreaLeftBound  = 0.;
    xAreaRightBound = 1.;
    areaLimit->xTo   = 1.;
    areaLimit->xFrom = 0.;
    areaLimit->yTo   = 1.;
    areaLimit->yFrom = 0.;
    xCurveStep = 0.0001;
    selectPoint(rootPoints->end());
}
ToolCurvesCurve::~ToolCurvesCurve()
{
    rootPoints->clear();
    curvePoints->clear();
    delete rootPoints;
    delete curvePoints;
}

Point ToolCurvesCurve::getRootPointCoordinates( size_t position )
{
    auto currentPoint = findRootPointByPosition( position );
    return Point(currentPoint->x, currentPoint->y);
}
Point ToolCurvesCurve::getCurvePointCoordinates( size_t position )
{
    auto currentPoint = findCurvePointByPosition( position );
    return Point(currentPoint->x,currentPoint->y);
}
Point ToolCurvesCurve::getAbsoluteRootPointCoordinates( size_t size, size_t position )
{
    Point tmp = getRootPointCoordinates( position );
    return Point ( size*tmp.x , size*tmp.y );
}
Point ToolCurvesCurve::getAbsoluteCurvePointCoordinates( size_t size, size_t position )
{
    Point tmp = getCurvePointCoordinates( position );
    return Point ( size*tmp.x , size*tmp.y );
}
std::list<Point>::iterator ToolCurvesCurve::findRootPointByPosition( size_t position )
{
    if ( position >= rootPoints->size() || rootPoints->empty())
        return rootPoints->end();
    std::list<Point>::iterator currentPoint = rootPoints->begin();
    for ( size_t i=0 ; i < position ; i++)
        ++currentPoint;
    return currentPoint;
}
std::list<Point>::iterator ToolCurvesCurve::findCurvePointByPosition( size_t position )
{
    if ( position >= curvePoints->size() || curvePoints->empty())
        return curvePoints->end();
    auto currentPoint = curvePoints->begin();
    for ( size_t i=0 ; i < position ; i++)
        ++currentPoint;
    return currentPoint;
}
/*********************/
float ToolCurvesCurve::getX(uint num)
{
    std::list<Point>::iterator currentPoint = findPointByNum(num);
    return currentPoint->x;
}

float ToolCurvesCurve::getY(uint num)
{
    std::list<Point>::iterator currentPoint = findPointByNum(num);
    return currentPoint->y;
}

std::list<Point>::iterator ToolCurvesCurve::findPointByNum(unsigned int num)
{
    if (num >= rootPoints->size() || rootPoints->empty())
        return rootPoints->end();

    std::list<Point>::iterator currentPoint = rootPoints->begin();
    for (uint i=0 ; i<num ; i++)
        ++currentPoint;
    return currentPoint;
}


void ToolCurvesCurve::buildBezierSpline( size_t rootPointsCount )
{
    int n = rootPointsCount;
    this->rootPointsCount = n;
     if (n < 2 )
         return;
     splines = new BezierSplineTuple[ rootPointsCount ];

     for ( size_t i = 0; i < rootPointsCount; ++i )
     {
             splines[i].x = getRootPointCoordinates(i).x;
             splines[i].a = getRootPointCoordinates(i).y;
             qDebug() << "Roots" << getRootPointCoordinates(i).x << getRootPointCoordinates(i).y;
     }
     splines[0].c = 0.;


     //
     double *alpha = new double[n - 1];
     double *beta = new double[n - 1];
     double A, B, C, F, h_i, h_i1, z;
     alpha[0] = beta[0] = 0.;
     for (std::size_t i = 1; i < n - 1; ++i)
     {
         h_i = getX(i) - getX(i-1), h_i1 = getX(i+1) - getX(i);
             A = h_i;
             C = 2. * (h_i + h_i1);
             B = h_i1;
             F = 6. * ( ( getY(i+1) - getY(i) ) / h_i1 - (getY(i) - getY(i-1)) / h_i);
             z = (A * alpha[i - 1] + C);
             alpha[i] = -B / z;
             beta[i] = (F - A * beta[i - 1]) / z;
     }
     splines[n - 1].c = (F - A * beta[n - 2]) / (C + A * alpha[n - 2]);
     // Нахождение решения - обратный ход метода прогонки
     for (std::size_t i = n - 2; i > 0; --i)
             splines[i].c = alpha[i] * splines[i + 1].c + beta[i];
     // Освобождение памяти, занимаемой прогоночными коэффициентами
     delete[] beta;
     delete[] alpha;
     // По известным коэффициентам c[i] находим значения b[i] и d[i]
     for (std::size_t i = n - 1; i > 0; --i)
     {
             double h_i = getX(i) - getX(i-1);
             splines[i].d = (splines[i].c - splines[i - 1].c) / h_i;
             splines[i].b = h_i * (2. * splines[i].c + splines[i - 1].c) / 6. + (getY(i) - getY(i-1)) / h_i;
     }
}

void ToolCurvesCurve::calculateCurve(float xCurveStep)
{
    this->xCurveStep = xCurveStep;
    rootPoints->sort();
    if (rootPoints->size() < 2)
        return;
    //qDebug() << "GGGGGGGGGGGGGGG" << rootPoints->size();
    buildBezierSpline( rootPoints->size() );
    const float epsilon = 0.00001;
    for ( float xCoord = xAreaLeftBound ;  xCoord <= xAreaRightBound+epsilon; xCoord += xCurveStep)
        addCurvePoint( Point( xCoord , interpolatePoint(xCoord)) );
    delete[] splines;
    toPointLimit();
}

float ToolCurvesCurve::interpolatePoint(float x) const
{
    if (!splines) return std::numeric_limits<float>::quiet_NaN(); // Если сплайны ещё не построены - возвращаем NaN
    BezierSplineTuple *s;
    if (x <= splines[0].x) // Если x меньше точки сетки x[0] - пользуемся первым эл-тов массива
            s = splines + 1;
    else if (x >= splines[ rootPointsCount - 1].x) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
             s = splines + rootPointsCount - 1;
    else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
    {
            size_t i = 0, j = rootPointsCount - 1;
            while (i + 1 < j)
            {
                    size_t k = i + (j - i) / 2;
                    if (x <= splines[k].x)
                            j = k;
                    else
                            i = k;
            }
            s = splines + j;
    }
    float dx = (x - s->x);
    qDebug() << "CURVE" << x << s->a + (s->b + (s->c/2. + s->d*dx/6.) * dx) * dx;
    return
    s->a + (s->b + (s->c/2. + s->d*dx/6.) * dx) * dx;
    //qDebug() << "CURVE" << x << s->a + (s->b + (s->c/2. + s->d*dx/6.) * dx) * dx;
    // Вычисляем значение сплайна в заданной точке.
    //return zzz;
}


//
// Checking methods
//
bool ToolCurvesCurve::isCorrectSize(unsigned int num)
{
    if ( num < rootPoints->size() )
        return true;
    return false;
}

bool ToolCurvesCurve::isCorrectPoint(const Point& point)
{
    if (( point.x <= areaLimit->xTo && point.x >= areaLimit->xFrom ) &&
        ( point.y <= areaLimit->yTo && point.y >= areaLimit->yFrom))
        return true;
    return false;
}


//
// Insert, modify, delete point's function
//
int ToolCurvesCurve::addRootPoint( const Point& point , size_t position )
{
    if (position == 0)
    {

        rootPoints->push_back(point);
        return 1;
    }
    if ( isCorrectPoint(point) || position == 0 )
    {
        rootPoints->insert( findRootPointByPosition( position ), point );
        return 0;
    }
    return 1;
}

int ToolCurvesCurve::addCurvePoint( const Point& point, size_t position )
{
    curvePoints->insert( findCurvePointByPosition( position ), point );
    //qDebug() << "Add curve" << point.x << point.y;
    return 0;
}


void ToolCurvesCurve::deleteRootPoint( size_t position )
{
    auto currentPoint = findRootPointByPosition( position );
    if ( currentPoint != rootPoints->end() )
        rootPoints->erase(currentPoint);
}

//
//  Other functions ...
//

void ToolCurvesCurve::toPointLimit()
{
    for ( auto currentPoint = curvePoints->begin() ; currentPoint != curvePoints->end(); currentPoint++ )
    {
        // x - coordinate
        if (currentPoint->x >  areaLimit->xTo)
            currentPoint->x = areaLimit->xTo;
        else
            if ( currentPoint->x < areaLimit->xFrom )
                currentPoint->x = areaLimit->xFrom;
        // y - coordinate
        if (currentPoint->y >  areaLimit->yTo)
            currentPoint->y = areaLimit->yTo;
        else
            if ( currentPoint->y < areaLimit->yFrom )
                 currentPoint->y = areaLimit->yFrom;
    }
}

void ToolCurvesCurve::selectPoint(std::list<Point>::iterator point)
{
    this->selectedPoint = point;
}

void ToolCurvesCurve::deselectPoint()
{
    selectedPoint = rootPoints->end();
}

Point &Point::operator =(const Point &pt)
{
    if ( this == &pt)
        return *this;
    this->x = pt.x;
    this->y = pt.y;
    return *this;
}

std::list<Point>::iterator ToolCurvesCurve::findPointByCoordinates(float x, float y, float radius_x, float radius_y)
{
    // Get points from  rect (x,y,x+radius, y+radius)
    float _x  = x-radius_x;
    float _y  = y-radius_x;
    float _x1 = x+radius_y;
    float _y1 = y+radius_y;

    std::list<Point>::iterator currentPoint = rootPoints->begin();
    std::list<Point>::iterator nearestPoint = rootPoints->end();
    float                      nearetsPointDistance = std::numeric_limits<float>::max();
    for (uint i=0 ; i< rootPoints->size() ; i++)
    {
        if ( currentPoint->x >= _x && currentPoint->x <= _x1 &&
             currentPoint->y >= _y && currentPoint->y <= _y1 )
        {
            float distance = (x-currentPoint->x)*(x-currentPoint->x) + (y-currentPoint->y)*(y-currentPoint->y);
            if  ( distance < nearetsPointDistance )
            {
                nearetsPointDistance = distance;
                nearestPoint = currentPoint;
            }
        }
        ++currentPoint;
    }
    return nearestPoint;
}
