#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

enum class Suit
{
	diamonds,
	baptize,
	peaks,
	worms
};

enum class Value
{
	ace = 11,
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
	king = 10
};

enum class CardType
{
	ace = 1,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	lady,
	king
};

class Card
{
private:
	Suit suit;
	Value value;
	CardType cardType;
	bool isFaceUp;
	Value CardValue(const CardType& cardType)
	{
		if (cardType == CardType::jack)
		{
			return Value::jack;
		}
		else if (cardType == CardType::lady)
		{
			return Value::lady;
		}
		else if (cardType == CardType::king)
		{
			return Value::king;
		}
		else if (cardType == CardType::ace)
		{
			return Value::ace;
		}
		else
		{
			auto test1 = static_cast<Value>(cardType);
			return test1;
		}
	}
public:
	Card(Suit suit, CardType cardType, bool isFaceUp) : suit(suit), cardType(cardType), isFaceUp(isFaceUp) 
	{
		value = CardValue(cardType);
	};

	void Flip()
	{
		isFaceUp = !isFaceUp;
	}

	bool GetisFaceUp() const
	{
		return this->isFaceUp;
	}

	Value GetValue() const
	{
		if (GetisFaceUp())
		{
			return this->value;
		}
	}

	CardType GetCardType() const
	{
		return this->cardType;
	}

	Suit GetSuit() const
	{
		return this->suit;
	}

};

class Hand {
private:
	std::vector<Card*> handOfCard;
public:
	void add(Card* card)
	{
		handOfCard.push_back(card);
	}

	void clear()
	{
		for (size_t i = 0; i < handOfCard.size(); i++)
		{
			delete handOfCard[i];
		}
		handOfCard.clear();
		handOfCard.shrink_to_fit();
	}

	uint16_t getValue() const
	{
		uint16_t result = 0;
		for (size_t i = 0; i < handOfCard.size(); i++)
		{
			if (handOfCard[i]->GetValue() == Value::ace && result > 21)
			{
				result += 1;
			}
			else
			{
				result += static_cast<uint16_t>(handOfCard[i]->GetValue());
			}
		}
		return result;
	}

	std::vector<Card*> GetCards() const
	{
		return handOfCard;
	}
};

class GenericPlayer : public Hand
{
private:
	std::string nameOfPlayer;
public:
	GenericPlayer(std::string& name) : nameOfPlayer(name) { };

	virtual bool IsHitting() const = 0;

	bool IsBoosted()
	{
		return Hand::getValue() > 21;
	}

	void Bust()
	{
		if (IsBoosted())
		{
			std::cout << "The " << nameOfPlayer << " has a bust" << std::endl;
		}
	}

	std::string GetName() const
	{
		return nameOfPlayer;
	}
};

class Player : public GenericPlayer
{
public:
	Player(std::string str) : GenericPlayer(str) { };

	virtual bool IsHitting() const override
	{
		bool result;
		std::cout << "Another card? (Y/N)" << std::endl;
		bool ansver = true;
		while (ansver)
		{
			switch (std::cin.get())
			{
			case 'y':
				result = true;
				ansver = false;
				break;
			case 'n' :
				result = false;
				ansver = false;
				break;
			default: std::cout << "Enter 'Y' or 'N'";
			}
			std::cout << std::endl;
		}
		return result;
	}

	void Win()
	{
		std::cout << this->GetName() << " is winner" << std::endl;
	}

	void Lose()
	{
		std::cout << this->GetName() << " is loser" << std::endl;
	}

	void Push()
	{
		std::cout << this->GetName() << " push" << std::endl;
	}
};

class House : public GenericPlayer
{
public:
	House(std::string str = "Dealer") : GenericPlayer(str) { };

	virtual bool IsHitting()  const override 
	{
		if (Hand::getValue() >= 16) 
		{
			return false;
		}
		return true;
	}

	void FlipFirstCard()
	{
		this->GetCards()[0]->Flip();
	}
};

class Deck : public Hand
{
private:
	std::vector<Card*> cardDeck;
public:
	Deck()
	{
		Populate();
	}
	
	void Populate()
	{	
		for (size_t i = static_cast<int>(Suit::diamonds); i <= static_cast<int>(Suit::worms); i++)
		{
			for (size_t j = static_cast<int>(CardType::ace); j <= static_cast<int>(CardType::king); j++)
			{
				cardDeck.push_back(new Card(static_cast<Suit>(i), static_cast<CardType>(j), false));
			}
		}
		int i = 0;
	}

	void Shuffle()
	{
		auto rng = std::default_random_engine{};
		rng.seed(time(0));
		std::shuffle(std::begin(cardDeck), std::end(cardDeck), rng);
	}

	void Deal(Hand& aHand)
	{
		aHand.add(cardDeck.back());
		cardDeck.pop_back();
	}

	void AddltionalCards(GenericPlayer& aGenerlcPlayer)
	{
		if (aGenerlcPlayer.IsHitting())
		{
			Deal(*this);
		}
	}

	void clear()
	{
		for (size_t i = 0; i < cardDeck.size(); i++)
		{
			delete cardDeck[i];
		}
		cardDeck.clear();
		cardDeck.shrink_to_fit();
	}

};

