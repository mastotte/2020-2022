#include <iostream> //necessary for cout and cin
#include <iomanip> //necessary for setprecision
#include <cmath> //necessary for sqrt
using namespace std;
double PI = 3.14159;
double ONE_THIRD = 1.0/3.0;

int main()
{
    double radius = 0;
    double height = 0;
    double volume = 0;
    double surface_area = 0;
    //------------------------------------Input------------------------------------
    cout<<"Enter the radius of the cone: ";
    cin>>radius;
    
    cout<<"Enter the height of the cone: ";
    cin>>height;
    //---------------------------------Calculations--------------------------------
    volume = ONE_THIRD *PI*radius*radius*height;
    surface_area = PI*radius*(radius+sqrt(radius*radius+height*height));
    //-----------------------------------Output-----------------------------------
    cout<<"radius = "<<radius<<endl;
    cout<<"height = "<<height<<endl;
    cout<<"volume = "<<volume<<endl;
    cout<<"surface_area = "<<surface_area<<endl;
}
