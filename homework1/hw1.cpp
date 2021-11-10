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
            Xcell.push_back(stoi(arr[i]));
        }
        else {
            Ycell.push_back(stoi(arr[i]));
        }
    }
    return (type == "X") ? Xcell : Ycell;
}

float scalar(float x1,float y1, float x2, float y2)
{
    return x1*x2+y1*y2;
}

double modyl(double x1,double y1,double x2, double y2)
{
    return sqrt(x1*x1+y1*y1) * sqrt(x2*x2+y2*y2);
}

int main() {
    vector<string> points = readFile();
    vector<double> vectorX = divider(points, "X");
    vector<double> vectorY = divider(points, "Y");

    float mleftmin = 1;
    float mrightmin = 1;
    int nleft, nright;

    int a = vectorX.size();
    double X[a];
    double Y[a];

    for (int i=0; i<a; i++)
    {
        double *c = &vectorX[i];
        double h = *c;
        X[i] = h;
        double *c1 = &vectorY[i];
        double h1 = *c1;
        Y[i] = h1;
        //cout<<X[i]<<"   "<<Y[i]<<endl;
    }


    //Для углов
    for (int i = 1; i < sizeof(X)/8; ++i)
    {
        if (X[0]==0)
        {
            if (X[i]<0)
            {
                double m1 = scalar(X[0], Y[0], X[i], Y[i]) / modyl(X[0], Y[0], X[i], Y[i]);
                if (m1 > Y[i])
                {
                    m1 = X[i];
                    nleft = i;
                }
            }
            else
            {
                float m1 = scalar(X[0], Y[0], X[i], X[i]) / modyl(X[0], Y[0], X[i], Y[i]);
                if (m1 > X[i])
                {
                    m1 = X[i];
                    nright = i;
                }
            }
        }
        else
        {
            if (X[i] * Y[0] /X[0] < Y[i]) {
                float m1 = scalar(X[0],X[0], X[i], X[i]) / modyl(X[0], Y[0], X[i], Y[i]);
                if (m1 <= mleftmin)
                {
                    mleftmin = m1;
                    nleft = i;
                }
            } else {
                float m1 = scalar(X[0], Y[0], X[i], Y[i]) / modyl(X[0], Y[0], X[i], Y[i]);
                if (m1 <= mrightmin) {
                    mrightmin = m1;
                    nright = i;
                }
            }
        }
    }

    cout<<"Leftmost: "<<X[nleft]<<" "<<Y[nleft]<<endl;
    cout<<"Rightmost: "<<X[nright]<<" "<<Y[nright]<<endl;


}
