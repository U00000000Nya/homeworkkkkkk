#include<iostream>
using namespace std;
void powerset(int numbernow,int size)
{
    if (numbernow < 0) {
        return; 
    }
    for (int i = size - 1; i >= 0; --i) {
        if (numbernow & (1 << i)) { 
            cout << (char)('A' + i) << " "; 
        }
        else{
            cout<<"  ";
        }
    }
    cout << endl;
    powerset(numbernow - 1, size);
}
int main()
{
    int size,total=1;
    cout<<"請輸入大小 :";
    cin>>size;
    for(int time=0;time<size;time++)
    {
        total*=2;
    }
    powerset(total-1,size);
}  
