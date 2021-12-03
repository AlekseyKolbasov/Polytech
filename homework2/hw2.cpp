#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

double traectoriaR(double g, double x, double xi, double yi, double V_x, double V_y){
    double Y = - g*(x-xi)*(x-xi)/2/V_x/V_x+(V_y-g*xi/V_x)*(x-xi)/V_x+yi;
    return Y;
}
double traectoriaL(double g, double x, double xi, double yi, double V_x, double V_y){
    double Y = - g*(x-xi)*(x-xi)/2/V_x/V_x-(V_y-g*xi/V_x)*(x-xi)/V_x+yi;
    return Y;
}
int proverkaRight(vector<double> X,vector<double> Y,double g, double yi, double V_x, double V_y,int zona,int a){
    int n;
    for (int i = zona; i<=a-1; ++i){
        double l = - g*(X[i] - X[zona-1])*(X[i]-X[zona-1])/2/V_x/V_x+(V_y-g*X[zona-1]/V_x)*(X[i]-X[zona-1])/V_x+yi;
        //cout<<l<<endl;
        if (l<0) {
            return 0;
        }
        if (l<Y[i]){
            int j = i;
            return j;
        }
        n = i+1;
    }
    return n;
}
int proverkaleft(vector<double> X,vector<double> Y,double g, double yi, double V_x, double V_y,int zona){
    int n;
    for (int i = 1; i<=zona; ++i){
        double l = - g*(X[zona-i]-X[zona])*(X[zona-i]-X[zona])/2/V_x/V_x-(V_y-g*X[zona]/V_x)*(X[zona-i]-X[zona])/V_x+yi;
        //cout<<l<<endl;
        if (zona-i==0){
            return 0;
        }
        if (l<Y[zona-i]){
            int j = zona-i+1;
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
    int  zona = 1;
    int zona1;

    ifstream file("file.txt");
    double  h,V_x,V_y,x,y;
    int a=1;
    vector<double>  X,Y;
    if (file.is_open()) {
        file>>h;
        file>>V_x>>V_y;
        X.push_back(0.);
        Y.push_back(h);
        //cout<<X[a]<<"  "<<Y[a]<<endl;
        while (file >> x >> y) {
            X.push_back(x);
            Y.push_back(y);
            a++;
            //cout<<X[a]<<"  "<<Y[a]<<endl;
        }
    }
    //cout<<a<<endl;
    if (V_x==0){
        cout<<0<<endl;
        return 0;
    }
        float g = 9.81; float xi = 0;

        double yi;
        yi = Y[0];

        while (yi>0){
            if (zona1==zona){
                cout<<zona-1<<endl;
                return 0;
            }
            zona1 = proverkaRight(X, Y,g , yi, V_x, V_y,zona, a);
            if (zona1==a){
                cout<<zona1<<endl;
                return 0;
            }
            //cout<<zona1<<endl;
            double yl = traectoriaR(g,X[zona1],X[zona-1],yi,V_x, V_y);
            //cout<<yl<<endl;
            yi = yl;
            if (yi<0){
                cout<<zona1-1<<endl;
                return 0;
            }
            zona = proverkaleft(X, Y,g , yi, V_x, V_y,zona1);
            if (zona==0){
                cout<<zona<<endl;
                return 0;
            }
            double yr = traectoriaL(g,X[zona-1],X[zona1],yi,V_x, V_y);
            //cout<<zona<<"JOPA"<<endl;
            yi=yr;
            if (yi<0){
                cout<<zona-1<<endl;
                return 0;
            }
        }
    }
