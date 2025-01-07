#include <iostream>
#include <sstream>
#include <cmath>
#include <chrono> // 用於計時
using namespace std;

// 節點結構
struct Node {
    int coef; // 係數
    int exp;  // 指數
    Node* next; // 下一個節點

    Node(int c, int e, Node* n = nullptr) : coef(c), exp(e), next(n) {}
};

class Polynomial {
private:
    Node* head; // 表頭節點

    // 添加節點到鏈結表中（依次數排序）
    void addNode(int coef, int exp) {
        if (coef == 0) return;
        Node* prev = head;
        Node* curr = head->next;

        while (curr != head && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != head && curr->exp == exp) {
            curr->coef += coef;
            if (curr->coef == 0) {
                prev->next = curr->next;
                delete curr;
            }
        }
        else {
            Node* newNode = new Node(coef, exp, curr);
            prev->next = newNode;
        }
    }

public:
    // 建構函數
    Polynomial() {
        head = new Node(0, 0); // 表頭節點
        head->next = head;
    }

    // 解構函數
    ~Polynomial() {
        Node* curr = head->next;
        while (curr != head) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        delete head;
    }

    // 輸入多項式 (istream 操作符)
    friend istream& operator>>(istream& in, Polynomial& poly) {
        poly.~Polynomial();
        poly.head = new Node(0, 0);
        poly.head->next = poly.head;

        string input;
        in >> input;

        stringstream ss(input);
        char op = '+'; // 預設操作符為 +
        int coef = 0, exp = 0;

        while (ss) {
            coef = 0;
            exp = 0;
            if (ss.peek() == '+' || ss.peek() == '-') {
                op = ss.get();
            }

            ss >> coef;
            if (ss.peek() == 'x') {
                ss.ignore();
                if (ss.peek() == '^') {
                    ss.ignore();
                    ss >> exp;
                }
                else {
                    exp = 1;
                }
            }

            if (op == '-') coef = -coef;
            poly.addNode(coef, exp);
        }
        return in;
    }

    // 輸出多項式 (ostream 操作符)
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        Node* curr = poly.head->next;
        bool first = true;

        while (curr != poly.head) {
            if (!first && curr->coef > 0) out << "+";
            out << curr->coef;
            if (curr->exp > 0) {
                out << "x";
                if (curr->exp > 1) out << "^" << curr->exp;
            }
            first = false;
            curr = curr->next;
        }

        if (first) out << "0"; // 若多項式為空，輸出 0
        return out;
    }

    // 複製建構函數
    Polynomial(const Polynomial& other) {
        head = new Node(0, 0);
        head->next = head;
        Node* curr = other.head->next;
        while (curr != other.head) {
            addNode(curr->coef, curr->exp);
            curr = curr->next;
        }
    }

    // 賦值運算符
    Polynomial& operator=(const Polynomial& other) {
        if (this == &other) return *this;

        // 清空現有多項式
        Node* curr = head->next;
        while (curr != head) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head->next = head;

        // 複製新多項式
        curr = other.head->next;
        while (curr != other.head) {
            addNode(curr->coef, curr->exp);
            curr = curr->next;
        }
        return *this;
    }

    // 加法運算
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        Node* curr = head->next;
        while (curr != head) {
            result.addNode(curr->coef, curr->exp);
            curr = curr->next;
        }
        curr = other.head->next;
        while (curr != other.head) {
            result.addNode(curr->coef, curr->exp);
            curr = curr->next;
        }
        return result;
    }

    // 減法運算
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        Node* curr = head->next;
        while (curr != head) {
            result.addNode(curr->coef, curr->exp);
            curr = curr->next;
        }
        curr = other.head->next;
        while (curr != other.head) {
            result.addNode(-curr->coef, curr->exp);
            curr = curr->next;
        }
        return result;
    }

    // 乘法運算
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;
        Node* curr1 = head->next;
        while (curr1 != head) {
            Node* curr2 = other.head->next;
            while (curr2 != other.head) {
                result.addNode(curr1->coef * curr2->coef, curr1->exp + curr2->exp);
                curr2 = curr2->next;
            }
            curr1 = curr1->next;
        }
        return result;
    }

    // 計算多項式在 x 點的值
    float Evaluate(float x) const {
        float result = 0;
        Node* curr = head->next;
        while (curr != head) {
            result += curr->coef * pow(x, curr->exp);
            curr = curr->next;
        }
        return result;
    }
};

int main() {
    Polynomial a, b;

    // 輸入多項式 A
    cout << "Enter Polynomial A (e.g., 2x^2+2x-2): ";
    cin >> a;
    cout << "A: " << a << endl;

    // 輸入多項式 B
    cout << "Enter Polynomial B (e.g., 3x^3+x-5): ";
    cin >> b;
    cout << "B: " << b << endl;
    cout << endl;
    // 測試加法
    auto start = chrono::high_resolution_clock::now();
    Polynomial sum = a + b;
    auto end = chrono::high_resolution_clock::now();
    cout << "A + B: " << sum << endl;
    cout << "Addition took: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;
    cout << endl;
    // 測試減法
    start = chrono::high_resolution_clock::now();
    Polynomial diff = a - b;
    end = chrono::high_resolution_clock::now();
    cout << "A - B: " << diff << endl;
    cout << "Subtraction took: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;
    cout << endl;
    // 測試乘法
    start = chrono::high_resolution_clock::now();
    Polynomial prod = a * b;
    end = chrono::high_resolution_clock::now();
    cout << "A * B: " << prod << endl;
    cout << "Multiplication took: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    // 測試多項式的值
    float x;
    cout << "Enter a value for x to evaluate Polynomial A: ";
    cin >> x;
    start = chrono::high_resolution_clock::now();
    cout << "A(" << x << "): " << a.Evaluate(x) << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Evaluation of A took: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    cout << "Enter a value for x to evaluate Polynomial B: ";
    cin >> x;
    start = chrono::high_resolution_clock::now();
    cout << "B(" << x << "): " << b.Evaluate(x) << endl;
    end = chrono::high_resolution_clock::now();
    cout << "Evaluation of B took: " << chrono::duration<double, milli>(end - start).count() << " ms" << endl;

    return 0;
}
