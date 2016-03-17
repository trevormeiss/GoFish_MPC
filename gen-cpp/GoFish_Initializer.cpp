#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <fstream>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>
#include <future>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <boost/algorithm/string.hpp>

#include "Initializer.h"

#define DECK_SIZE 52

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace gofish;
using namespace std;

// A struct to hold a client and transport
struct InitializerClientTransport {
  InitializerClient client;
  boost::shared_ptr<TTransport> transport;

  InitializerClientTransport(InitializerClient aClient, boost::shared_ptr<TTransport> aTransport)  : client(aClient) {
    transport = aTransport;
  }
};

//**********************************************************
// error
//
// prints error and quits
//**********************************************************
void error(string msg)
{
  fprintf(stderr, "ERROR: %s\n\n", msg.c_str());
  exit(1);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// random number generator from Stroustrup:
// http://www.stroustrup.com/C++11FAQ.html#std-random
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int rand_int(int low, int high)
{
    static default_random_engine re (random_device{}());
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    return uid(re, Dist::param_type{low,high});
}

//**********************************************************
// generate_share
//**********************************************************
int generate_share(const int i, const int val, const vector<int> &coefficients, const int prime) {

    // f(i) = val + a1*i + a2*i^2 + ... + an*i^n mod p
    int evaluation = val;
    int j=1;
    for (auto &c : coefficients) {
        evaluation += c * pow(i,j);
        evaluation %= prime;
        j++;
    }

    return evaluation;
}

//**********************************************************
// Split string into vector
// http://stackoverflow.com/a/236803
//**********************************************************
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

//**********************************************************
// addNewPlayer
//  - connect to player
//  - add player to set of connected players
//  - tell all other players about new player
//**********************************************************
void addNewPlayer(ServerAddress &serverAddress, map<ServerAddress, InitializerClientTransport*> &connectedPlayers) {
  // Make sure not already connected
  auto it = connectedPlayers.find(serverAddress);

  if (it == connectedPlayers.end() || it->second->transport == NULL) {
    // Set up connection
    boost::shared_ptr<TTransport> socket(new TSocket(serverAddress.hostname, serverAddress.port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    boost::shared_ptr<TProtocol> mp(new TMultiplexedProtocol(protocol, "Initializer"));
    InitializerClient aPlayer(mp);
    try {
      // Connect to server
      transport->open();
      // Let this player know all the other players
      for (auto clientTransport : connectedPlayers) {
        aPlayer.connectToPlayer(clientTransport.first);
      }
      // Store transport and client
      connectedPlayers[serverAddress] = new InitializerClientTransport(aPlayer, transport);
      cout << "Connection to player successful\n\n";
    } catch (TException& tx) {
      string what(tx.what());
      cout << "Failed to connect to player at " << serverAddress.hostname << ":" << serverAddress.port << endl;
    }
    // Tell all players about this new player
    for (auto player : connectedPlayers) {
      player.second->client.connectToPlayer(serverAddress);
    }
  } // end if
  else cout << "Already connected to player at " << serverAddress.hostname << ":" << serverAddress.port << "\n\n";
}

//**********************************************************
// shuffleDeck
//**********************************************************
void shuffleDeck(map<ServerAddress, InitializerClientTransport*> &connectedPlayers, const int prime) {
	int numPlayers = connectedPlayers.size();

	// Create deck
	vector<int> deck;
	for (int i=1; i<=DECK_SIZE; i++) {
		deck.push_back(i);
	}

	// Shuffle Deck
	random_device rng;
	mt19937 urng(rng());
	shuffle(deck.begin(), deck.end(), urng);

	// Create shares for players
	vector<vector<int> > deckShares(numPlayers);
	vector<int> coefficients(numPlayers-1);

	// For all cards in the deck
	for (auto &card : deck) {
		// Each secret must have different random coefficients
		for (int i=0; i<coefficients.size(); i++) {
			coefficients[i] = rand_int(0, prime-1);
		}
		// Generate a share of this card for each player
		for (int i=0; i<numPlayers; i++) {
			deckShares[i].push_back(generate_share(i+1,card,coefficients,prime));
		}
	}

	// Send shares to players
	int i=0;
	for (auto player : connectedPlayers) {
		if (!player.second->client.sendDeckShares(deckShares[i])) {
			cout << "Unable to send shares of deck to Player " << i+1 << endl; 
		}
		i++;
	}
}

//**********************************************************
// drawHands
//**********************************************************
void drawHands(map<ServerAddress, InitializerClientTransport*> &connectedPlayers) {
	int numCards = 9 - connectedPlayers.size();
	int i=1;
	for (auto player : connectedPlayers) {
		if (!player.second->client.drawHand(numCards)) {
			cout << "Player " << i << " was unable to draw their hand\n";
		}
		i++;
	}
}

//**********************************************************
// startGame
//**********************************************************
void startGame(map<ServerAddress, InitializerClientTransport*> &connectedPlayers) {

  // Choose random player to start the game
  auto it = connectedPlayers.begin();
  int adv = rand_int(0, connectedPlayers.size()-1);
  advance(it, adv);

  int winner = it->second->client.startGame();
  cout << "Player " << winner << " won the game!\n";
}

//**********************************************************
// closeTransports
//**********************************************************
void closeTransports(map<ServerAddress, InitializerClientTransport*> &connectedPlayers) {
  for (auto server : connectedPlayers) {
    server.second->transport->close();
  }
  cout << "All transports closed\n";
}

//**********************************************************
// main
//
//**********************************************************
int main(int argc, char *argv[])
{
  string viableCommands = "\nViable commands are:\n"
    "c IP PORT:\tconnect to Player\n"
    "ls:\t\tlist connected Players\n"
    "p PRIME:\tset value of prime (default 127)\n"
    "s:\t\tstart Go Fish\n"
    "q:\t\tquit\n\n";

  cout << "~\nWelcome to Go Fish with MPC!\n~" << viableCommands;

  map<ServerAddress, InitializerClientTransport*> connectedPlayers;
  string input;
  int prime = 127;
  bool primeSet = false;
  bool quit = false;

  // Continue accepting commands until user quits
  while (!quit) {
    // Receive command from user
    printf("Enter command: ");
    getline(cin, input);

    vector<int> playerValues;
    vector<string> splitInput = split(input, ' ');

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Connect to Player
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (splitInput.size() >= 3 && boost::iequals(splitInput[0], "c")) {
      ServerAddress server;
      server.hostname = splitInput[1];
      server.port = stoi(splitInput[2]);

      addNewPlayer(server, connectedPlayers);
      // If the user first changed the prime and then added another player
      if (primeSet && !connectedPlayers[server]->client.setPrime(prime)) {
        cout << "Unable to set prime for player " << server.hostname << ":" << server.port << "\n";
      }
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // List connected players
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (boost::iequals(splitInput[0], "ls")) {
      int i=1;
      for (auto server : connectedPlayers) {
        cout << "Player " << i << " at " << server.first.hostname << ":" << server.first.port << "\n";
        i++;
      }
      cout << endl;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Set prime
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (splitInput.size() >= 2 && boost::iequals(splitInput[0], "p")) {
      primeSet = true;
      prime = stoi(splitInput[1]);
      cout << "Setting prime to " << prime << endl;
      for (auto player : connectedPlayers) {
        if (!player.second->client.setPrime(prime))
          cout << "Unable to set prime for player " << player.first.hostname << ":" << player.first.port << "\n";
      }
      cout << endl;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Start Go Fish
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (boost::iequals(splitInput[0], "s")) {
      if (prime <= connectedPlayers.size()) printf("Prime number must be greater than the number of players\n");
      else {
        // Go Fish has started, give each player their number
        int i=1;
        for (auto player : connectedPlayers) {
          // This will also let them know that no more players will be added
          if(!player.second->client.setPlayerNum(i))
            cout << "Failed to set player number for player " << i << endl;
          i++;
        }

        shuffleDeck(connectedPlayers, prime);

        drawHands(connectedPlayers);

        startGame(connectedPlayers);
        cout << viableCommands;
      }
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Quit
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else if (boost::iequals(splitInput[0], "q")) {
      cout << "Initializer quit\n";
      quit = true;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Command not recognized
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else {
      cout << "Command not recognized\n" << viableCommands;
    }
  } // end While(!quit)
  // Close all the transports
  closeTransports(connectedPlayers);
} // end main