#include <iostream>
#include <algorithm>
#include <cmath> // 使用 pow 函數來計算次方
#include <chrono> // 宣告 chrono 用於高解析度計時
#include <iomanip> // for setprecision
using namespace std;
using namespace chrono;

// Term 類別用來表示多項式的一項
class Term {
    friend class Polynomial; // 讓 Polynomial 類別可以訪問 Term 類別的私有成員
    friend ostream& operator<<(ostream& output, const Polynomial& p); // friend，用於輸出 Polynomial 類別
private:
    float coef; // 係數
    int exp;    // 指數
};

// Polynomial 類別用來表示多項式，包含多項式的操作
class Polynomial {
    friend istream& operator>>(istream& input, Polynomial& p); // friend，用於輸入 Polynomial 類別
    friend ostream& operator<<(ostream& output, const Polynomial& p); // friend，用於輸出 Polynomial 類別
public:
    // 預設建構子
    Polynomial() : termArray(nullptr), capacity(0), terms(0) {}

    // 帶容量的建構子
    Polynomial(int capacity) {
        this->capacity = capacity;
        terms = 0;
        termArray = new Term[capacity]; // 用來儲存多項式的項目
    }

    // 解構子
    ~Polynomial() {
    }

    // 多項式相加
    Polynomial Add(const Polynomial& poly) {
        Polynomial result(max(capacity, poly.capacity)); // 創建一個結果多項式
        int i = 0, j = 0;
        while (i < terms && j < poly.terms) { // 遍歷兩個多項式的項目
            if (termArray[i].exp == poly.termArray[j].exp) {
                float sumCoef = termArray[i].coef + poly.termArray[j].coef;
                if (sumCoef != 0) result.AddTerm(sumCoef, termArray[i].exp); // 若係數和不為 0，則加入結果
                i++;
                j++;
            }
            else if (termArray[i].exp > poly.termArray[j].exp) { // 若 p1 的指數較大
                result.AddTerm(termArray[i].coef, termArray[i].exp); // 將 p1 的項目加入結果
                i++;
            }
            else { // 若 p2 的指數較大
                result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp); // 將 p2 的項目加入結果
                j++;
            }
        }
        // 如果 p1 還有剩餘項目，加入結果
        while (i < terms) {
            result.AddTerm(termArray[i].coef, termArray[i].exp);
            i++;
        }
        // 如果 p2 還有剩餘項目，加入結果
        while (j < poly.terms) {
            result.AddTerm(poly.termArray[j].coef, poly.termArray[j].exp);
            j++;
        }
        return result; // 返回加法結果
    }

    // 多項式相乘
    Polynomial Mult(const Polynomial& poly) {
        Polynomial result(terms * poly.terms); // 創建一個結果多項式，容量為兩多項式項數的乘積
        for (int i = 0; i < terms; i++) { // 遍歷 p1 的每一項
            for (int j = 0; j < poly.terms; j++) { // 遍歷 p2 的每一項
                float newCoef = termArray[i].coef * poly.termArray[j].coef; // 係數相乘
                int newExp = termArray[i].exp + poly.termArray[j].exp; // 指數相加
                result.AddTermToResult(newCoef, newExp); // 加入結果多項式
            }
        }
        return result; // 返回乘法結果
    }

    // 計算多項式的值，傳入某個 x 的值
    double Eval(float f) {
        double result = 0.0;
        for (int i = 0; i < terms; i++) {
            result += termArray[i].coef * pow(f, termArray[i].exp); // 根據每項的係數與指數計算值
        }
        return result; // 返回計算結果
    }

