#include <iostream>
#include <chrono>
#include <ctime>
#include <memory>

//==1==============================================================================================================================
class Date
{
private:

    uint8_t m_day{0};
    uint8_t m_month{0};
    int16_t m_year{0};

public:

    void setDate(uint8_t day, uint8_t month, int16_t year)
    {
        m_day = day;
        m_month = month;
        m_year = year;
    }

    friend std::ostream& operator<<(std::ostream& out, const Date& date);

    static std::shared_ptr<Date> getLatestDate(const std::shared_ptr<Date> a,const std::shared_ptr<Date> b)
    {
        if (a->m_year>b->m_year)
        {
            return a;
        }
        else if (a->m_year < b->m_year)
        {
            return b;
        }
        else
        {
            if (a->m_month > b->m_month)
            {
                return a;
            }
            else if (a->m_month < b->m_month)
            {
                return b;
            }
            else
            {
                if (a->m_day >= b->m_day)
                {
                    return a;
                }
                else
                {
                    return b;
                }
            }
        }
        
    }

    std::shared_ptr<Date> years(const std::shared_ptr<Date> a, const std::shared_ptr<Date> b)
    {

    }

    static void swapDate(std::shared_ptr<Date>& a,std::shared_ptr<Date>& b)
    {
        std::swap(a, b);
    }

};

std::ostream& operator<<(std::ostream& out, const Date& date)
{
    out << "Day: " << static_cast<short>(date.m_day) << "." << static_cast<short>(date.m_month) << "." << date.m_year << std::endl;
    return out;
}

int main()
{
//==1==============================================================================================================================
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm* parts = std::localtime(&now_c);

    std::shared_ptr<Date> today(new Date);
    today->setDate(parts->tm_mday, 1 + parts->tm_mon,1900 + parts->tm_year);
    std::cout << *today << std::endl;
    std::shared_ptr<Date> date = std::move(today);
    std::cout << *date;
    if (today == nullptr)
    {
        std::cout << "today ptr is null" << std::endl;
    }
    else
    {
        std::cout << "today ptr is NOT null" << std::endl;
    }
    if (date == nullptr)
    {
        std::cout << "day ptr is null" << std::endl;
    }
    else
    {
        std::cout << "day ptr is NOT null" << std::endl;
    }
    
//==2==============================================================================================================================

    std::shared_ptr<Date> date1(new Date);
    std::shared_ptr<Date> date2(new Date);
    date1->setDate(18, 4,2003);
    date2->setDate(19, 1, 2002);
    std::cout << *Date::getLatestDate(date1,date2) << std::endl;

    std::cout << *date1 << std::endl;
    std::cout << *date2 << std::endl;
    Date::swapDate(date1, date2);
    std::cout << *date1 << std::endl;
    std::cout << *date2 << std::endl;
    
    return 0;
}

/*1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям. Перегрузите оператор вывода для данного класса.
Создайте два "умных" указателя today и date. Первому присвойте значение сегодняшней даты.
Для него вызовите по отдельности методы доступа к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного оператора вывода.
Затем переместите ресурс, которым владеет указатель today в указатель date.
Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию об этом в консоль.
2. По условию предыдущей задачи создайте два умных указателя date1 и date2.
• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и сравнивает их между собой (сравнение происходит по датам).
Функция должна вернуть более позднюю дату.
• Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.

Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в качестве параметров.*/