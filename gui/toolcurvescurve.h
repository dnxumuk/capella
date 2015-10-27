#ifndef TOOLCURVESCURVE_H
#define TOOLCURVESCURVE_H
#include <list>
#include <cstdlib>
#include <cmath>
#include <limits>

class Point;
class Rectangle;
class BezierSplineTuple;

struct Point
{
    float x;
    float y;
    Point (int x, int y)     { this->x = x   ; this->y = y;   };
    Point (float x, float y) { this->x = x   ; this->y = y;   };
    Point (const Point &pt)  { this->x = pt.x; this->y = pt.y;};
    Point& operator = ( const Point& pt);
    bool operator <   ( const Point& pt) { if (pt.x > this->x) return true; return false; }
};


class ToolCurvesCurve
{
public:
    std::list<Point>::iterator findPointByNum(unsigned int num);
    std::list<Point> *rootPoints;
    std::list<Point> *curvePoints;
    std::list<Point>::iterator selectedPoint;
    BezierSplineTuple *splines;
    Rectangle         *areaLimit;
    std::list<Point>::iterator findRootPointByPosition  (size_t position );
    std::list<Point>::iterator findCurvePointByPosition (size_t position );
    std::size_t rootPointsCount;

    void  buildBezierSpline( size_t rootPointsCount );
    void  calculateCurve   ( float step );
    float interpolatePoint ( float x ) const;


    void toPointLimit();
    bool isCorrectSize  ( size_t postion );
    bool isCorrectPoint ( const Point& point );

    float xAreaLeftBound;
    float xAreaRightBound;
    float xCurveStep;
public:
    ToolCurvesCurve();
    ~ToolCurvesCurve();
    int  addRootPoint   ( const Point& point, size_t position = 0 );
    int  addCurvePoint  ( const Point& point, size_t position = 0 );

    void deleteRootPoint( size_t postion );

    Point getRootPointCoordinates  ( size_t position );
    Point getCurvePointCoordinates ( size_t position );
    Point getAbsoluteRootPointCoordinates  ( size_t size, size_t position );
    Point getAbsoluteCurvePointCoordinates ( size_t size, size_t position );

    void resetAll(); // nonrealized


    void selectPoint   (std::list<Point>::iterator point);
    void deselectPoint ();
    std::list<Point>::iterator findPointByCoordinates(float x, float y, float radius_x, float radius_y);
    bool pointExists   (std::list<Point>::iterator pt) { return ( &(*pt) == &(*rootPoints->end()) )?0:1; };
};


struct Rectangle
{
    float xFrom , xTo,
          yFrom , yTo;
};

struct BezierSplineTuple
{
        float a, b, c, d, x;
};


#endif // TOOLCURVESCURVE_H
