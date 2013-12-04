#include "Point2D.h"
#include "math.h"
Point2D::Point2D()
{
        px = 0;
        py = 0;
        match = false;
}
Point2D::Point2D(double x, double y)
{
        px = x;
        py = y;
        match = false;
}
Point2D::~Point2D()
{

}

void Point2D::copyPoint(const Point2D& point){
	px=point.px;
	py=point.py;
}

void Point2D::normalisePoint(double leftmost, double bottommost, double scaleFactor)
{
        px = (px - leftmost)/scaleFactor;
		py = (py - bottommost)/scaleFactor;
}
void Point2D::denormalisePoint(double leftmost, double bottommost, double scaleFactor)
{
        px = px*scaleFactor+ leftmost;
        py = py*scaleFactor + bottommost;
}

bool Point2D::isAMatch() 
{
        if(match) return false;
        return match = true;
}
double Point2D::dist(const Point2D& a , const Point2D& b)
{
     return sqrt(squareDist(a,b));
}
double  Point2D::squareDist(const Point2D& a, const Point2D& b)
{
   return  (a.px-b.px)*(a.px-b.px) + (a.py-b.py)*(a.py-b.py); 
}
        