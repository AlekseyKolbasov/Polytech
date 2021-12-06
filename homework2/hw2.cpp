#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

double traectoriaR(double g, double x, double xi, double yi, double V_x, double V_y){
    double Y = - g*(x-xi)*(x-xi)/2/V_x/V_x+(V_y-g*xi/V_x)*(x-xi)/V_x+yi;
    return Y;
}
double traectoriaL(double g, double x, double xi, double yi, double V_x, double V_y){
    double Y = - g*(x-xi)*(x-xi)/2/V_x/V_x-(V_y-g*xi/V_x)*(x-xi)/V_x+yi;
    return Y;
}
int proverkaRight(vector<double> X,vector<double> Y,double g, double yi, double V_x, double V_y,int zona, int a){
    int n;
    for (int i = zona; i<=a; ++i){
        double l = - g*(X[i] - X[zona-1])*(X[i]-X[zona-1])/2/V_x/V_x+(V_y-g*X[zona-1]/V_x)*(X[i]-X[zona-1])/V_x+yi;
        if (l<Y[i]){
            int j = i-1;
            return j;
        }
        n = i;
    }
    return n;
}
int proverkaleft(vector<double> X,vector<double> Y,double g, double yi, double V_x, double V_y,int zona){
    int n;
    for (int i = 0; i<=zona; ++i){
        double l = - g*(X[zona-i]-X[zona+1])*(X[zona-i]-X[zona+1])/2/V_x/V_x-(V_y-g*X[zona+1]/V_x)*(X[zona-i]-X[zona+1])/V_x+yi;

        if (l<Y[zona-i]){
            int j = zona-i;
            return j;
        }
        else if (zona-i==0){
            return zona-i;
        }
        n = zona-i;
    }
    return n;
}

int main(int argc, char** argv) {
    if (argc==2) {
        cout<<1<<endl;
    }
    
}
