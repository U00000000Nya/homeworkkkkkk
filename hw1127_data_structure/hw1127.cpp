#include <iostream>
#include <algorithm>
#include <cmath> // pow
using namespace std;

class Term {
    friend class Polynomial; // Polynomial 可存取 Term 的私有成員
    friend ostream& operator<<(ostream& output, const Polynomial& p);
private:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
    friend istream& operator>>(istream& input, Polynomial& p);
    friend ostream& operator<<(ostream& output, const Polynomial& p);
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

    // 多項式相加
    Polynomial Add(const Polynomial& poly) {
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
    Polynomial Mult(const Polynomial& poly) {
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
private:
    Term* termArray; // 儲存多項式的項目
    int capacity;    // 容量
    int terms;       // 當前項數

    void AddTerm(float coef, int exp) {
        if (coef == 0) return;
        if (terms >= capacity) {
            Copy(capacity * 2);
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        terms++;
    }

    void Copy(int newCapacity) {
        Term* newArray = new Term[newCapacity];
        copy(termArray, termArray + terms, newArray);
        delete[] termArray;
        termArray = newArray;
        capacity = newCapacity;
    }

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
ostream& operator<<(ostream& output, const Polynomial& p) {
    if (p.terms == 0) {
        output << "0";
        return output;
    }
    for (int i = 0; i < p.terms; i++) {
        if (i > 0 && p.termArray[i].coef > 0) output << " + ";
        output << p.termArray[i].coef;
        if (p.termArray[i].exp != 0) output << "x^" << p.termArray[i].exp;
    }
    return output;
}
istream& operator>>(istream& input, Polynomial& p) {
    float t_coef;
    int t_exp;
    char tmp;
    bool isNegative = false;

    while (true) {
        input >> t_coef; // 讀入係數
        if (isNegative) {
            t_coef *= -1; // 處理負號
            isNegative = false;
        }

        input.get(tmp); // 讀取下一個字元，可能是 'x' 或 '\n'
        if (tmp == '\n') {
            p.AddTerm(t_coef, 0); // 如果是 '\n'，代表是常數
            break;
        }

        if (tmp == 'x') {
            input.get(tmp); // 讀取 '^' 或 '\n'
            if (tmp == '^') {
                input >> t_exp; // 讀取指數
            }
            else {
                t_exp = 1; // 預設指數為 1
                if (tmp == '\n') break;
            }
        }
        else {
            t_exp = 0; // 沒有 'x'，指數為 0
        }

        p.AddTerm(t_coef, t_exp); // 新增項目

        input.get(tmp); // 讀取下一個項目的分隔符號
        if (tmp == '\n') break; // 若為換行符，結束輸入
        else if (tmp == '-') isNegative = true; // 若為負號，處理下一項目
    }
    return input;
}
int main() {
    Polynomial p1(10), p2(10);

    // 輸入多項式
    cout << "輸入第一個多項式 (格式：3x^2 -4x +5):";
    cin >> p1;
    cout << "輸入第二個多項式 (格式：2x^3 +x -7):";
    cin >> p2;

    // 輸出多項式
    cout << "多項式 P1 = " << p1 << endl;
    cout << "多項式 P2 = " << p2 << endl;

    // 多項式相加
    Polynomial sum = p1.Add(p2);
    cout << "P1 + P2 = " << sum << endl;

    // 多項式相乘
    Polynomial product = p1.Mult(p2);
    cout << "P1 * P2 = " << product << endl;

    // 計算多項式值
    float x;
    cout << "輸入 x 的值來計算 P1(x): ";
    cin >> x;
    cout << "P1(x=" << x << ") 的值 = " << p1.Eval(x) << endl;

    return 0;
}
