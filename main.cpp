#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

float scalar(float x1,float y1, float x2, float y2)
{
    return x1*x2+y1*y2;
}

float modyl(float x1,float y1, float x2, float y2)
{
    return sqrt(x1*x1+y1*y1) * sqrt(x2*x2+y2*y2);
}

int main() {
    string path = "F:\\C++\\HomeWork2\\toch.txt";

    ifstream F;
    F.open(path);

    if (!F.is_open()) {
        cout << "Oshibka" << endl;
    } else {
        cout << "Net oshibki" << endl;
        string str;
        while (!F.eof()) {
            str = "";
            getline(F, str);
            //cout << str << endl;

        }
    }
    F.close();

    float X[2];
    float Y[2];

    X[1] = -2;
    Y[1] = 1;
    X[2] = 2;
    Y[2] = -1;

    float xn = 1;
    float yn = 1;

    float mleftmin = 1;
    float mrightmin = 1;
    int nleft,nright;

    //Для углов
    for (int i = 1; i <= sizeof(X)/4; ++i)
    {
        if (X[i] < Y[i])
        {
            float m1 = scalar(xn, yn, X[i], Y[i]) / modyl(xn, yn, X[i], Y[i]);
            if (m1 < mleftmin)
            {
                mleftmin = m1;
                nleft = i;
            }
        }
        else
         {
             float m1 = scalar(xn, yn, X[i], Y[i]) / modyl(xn, yn, X[i], Y[i]);
             if (m1 < mrightmin)
             {
                mrightmin = m1;
                nright = i;
            }
        }
    }

    cout<<"Leftangle: "<<X[nleft]<<" "<<Y[nleft]<<endl;
    cout<<"Rightangle:  "<<X[nright]<<" "<<Y[nright]<<endl;


    float Rleftmin = 0;
    float Rrightmin = 0;

    //Для расстояний
    for (int i = 1; i <= sizeof(X)/4; ++i)
    {
        if (X[i] < Y[i])
        {
            float m1 = modyl(xn, yn, X[i], Y[i]);
            if (m1 < Rleftmin)
            {
                Rleftmin = m1;
                nleft = i;
            }
        }
        else
        {
            float m1 = modyl(xn, yn, X[i], Y[i]);
            if (m1 > Rrightmin)
            {
                Rrightmin = m1;
                nright = i;
            }
        }
    }

    cout<<"LeftR: "<<X[nleft]<<" "<<Y[nleft]<<endl;
    cout<<"RightR:  "<<X[nright]<<" "<<Y[nright]<<endl;
    return 0;

}
