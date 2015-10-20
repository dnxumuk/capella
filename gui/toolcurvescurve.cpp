#include "toolcurvescurve.h"
#include <QDebug>
#include <limits>
#include <math.h>

ToolCurvesCurve::ToolCurvesCurve()
{
    points = new std::list<point>();
    curve  = new std::list<point>();
    Limit =  new rectangle();

    Limit->y_max = Limit->x_max =      std::numeric_limits<float>::max();
    Limit->y_min = Limit->x_min = (-1)*std::numeric_limits<float>::max();
    xLeftBound  = 0.;
    xRightBound = 1.;

    Limit->x_max = 1.;
    Limit->x_min = 0.;
    Limit->y_max = 1.;
    Limit->y_min = 0.;

    xStep = 0.0001;
    selectPoint(points->end());
}

ToolCurvesCurve::~ToolCurvesCurve()
{
    points->clear();
    curve->clear();
    delete points;
    delete curve;
    //delete Limit;
}

//
// Getting coordinates
//
float ToolCurvesCurve::getX(uint num)
{
    std::list<point>::iterator currentPoint = findPointByNum(num);
    return currentPoint->x;
}

float ToolCurvesCurve::getY(uint num)
{
    std::list<point>::iterator currentPoint = findPointByNum(num);
    return currentPoint->y;
}

float ToolCurvesCurve::getCurveX(unsigned int num)
{
    std::list<point>::iterator currentPoint = findCurvePointByNum(num);
    return currentPoint->x;
}

float ToolCurvesCurve::getCurveY(unsigned int num)
{
    std::list<point>::iterator currentPoint = findCurvePointByNum(num);
    return currentPoint->y;
}

//
// Finding point by number
//
std::list<point>::iterator ToolCurvesCurve::findPointByNum(unsigned int num)
{
    if (num >= points->size() || points->empty())
        return points->end();

    std::list<point>::iterator currentPoint = points->begin();
    for (uint i=0 ; i<num ; i++)
        ++currentPoint;
    return currentPoint;
}

std::list<point>::iterator ToolCurvesCurve::findCurvePointByNum(unsigned int num)
{
    if (num >= curve->size() || curve->empty())
        return curve->end();

    std::list<point>::iterator currentPoint = curve->begin();
    for (uint i=0 ; i<num ; i++)
        ++currentPoint;
    return currentPoint;
}

