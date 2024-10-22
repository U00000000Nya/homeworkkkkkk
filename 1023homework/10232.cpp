#include<iostream>
using namespace std;
void powerset(int numbernow,int size)
{
    if (numbernow < 0) { //判斷是否結束
        return; 
    }
    for (int i = size - 1; i >= 0; --i) {
        if (numbernow & (1 << i)) { //判斷i推過去的位元是否為1
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
        total*=2; //算出總共有幾個結果
    }
    powerset(total-1,size);
}  
