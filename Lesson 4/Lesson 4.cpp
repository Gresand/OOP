#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr) { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0) {
            m_data = new int[length];
        }
        else {
            m_data = nullptr;
        }
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }

    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    void resize(int newLength)
    {
        if (newLength == m_length) {
            return;
        }

        if (newLength <= 0) {
            erase();
            return;
        }

        int* data = new int[newLength];

        if (m_length > 0) {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            for (int index = 0; index < elementsToCopy; ++index) {
                data[index] = m_data[index];
            }
        }

        delete[] m_data;

        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);

        int* data = new int[m_length + 1];

        for (int before = 0; before < index; ++before) {
            data[before] = m_data[before];
        }

        data[index] = value;

        for (int after = index; after < m_length; ++after) {
            data[after + 1] = m_data[after];
        }

        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void push_back(int value) { insertBefore(value, m_length); }

//==1===============================================================
    void pop_back()
    {
        assert(m_length > 0);
        m_length--;
    }

    void pop_front()
    {
        assert(m_length > 0);

        int* data = new int[m_length-1];
        
        for (size_t i = 0; i < m_length-1; i++)
        {
            data[i] = m_data[i+1];
        }

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void sort1()
    {
        std::sort(m_data, m_data+m_length);
    }
    
    void PrintArr()
    {
        for (size_t i = 0; i < m_length; i++)
        {
            std::cout << m_data[i] << std::endl;
        }
    }
    
};

//==2=====================================================
int dat()
{
    return rand() % 10 + 1;
}

//==3====================================================
enum Meaning 
{
    ace = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10,
    jack = 10,
    lady = 10,
    theking = 10
};

class Card //Класс взят из домашего задания Лекции 3 и исправлен с добавлением конструктора
{
private:
    Meaning meaning;
    bool isFaceUp;
public:
    Card(Meaning cards)
    {
        meaning = cards;
    }
    bool flip() { isFaceUp = !isFaceUp; }
    int GetValue() { return this->meaning; }
};

class Hand
{
private:
    std::vector<Card*> HandofCards;
public:
    int add(Card* card)
    {
        HandofCards.push_back(card);
    }

    void Clear()
    {
        HandofCards.clear();
    }

    int getValue()
    {
        int result = 0;
        bool aceOnHand = false;
        for (size_t k = 0; k < HandofCards.size(); ++k)
        {
            if (HandofCards[k]->GetValue() == ace)
            {
                aceOnHand = true;
            }

            if (HandofCards[k]->GetValue() == jack || HandofCards[k]->GetValue() == lady || HandofCards[k]->GetValue() == theking)
            {
                result += 10;
            }
            else
            {
                result += HandofCards[k]->GetValue();
            }
        }
        if (aceOnHand && result <= 11)
        {
            result += 10;
        }
        return result;
    }
};

void printint(int* i) { std::cout << *i << std::endl; }

int main(int argc, char* argv[])
{
    ArrayInt arrayInt;
    arrayInt.push_back(100);
    arrayInt.push_back(10);
    arrayInt.push_back(50);
    arrayInt.push_back(6);
    arrayInt.pop_back();
    arrayInt.push_back(1);
    arrayInt.PrintArr();
    arrayInt.pop_front();
    std::cout << std::endl;
    arrayInt.PrintArr();
    arrayInt.sort1();
    std::cout << std::endl;
    arrayInt.PrintArr();
    
//==2====================================================

    int value;
    std::cout << "Value=";
    std::cin >> value;
    std::vector<int> v(value);
    generate(v.begin(), v.end(), dat);
    std::set<int> s(v.begin(), v.end());
    std::cout << "Total different numbers=" << s.size() << std::endl << "They are: ";
    copy(s.begin(), s.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

//==3===================================================
    Hand hand1;
    Card* card1 = new Card(ace);
    Card* card2 = new Card(theking);
    Card* card3 = new Card(six);

    hand1.add(card1);
    hand1.add(card2);
    hand1.add(card3);

    hand1.Clear(); //Вывод на экран значений карт я напишу в следующий дз перегружая оператор вывода, так как не успеваю

    return 0;
}

/*1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
• для удаления последнего элемента массива (аналог функции pop_back() в векторах)
• для удаления первого элемента массива (аналог pop_front() в векторах)
• для сортировки массива
• для вывода на экран элементов.

2. Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать максимально быстрый алгоритм.
3. Реализовать класс Hand, который представляет собой коллекцию карт. В классе будет одно поле: вектор указателей карт (удобно использовать вектор, т.к. это по сути динамический массив,
а тип его элементов должен быть - указатель на объекты класса Card). Также в классе Hand должно быть 3 метода:
• метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
• метод Clear, который очищает руку от карт
• метод GetValue, который возвращает сумму очков карт руки (здесь предусмотреть возможность того, что туз может быть равен 11).*/