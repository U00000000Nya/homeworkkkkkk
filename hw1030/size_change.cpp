#include<iostream>
using namespace std;
void size_change_size(int *&arr,int size,int new_size) {
	int* new_arr = new int[new_size];
	int* recycler = arr;
	copy(arr, arr + size, new_arr);
	//把新增的初始化為0
	for (int i = size; i < new_size; i++) {
		new_arr[i] = 0;
	}
	delete[] recycler; //把舊的蛋雕
	arr = new_arr;
}

void print_arr(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int size; //輸入一開始的大小
	cout << "enter size:"; 
	cin>>size;
	int *arr = new int[size]; //新增陣列
	
	for (int i = 0; i < size; i++) { //存入數字
		arr[i] = i + 1;
	} 
	
	cout << "初始:";
	print_arr(arr, size); //輸出出來
	int newsize=size*2;
	cout << "after extra:";
	size_change_size(arr, size, newsize);
	print_arr(arr, newsize);
}
