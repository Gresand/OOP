#include <iostream>
#include <vector>

//=================01===============================

template<typename T>
class Pair1
{
private:
    T firstItem, secondItem;
public:
    Pair1(T firstItem, T secondItem) : firstItem(firstItem), secondItem(secondItem)
    {}
    T first() const
    {
        return firstItem;
    }
    T second() const
    {
        return secondItem;
    }
};

//=================02===============================

template<typename T1, typename T2>
class Pair
{
private:
    T1 firstItem;
    T2 secondItem;
public:
    Pair(T1 firstItem, T2 secondItem) : firstItem(firstItem), secondItem(secondItem)
    {}
    T1 first() const
    {
        return firstItem;
    }
    T2 second() const
    {
        return secondItem;
    }
};

//=================03===============================

template<typename T>
class StringValuePair : public Pair<std::string, T>
{
public:
    StringValuePair(std::string firstItem, T secondItem) : Pair<std::string, T>(firstItem, secondItem)
    {}
};

//=================04===============================

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
enum cardSuit
{
    HEART = 3,
    DIAMOND,
    CLUB,
    SPADE
};

enum cardVisibility
{
    OFF = 0,
    ON = 1
};

class Card
{
private:
    Meaning  value;
    cardSuit suit;
    bool visible;
public:
    Card(Meaning  value, cardSuit suit, bool visible) : value(value), suit(suit), visible(visible)
    {}
    void Flip()
    {
        visible = !visible;
    }
    uint16_t GetValue() const
    {
        return this->value;
    }
    uint8_t GetSuit() const
    {
        return this->suit;
    }
    bool GetVisible() const
    {
        return this->visible;
    }
};
std::ostream& operator<<(std::ostream& os, const Card& c)
{
    if (c.GetVisible())
    {
        switch (c.GetValue())
        {
        case ace: return os << '(' << 'A' << c.GetSuit() << ')'; break;
        case jack: return os << '(' << 'J' << c.GetSuit() << ')'; break;
        case lady: return os << '(' << 'Q' << c.GetSuit() << ')'; break;
        case theking: return os << '(' << 'K' << c.GetSuit() << ')'; break;
        default: return os << '(' << c.GetValue() << c.GetSuit() << ')';
        }

    }
    return os << "Card is: " << "(**)";
}

class Hand
{
private:
    std::vector<Card*> cardsOnHand;
public:
    void Add(Card* card)
    {
        cardsOnHand.push_back(card);
    }
    void Clear()
    {
        cardsOnHand.clear();
    }
    uint16_t GetValue()
    {
        uint16_t result = 0;
        bool aceOnHand = false;
        for (size_t k = 0; k < cardsOnHand.size(); ++k)
        {
            if (cardsOnHand[k]->GetValue() == ace)
            {
                aceOnHand = true;
            }

            if (cardsOnHand[k]->GetValue() == jack|| cardsOnHand[k]->GetValue() == lady || cardsOnHand[k]->GetValue() == theking)
            {
                result += 10;
            }
            else
            {
                result += cardsOnHand[k]->GetValue();
            }
        }
        if (aceOnHand && result <= 11)
        {
            result += 10;
        }
        return result;
    }
};

class GenericPlayer : public Hand
{
private:
    std::string name;
public:
    GenericPlayer(std::string name) : name(name)
    {}
    virtual bool IsHitting() const = 0;

    bool IsBoosted()
    {
        if (this->GetValue() > 21)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void Bust()
    {
        std::cout << "Player " << name << " busted";
    }
};

int main()
{
    //=================01===============================

    Pair1<int> p1(6, 9);
    std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    std::cout << std::endl;

    //=================02===============================

    Pair<int, double> p01(6, 7.8);
    std::cout << "Pair: " << p01.first() << ' ' << p01.second() << '\n';

    const Pair<double, int> p02(3.4, 5);
    std::cout << "Pair: " << p02.first() << ' ' << p02.second() << '\n';

    std::cout << std::endl;

    //=================03===============================

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    std::cout << std::endl;

    //=================04===============================

    std::cout << "Description above the function MAIN" << std::endl;

    std::cout << std::endl;


    return 0;
}