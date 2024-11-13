#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

template <typename T>
int binary_search(T* arr, int n, T tofind) {
    int l = 0, r = n - 1, naka;

    while (l <= r) {
        naka = (l + r) / 2;
        if (arr[naka] < tofind) {
            l = naka + 1;
        }
        else if (arr[naka] > tofind) {
            r = naka - 1;
        }
        else {
            return naka;
        }
    }
    return -1;
}

class searchh {
public:
    searchh(char sornum = ' ', int inp=0, int numofs = 0);
    ~searchh() {};
    int serr();
    int sori();
    void set(char a, int i1, int i2);

private:
    char sornum;
    int inp;
    int numofs;
    int fg;
};

searchh::searchh(char sornum, int inp, int numofs)
{
    sornum = ' ';
    inp = 0;
    numofs = 0;
}

int searchh::serr() {
    if (fg == 1) {  
        int* arr;
        arr = new int[inp];
        for (int i = 0; i < inp; i++) {
            cin >> arr[i];
        }
        for (int i = 0; i < numofs; i++) {
            int wtof;
            cin >> wtof;
            cout << binary_search<int>(arr, inp, wtof) << endl;
        }
    }
    else {  
        string* arr;
        arr = new string[inp];
        for (int i = 0; i < inp; i++) {
            cin >> arr[i];
        }
        
        for (int i = 0; i < numofs; i++) {
            string wtof;
            cin >> wtof;
            cout << binary_search<string>(arr, inp, wtof) << endl;
        }
    }
    return 0;
}

int searchh::sori() {
    if (sornum == 'i') {
        fg = 1; 
    }
    else {
        fg = 0; 
    }
    return 0;
}

void searchh::set(char a, int i1, int i2) {
    sornum = a;
    inp = i1;
    numofs = i2;
    sori();
}

int main() {
    searchh sss;
    char a;
    int seti, sete;
    cin >> a >> seti >> sete;
    sss.set(a, seti, sete);
    sss.serr();
    return 0;
}
