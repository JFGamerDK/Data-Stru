#include <iostream>
using namespace std;

// 定義多項式節點
struct Term 
{
    int coefficient;  // 係數
    int exponent;     // 指數
    Term* next;      // 指向下一項的指標
};

// 多項式類別
class Polynomial 
{
public:
    Term* head;  // 頭節點

    Polynomial()  // 建構子，初始化為空的多項式
	{
        head = nullptr;
    }
    ~Polynomial() // 解構子，釋放鏈表記憶體
	{
        Term* current = head;
        while (current != nullptr) 
		{
            Term* temp = current;
            current = current->next;
            delete temp;  // 釋放節點
        }
    }
    void input() // 輸入多項式
	{
        int coefficient, exponent;
        while (true) 
		{
            cin >> coefficient >> exponent;  // 讀取係數和指數
            if (exponent == 0 && coefficient == 0) break;  // 當指數和係數都為 0 時結束輸入
            insertTerm(coefficient, exponent);  // 插入該項
        }
    }
    void insertTerm(int coefficient, int exponent) // 插入項（根據指數排序）
	{
        Term* newTerm = new Term{coefficient, exponent, nullptr};  // 創建新節點
        if (head == nullptr || head->exponent < exponent) 
		{
            newTerm->next = head;
            head = newTerm;  // 插入到最前面
        } else {
            Term* current = head;
            while (current->next != nullptr && current->next->exponent > exponent) 
			{
                current = current->next;
            }
            if (current->next != nullptr && current->next->exponent == exponent) 
			{
                current->next->coefficient += coefficient;  // 若同次方，則合併係數
                delete newTerm;
            }
			else 
			{
                newTerm->next = current->next;
                current->next = newTerm;  // 插入到適當位置
            }
        }
    }
    void print() const // 打印多項式
	{
        Term* current = head;
        bool first = true;
        while (current != nullptr) 
		{
            if (!first && current->coefficient > 0) cout << "+";  // 輸出加號
            if (current->coefficient != 0) 
			{
                cout << current->coefficient;
                if (current->exponent > 0) cout << "X^" << current->exponent;  // 輸出指數
            }
            current = current->next;
            first = false;
        }
        cout << endl;
    }
    Polynomial operator+(const Polynomial& other) const // 多項式加法
	{
        Polynomial result;
        Term* current1 = head;
        Term* current2 = other.head;

        while (current1 != nullptr || current2 != nullptr) 
		{
            if (current1 == nullptr) 
			{
                result.insertTerm(current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
			else if (current2 == nullptr) 
			{
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            } 
			else if (current1->exponent > current2->exponent) 
			{
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            }
			else if (current1->exponent < current2->exponent) 
			{
                result.insertTerm(current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
			else 
			{
                int sumCoefficient = current1->coefficient + current2->coefficient;
                if (sumCoefficient != 0) 
				{
                    result.insertTerm(sumCoefficient, current1->exponent);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }

        return result;
    }
    Polynomial operator-(const Polynomial& other) const // 多項式減法
	{
        Polynomial result;
        Term* current1 = head;
        Term* current2 = other.head;

        while (current1 != nullptr || current2 != nullptr) 
		{
            if (current1 == nullptr) 
			{
                result.insertTerm(-current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
			else if (current2 == nullptr) 
			{
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            }
			else if (current1->exponent > current2->exponent) 
			{
                result.insertTerm(current1->coefficient, current1->exponent);
                current1 = current1->next;
            }
			else if (current1->exponent < current2->exponent) 
			{
                result.insertTerm(-current2->coefficient, current2->exponent);
                current2 = current2->next;
            }
			else 
			{
                int diffCoefficient = current1->coefficient - current2->coefficient;
                if (diffCoefficient != 0) 
				{
                    result.insertTerm(diffCoefficient, current1->exponent);
                }
                current1 = current1->next;
                current2 = current2->next;
            }
        }

        return result;
    }
    Polynomial operator*(const Polynomial& other) const // 多項式乘法
	{
        Polynomial result;
        Term* current1 = head;

        while (current1 != nullptr) 
		{
            Term* current2 = other.head;
            while (current2 != nullptr) 
			{
                result.insertTerm(current1->coefficient * current2->coefficient,
                                  current1->exponent + current2->exponent);
                current2 = current2->next;
            }
            current1 = current1->next;
        }

        return result;
    }
};

int main() 
{
    Polynomial poly1, poly2;  // 創建兩個多項式
    cout << "Enter first polynomial (coefficient and exponent, end with 0 0):" << endl;
    poly1.input();  // 輸入第一個多項式
    cout << "Enter second polynomial (coefficient and exponent, end with 0 0):" << endl;
    poly2.input();  // 輸入第二個多項式

    cout << "First Polynomial: ";
    poly1.print();  // 顯示第一個多項式

    cout << "Second Polynomial: ";
    poly2.print();  // 顯示第二個多項式

    // 多項式加法
    Polynomial sum = poly1 + poly2;
    cout << "Sum of polynomials: ";
    sum.print();  // 顯示加法結果

    // 多項式減法
    Polynomial diff = poly1 - poly2;
    cout << "Difference of polynomials: ";
    diff.print();  // 顯示減法結果

    // 多項式乘法
    Polynomial prod = poly1 * poly2;
    cout << "Product of polynomials: ";
    prod.print();  // 顯示乘法結果

    return 0;  // 程式結束
}

