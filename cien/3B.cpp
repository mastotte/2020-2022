// Online C++ compiler to run C++ program online
#include <iostream> //necessary for cout and cin
#include <iomanip> //necessary for setprecision
#include <cmath> //necessary for sqrt and pow
#include <cstdlib> //necessary for random numbers
#include <ctime> //necessary for the clock to seed the random numbers
using namespace std;
int LOW = 1;
int HIGH = 100;
int main() {    
    double base = 0;
    double id_square = 0;
    double base_to_power = 0;
    int id_number,exponent,ascii_code,random_number,name_length = 0;
    char letter = ' ';
    string consume_newline = "";
    string full_name;
    //------------------------------------Input------------------------------------
    cout<<"Enter your ID number"<<endl;
    cin>>id_number;
    cout<<"Enter your full name"<<endl;
    cin.ignore();
    getline(cin,full_name);
    cout<<full_name<<endl;
    return 0;
}
