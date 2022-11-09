#include <iostream>

using namespace std;

#include <iostream>
#include <math.h>
using namespace std;
int factorial(int num){
    int f = 1;
    for(int i = 1; i <= num; i++){
        f = f*i;
    }
    return f;
}
void permute(string &a, int l, int r, int* count,int f, int size)
{
    // Base case
    
    if (l == r){
        *count = *count + 1;
        if(*count%f == 0){
            for(int i = 0; i < size; i++){
                cout<<a[i];
            }
            cout<<endl;
        }
    }
    
        
    else
    {
        
        // Permutations made
        for (int i = l; i <= r; i++)
        {
            
 
            // Swapping done
            swap(a[l], a[i]);
 
            // Recursion called
            permute(a, l+1, r, count, f, size);
 
            //backtrack
            swap(a[l], a[i]);
        }
        
    }
}
 
// Driver Code
int main()
{
    string str = "ABCD";
    int count = 0;
    int n = str.size();
    int size = 3;
    int f = 1;
    cout<<"start"<<endl;
    for(int i = 0; i < size; i++){
        f = factorial(size-i);
        cout<<f<<endl;
        permute(str, 0, n-1,&count,f,i+1);
    }
    string str = "ABC";
    int count = 0;
    int n = str.size();
    int size = 3;
    int f = 1;
    cout<<"start"<<endl;
    string b = "";
    string c = "";
    //permute(str, 0, n-1);
    for(int j = 0; j < pow(2,size); j++){
        b = bitset<3>(j).to_string();
        c = str;
        for(int i = size; i >= 0; i--){
            if(b[i] == 0){
                c.insert(i,"a");
            }
        }
        cout<<c<<endl;
        c = str;
    }
    
    return 0;
}
