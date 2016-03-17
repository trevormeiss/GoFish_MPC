#include <string>

const static std::string SUITS[] = {"Spades", "Clubs", "Hearts", "Diamonds"};
const static std::string RANKS[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

class Card {
private:
	int rank;
	int suit;
	int index;
public:
	Card(int num, int index);
	int getRank() const;
	int getSuit() const;
	int getIndex() const;
	std::string cardString() const;
	std::string rankString() const;

	bool operator < (const Card &rhs) const {
		return this->rank < rhs.rank ||
		       (this->rank == rhs.rank && this->suit < rhs.suit);
	}
};
