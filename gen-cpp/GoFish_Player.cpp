#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/processor/TMultiplexedProcessor.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include <boost/make_shared.hpp>

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>

#include "Initializer.h"
#include "Player.h"
#include "PlayerStore.hpp"

using namespace apache::thrift;
using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using boost::shared_ptr;

using namespace gofish;
using namespace std;

//**********************************************************
// error
//
// logs errors and quits
//**********************************************************
void error(const string msg) {
  fprintf(stderr, "ERROR: %s\n", msg.c_str());
  exit(1);
}

//==========================================================
// Handlers
//==========================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// InitializerHandler
// handles calls from the admin
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class InitializerHandler : virtual public InitializerIf {
private:
  PlayerStore* thisPlayer;
 public:
  InitializerHandler(PlayerStore* playerStore) {
    thisPlayer = playerStore;
  }

  bool connectToPlayer(const ServerAddress& serverAddress) {
    cout << "Connecting to player at " << serverAddress.hostname << ":" << serverAddress.port << endl;
    return thisPlayer->connectToPlayer(serverAddress);
  }

  // Once a player number is set, no more players will be added
  bool setPlayerNum(const int16_t num) {
    thisPlayer->setNum(num);
    cout << "Player number set to " << num << endl;
    thisPlayer->lockPlayers();
    cout << "No more players will be added\n";
    return true;
  }

  bool setPrime(const int32_t prime) {
    cout << "Prime set to " << prime << endl;
    thisPlayer->setPrime(prime);
    return true;
  }

  bool sendDeckShares(const std::vector<int32_t> & deckShares) {
  	thisPlayer->setDeckShares(deckShares);
  	return true;
  }

  bool drawHand(const int16_t numCards) {
  	bool dummyBool;
	string dummyRank = "";
    for (int i=0; i<numCards; i++) {
    	if (!thisPlayer->drawCard(dummyBool, dummyRank))
    		cout << "Unable to draw card\n";
    }
    return true;
  }

  int16_t startGame() {
    thisPlayer->beginTurn();
    return thisPlayer->waitForFinish();
  }

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PlayerHandler
// handles calls from other players
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class PlayerHandler : virtual public PlayerIf {
private:
  PlayerStore* thisPlayer;
 public:
  PlayerHandler(PlayerStore* playerStore) {
    thisPlayer = playerStore;
  }

  void request(std::vector<int16_t> & _return, const std::string& rank, const int16_t index) {
    thisPlayer->receivedRequest(_return, rank, index);
  }

  bool validateRequest(const std::string& rank, const int16_t index) {
    return thisPlayer->validateRequest(rank, index);
  }

  int32_t cardDrawn(const int16_t index) {
    return thisPlayer->cardDrawn(index);
  }

  int32_t getDeckShare(const int16_t index) {
    return thisPlayer->getDeckShare(index);
  }

  void startTurn(State& _return, const int16_t pNum) {
  	thisPlayer->getState(_return);
  	thisPlayer->setActivePlayer(pNum);
  }

  void yourTurn() {
    thisPlayer->beginTurn();
    thisPlayer->setActivePlayer(thisPlayer->getNum());
  }

  bool bookAcquired(const std::vector<int32_t> & indices) {
    return thisPlayer->validateBook(indices);
  }

};

//**********************************************************
// checkArgs
//
// validates arguments
//**********************************************************
void checkArgs(int argc, char **argv, int &port) {
  if (argc < 2) {
    error("please use arguments: ./GoFish_Player PORT");
  }

  port = atoi(argv[1]);
  if (port < 2000 || port > 65535) {
    error("please use a port number between 2000 and 65535");
  }
}

//**********************************************************
// Main
//**********************************************************
int main(int argc, char *argv[]) {

  int port;
  PlayerStore* thisPlayer;

  // Make sure valid port
  checkArgs(argc, argv, port);

  thisPlayer = new PlayerStore();

  // Handlers
  boost::shared_ptr<InitializerHandler> admin_handler(new InitializerHandler(thisPlayer));
  boost::shared_ptr<PlayerHandler> player_handler(new PlayerHandler(thisPlayer));

  // Processors
  boost::shared_ptr<TMultiplexedProcessor> processor(new TMultiplexedProcessor());
  boost::shared_ptr<TProcessor> admin_processor(new InitializerProcessor(admin_handler));
  boost::shared_ptr<TProcessor> player_processor(new PlayerProcessor(player_handler));

  // Add all the services!!!
  processor->registerProcessor("Initializer", admin_processor);
  processor->registerProcessor("Player", player_processor);

  boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  boost::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  boost::shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(4);
  boost::shared_ptr<PosixThreadFactory> threadFactory = boost::shared_ptr<PosixThreadFactory> (new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();

  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);

  cout << "Player started, waiting for initializer..." << endl;
  server.serve();
  cout << "Done." << endl;
  return 0;
}