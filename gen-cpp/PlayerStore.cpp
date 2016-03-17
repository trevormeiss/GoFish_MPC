#include "PlayerStore.hpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Calculate the inverse modulus
// Fermat’s Little Theorem
// https://comeoncodeon.wordpress.com/2011/10/09/modular-multiplicative-inverse/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/* This function calculates (a^b)%MOD */
int PlayerStore::fermatPow(int a, int b, int MOD) {
int x = 1, y = a;
while(b > 0) {
    if(b%2 == 1) {
        x=(x*y);
        if(x>MOD) x%=MOD;
    }
    y = (y*y);
    if(y>MOD) y%=MOD;
    b /= 2;
}
return x;
}
int PlayerStore::modInverse(int a, int m) {
if (a<0) a = (((a%m)+m) % m);
return fermatPow(a,m-2,m);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Delta function
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PlayerStore::delta(int i, int x, queue<int> players) {
int product = 0;
int j;
while (!players.empty()) {
    j = players.front();
    players.pop();
    
    int y = (x-j)*modInverse(i-j, prime);
    if (product == 0)   product = y;
    else                product *= y;
}
product %= prime;
product += prime;
return product % prime;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Calculate recombination vector
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector<int> PlayerStore::recombination_vector(queue<int> &players) {
vector<int> recomb;
int i;
for (int j=0; j<players.size(); j++) {
    i = players.front();
    players.pop();
    recomb.push_back(delta(i, 0, players));
    players.push(i);
}
return recomb;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Card Reconstruction
// returns the card number (1-52)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PlayerStore::cardReconstruction() {
// Solve card
int cardNum = 0;
for (int i=0; i<numPlayers; i++) {
  cardNum += recomb_all[i] * receivedShares[i];
  cardNum %= prime;
}
return cardNum;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// indexToCard
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Card* PlayerStore::indexToCard(const int index) {
	// Get all the shares for card at this index
	int i=0;
	for (auto player : connectedPlayers) {
		if (i+1 == playerNum) {
			receivedShares[i] = deckShares[index];
		}
		else {
			receivedShares[i] = player.second->client.getDeckShare(index);
		}
		i++;
	}
	// Reconstruct card from shares
	int cardNum = cardReconstruction();
	return new Card(cardNum, index);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ranksHeld
// returns set of all ranks held by player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set<string> PlayerStore::ranksHeld() {
	set<string> ranksHeld;
	for (auto card : hand) {
		ranksHeld.insert(card.rankString());
	}
	return ranksHeld;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// bookFound
// book found in hand, tell other players
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::bookFound(vector<Card*> &book) {
	vector<int> indices;
	for (auto card : book) {
		indices.push_back(card->getIndex());
	}
	// Tell the players
	int i=1;
	for (auto player : connectedPlayers) {
		if (!player.second->client.bookAcquired(indices))
			cout << "Player " << i << "doesn't agree that book was acquired\n";
		i++;
	}
	numBooks++;
	// Remove these cards from hand
	for (auto card : book) {
		hand.erase(*card);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// checkForBook
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::checkForBook() {
	vector<Card*> sameRank;
	int prevRank = -1;
	// Count the occurrences of each rank in hand
	// Since the cards are ordered in the hand, we can count linearly
	for (auto card : hand) {
		if (card.getRank() == prevRank) {
			sameRank.push_back(&card);
			// Book found?
			if (sameRank.size() == bookSize) {
				bookFound(sameRank);
			}
		}
		else {
			sameRank.clear();
			sameRank.push_back(&card);
			prevRank = card.getRank();
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// printHands
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::printHands() {
	int totalBooks = numBooks;
	int mostBooks = numBooks;
	int winningPlayer = playerNum;

	// Tell the other players that you are starting your turn
	// Display the number of cards in their hand and number of books
	int i=1;
	for (auto player : connectedPlayers) {
		if (i != playerNum) {
			State _return;
			player.second->client.startTurn(_return, playerNum);
			cout << "Player " << i << " has " << _return.numCards << " cards and " << _return.numBooks << " books\n";

			totalBooks += _return.numBooks;

			// See who has the most books
			if (_return.numBooks > mostBooks) {
				mostBooks = _return.numBooks;
				winningPlayer = i;
			}
		}
		i++;
	}
	// Display your hand
	if (hand.empty()) {
		cout << "You have 0 cards and " << numBooks << " books\n";
	}
	else {
		cout << "You have " << numBooks << " books and your hand is:\n";
		for (auto card : hand) {
			cout << card.cardString() << endl;
		}
	}

	// Is the game over?
	if (totalBooks >= 13) {
		winner = winningPlayer;
		cout << "Player " << winner << " won the game!\n";
		finished.store(true);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// inputPlayerNum
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PlayerStore::inputPlayerNum() {
	// Ask user to specify what player they want to request cards from
	int pNum;
	bool validNumber = false;
while (!validNumber) {
	cout << "Enter player number to ask for cards: ";
	cin >> pNum;
	if (pNum == playerNum) cout << "You cannot ask yourself for cards\n";
	else if (pNum <= 0 || pNum > numPlayers) cout << pNum << " is not a valid player number\n";
	else validNumber = true;
}
return pNum;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// inputRank
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
string PlayerStore::inputRank() {
	string rank;
	// Ask user to specify which rank they want
set<string> ranks = ranksHeld();
bool validRank = false;
while (!validRank) {
	cout << "Enter desired rank (";
	// Display possible ranks
	for (auto &r : ranks) {
		cout << r << ",";
	}
	cout << "\b): ";
	cin >> rank;

	if (ranks.find(rank) == ranks.end())
		cout << "You don't have any cards of rank " << rank << endl;
	else validRank = true;
}
	return rank;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// makeRequest
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool PlayerStore::makeRequest() {
	bool catchMade = false;
	// Ask user to specify what player they want to request cards from
int pNum = inputPlayerNum();
// Ask user which rank they want to fish for
string rank = inputRank();

int index;
// Find a card in hand that matches this rank
for (auto card : hand) {
	if (card.rankString() == rank) {
		index = card.getIndex();
	}
}

// Make request
vector<int16_t> _return;
int i=1;
for (auto player : connectedPlayers) {
	if (i==pNum) {
		player.second->client.request(_return, rank, index);
		break;
	}
	i++;
}

// If nothing returned, go fish
if (_return.empty()) {
	cout << "Go Fish!\n";
	if (!drawCard(catchMade, rank))
		cout << "Unable to draw card\n";
}
// Caught fish!
else {
	// Let player know how many fish they caught
	cout << "Player " << pNum << " returned " << _return.size() << " card(s) of rank " << rank << endl;

	// Make sure the player gave you the correct cards
	for (auto &index : _return) {
		
		Card* card = indexToCard(index);
  		hand.insert(*card);

  		// Is this card of expected rank?
  		if (card->rankString() != rank)
  			cout << "Player " << pNum << " returned card with rank " << card->rankString() << endl;
	}
	checkForBook();
	catchMade = true;
}

return catchMade;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PlayerStore::PlayerStore() {
	playerNum = 1;
	prime     = 127;
	bookSize  = 4;
	numBooks  = 0;
	winner    = 1;
	finished.store(false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// lockPlayers
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::lockPlayers() {
numPlayers     = (int)connectedPlayers.size();
receivedShares = vector<int> (numPlayers);

// Calculate recombination vector for all players
queue<int> all_players;
for (int i=1; i<=numPlayers; i++) {
    all_players.push(i);
}
recomb_all = recombination_vector(all_players);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setNum
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::setNum(const int16_t num) {
	playerNum = num;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getNum
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int16_t PlayerStore::getNum() {
	return playerNum;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setPrime
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::setPrime(const int32_t p) {
	prime = p;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setActivePlayer
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::setActivePlayer(const int16_t pNum) {
	activePlayer = pNum;
	if (pNum != playerNum) {
		cout << "Player " << pNum << "'s turn\n";
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setDeckShares
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::setDeckShares(const std::vector<int32_t> & pDeckShares) {
	int i=0;
	for (auto &s : pDeckShares) {
		deckShares.push_back(s);
		remainingCardIndices.insert(i);
		i++;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getState
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::getState(State &_return) {
	_return.numCards = hand.size();
	_return.numBooks = numBooks;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getDeckShare
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PlayerStore::getDeckShare(const int16_t index) {
	return deckShares[index];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// drawCard
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool PlayerStore::drawCard(bool &catchMade, string rank) {
	bool cardDrawn = false;
	if (!remainingCardIndices.empty()) {
		// This index could be random but we draw from top of deck
		int cardIndex = *remainingCardIndices.begin();
		// Let other players know what card index was drawn
		// and get their share of this card
		int i=0;
		for (auto player : connectedPlayers) {
			receivedShares[i] = player.second->client.cardDrawn(cardIndex);
			i++;
		}
		int cardNum = cardReconstruction();

		Card* card = new Card(cardNum, cardIndex);
		hand.insert(*card);
		cout << "You drew the " << card->cardString() << endl; 
		cardDrawn = true;

		if (card->rankString() == rank)
			catchMade = true;

		checkForBook();
	}
	return cardDrawn;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// cardDrawn
// another player drew a card
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int PlayerStore::cardDrawn(const int16_t index) {
	remainingCardIndices.erase(index);
	return deckShares[index];
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// beginTurn
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::beginTurn() {
	cout << "~\n";
	// Let player know how many cards/books other players have
	printHands();

	cout << endl;

	// If you don't have any cards and there are no more cards to draw, you are done
	if (!hand.empty() || !remainingCardIndices.empty()) {
	// You cannot ask for cards if you don't have any
	if (!hand.empty()) {
		bool catchMade = true;
		// The player continues to ask for cards until they don't catch the fish they want
		while (catchMade && !hand.empty()) {
			catchMade = makeRequest();
		}
	}

	// You are out of cards so you must draw
	else {
		bool dummyBool;
		string dummyRank = "";
		if (!drawCard(dummyBool, dummyRank)) cout << "Unable to draw card\n";
	}
	}
	else {
		cout << "You are out of cards and there are no more to draw\n";
	}

	// Tell next player it is their turn
	int i=1;
	for (auto player : connectedPlayers) {
		if ((playerNum % numPlayers) + 1 == i) {
			player.second->client.yourTurn();
			break;
		}
		i++;
	}
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setReceivedShare
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::setReceivedShare(const int pNum, const int val) {
receivedShares[pNum-1] = val;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// receivedRequest
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PlayerStore::receivedRequest(std::vector<int16_t> & _return, const std::string& rank, const int16_t index) {
	cout << "Received request for cards of rank " << rank << endl;
	
	// Ask all players if this is a valid request
	int i=1;
	for (auto player : connectedPlayers) {
		// Requester should not validate their own request
		if (i != activePlayer) {
			if (!player.second->client.validateRequest(rank, index))
				cout << "Player " << i << " does not believe this is a valid request\n";
		}
		
		i++;
	}
	// Give the player all cards of requested rank
	// and remove them from your hand
	auto iter = hand.begin();
	while (iter != hand.end()) {
	    if(iter->rankString() == rank) {
	        _return.push_back(iter->getIndex());
	        iter = hand.erase(iter);
	    }
	    else
	        ++iter;
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// validateRequest
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool PlayerStore::validateRequest(const std::string& rank, const int16_t index) {
	bool valid = false;

	Card* card = indexToCard(index);

	// Does this card have the expected rank?
	if (card->rankString() == rank)
		valid = true;

	return valid;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// validateBook
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool PlayerStore::validateBook(const std::vector<int32_t> & indices) {
	bool valid = true;
	int count = 0;
	int rank;
	string rankString;
	// Make sure all cards have same rank
	for (auto &index : indices) {
		Card* card = indexToCard(index);
		if (count == 0) {
			rank = card->getRank();
			rankString = card->rankString();
		}
	else if (card->getRank() != rank) {
		valid = false;
		break;
	}
	count++;
	}

	if (count > 0) {
		cout << "Player has a book of cards with rank " << rank << endl;
	}

	// Make sure there are actually enough cards in book
	if (count < bookSize) {
		valid = false;
	}

	return valid;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Connect to another player
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool PlayerStore::connectToPlayer(const ServerAddress &pServerAddress) {
bool result = false;
// Make sure not already connected
auto it = connectedPlayers.find(pServerAddress);
// Not found, try to connect
if (it == connectedPlayers.end() || it->second->transport == NULL) {
  // Set up connection
  boost::shared_ptr<TTransport> socket(new TSocket(pServerAddress.hostname, pServerAddress.port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  boost::shared_ptr<TProtocol> mp(new TMultiplexedProtocol(protocol, "Player"));
  PlayerClient pClient(mp);
  try {
    // Connect to server
    transport->open();
    connectedPlayers[pServerAddress] = new PlayerClientTransport(pClient, transport);
    result = true;
  } catch (TException& tx) {
    string what(tx.what());
    printf("Failed to connect to player\n");
  }
} // end if
return result;
}


int16_t PlayerStore::waitForFinish() {
	while (!finished.load()) ;
	return winner;
}