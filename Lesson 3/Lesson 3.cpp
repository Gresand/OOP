#include <iostream>
#include <string>

//==1==

class Figure
{
public:
	virtual double area() = 0;
};

class Parallelogram : public Figure
{
protected:
	double m_Val1;
	double m_Val2;
	double s;
public:
	Parallelogram(double Val1,double Val2)
	{
		this->m_Val1 = Val1;
		this->m_Val2 = Val2;
	}

	virtual double area() override
	{	
		return s = m_Val1 * m_Val2;
	}
};

class Rectangle : public Parallelogram
{
public:
	Rectangle(double m_Val1,double m_Val2) : Parallelogram(m_Val1, m_Val2)	{}
};

class Square : public Parallelogram
{
public:
	Square(double m_Val1) : Parallelogram(m_Val1, m_Val1) {}
};

class Rhombus : public Parallelogram
{
public:
	Rhombus(double m_Val1,double m_Val2) : Parallelogram(m_Val1, m_Val2) {}

	double area() override
	{
		return s = (m_Val1 * m_Val2) / 2;
	}
};

class Circle : public Figure
{
private:
	double pi = 3.14;
	double s=0;
	double m_rad=0;
public:
	Circle(double rad)
	{
		this->m_rad = rad;
	}

	double area() override
	{
		return s = (pi * (m_rad * m_rad));
	}
};

//==2==
class Car
{
protected:
	std::string company;
	std::string model;
public:
	Car()
	{
		std::cout << "Car class" << std::endl;
	}
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar()
	{
		std::cout << "PassengerCar class" << std::endl;
	}
};

class Bus : virtual public Car
{
public:
	Bus()
	{
		std::cout << "Bus class" << std::endl;
	}
};

class Minivan : public PassengerCar, public Bus
{
public:
	Minivan()
	{
		std::cout << "Minivan class" << std::endl;
	}
};


//==3==
class Fraction
{
private:
	int m_numerator;
	int m_denominator;
public:
	Fraction(int numerator = 1, int denomerator = 1)
	{
			this->m_numerator = numerator;
			this->m_denominator = denomerator;	
	}

	int numeration()
	{
		return m_numerator;
	}

	int denomeration()
	{
		return m_denominator;
	}

	Fraction operator + (Fraction b);

	Fraction operator - ()
	{
		return Fraction(-m_numerator, m_denominator);
	}

	friend Fraction operator - (Fraction a, Fraction b);

	void prinf()
	{
		std::cout << m_numerator << '/' << m_denominator;
	}

	bool operator== (const Fraction& fraction)
	{
		if (m_numerator * fraction.m_denominator == fraction.m_numerator * m_denominator)
		{
			return true;
		}
		return false;
	}
	bool operator!= (const Fraction& fr)
	{
		if (*this == fr)
		{
			return false;
		}
		return true;
	}
	bool operator< (const Fraction& fraction)
	{
		if (m_numerator * fraction.m_denominator < fraction.m_numerator * m_denominator)
		{
			return true;
		}
		return false;
	}
	bool operator>= (const Fraction& fraction)
	{
		if (*this < fraction)
		{
			return false;
		}
		return true;
	}
	bool operator> (const Fraction& fraction)
	{
		if (m_numerator * fraction.m_denominator > fraction.m_numerator * m_denominator)
		{
			return true;
		}
		return false;
	}
	bool operator<= (const Fraction& fraction)
	{
		if (*this > fraction)
		{
			return false;
		}
		return true;
	}
	friend std::ostream& operator<<(std::ostream& os, const Fraction& fr)
	{
		return os << fr.m_numerator << '/' << fr.m_denominator;
	}
};

Fraction operator * (Fraction a, Fraction b); 
Fraction operator / (Fraction a, Fraction b);

Fraction Fraction::operator+(Fraction b)
{
	int cd = m_denominator * b.m_denominator;
	int ns = m_numerator * b.m_denominator + b.m_numerator * m_denominator;
	Fraction sum(ns, cd);
	return sum;
}

Fraction operator - (Fraction a, Fraction b)
{
	int cd = a.m_denominator * b.m_denominator;
	int ns = a.m_numerator * b.m_denominator - b.m_numerator * a.m_denominator;
	Fraction subtr(ns, cd);
	return subtr;
}

Fraction operator * (Fraction a, Fraction b)
{
	int np = a.numeration() * b.numeration();
	int dp = a.denomeration() * b.denomeration();
	return Fraction(np, dp);
}

