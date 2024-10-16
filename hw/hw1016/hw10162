#include<iostream>
using namespace std;
int main() {
	int a[10000],time=0,buf;
	while (cin >> a[time])
	{
		buf = a[time];
		for (int i = 0; i <= time; i++)
		{
			if (a[i] >= buf)
			{
				for (int count = time + 1; count > i; count--)
				{
					a[count] = a[count - 1];
				}
				a[i] = buf;
				break;
			}
		}
		if (time % 2 == 0)
		{
			cout << a[time/2]<< endl;
		}
		else
		{
			cout << (a[time / 2] + a[time / 2 + 1]) / 2 << endl;
		}
		time++;
	}
	return 0;
}
