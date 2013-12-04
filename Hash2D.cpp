#include "Hash2D.h"
#include "math.h"
#include "iostream"
#ifdef	mapHash

Hash2D::Hash2D(double width)
{
	cellwidth = width;
	cols = ceil(1/width);
}
Hash2D::~Hash2D()
{
	pointMap.clear();
}
int Hash2D::getHashKey(const Point2D& a)
{
	int x = floor(a.getPx()/cellwidth);
	int y = floor(a.getPy()/cellwidth);
	return y*cols + x;
}
void Hash2D::hashPoint( Point2D& a)
{
	pointMap[getHashKey(a)] = &a;
}
void Hash2D::hashPoints( std::vector<Point2D> & list)
{
	for (std::vector<Point2D>::iterator it = list.begin(); it != list.end(); ++it)
	{
		hashPoint(*it);
	}
}
bool Hash2D::isEmpty(int key)
{
	if(pointMap.find(key)==pointMap.end()) return true;
	return false;
}
Point2D *Hash2D::getPoint(int key)
{
	if(!isEmpty(key)) return pointMap.find(key)->second;
	return NULL;
}
Point2D* Hash2D::getMinDistNeighbour(const Point2D& pt, double& dist)
{
	int x = floor(pt.getPx()/cellwidth);
	int y = floor(pt.getPy()/cellwidth);
	dist = 9;
	Point2D * nearPt=NULL, *temp;
	for (int i = x-1; i <= x+1; ++i)
	{
		for (int j = y-1; j <= y+1; ++j)
		{
			if(i>=0 && i<cols && j>=0 && j<cols)
			{
				temp = getPoint(j*cols+i);
				if(temp !=NULL && dist > Point2D::squareDist(*temp,pt))
				{
					 dist = Point2D::squareDist(*temp,pt);
					 nearPt = temp;
				}
			}
		}
	}
	dist = sqrt(dist);
	return nearPt;
}
#endif
