#include <iostream>
#include <cmath>

using namespace std;

// 節點結構
struct Node {
    int coef;  // 系數
    int exp;   // 指數
    Node* next; // 下一個節點

    Node(int c = 0, int e = 0, Node* n = nullptr) : coef(c), exp(e), next(n) {}
};

// Polynomial 類
class Polynomial {
private:
    Node* head; // 環形鏈表的頭結點

    void Clear() { // 清除多項式節點
        Node* temp = head->next;
        while (temp != head) {
            Node* del = temp;
            temp = temp->next;
            delete del;
        }
        head->next = head; // 恢復環形結構
    }

public:
    // 構造函數
    Polynomial() {
        head = new Node(); // 頭結點
        head->next = head;
    }

    // 拷貝構造函數
    Polynomial(const Polynomial& a) : Polynomial() {
        Node* temp = a.head->next;
        while (temp != a.head) {
            Insert(temp->coef, temp->exp);
            temp = temp->next;
        }
    }

    // 析構函數
    ~Polynomial() {
        Clear();
        delete head;
    }

    // 插入節點
    void Insert(int coef, int exp) {
        Node* prev = head;
        Node* curr = head->next;
        while (curr != head && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }

        if (curr != head && curr->exp == exp) {
            curr->coef += coef; // 合併同類項
            if (curr->coef == 0) { // 如果系數為0，刪除節點
                prev->next = curr->next;
                delete curr;
            }
        } else {
            Node* newNode = new Node(coef, exp, curr);
            prev->next = newNode;
        }
    }

    // 賦值運算符重載
    Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this; // 避免自我賦值
        Clear();
        Node* temp = a.head->next;
        while (temp != a.head) {
            Insert(temp->coef, temp->exp);
            temp = temp->next;
        }
        return *this;
    }

    // 輸入運算符重載
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n, coef, exp;
        is >> n;
        for (int i = 0; i < n; ++i) {
            is >> coef >> exp;
            x.Insert(coef, exp);
        }
        return is;
    }

    // 輸出運算符重載
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* temp = x.head->next;
        bool first = true;
        while (temp != x.head) {
            if (!first && temp->coef > 0) os << " + ";
            if (temp->exp == 0) os << temp->coef;
            else if (temp->exp == 1) os << temp->coef << "x";
            else os << temp->coef << "x^" << temp->exp;
            first = false;
            temp = temp->next;
        }
        return os;
    }

    // 多項式加法
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* tempA = head->next;
        Node* tempB = b.head->next;
        while (tempA != head || tempB != b.head) {
            if (tempA != head && (tempB == b.head || tempA->exp > tempB->exp)) {
                result.Insert(tempA->coef, tempA->exp);
                tempA = tempA->next;
            } else if (tempB != b.head && (tempA == head || tempB->exp > tempA->exp)) {
                result.Insert(tempB->coef, tempB->exp);
                tempB = tempB->next;
            } else {
                result.Insert(tempA->coef + tempB->coef, tempA->exp);
                tempA = tempA->next;
                tempB = tempB->next;
            }
        }
        return result;
    }

    // 多項式減法
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Node* tempB = b.head->next;
        while (tempB != b.head) {
            result.Insert(-tempB->coef, tempB->exp);
            tempB = tempB->next;
        }
        return *this + result;
    }

    // 多項式乘法
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;

        // 遍歷 this 的每一項
        Node* tempA = head->next;
        while (tempA != head) {
            Node* tempB = b.head->next;
            // 遍歷 b 的每一項
            while (tempB != b.head) {
                int newCoef = tempA->coef * tempB->coef;
                int newExp = tempA->exp + tempB->exp;
                result.Insert(newCoef, newExp); // 插入結果多項式
                tempB = tempB->next;
            }
            tempA = tempA->next;
        }

        return result;
    }

    // 評估多項式
    float Evaluate(float x) const {
        float result = 0;
        Node* temp = head->next;
        while (temp != head) {
            result += temp->coef * pow(x, temp->exp);
            temp = temp->next;
        }
        return result;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "Enter polynomial 1 (format: n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "Enter polynomial 2 (format: n c1 e1 c2 e2 ...): ";
    cin >> p2;

    cout << "Polynomial 1: " << p1 << endl;
    cout << "Polynomial 2: " << p2 << endl;

    // 測試加法
    Polynomial sum = p1 + p2;
    cout << "Sum: " << sum << endl;

    // 測試減法
    Polynomial diff = p1 - p2;
    cout << "Difference: " << diff << endl;

    // 測試乘法
    Polynomial product = p1 * p2;
    cout << "Product: " << product << endl;

    // 測試評估
    float x;
    cout << "Enter a value to evaluate polynomial 1: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
