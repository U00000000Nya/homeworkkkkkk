#include<iostream>
using  namespace std;
int ackermann(int m, int n)
{
	if (m == 0)
	{
		return n + 1;
	}
	else if (n == 0)
	{
		return ackermann(m - 1, 1);
	}
	else
	{
		return ackermann(m - 1, ackermann(m, n - 1));
	}
}
int main() {
	int m, n;
	cout << "M跟N中間請用空格隔開 #3 3"<<endl;
	cout << "請輸入M & N :";
	while (cin >> m >> n)
	{
		cout << "結果為 :" << ackermann(m, n)<<endl;
		cout << "請輸入M & N :";
	}
}
