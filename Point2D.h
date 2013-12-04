#ifndef Point2D_H
#define Point2D_H 
#include <iostream>

//todo: Add more methods if u have to.
class Point2D
{
        double px,py;
        bool match;       //true for Pi if there is a circle which contains a point of Q
                                          //true for Qi if it matches some point in P
public:
        Point2D();
        Point2D(double, double);
        ~Point2D();
        void normalisePoint(double,double,double); //normalises the point. Parameters are the lower left and upper right points.
        void denormalisePoint(double,double,double);//denormalises the point. Parameters are the lower left and upper right points.
        bool isAMatch() ;       //sets match to true. returns true if it was previously false.
        void copyPoint(const Point2D&); //Copies the point values
		inline void setPx(double x) {px = x;}
        inline void setPy(double y) {py = y;}
        inline double getPx() const { return px;}
        inline double getPy() const{ return py;}
        inline bool getIsMatching() const{ return match;}
		inline void display() const{ std::cout<<"["<<px<<","<<py<<"]";}
        static double dist(const Point2D&, const Point2D&);  //returns euclidean dist of two given point.
        static double squareDist(const Point2D&,const Point2D&);  //returns square of euclidean dist of two given point.
};

#endif