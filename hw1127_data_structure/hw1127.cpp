#include <iostream>
#include <algorithm>
#include <cmath> // pow
using namespace std;

class Term {
    friend class Polynomial; // Polynomial 可存取 Term 的私有成員
private:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
public:
    // 建構子
    Polynomial() : termArray(nullptr), capacity(0), terms(0) {}

    Polynomial(int capacity) {
        this->capacity = capacity;
        terms = 0;
        termArray = new Term[capacity];
    }

    ~Polynomial() {
        
    }

    // 輸入多項式
    void Input() {
        cout << "輸入多項式(格式:3x^2 4x 5,每項用空格分隔，結束輸入按 Enter):";
        while (true) {
            float coef;
            int exp;
            char variable, caret;
            cin >> coef;
            if (cin.peek() == '\n' || !cin) {
                AddTerm(coef, 0);
                break;
            }
            cin >> variable; // 讀取 'x'
            if (variable == 'x') {
                if (cin.peek() == '^') {
                    cin >> caret >> exp; // 讀取 '^' 和指數
                }
                else {
                    exp = 1; // 如果沒有 ^，預設指數為 1
                }
            }
            else {
                exp = 0; // 如果沒有 x，指數為 0
            }
            AddTerm(coef, exp);
            if (cin.peek() == '\n') break; // 如果換行符則結束
        }
    }

    // 多項式相加
    Polynomial Add(Polynomial poly) {
        Polynomial result(max(capacity, poly.capacity));
        int i = 0, j = 0;
        while (i < terms && j < poly.terms) {
            if (termArray[i].exp == poly.termArray[j].exp) {
                float sumCoef = termArray[i].coef + poly.termArray[j].coef;
                if (sumCoef != 0) result.AddTerm(sumCoef, termArray[i].exp);
                i++;
                j++;
            }
            else if (termArray[i].exp > poly.termArray[j].exp) {
                result.AddTerm(termArray[i].coef, termArray[i].exp);
                i++;
            }
            else {
                result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
                j++;
            }
        }
        while (i < terms) {
            result.AddTerm(termArray[i].coef, termArray[i].exp);
            i++;
        }
        while (j < poly.terms) {
            result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
        return result;
    }

    // 多項式相乘
    Polynomial Mult(Polynomial poly) {
        Polynomial result(terms * poly.terms);
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < poly.terms; j++) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                result.AddTermToResult(newCoef, newExp);
            }
        }
        return result;
    }

    // 計算多項式的值
    double Eval(float f) {
        double result = 0.0;
        for (int i = 0; i < terms; i++) {
            result += termArray[i].coef * pow(f, termArray[i].exp);
        }
        return result;
    }

    // 輸出多項式
    void Print() const {
        if (terms == 0) {
            cout << "0" << endl;
            return;
        }
        for (int i = 0; i < terms; i++) {
            if (i > 0 && termArray[i].coef > 0) cout << " + ";
            cout << termArray[i].coef;
            if (termArray[i].exp != 0) cout << "x^" << termArray[i].exp;
        }
        cout << endl;
    }

private:
    Term* termArray;
    int capacity;
    int terms;

    // 新增項目
    void AddTerm(float coef, int exp) {
        if (coef == 0) return;
        if (terms >= capacity) {
            Copy(capacity * 2);
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        terms++;
    }

    // 複製陣列並調整容量
    void Copy(int newCapacity) {
        Term* newArray = new Term[newCapacity];
        copy(termArray, termArray + terms, newArray);
        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }

    // 新增項目到結果多項式
    void AddTermToResult(float coef, int exp) {
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;
                return;
            }
        }
        AddTerm(coef, exp);
    }
};

int main() {
    Polynomial p1(10), p2(10);

    // 輸入第一個多項式
    cout << "第一個多項式" << endl;
    p1.Input();

    // 輸入第二個多項式
    cout << "第二個多項式" << endl;
    p2.Input();

    cout << "多項式 P1 = ";
    p1.Print();

    cout << "多項式 P2 = ";
    p2.Print();

    // 多項式相加
    Polynomial sum = p1.Add(p2);
    cout << "P1 + P2 = ";
    sum.Print();

    // 多項式相乘
    Polynomial product = p1.Mult(p2);
    cout << "P1 * P2 = ";
    product.Print();

    // 計算多項式值
    float x;
    cout << "輸入 x 的值來計算 P1(x): ";
    cin >> x;
    cout << "P1(X=" << x << ") 的值 = " << p1.Eval(x) << endl;

    return 0;
}
