#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> readFile() {
    string line;
    vector<string> points;
    ifstream file("in.txt");
    points.push_back("0");
    if (file.is_open()) {
        string str;
        while (!file.eof()) {
            file >> str;
            points.push_back(str);
        }
        points.pop_back();
    }
    file.close();
    return points;
}
vector<double> divider(vector<string>& arr, string type) {
    int n = arr.size();
    vector<double> Xcell;
    vector<double> Ycell;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            Xcell.push_back(stod(arr[i]));
        }
        else {
            Ycell.push_back(stod(arr[i]));
        }
    }
    return (type == "X") ? Xcell : Ycell;
}

float traectoriaR(float g, float x, float xi, float yi, float V_x, float V_y){
    float Y = - g*(x-xi)*(x-xi)/2/V_x/V_x+(V_y-g*xi/V_x)*(x-xi)/V_x+yi;
}
float traectoriaL(float g, float x, float xi, float yi, float V_x, float V_y){
    float Y = - g*(x-xi)*(x-xi)/2/V_x/V_x-(V_y-g*xi/V_x)*(x-xi)/V_x+yi;
}
int proverkaRight(double X[],double Y[],float g, float xi, float yi, float V_x, float V_y,int zona,int a){
    int n;
    //cout<<a<<endl;
    for (int i = zona; i<=a; ++i){
        float l = - g*(X[i]-X[zona-1])*(X[i]-X[zona-1])/2/V_x/V_x+(V_y-g*X[zona-1]/V_x)*(X[i]-X[zona-1])/V_x+yi;
        //cout<<X[i]<<"  "<<l<<"  provekraR"<<endl;
        if (l<Y[i]){
           int j = i;
            return j;
        }
        n = i+1;
    }
    return n;
}
int proverkaleft(double X[],double Y[],double g, double yi, double V_x, double V_y,int zona){
    int n;
    for (int i = 1; i<=zona; ++i){
        double l = - g*(X[zona-i]-X[zona])*(X[zona-i]-X[zona])/2/V_x/V_x-(V_y-g*X[zona]/V_x)*(X[zona-i]-X[zona])/V_x+yi;
        //cout<<X[zona-i]<<"  "<<l<<"  provekraL"<<endl;
        //cout<<zona-i<<"    popka22   "<<endl;
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

int main() {
    vector<string> points = readFile();
    vector<double> vectorX = divider(points, "X");
    vector<double> vectorY = divider(points, "Y");

    double mleftmin = 1;
    double mrightmin = 1;
    int nleft, nright;

    int a = vectorX.size();
    double X[a];
    double Y[a];
    //cout<<a<<endl;

    for (int i=0; i<a; i++)
    {
        double *c = &vectorX[i];
        double h = *c;
        X[i] = h;
        double *c1 = &vectorY[i];
        double h1 = *c1;
        Y[i] = h1;
        //cout<<X[i]<<"  popka "<<Y[i]<<endl;
    }

    float g = 9.81; float xi = 0; float V_x = 4.24; float V_y =  4.24;

    int  zona = 1;
    int zona1;

    double yi;
    yi = Y[0];
    while (yi>0){
        if (zona1==zona){
            cout<<zona-1<<endl;
            return 0;
        }
        zona1 = proverkaRight(X, Y,g,xi , yi, V_x, V_y,zona,a);
        //cout<<sizeof(X)/8<<endl;
        if (zona1==sizeof(X)/8){
            cout<<zona1-1<<endl;
            return 0;
        }
        double yl = traectoriaR(g,X[zona1],X[zona-1],yi,V_x, V_y);
        //cout<<yl<<"   "<<zona1<<endl;
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
        //cout<<yr<<"   "<<zona<<endl;
        yi=yr;
        if (yi<0){
            cout<<zona-1<<endl;
            return 0;
        }
    }
}