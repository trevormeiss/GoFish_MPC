#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/TTransportException.h>

#include "Card.hpp"
#include "Player.h"
#include <boost/make_shared.hpp>
#include <set>
#include <vector>
#include <queue>
#include <iostream>
#include <atomic>

using boost::shared_ptr;

using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

using namespace gofish;
using namespace std;

// A struct to hold a client and transport
//  - transport opens and closes communication
//  - methods are called on client
struct PlayerClientTransport {
	PlayerClient client;
	boost::shared_ptr<TTransport> transport;

	PlayerClientTransport(PlayerClient pClient, boost::shared_ptr<TTransport> pTransport)  : client(pClient) {
		transport = pTransport;
	}
};

//==========================================================
// PlayerStore
//==========================================================
class PlayerStore {
private:
	int playerNum;
	int prime;
	int activePlayer;
	int requestedPlayer;

	atomic<bool> finished;
	int winner;

	vector<int> deckShares;
	set<int> remainingCardIndices;
	multiset<Card> hand;
	int numBooks;
	int bookSize;

	int numPlayers;
	vector<int> receivedShares;
	vector<int> recomb_all;

	// Connected Players
	map<ServerAddress, PlayerClientTransport*> connectedPlayers;

	int fermatPow(int a, int b, int MOD);
	int modInverse(int a, int m);
	int delta(int i, int x, queue<int> players);
	vector<int> recombination_vector(queue<int> &players);
	int cardReconstruction();
	Card* indexToCard(const int index);
	set<string> ranksHeld();
	void bookFound(vector<Card*> &book);
	void checkForBook();
	void printHands();
	int inputPlayerNum();
	string inputRank();
	bool makeRequest();

public:
	PlayerStore();
	void lockPlayers();
	void setNum(const int16_t num);
	int16_t getNum();
	void setPrime(const int32_t p);
	void setActivePlayer(const int16_t pNum);
	void setDeckShares(const std::vector<int32_t> & pDeckShares);
	int getDeckShare(const int16_t index);
	void getState(State &_return);
	bool drawCard(bool &catchMake, string rank);
	int cardDrawn(const int16_t index);
	void beginTurn();
	void setReceivedShare(const int pNum, const int val);
	void receivedRequest(std::vector<int16_t> & _return, const int16_t pNum, const std::string& rank, const int16_t index);
	void numCardsReplied(const int16_t numCards);
	bool validateBook(const std::vector<int32_t> & indices);
	bool connectToPlayer(const ServerAddress &pServerAddress);
	int16_t waitForFinish();

};