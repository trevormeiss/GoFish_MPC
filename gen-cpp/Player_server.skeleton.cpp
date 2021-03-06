// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Player.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::gofish;

class PlayerHandler : virtual public PlayerIf {
 public:
  PlayerHandler() {
    // Your initialization goes here
  }

  void request(std::vector<int16_t> & _return, const int16_t pNum, const std::string& rank, const int16_t index) {
    // Your implementation goes here
    printf("request\n");
  }

  void numCardsOfRankInHand(const int16_t numCards) {
    // Your implementation goes here
    printf("numCardsOfRankInHand\n");
  }

  int32_t cardDrawn(const int16_t index) {
    // Your implementation goes here
    printf("cardDrawn\n");
  }

  int32_t getDeckShare(const int16_t index) {
    // Your implementation goes here
    printf("getDeckShare\n");
  }

  void startTurn(State& _return, const int16_t pNum) {
    // Your implementation goes here
    printf("startTurn\n");
  }

  void yourTurn() {
    // Your implementation goes here
    printf("yourTurn\n");
  }

  bool bookAcquired(const std::vector<int32_t> & indices) {
    // Your implementation goes here
    printf("bookAcquired\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<PlayerHandler> handler(new PlayerHandler());
  shared_ptr<TProcessor> processor(new PlayerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

