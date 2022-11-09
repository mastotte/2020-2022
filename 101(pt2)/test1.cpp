#include <iostream>
#include <math.h>
using namespace std;

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
    int size = 2;
    int f = 1;
    cout<<"start"<<endl;
    for(int i = 1; i <= size; i++){
        f = f*i;
    }
    cout<<f<<endl;
    permute(str, 0, n-1,&count,f,size);
    return 0;
}