Fraction operator / (Fraction a, Fraction b)
{
	if (b.numeration() == 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	return a * Fraction(b.denomeration(), b.numeration());
}

//==4==
enum Suit
{
	diamonds,
	baptize,
	peaks,
	worms
};

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

class Card
{
private:
	Meaning meaning;
	bool isFaceUp;
public:
	bool flip() {return !this->isFaceUp;}
	int GetValue(Meaning) { return this->meaning == ace; }
};

int main()
{
//==1==
	int index=0;
	std::cout << "What area do you want to find?" << std::endl;
	std::cout << "1: Parallelogram" << std::endl
		<< "2: Rectangle" << std::endl
		<< "3: Square" << std::endl
		<< "4: Rhombus" << std::endl
		<< "5: Circle" << std::endl
		<< "Enter something else to exit" << std::endl;
	std::cin >> index;
	if (index == 1)
	{
		double val1 = 0, val2 = 0;
		std::cout << "Base length: ";
		std::cin >> val1; std::cout << std::endl;
		std::cout << "Height length: ";
		std::cin >> val2; std::cout << std::endl;
		Parallelogram parallelogram(val1, val2);
		std::cout << "The area of parallelogram: " << parallelogram.area();
	}
	else if (index == 2)
	{
		double val1 = 0, val2 = 0;
		std::cout << "Width: ";
		std::cin >> val1; std::cout << std::endl;
		std::cout << "Height: ";
		std::cin >> val2; std::cout << std::endl;
		Rectangle rectangle(val1, val2);
		std::cout << "The area of rectangle: " << rectangle.area();
	}
	else if (index == 3)
	{
		double val1 = 0;
		std::cout << "Enter side length: ";
		std::cin >> val1; std::cout << std::endl;
		Square square(val1);
		std::cout << "The area of square: " << square.area();
	}
	else if (index == 4)
	{
		double val1 = 0, val2 = 0;
		std::cout << "Enter the length of the first diagonal: ";
		std::cin >> val1; std::cout << std::endl;
		std::cout << "Enter the length of the second diagonal: ";
		std::cin >> val2; std::cout << std::endl;
		Rhombus rhombus(val1, val2);
		std::cout << "The area of rhombus: " << rhombus.area();
	}
	else if (index == 5)
	{
		double val1 = 0;
		std::cout << "Enter radius: ";
		std::cin >> val1; std::cout << std::endl;
		Circle circle(val1);
		std::cout << "The area of circle: " << circle.area();
	}
	else
	{
		std::cout << "Exit";
	}
	
//==2==
	Car car;
	PassengerCar passengercar;
	Bus bus;
	Minivan minivan;

	/*Проблема в ромбовидном наследовании заключается в том, что создаётся лишний конструктор родительского класса
	эту проблему можно решить используя виртуальное наследование, в репозитории оставлю скриншоты создания чисто
	дочернего класса Minivan С использование виртуального наследования и БЕЗ виртуального наследования*/

//==3==
	Fraction f12(1, 2);
	Fraction f13(1, 3);
	Fraction fs, fd, fp, fm, fdiv;
	std::cout << "f12 = "; f12.prinf(); std::cout << std::endl;
	std::cout << "f12 = "; f13.prinf(); std::cout << std::endl;
	fs = f12 + f13;
	std::cout << "fs = "; fs.prinf(); std::cout << std::endl;
	fd = f12 - f13;
	std::cout << "fd = "; fd.prinf(); std::cout << std::endl;
	fp = f12 * f13;
	std::cout << "fp = "; fp.prinf(); std::cout << std::endl;
	fm = -f12;
	std::cout << "fm = "; fm.prinf(); std::cout << std::endl;
	fdiv = f12 / f13;
	std::cout << "fdiv = "; fdiv.prinf(); std::cout << std::endl;

//==4==

	/*Создал два перечисления, но объявил их вне класса (думаю так будет лучше), создал два метода,
	первый возвращает состояние карты, второй возвращает значение карты из перечисления в данном случае - туз*/
}

/*1. Создать абстрактный класс Figure (фигура). Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг).
Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб). Для всех классов создать конструкторы.
Для класса Figure добавить чисто виртуальную функцию area() (площадь). Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.

2. Создать класс Car (автомобиль) с полями company (компания) и model (модель). Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус).
От этих классов наследует класс Minivan (минивэн). Создать конструкторы для каждого из классов, чтобы они выводили данные о классах. 
Создать объекты для каждого из классов и посмотреть, в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».
Примечание: если использовать виртуальный базовый класс, то объект самого "верхнего" базового класса создает самый "дочерний" класс.

3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2).
Предусмотреть, чтобы знаменатель не был равен 0. Перегрузить:
математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
унарный оператор (-)
логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).

Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте перегрузить один через другой.

Продемонстрировать использование перегруженных операторов.

4. Создать класс Card, описывающий карту в игре БлэкДжек. У этого класса должно быть три поля: масть, значение карты и положение карты (вверх лицом или рубашкой).
Сделать поля масть и значение карты типом перечисления (enum). Положение карты - тип bool. Также в этом классе должно быть два метода:
метод Flip(), который переворачивает карту, т.е. если она была рубашкой вверх, то он ее поворачивает лицом вверх, и наоборот.
метод GetValue(), который возвращает значение карты, пока можно считать, что туз = 1.*/