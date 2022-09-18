#include <iostream>
#include <cmath>
#include <cstdint>
#include <cassert>

using namespace std;

//1=============================================================================================

class Power
{
private:
    float first{0};
    float second{0};
public:
    void SetValue(float first, float second) { this->first = first; this->second = second; };
    void Calculate() { cout << pow(this->first,this->second) << endl; };
};

//2==============================================================================================

class RGBA
{
private:
    uint8_t m_red { 0 };
    uint8_t m_green { 0 };
    uint8_t m_blue { 0 };
    uint8_t m_alpha { 0 };
public:
    RGBA()
    {
        uint8_t r; uint8_t g; uint8_t b; uint8_t a;
        cout << "Enter R,G,B,A: " << endl;
        cin >> r; cin >> g; cin >> b; cin >> a;
        this->m_red = r; this->m_green = g; this->m_blue = b; this->m_alpha = a;
    }
    void print()
    {
        cout << "Red: " << this->m_red << " Green: " << this->m_green
             << " Blue: " << this->m_blue << " Aplha: " << this->m_alpha << endl;
    }
};


//3==============================================================================================

class Stack
{
private:
    int arr[10];
    int len ;
public:
    void reset()
    {
        len = 0;
        for (int i = 0; i < 10; ++i)
            arr[i] = 0;
    }

    bool push(int value)
    {
        if (len == 10)
            return false;

        arr[len++] = value; 
        return true;
    }

    int pop()
    {
        
        assert(len > 0);

       return arr[--len];
    }

    void print()
    {
        cout << "( ";
        for (int i = 0; i < len; ++i)
            cout << arr[i] << ' ';
        cout << ")\n";
    }

};

int main()
{
    //1
    Power my1; my1.SetValue(3.15, 4.5); my1.Calculate(); cout << endl;
    //2
    RGBA my2; my2.print(); cout << endl;
    //3
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

}


/*1. Создать класс Power, который содержит два вещественных числа.Этот класс должен иметь
две переменные - члена для хранения этих вещественных чисел.Еще создать два метода :
один с именем set, который позволит присваивать значения переменным, второй — calculate,
который будет выводить результат возведения первого числа в степень второго числа.Задать
значения этих двух чисел по умолчанию.
2. Написать класс с именем RGBA, который содержит 4 переменные - члена типа std::uint8_t :
    m_red, m_green, m_blue и m_alpha(#include cstdint для доступа к этому типу).Задать 0 в
    качестве значения по умолчанию для m_red, m_green, m_blue и 255 для m_alpha.Создать
    конструктор со списком инициализации членов, который позволит пользователю передавать
    значения для m_red, m_blue, m_green и m_alpha.Написать функцию print(), которая будет
    выводить значения переменных - членов.
    © geekbrains.ru 15
    3. Написать класс, который реализует функциональность стека.Класс Stack должен иметь :
● private - массив целых чисел длиной 10;
● private целочисленное значение для отслеживания длины стека;
● public - метод с именем reset(), который будет сбрасывать длину и все значения
элементов на 0;
● public - метод с именем push(), который будет добавлять значение в стек.push()
должен возвращать значение false, если массив уже заполнен, и true в противном
случае;
● public - метод с именем pop() для вытягивания и возврата значения из стека.Если в
стеке нет значений, то должно выводиться предупреждение;
● public - метод с именем print(), который будет выводить все значения стека.*/