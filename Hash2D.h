#ifndef Hash2D_H
#define Hash2D_H 


#include "Point2D.h"
#include "map"
#include "vector"
#define mapHash         

#ifdef mapHash
class Hash2D
{

	std::map<int, Point2D*> pointMap;
	
	int cols;
	double cellwidth;
public:
	Hash2D(double);
	~Hash2D();
	void hashPoint( Point2D &);
	void hashPoints( std::vector<Point2D> &);
	bool isEmpty(int);
	Point2D *getPoint(int);
	int getHashKey(const Point2D &);
	Point2D* getMinDistNeighbour(const Point2D &, double&);
	/* data */
};

#endif

#endif