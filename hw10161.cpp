#include<iostream>
#include<cstring>
using namespace std;
int main() {

    int n;
    char str[999] = { 0 };
    int count[91] = { 0 };
    int i, j;

    cin >> n;
    getchar();

    while (n--) {

        gets(str);

        for (i = 0; i < strlen(str); i++) {
            if (str[i] >= 'a' && str[i] <= 'z') {
                count[str[i] - 'a' + 'A']++;
            }
            else {
                count[str[i]]++;
            }
        }
    }

    for (i = sizeof(str); i >= 1; i--) {
        for (j = 'A'; j <= 'Z'; j++) {
            if (count[j] == i) {
                cout <<(char)j<< " " << i << endl;
            }
        }
    }

    return 0;
}