#include <iostream>
#include <string>

//==01====================================
template <typename T>
const T& dev(const T& a,const T& b)
{
    if (b == 0)
        throw std::invalid_argument("Division By Zero");
    return a / b;
}

//==02====================================
class Ex
{
private:
	float x;
public:
	Ex(float x) : x(x) { };

	void getX() const
	{
		std::cout << x << std::endl;
	}
};

class Bar
{
private:
	float y;
public:
	Bar() : y(0) { };

	void set(float a)
	{
		if (y + a > 100)
			throw Ex(a * y);
		y = a;
	}
	void getY() const
	{
		std::cout << y << std::endl;
	}
};

//==03====================================

class OffTheField
{
	int x;
	int y;
	int new_pos_x;
	int new_pos_y;
	std::string m_message;
public:
	OffTheField(int c_x, int c_y, int n_x, int n_y) :
		x(c_x), y(c_y), new_pos_x(n_x), new_pos_y(n_y), m_message("")
	{
		if (new_pos_x > 10 || new_pos_x < 1)
		{
			m_message += "X coordinate error! The robot is out of bounds!\n";
			m_message += '[' + std::to_string(x) + ';' + std::to_string(y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}
		if (new_pos_y > 10 || new_pos_y < 1)
		{
			m_message += "Y coordinate error! The robot is out of bounds!\n";
			m_message += '[' + std::to_string(x) + ';' + std::to_string(y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}
	}

	const std::string& getInfo() const
	{
		return m_message;
	}
};

class IllegalCommand
{
private:
	int x;
	int y;
	int new_pos_x;
	int new_pos_y;
	std::string m_message;
public:
	IllegalCommand(int c_x, int c_y, int n_x, int n_y) :
		x(c_x), y(c_y), new_pos_x(n_x), new_pos_y(n_y), m_message("")
	{
		if (abs(x - new_pos_x) > 1)
		{
			m_message += "X coordinate error! The robot is out of bounds!\n";
			m_message += '[' + std::to_string(x) + ';' + std::to_string(y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}

		if (abs(y - new_pos_y) > 1)
		{
			m_message += "Y coordinate error! The robot is out of bounds!\n";
			m_message += '[' + std::to_string(x) + ';' + std::to_string(y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}

		if (x == new_pos_x && y == new_pos_y)
		{
			m_message += "X and Y coordinate error! You can't move to your current location!\n";
			m_message += '[' + std::to_string(x) + ';' + std::to_string(y) + "] => [" +
				std::to_string(new_pos_x) + ';' + std::to_string(new_pos_y) + "]\n";
		}
	}

	const std::string& getInfo() const
	{
		return m_message;
	}
};

class Robot
{
private:
	int pos_x;
	int pos_y;
public:
	Robot(int x = 5, int y = 5) : pos_x(x), pos_y(y)
	{
		std::cout << "Starting position of the robot: [" << pos_x << ';' << pos_y << ']' << std::endl;
	}

	void move(int x, int y)
	{
		if (abs(pos_x - x) > 1 || abs(pos_y - y) > 1 || (pos_x == x && pos_y == y))
			throw IllegalCommand(pos_x, pos_y, x, y);
		if (x > 10 || x < 1 || y > 10 || y < 1)
			throw OffTheField(pos_x, pos_y, x, y);

		std::cout << "Robot stepped [" << pos_x << ';' << pos_y << "] => [" << x << ';' << y << ']' << std::endl;

		pos_x = x;
		pos_y = y;
	}
};

int main()
{
	//==01====================================
	double a;
	double b;
	std::cout << "Enter a:" << std::endl;
	std::cin >> a;
	std::cout << "Enter b:" << std::endl;
	std::cin >> b;
	try
	{
		std::cout << dev(a,b) << std::endl;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error: division by zero" << std::endl;
	}
	
	//==02====================================
	int n = 0;
	
	Bar bar;
	try
	{
		do
		{
			std::cout << "Enter N: " << std::endl;
			std::cin >> n;
			bar.set(n);
		} while (n != 0);
	}
	catch (const Ex& ex)
	{
		ex.getX();
	}

	//==03====================================
	int x = 0, y = 0;
	Robot r;

	while (true)
	{
		std::cin >> x >> y;

		if (x == 0 && y == 0)
			break;

		try
		{
			r.move(x, y);
		}
		catch (const IllegalCommand& e)
		{
			std::cerr << e.getInfo() << std::endl;
		}
		catch (const OffTheField& e)
		{
			std::cerr << e.getInfo() << std::endl;
		}
	}
}

/*1. Написать шаблонную функцию div, которая должна вычислять результат деления двух параметров и запускать исключение DivisionByZero,
если второй параметр равен 0. В функции main выводить результат вызова функции div в консоль, а также ловить исключения.

2. Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий x значением параметра.
Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем) и имеющий метод set с единственным вещественным
параметром a. Если y + a > 100, возбуждается исключение типа Ex с данными a*y, иначе в y заносится значение a.
В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n. 
Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0.
В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.

3. Написать класс «робот», моделирующий перемещения робота по сетке 10x10, у которого есть метод,
означающий задание переместиться на соседнюю позицию. 
Эти методы должны запускать классы-исключения OffTheField, если робот должен уйти с сетки, и IllegalCommand, 
если подана неверная команда (направление не находится в нужном диапазоне).
Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения. 
Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов,
а также выводящую подробную информацию о всех возникающих ошибках.*/