std::ostream& operator<<(std::ostream& os, const Card& c)
{
	if (c.GetisFaceUp())
	{
		switch (c.GetCardType())
		{
		case CardType::ace: return os << 'A'; break;
		case CardType::jack: return os << 'J'; break;
		case CardType::lady: return os << 'Q'; break;
		case CardType::king: return os << 'K'; break;
		default: return os << static_cast<int>(c.GetValue());
		}
	}
	return os << " (**)";
}

std::ostream& operator<<(std::ostream& pl, const GenericPlayer& c)
{
	pl << c.GetName() << " Has cards: ";
	for (size_t i = 0; i < c.GetCards().size(); i++)
	{
	pl << *c.GetCards()[i] << " ";
	}
	pl << " Value: " << c.getValue();
	return pl;
}

class Game
{
private:
	Deck deck;
	House house;
	std::vector<Player> player;
public:
	Game(std::vector<std::string> namesOfPlayers)
	{
		for (size_t i = 0; i < namesOfPlayers.size(); i++)
		{
			player.push_back(Player(namesOfPlayers[i]));
		}
		deck.Shuffle();
	}

	void play()
	{
		for (size_t i = 0; i < player.size(); i++)
		{
			deck.Deal(player[i]);
			deck.Deal(player[i]);
		}
		deck.Deal(house);
		deck.Deal(house);
		house.FlipFirstCard();

		for (size_t i = 0; i < player.size(); i++)
		{
			for (size_t j = 0; j < player[i].GetCards().size(); j++)
			{
				player[i].GetCards()[j]->Flip();
			}
			std::cout <<player[i];
			std::cout << std::endl;
		}
		for (size_t i = 0; i < house.GetCards().size(); i++)
		{
			house.GetCards()[i]->Flip();
		}
		std::cout << house;
		std::cout << std::endl;
		std::cout << std::endl;

		house.FlipFirstCard();
		do
		{
			for (size_t i = 0; i < player.size(); i++)
			{
				if (player[i].getValue() < 22)
				{
					std::cout << player[i].GetName() << " ";
					if (player[i].IsHitting())
					{
						deck.Deal(player[i]);
						player[i].GetCards()[player[i].GetCards().size() - 1]->Flip();
					}
				}
				else
				{
					std::cout << player[i].GetName() << " has a enumeration" << std::endl;
				}
			}
			if (house.IsHitting())
			{
				deck.Deal(house);
				house.GetCards()[house.GetCards().size() - 1]->Flip();
			}
			for (size_t i = 0; i < player.size(); i++)
			{
				std::cout << player[i];
				std::cout << std::endl;
			}
			std::cout << house;
			std::cout << std::endl;
		} while (house.IsHitting());
		for (size_t i = 0; i < player.size(); i++)
		{
			if (player[i].getValue()>21 || player[i].getValue() < house.getValue() && house.getValue() < 21)
			{
				player[i].Lose();
			}
			else if (player[i].getValue() < 21 && house.getValue() > 21 || player[i].getValue() == 21 || player[i].getValue() > 21 && house.getValue() > player[i].getValue())
			{
				player[i].Win();
			}
			else if (player[i].getValue() > house.getValue() && player[i].getValue() < 21)
			{
				player[i].Win();
			}
			else if (player[i].getValue() == house.getValue())
			{
				player[i].Push();
			}
			else if (house.getValue() == 21 && player[i].getValue() < 21)
			{
				player[i].Lose();
			}
			std::cout << std::endl;
		}

		for (size_t i = 0; i < player.size(); i++)
		{
			player[i].clear();
		}
		house.clear();
		deck.clear();
	}
	
};

bool isNumber(const std::string& str)
{
	for (char const& c : str) {
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

int main()
{
	
	std::cout << "Enter the number of players 1 - 8";
	std::cout << std::endl;
	std::string s_players;
	std::cin >> s_players;
	while (!isNumber(s_players))
	{
		std::cout << "incorrecrect value " << std::endl;
		std::cin >> s_players;
	}
	int players = std::stoi(s_players);
	while(players < 0 || players > 8)
	{
		std::cout << "incorrecrect value " << std::endl;
		std::cin >> s_players;
		while (!isNumber(s_players))
		{
			std::cout << "incorrecrect value " << std::endl;
			std::cin >> s_players;
		}
		players = std::stoi(s_players);
	}

	std::vector<std::string> v_players;
	for (size_t i = 0; i < players; i++)
	{
		std::string buf;
		std::cout << "Enter name " << i + 1 << " player: ";
		std::cin >> buf;
		v_players.push_back(buf);
	}

	bool gameInProcessing = true;
	do
	{
		Game* first = new Game(v_players);
		first->play();
		delete first;
		std::cout << "Another game?(Y/N)";
		char exit;
		do
		{
			std::cin >> exit;
			if (exit == 'n')
			{
				continue;
			}
			else if (exit == 'y')
			{
				continue;
			}
			else
			{
				std::cout << "Incorrect, please enter Y or N" << std::endl;
			}
		} while (exit != 'n' && exit != 'y');
		if (exit == 'n')
		{
			std::cout << "The Game is Over, Bye!" << std::endl;
			break;
		}
		else if (exit == 'y')
		{
			system("cls");
		}
	} while (gameInProcessing);
	
	return 0;
}