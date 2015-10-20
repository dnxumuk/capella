#ifndef TOOLCURVESCURVE_H
#define TOOLCURVESCURVE_H
#include <list>
#include <cstdlib>
#include <cmath>
#include <limits>

class point;
class rectangle;
class spline_tuple;

class ToolCurvesCurve
{
public:
    std::list<point> *points;
    std::list<point> *curve;
    rectangle *Limit;

    std::list<point>::iterator findPointByNum (uint num);
    std::list<point>::iterator findCurvePointByNum (uint num);
    std::list<point>::iterator selectedPoint;

    spline_tuple *splines;
    std::size_t n; // Количество узлов сетки

    void  build_spline(std::size_t n);
    void  calcCurve(float step);
    float interpolatePoint(float x) const;


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

    void selectPoint   (std::list<point>::iterator point);
    void deselectPoint ();
    std::list<point>::iterator findPointByCoordinates(float x, float y, float radius_x, float radius_y);
    bool pointExists   (std::list<point>::iterator pt) { return ( &(*pt) == &(*points->end()) )?0:1; };
};


struct point
{
    float x;
    float y;
    point (int x, int y)     { this->x = x   ; this->y = y;};
    point (float x, float y) { this->x = x   ; this->y = y;};
    point (const point &pt)  { this->x = pt.x; this->y = pt.y;};
    point& operator = (const point& pt);
    bool operator < ( const point& pt) { if (pt.x > this->x) return true; return false; }
};

struct rectangle
{
    float x_max,x_min,y_max,y_min;
};

struct spline_tuple
{
        float a, b, c, d, x;
};

/*
class Curve
{
    public:
        std::list<point> *points;
        std::list<point> *curve;
        rectangle *Limit;

        std::list<point>::iterator findPointByNum (uint num);
        std::list<point>::iterator findCurvePointByNum (uint num);
        std::list<point>::iterator selectedPoint;

        spline_tuple *splines;
        std::size_t n; // Количество узлов сетки

        void  build_spline(std::size_t n);
        void  calcCurve(float step);
        float interpolatePoint(float x) const;


        void toPointLimit();
        bool isCorrectSize  (uint num);
        bool isCorrectPoint (float x, float y);

        float xLeftBound;
        float xRightBound;
        float xStep;
    public:
        Curve();
        ~Curve();
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

        void selectPoint   (std::list<point>::iterator point);
        void deselectPoint ();
        std::list<point>::iterator findPointByCoordinates(float x, float y, float radius_x, float radius_y);
        bool pointExists   (std::list<point>::iterator pt) { return ( &(*pt) == &(*points->end()) )?0:1; };
};
*/

#endif // TOOLCURVESCURVE_H
