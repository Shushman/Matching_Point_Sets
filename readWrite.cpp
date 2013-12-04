#include "Point2D.h"
#include "Hash2D.h"
#include "vector"
#include "stdio.h"
#include "iostream"
#include <stdlib.h>    
#include <time.h> 

#define READ_SIZE_FROM_USER
#define sizeP 1000
#define sizeQ 50000
#define OutImg  "myplot.svg"
#define xSD 100
#define ySD 150
using namespace std;
double min_x,max_x,min_y,max_y,scaleFactor,dmin;

void writePointsToFile(const vector<Point2D>& pSet,const vector<Point2D>& qSet, double radius)
{
	FILE *f1;
	
	f1 = fopen(OutImg,"w");
	fprintf(f1, "<svg height=\"%lf\" width=\"%lf\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n",max_y,max_x );
	for (vector<Point2D>::const_iterator it= pSet.begin();it!=pSet.end();++it)
	{
		if((*it).getIsMatching())
		{
			fprintf(f1,  "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"blue\" stroke-width=\"1\" fill-opacity=\"0.0\" />\n",(*it).getPx(),(*it).getPy(),radius );
		}
		fprintf(f1,  "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"blue\" stroke-width=\"1\" fill=\"blue\" fill-opacity=\"1\" />\n",(*it).getPx(),(*it).getPy(),2.5 );
	
	}
	for (vector<Point2D>::const_iterator it= qSet.begin();it!=qSet.end();++it)
	{
		if((*it).getIsMatching())
		{
		fprintf(f1,  "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"red\" stroke-width=\"1\" fill=\"red\" fill-opacity=\"1\" />\n",(*it).getPx(),(*it).getPy(),2.5);
		}
		else
		{
		fprintf(f1,  "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"green\" stroke-width=\"1\" fill=\"green\" fill-opacity=\"1\" />\n",(*it).getPx(),(*it).getPy(),2.5 );
		}
	}
	fprintf(f1, "</svg> \n");
	fclose(f1);
}
void readFromFile(vector<Point2D>& pSet,vector<Point2D>& qSet,double&  alpha)
{
	char fileName[100];
	printf("Enter File Name: ");
	scanf("%s",fileName);
	FILE *fp;
	fp = fopen(fileName,"r");
	if(fp==NULL)
	{
		printf("Error Opening File\n");
		exit(0);
	}
	int n,m, i=0,j=0;
	double x,y;
	fscanf(fp,"%d %d %lf",&n,&m,&alpha);
	fscanf(fp,"%lf %lf %lf %lf",&min_x,&max_x,&min_y,&max_y);
	pSet.resize(n);
	qSet.resize(m);
	
	for(i=0;i<n;i++){
		fscanf(fp,"%lf %lf",&x,&y);
		Point2D p(x,y);
		pSet[i].copyPoint(p);
	}

	for(i=0;i<m;i++){
		fscanf(fp,"%lf %lf",&x,&y);
		Point2D p(x,y);
		qSet[i].copyPoint(p);
	}
}

bool checkHashMap(bool **hmap, int rows, int cols, int r, int c){ //rows is total rows, r and c is position to check
    int i,j;
    if(hmap[r][c]==true) //Point there already
        return false;
    int str = (r-1>=0)?r-1:0, stc = (c-1>=0)?c-1:0;
    int endr = (r+1<rows)?r+1:rows-1, endc = (c+1<cols)?c+1:cols-1;
    for(i=str;i<=endr;i++){
        for(j=stc;j<=endc;j++){
			//make 3X3 all true
            hmap[i][j] = true;
        }
    }
    return true;
}

