#include "Point2D.h"
#include "vector"
#include "algorithm" 
#include "stdio.h"
using namespace std;

bool compareX(const Point2D& p1, const Point2D& p2){
	//Comparator for the sort algorithm
	if(p1.getPx()<p2.getPx())
		return true;
	else if(p1.getPx()>p2.getPx())
		return false;
	else{
		if(p1.getPy()<p2.getPy())
			return true;
		return false;
	}
}

bool compareY(const Point2D& p1, const Point2D& p2){
	return (p1.getPy()<p2.getPy());
}

double minOfThree(double a, double b, double c){
	if(a<=b){
		if(b<=c)
			return a;
		if(a<=c)
			return a;
		else
			return c;
	}
	else{
		if(a<=c)
			return b;
		if(b<=c)
			return b;
		else 
			return c;
	}
	return -1;
}

void displist(vector<Point2D>& plist){
	int i,s=plist.size();
	for(i=0;i<s;i++){
		plist[i].display();
	}
	cout<<"\n";
}

double closestPair(vector<Point2D>& p_x, int start, int end, vector<Point2D>& p_y){
	
	//Implements the optimized algorithm for obtaining the distance between the closest pair of points in a plane
	int i=0,s=end-start+1;
	//Base cases
	if(s==2){
		return (Point2D::dist(p_x[start],p_x[start+1]));
	}
	
	if(s==3){
		return minOfThree(Point2D::dist(p_x[start+1],p_x[start+2]),Point2D::dist(p_x[start+2],p_x[start+0]),Point2D::dist(p_x[start+0],p_x[start+1]));
	}
	
	int mid = (start+end)/2;
	vector<Point2D> pyl(mid-start+1);
	vector<Point2D> pyr(end-mid);
	Point2D medpt(p_x[mid]); //The median point to use as the partition
	double x_med = medpt.getPx();
	s=p_y.size();
	int j=0,k=0;

	for(i=0;i<s;i++){
		if(p_y[i].getPx()<x_med||p_y[i].getPx()==x_med&&p_y[i].getPy()<=medpt.getPy())
			pyl[j++].copyPoint(p_y[i]);
		else
			pyr[k++].copyPoint(p_y[i]);
	}

	double d1 = closestPair(p_x,start,mid,pyl);
	double d2 = closestPair(p_x,mid+1,end,pyr);

	double delta = (d1<d2)?d1:d2;
	double mindist = delta,tempdist=0.0;
	s=p_y.size();
	vector<Point2D> Q_y(s);
	vector<bool> labels(s);
	x_med = medpt.getPx();
	j=k=0;
	int n=0;
	
	//Dividing the points based on which partition they are in
	for(i=0;i<s;i++){
		if(p_y[i].getPx()>=x_med-delta&&p_y[i].getPx()<=x_med+delta){
			Q_y[n].copyPoint(p_y[i]);
			if(p_y[i].getPx()<x_med||p_y[i].getPx()==x_med&&p_y[i].getPy()<=medpt.getPy())
				labels[n++]=true;
			else
				labels[n++]=false;
		}
	}
	
	int count=0;
	//Search the rectangle around each point for possible closest neighbours
	for(i=0;i<n;i++){
		if(labels[i]==true){
			j=i-1;
			while(j>=0&&count<4){
				if(labels[j]==false){
					tempdist=Point2D::dist(Q_y[i],Q_y[j]);
					if(tempdist<mindist)
						mindist=tempdist;
					count++;
				}
				j--;
			}
			count=0;
			j=i+1;
			while(j<n&&count<4){
				if(labels[j]==false){
					tempdist=Point2D::dist(Q_y[i],Q_y[j]);
					if(tempdist<mindist)
						mindist=tempdist;
					count++;
				}
				j++;
			}
		}
	}
	return mindist;
}

double getShortestDistance(vector<Point2D>& pointlist){

	//The actual function to use. It returns the shortest distance in the original point-set
	int i,n=pointlist.size();
	vector<Point2D> plistCopy(n);
	
	for(i=0;i<n;i++){
		plistCopy[i].copyPoint(pointlist[i]);
	}
	double d;
	sort(pointlist.begin(),pointlist.end(),compareX);
	sort(plistCopy.begin(),plistCopy.end(),compareY);
	d=closestPair(pointlist,0,n-1,plistCopy);
	return d;
}

