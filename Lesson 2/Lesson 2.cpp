#include <iostream>
#include <string>

using namespace std;

//1=================================================================================================================================================

struct DataPerson
    {
        string name;
        unsigned int age;
        char gender;
        int weight;
    };

class Person
{
private:
    string name;
    unsigned int age  = 0;
    char gender;
    int weight = 0;
public:

    void SetData(string name, unsigned int age, char gender, int weight)
    {
        this->name = name;
        this->age = age;
        this->gender = gender;
        this->weight = weight;
    }

    DataPerson GetData()
    {
        DataPerson dataperson;
        dataperson.name = this->name;
        dataperson.age = this->age;
        dataperson.gender = this->gender;
        dataperson.weight = this->weight;
        return dataperson;
    }

};

ostream& operator<<(ostream& os, const DataPerson& dataperson)
{
    os << "Name: " << dataperson.name << ", Age: " << dataperson.age << ", Gender: " << dataperson.gender << ", Weight: " << dataperson.weight;
    return os;
}

class Student : public Person
{
private:

    int YearOfStudy = 0;

public:
    static int NumberOfStudent;
    Student()
    {
        NumberOfStudent++;
    }

    void SetYear(int year)
    {
        this->YearOfStudy = year;
    }

    int GetYear()
    {
        return this->YearOfStudy;
    }

    static int GetNumberOfStudent()
    {
        return NumberOfStudent;
    }

};

int Student::NumberOfStudent = 0;

//2=================================================================================================================================================

class Fruit
{
private:
    string name;
    string color;
public:

    string getName() {return this->name;}

    string getColor() {return this->color;}
};

class Apple : public Fruit
{
private:
    string name = "Apple";
    string color;
public:
    Apple() {};
    Apple(string color)
    {
        this->color = color;
    };
    string getName() { return name; }
    string getColor() { return color; }
};

class Banana : public Fruit
{
private:
    string name = "banana";
    string color = "yellow";
public:
    string getName() { return name; }
    string getColor() { return color; }
};

class GrannySmith : public Apple
{
private:
    string name = "Granny Smith apple";
    string color = "green";
public:
    string getName() { return name; }
    string getColor() { return color; }
};

int main()
{
    //1=================================================================================================================================================
    Student man1;
    man1.SetData("Andrey", 24, 'M', 80);
    cout << man1.GetData() << endl;
    man1.SetYear(2015);
    cout << "Year of study: " <<  man1.GetYear() << endl;
    Student woman1;
    woman1.SetData("Nastya", 21, 'W', 55);
    cout << woman1.GetData() << endl;
    woman1.SetYear(2018);
    cout << "Year of study: " << woman1.GetYear() << endl;
    Student man2;
    man2.SetData("Ivan", 22, 'M', 75); 
    cout << man2.GetData() << endl;
    man2.SetYear(2017);
    cout << "Year of study: " << man2.GetYear() << endl;
    cout << Student::GetNumberOfStudent();
    cout << endl;

    //2=================================================================================================================================================

    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    //3=================================================================================================================================================

    /*Суть игры Blackjack в том, чтобы набрать количество очков больше чем у раздающего (но не больше чем 21).
    В игре есть сами игроки и раздающий, раздающий набирает карты последним, вначале игрок получает две карты,
    сумма которых позволит игроку определить нужны ли дополнительные карты или нет, если игрок набрал сумму очков,
    превышающую 21, то его ставка проигрывается.
    Если сумма очков игрока равна сумме очков дилера, то объявляется ничья.
    Игроки, набравшие сумму очков меньше чем диер проигрывают.
    Исходя из вышесказанного в отношении ООП можно создать классы:
    Blackjack - класс самой игры, в которой будут созданы:
    Класс игрока - Player
    Класс карт на руках - Hand
    Класс раздающего карты - Dealer
    Колода -Deck, Стопка карт - Deckpile
    Класс карта - Card
    Класс Card в свою очередь имеет подклассы
    Масть - Suit
    Ранг - Rank
    Игрок хранит карты на руках - Hand, может либо добавлять новые карты либо остановится и сообщить своё решение дилеру
    Дилер в свою очередь может передавать ход игроку, отслеживать игроков в ходе игры, сдавать карты и так же выбирать останавливаться или нет
    Карты на руках - Card можно хранить, добавлять, переворачивать, отображать, вычислять сумму очков, обнаруживать проигрыш
    Стопка карт - Deckpile принимает на хранение карты, тасует их, сдаёт, устанавливает начальное значение
    По поводу взаимодействия классов:
    BlackJack родительский класс для  Player, Dealer, Deckpile
    Player и Dealer родительский класс для Hand
    Deckpile родительский класс для Card, которая в своб очередь родительский класс для Deck*/


}

/*1. Создать класс Person (человек) с полями: имя, возраст, пол и вес. Определить методы переназначения имени, изменения возраста и веса.
Создать производный класс Student (студент), имеющий поле года обучения. Определить методы переназначения и увеличения этого значения. 
Создать счетчик количества созданных студентов. В функции main() создать несколько (не больше трёх) студентов. Вывести информацию о них.
2. Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт). У Fruit есть две переменные-члена: name (имя) и color (цвет). 
Добавить новый класс GrannySmith, который наследует класс Apple.
int main()
{
Apple a("red");
Banana b;
GrannySmith c;

std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

return 0;
}

Код, приведенный выше, должен давать следующий результат:

My apple is red.
My banana is yellow.
My Granny Smith apple is green.

3. Изучить правила игры в Blackjack. Подумать, как написать данную игру на С++, используя объектно-ориентированное программирование. 
Сколько будет классов в программе? Какие классы будут базовыми, а какие производными?
Продумать реализацию игры с помощью классов и записать результаты в виде комментария в основном файле сдаваемой работы.*/