void genRandomInput(vector<Point2D>& pSet,vector<Point2D>& qSet,double&  alpha)
{
	//m must be greater than at least 2n/3
	int n=sizeP,m=sizeQ, i=0,j=0,k=0;
	double x,y, temp1, temp2,temp3,dmin;
	#ifdef READ_SIZE_FROM_USER
		printf("Enter Size of P:");
		scanf("%d",&n);
		printf("Enter Size of Q:");
		scanf("%d",&m);
		printf("Enter value of alpha:");
		scanf("%lf",&alpha);
	#endif
	srand(time(NULL));
	do
	{
		printf("Enter a positive double for min X:");
		scanf("%lf",&min_x);
	}while(min_x<0);

	do
	{
		printf("Enter a positive double for min Y:");
		scanf("%lf",&min_y);
	}while(min_y<0);

	do
	{
		printf("Enter a positive double for max X:");
		scanf("%lf",&max_x);
	}while(max_x<=0);

	do
	{
		printf("Enter a positive double for max Y:");
		scanf("%lf",&max_y);
	}while(max_y<=0);
	
	do
	{
		printf("Enter a minimum distance between pts of P (preferably >20 units):");
		scanf("%lf",&dmin);
	}while(dmin<=0);
	pSet.resize(n);
	qSet.resize(m);
	
	double perturb;
    int hrows = (int)((max_x-min_x)/dmin)+1, hcols = (int)((max_y-min_y)/dmin)+1;
    int hr,hc;
    bool **hmap = new bool*[hrows];
    for(i=0;i<hrows;i++){
        hmap[i] = new bool[hcols];
        for(j=0;j<hcols;j++)
                hmap[i][j]=false;
    }
    
	for(i=0;i<n;i++){
		temp1 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp2 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp3 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range

		x= temp1+temp2+temp3; //Kept it between 0 and 800; change to increase range

		temp1 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp2 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp3 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range

		y= temp1+temp2+temp3;

		x = x*(max_x-min_x)/4 + (max_x+min_x)/2;
		y = y*(max_y-min_y)/4 + (max_y+min_y)/2;
		hr = (int)((x-min_x)/dmin);
		hc = (int)((y-min_y)/dmin);
		
		//Check hashmap too
		if(x>=min_x && x<=max_x && y>=min_y && y<=max_y && checkHashMap(hmap,hrows,hcols,hr,hc)==true)
		{
			Point2D p(x,y);
			pSet[i].copyPoint(p);
		}
		else i--;
	}

	for(i=0;i<(n/3)&&i<m;i++){
		qSet[i].copyPoint(pSet[i]);
		//perturb each point of Q by a random amount
		
		perturb = 1.0 + (rand()*dmin/(4*RAND_MAX));
		qSet[i].setPy(pSet[i].getPy()+perturb);
		perturb = 1.0 + (rand()*dmin/(4*RAND_MAX));
		qSet[i].setPx(pSet[i].getPx()+perturb);
		
	}

	for(i=n/3;i<m;i++){
		temp1 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp2 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp3 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range

		x= temp1+temp2+temp3; //Kept it between 0 and 800; change to increase range

		temp1 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp2 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range
		temp3 = (rand()*2.0/RAND_MAX) -1;  //Kept it between 0 and 800; change to increase range

		y= temp1+temp2+temp3;

		x = x*(max_x-min_x)/4 + (max_x+min_x)/2;
		y = y*(max_y-min_y)/4 + (max_y+min_y)/2;
		if(x>=min_x && x<=max_x && y>=min_y && y<=max_y)
		{
			Point2D p(x,y);
			qSet[i].copyPoint(p);
		}
		else i--;
	}
}

void readInput(vector<Point2D>& pSet,vector<Point2D>& qSet,double&  alpha)
{
	int option;
	do{
	printf("To Generate Random Input Enter 1\n");
	printf("To Read Input From File  Enter 2\n");
	scanf("%d",&option);
	}while(option<1 || option>2);
	if(option==1) genRandomInput(pSet,qSet,alpha);
	else  readFromFile(pSet,qSet,alpha);


	if((max_x-min_x)>(max_y-min_y))scaleFactor = max_x-min_x;
	else scaleFactor = max_y-min_y;
	
}