void ToolCurvesCurve::build_spline(std::size_t n)
{
    this->n = n;
    if (n < 2 )
        return;
    // Init spline array
    splines = new spline_tuple[n];
    for (std::size_t i = 0; i < n; ++i)
    {
            splines[i].x = getX(i);
            splines[i].a = getY(i);
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

void ToolCurvesCurve::calcCurve(float step)
{
    xStep = step;
    points->sort();
    if (points->size() < 2) return;

    build_spline(points->size());
    float epsilon = 0.00001;
    for (float i=xLeftBound ; i<=xRightBound+epsilon; i+=xStep)
        addCurvePoint( i, interpolatePoint(i) );
    delete[] splines;
    toPointLimit();
}

float ToolCurvesCurve::interpolatePoint(float x) const
{
    if (!splines)
            return std::numeric_limits<float>::quiet_NaN(); // Если сплайны ещё не построены - возвращаем NaN
    spline_tuple *s;
    if (x <= splines[0].x) // Если x меньше точки сетки x[0] - пользуемся первым эл-тов массива
            s = splines + 1;
    else if (x >= splines[n - 1].x) // Если x больше точки сетки x[n - 1] - пользуемся последним эл-том массива
            s = splines + n - 1;
    else // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
    {
            std::size_t i = 0, j = n - 1;
            while (i + 1 < j)
            {
                    std::size_t k = i + (j - i) / 2;
                    if (x <= splines[k].x)
                            j = k;
                    else
                            i = k;
            }
            s = splines + j;
    }
    float dx = (x - s->x);
    return s->a + (s->b + (s->c / 2. + s->d * dx / 6.) * dx) * dx; // Вычисляем значение сплайна в заданной точке.
}


//
// Checking methods
//
bool ToolCurvesCurve::isCorrectSize(unsigned int num)
{
    if ( num < points->size() )
        return true;
    return false;
}

bool ToolCurvesCurve::isCorrectPoint(float x, float y)
{
    if (( x <= Limit->x_max && x >= Limit->x_min ) &&
        ( y <= Limit->y_max && y >= Limit->y_min))
        return true;
    return false;
}


//
// Insert, modify, delete point's function
//
int ToolCurvesCurve::addPoint(uint num, float x, float y)
{
    if ( isCorrectPoint(x,y) || num == 0 )
    {
        points->insert(findPointByNum(num), point(x,y) );
        return 0;
    }
    return 1;
}

int ToolCurvesCurve::addPoint(float x, float y)
{
    if ( isCorrectPoint(x,y) )
    {
        points->push_back( point(x,y) );
        return 0;
    }
    return 1;
}

int ToolCurvesCurve::addCurvePoint(unsigned int num, float x, float y)
{
    curve->insert(findCurvePointByNum(num), point(x,y) );
    return 0;
}

int ToolCurvesCurve::addCurvePoint(float x, float y)
{
    curve->push_back( point(x,y) );
}

void ToolCurvesCurve::movePoint(unsigned int num, float x_new, float y_new)
{
    if ( isCorrectSize(num) && isCorrectPoint(x_new,y_new) )
    {
        std::list<point>::iterator currentPoint = findPointByNum(num);
        if ( currentPoint != points->end() )
        {
            currentPoint->x = x_new;
            currentPoint->y = y_new;
        }
    }
}

void ToolCurvesCurve::deletePoint(unsigned int num)
{
    std::list<point>::iterator currentPoint = findPointByNum(num);
    if ( currentPoint != points->end() )
        points->erase(currentPoint);
}


int ToolCurvesCurve::deleteCurvePoint(unsigned int num)
{
    std::list<point>::iterator currentPoint = findCurvePointByNum(num);
    if ( currentPoint != curve->end() )
    curve->erase(currentPoint);
}


//
//  Other functions ...
//

void ToolCurvesCurve::toPointLimit()
{
    for ( std::list<point>::iterator currentPoint = curve->begin() ; currentPoint != curve->end(); currentPoint++ )
    {
        // x - coordinate
        if (currentPoint->x >  Limit->x_max)
            currentPoint->x = Limit->x_max;
        else
            if ( currentPoint->x < Limit->x_min )
                currentPoint->x = Limit->x_min;
        // y - coordinate
        if (currentPoint->y >  Limit->y_max)
            currentPoint->y = Limit->y_max;
        else
            if ( currentPoint->y < Limit->y_min )
                currentPoint->y = Limit->y_min;
    }
}
void ToolCurvesCurve::dumpPoint(unsigned int num)
{
    std::list<point>::iterator currentPoint = findPointByNum(num);
    if ( currentPoint != points->end() )
        qDebug() << "Point [" << num << "] = {" << currentPoint->x << "," << currentPoint->y << "}";
    else
        qDebug() << "Point [" << num << "] is not find / exists ";
}

void ToolCurvesCurve::dumpCurvePoint(unsigned int num)
{
    std::list<point>::iterator currentPoint = findCurvePointByNum(num);
    if ( currentPoint != curve->end() )
        qDebug() << "     CurvePoint [" << num << "] = {" << currentPoint->x << "," << currentPoint->y << "}";
    else
        qDebug() << "Point [" << num << "] is not find / exists ";
}

void ToolCurvesCurve::selectPoint(std::list<point>::iterator point)
{
    this->selectedPoint = point;
}

void ToolCurvesCurve::deselectPoint()
{
    selectedPoint = points->end();
}

point &point::operator =(const point &pt)
{
    if ( this == &pt)
        return *this;
    this->x = pt.x;
    this->y = pt.y;
    return *this;
}

std::list<point>::iterator ToolCurvesCurve::findPointByCoordinates(float x, float y, float radius_x, float radius_y)
{
    // Get points from  rect (x,y,x+radius, y+radius)
    float _x  = x-radius_x;
    float _y  = y-radius_x;
    float _x1 = x+radius_y;
    float _y1 = y+radius_y;

    std::list<point>::iterator currentPoint = points->begin();
    std::list<point>::iterator nearestPoint = points->end();
    float                      nearetsPointDistance = std::numeric_limits<float>::max();
    for (uint i=0 ; i< points->size() ; i++)
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
