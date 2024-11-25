#include <iostream>
using namespace std;

// �w�q�h�����`�I
struct Term 
{
    int coefficient;  // �Y��
    int exponent;     // ����
    Term* next;      // ���V�U�@��������
};

// �h�������O
class Polynomial 
{
public:
    Term* head;  // �Y�`�I

    Polynomial()  // �غc�l�A��l�Ƭ��Ū��h����
	{
        head = nullptr;
    }
    ~Polynomial() // �Ѻc�l�A�������O����
	{
        Term* current = head;
        while (current != nullptr) 
		{
            Term* temp = current;
            current = current->next;
            delete temp;  // ����`�I
        }
    }
    void input() // ��J�h����
	{
        int coefficient, exponent;
        while (true) 
		{
            cin >> coefficient >> exponent;  // Ū���Y�ƩM����
            if (exponent == 0 && coefficient == 0) break;  // ����ƩM�Y�Ƴ��� 0 �ɵ�����J
            insertTerm(coefficient, exponent);  // ���J�Ӷ�
        }
    }
    void insertTerm(int coefficient, int exponent) // ���J���]�ھګ��ƱƧǡ^
	{
        Term* newTerm = new Term{coefficient, exponent, nullptr};  // �Ыطs�`�I
        if (head == nullptr || head->exponent < exponent) 
		{
            newTerm->next = head;
            head = newTerm;  // ���J��̫e��
        } else {
            Term* current = head;
            while (current->next != nullptr && current->next->exponent > exponent) 
			{
                current = current->next;
            }
            if (current->next != nullptr && current->next->exponent == exponent) 
			{
                current->next->coefficient += coefficient;  // �Y�P����A�h�X�֫Y��
                delete newTerm;
            }
			else 
			{
                newTerm->next = current->next;
                current->next = newTerm;  // ���J��A���m
            }
        }
    }
    void print() const // ���L�h����
	{
        Term* current = head;
        bool first = true;
        while (current != nullptr) 
		{
            if (!first && current->coefficient > 0) cout << "+";  // ��X�[��
            if (current->coefficient != 0) 
			{
                cout << current->coefficient;
                if (current->exponent > 0) cout << "X^" << current->exponent;  // ��X����
            }
            current = current->next;
            first = false;
        }
        cout << endl;
    }
    Polynomial operator+(const Polynomial& other) const // �h�����[�k
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
    Polynomial operator-(const Polynomial& other) const // �h������k
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
    Polynomial operator*(const Polynomial& other) const // �h�������k
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
    Polynomial poly1, poly2;  // �Ыب�Ӧh����
    cout << "Enter first polynomial (coefficient and exponent, end with 0 0):" << endl;
    poly1.input();  // ��J�Ĥ@�Ӧh����
    cout << "Enter second polynomial (coefficient and exponent, end with 0 0):" << endl;
    poly2.input();  // ��J�ĤG�Ӧh����

    cout << "First Polynomial: ";
    poly1.print();  // ��ܲĤ@�Ӧh����

    cout << "Second Polynomial: ";
    poly2.print();  // ��ܲĤG�Ӧh����

    // �h�����[�k
    Polynomial sum = poly1 + poly2;
    cout << "Sum of polynomials: ";
    sum.print();  // ��ܥ[�k���G

    // �h������k
    Polynomial diff = poly1 - poly2;
    cout << "Difference of polynomials: ";
    diff.print();  // ��ܴ�k���G

    // �h�������k
    Polynomial prod = poly1 * poly2;
    cout << "Product of polynomials: ";
    prod.print();  // ��ܭ��k���G

    return 0;  // �{������
}

