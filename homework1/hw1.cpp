#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
	ifstream infile("in.txt");

	int x, y;

	int xleft=0,yleft=0,xright=0,yright=0;

	double cosright, cosleft;
	cosleft = 1; cosright = 1;

	int x0, y0;
	infile >> x0 >> y0;

	while (infile >> x >> y)
	{
		double cos = (x0*x+y0*y)/(sqrt(x*x+y*y)*sqrt(x0*x0+y0*y0));
        	cos =round(cos * 1000.0) / 1000.0;
		if (cos <=cosleft && (y0*x < x0*y)) 
		{
			cosleft = cos;
			xleft = x; yleft = y;
		}
		if (cos <=cosright && (y0*x >= x0*y)) 
		{
			cosright = cos;
			xright = x; yright = y;
		}
	}

	cout << "Leftmost: " << xleft << " " << yleft << endl;
	cout << "Rightmost: " << xright << " " << yright << endl;
}
