#ifndef TOOLCURVESCURVE_H
#define TOOLCURVESCURVE_H
#include <list>
#include <cstdlib>
#include <cmath>
#include <limits>

class Point;
class Rectangle;
class BezierSplineTuple;

class ToolCurvesCurve
{
public:
    std::list<Point> *rootPoints;
    std::list<Point> *curvePoints;
    std::list<Point>::iterator selectedPoint;
    BezierSplineTuple *splines;
    Rectangle *areaLimit;
    std::size_t n; // Количество узлов сетки


    std::list<Point>::iterator findPointByNum      (size_t num);
    std::list<Point>::iterator findCurvePointByNum (size_t num);

    void  build_spline(std::size_t n);
    void  calculateCurve  ( float step );
    float interpolatePoint( float x ) const;


    void toPointLimit();
    bool isCorrectSize  (uint num);
    bool isCorrectPoint (float x, float y);

    float xLeftBound;
    float xRightBound;
    float xStep;
public:
    ToolCurvesCurve();
    ~ToolCurvesCurve();
    int  addPoint   (uint num, float x, float y);
    int  addPoint(float x, float y);

    int  addCurvePoint (uint num, float x, float y);
    int  addCurvePoint (float x, float y);

    int  deleteCurvePoint (uint num);

    void movePoint  (uint num,float x_new, float y_new);
    void deletePoint(uint num);

    float getX (uint num);
    float getY (uint num);
    float getRealX (uint size, int num) {  return size*getX(num); };
    float getRealY (uint size, int num) {  return size*getY(num); };

    float getCurveX (uint num);
    float getCurveY (uint num);
    float getCurveRealX (uint size, int num) {  return size*getCurveX(num); };
    float getCurveRealY (uint size, int num) {  return size*getCurveY(num); };

    void resetAll();
    void dumpPoint(uint num);
    void dumpCurvePoint(unsigned int num);

    void selectPoint   (std::list<Point>::iterator point);
    void deselectPoint ();
    std::list<Point>::iterator findPointByCoordinates(float x, float y, float radius_x, float radius_y);
    bool pointExists   (std::list<Point>::iterator pt) { return ( &(*pt) == &(*rootPoints->end()) )?0:1; };
};


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

struct Rectangle
{
    float x_max,x_min,y_max,y_min;
};

struct BezierSplineTuple
{
        float a, b, c, d, x;
};


#endif // TOOLCURVESCURVE_H