private:
    Term* termArray; // 儲存多項式項目的陣列
    int capacity;    // 多項式項目的容量
    int terms;       // 當前有效的項數

    // 新增項目
    void AddTerm(float coef, int exp) {
        if (coef == 0) return; // 若係數為 0，不加入
        if (terms >= capacity) { // 若容量不足，擴展容量
            Copy(capacity * 2);
        }
        termArray[terms].coef = coef;
        termArray[terms].exp = exp;
        terms++; // 增加項數
    }

    // 擴展容量
    void Copy(int newCapacity) {
        Term* newArray = new Term[newCapacity]; // 創建新的陣列
        copy(termArray, termArray + terms, newArray); // 將原陣列的資料複製到新陣列
        delete[] termArray; // 釋放舊陣列的記憶體
        termArray = newArray; // 將新陣列賦值給 termArray
        capacity = newCapacity; // 更新容量
    }

    // 若多項式相乘時，發現有相同指數的項目，則更新項目
    void AddTermToResult(float coef, int exp) {
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef; // 若已有相同指數，更新係數
                return;
            }
        }
        AddTerm(coef, exp); // 若沒有相同指數的項目，則新增
    }
};

// 運算子 << 多載，用於將多項式輸出
ostream& operator<<(ostream& output, const Polynomial& p) {
    if (p.terms == 0) {
        output << "0"; // 若多項式無項目，輸出 0
        return output;
    }
    for (int i = 0; i < p.terms; i++) {
        if (i > 0 && p.termArray[i].coef > 0) output << " + "; // 若不是第一項且係數為正數，輸出加號
        output << p.termArray[i].coef;
        if (p.termArray[i].exp != 0) output << "x^" << p.termArray[i].exp; // 輸出指數
    }
    return output;
}

// 運算子 >> 多載，用於輸入多項式
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
            p.AddTerm(t_coef, 0); // 若為換行符，代表此項為常數
            break;
        }

        if (tmp == 'x') {
            input.get(tmp); // 讀取 '^' 或 '\n'
            if (tmp == '^') {
                input >> t_exp; // 讀取指數
            }
            else {
                t_exp = 1; // 若沒有 '^'，指數為 1
                if (tmp == '\n') break;
            }
        }
        else {
            t_exp = 0; // 若沒有 'x'，指數為 0
        }

        p.AddTerm(t_coef, t_exp); // 新增項目

        input.get(tmp); // 讀取下一個項目的分隔符號
        if (tmp == '\n') break; // 若為換行符，結束輸入
        else if (tmp == '-') isNegative = true; // 若為負號，處理下一項
    }
    return input;
}

int main() {
    Polynomial p1(10), p2(10); // 創建兩個多項式

    // 輸入多項式
    cout << "輸入第一個多項式 (格式：3x^2 -4x +5):";
    cin >> p1;
    cout << "輸入第二個多項式 (格式：2x^3 +x -7):";
    cin >> p2;

    //輸出多項式
    cout << "多項式 P1 = " << p1 << endl;
    cout << "多項式 P2 = " << p2 << endl;

    // 多項式相加
    auto start_add = high_resolution_clock::now();
    Polynomial sum = p1.Add(p2);
    cout << "P1 + P2 = " << sum << endl;
    auto end_add = high_resolution_clock::now();
    auto add_duration = duration_cast<nanoseconds>(end_add - start_add).count(); // 計時
    cout << "Add() 需時：" << add_duration / 1e6 << " ms" << endl; // 轉換為毫秒並輸出

// 多項式相乘
    auto start_mult = high_resolution_clock::now();
    Polynomial product = p1.Mult(p2);
    cout << "P1 * P2 = " << product << endl;
    auto end_mult = high_resolution_clock::now();
    auto mult_duration = duration_cast<nanoseconds>(end_mult - start_mult).count(); // 計時
    cout << "Mult() 需時：" << mult_duration / 1e6 << " ms" << endl; // 轉換為毫秒並輸出

    //計算多項式的值
    float x;
    cout << "輸入 x 的值來計算 P1(x): ";
    cin >> x;
    cout << "P1(x=" << x << ") 的值 = " << p1.Eval(x) << endl;
    return 0;
}
