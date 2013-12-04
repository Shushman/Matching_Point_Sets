#include "Point2D.h"
#include "Hash2D.h"
#include "math.h"
#include "vector"
#include "stdio.h"


using namespace std;

extern double min_x,max_x,min_y,max_y,scaleFactor;

double getShortestDistance(vector<Point2D>& pointlist);
void writePointsToFile(const vector<Point2D>& pSet,const vector<Point2D>& qSet, double radius);
void readInput(vector<Point2D>& pSet,vector<Point2D>& qSet,double&  alpha);

void deNormalisePoints(vector<Point2D>& set)
{
	
	for (vector<Point2D>::iterator it= set.begin();it!=set.end();++it)
	{
		(*it).denormalisePoint(min_x,min_y,scaleFactor);
	}
}


void normalisePoints(vector<Point2D>& set)
{
	
	for (vector<Point2D>::iterator it= set.begin();it!=set.end();++it)
	{
		(*it).normalisePoint(min_x,min_y,scaleFactor);
	}
}

//asumming normalised sets and radius in normalised form;
bool findMatchs(vector<Point2D>& pSet, vector<Point2D>& qSet, double radius,const double alpha)
{
	int pSize = pSet.size(), qSize = qSet.size();
	int k = floor(alpha* min(pSize,qSize));
	int pMatchCount=0, qMatchCount=0;
	Point2D * pTemp;
	double dist;
	Hash2D hash(radius);
	hash.hashPoints(pSet);
	for (vector<Point2D>::iterator it= qSet.begin();it!=qSet.end();++it)
	{
		pTemp = hash.getMinDistNeighbour(*it,dist);
		if(dist<=radius)
		{
			if(pTemp->isAMatch())
			{
				pMatchCount++;
			}
			(*it).isAMatch();
			qMatchCount++;
		}
	}
	int myk = min(pMatchCount,qMatchCount);
	double myalpha = (myk+1)*1.0/min(pSize,qSize) - 0.000001;
	printf("Maximum alpha for which there is a match: %lf\n",myalpha );
	//todo : explain Q is said to match P if k points of Q are found to match with k points of P in the aforesaid manner.
	if(pMatchCount>=k && qMatchCount>=k) return true;
	return false;
}



int main(int argc, char const *argv[])
{
	std::vector<Point2D> P,Q;
	double radius, temp,alpha;
	
	readInput(P,Q,alpha);
	
	radius = getShortestDistance(P)/2;

	normalisePoints(P);
	normalisePoints(Q);
	radius/=scaleFactor;
	
	if(findMatchs(P,Q,radius,alpha)) printf("Q is a match to P\n");
	else 							 printf("Q is not a match to P\n");

	deNormalisePoints(P);
	deNormalisePoints(Q);
	radius*=scaleFactor;

	writePointsToFile(P,Q,radius);
	/*todo
		to run the program type following :$ bash setup.sh

		to build run following on terminal:
		$ g++ main.cpp mindistance.cpp readWrite.cpp Point2D.cpp Hash2D.cpp 

		
	*/
	

	return 0;
}