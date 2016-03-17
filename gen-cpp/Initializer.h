/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Initializer_H
#define Initializer_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "gofish_types.h"

namespace gofish {

#ifdef _WIN32
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class InitializerIf {
 public:
  virtual ~InitializerIf() {}
  virtual bool connectToPlayer(const ServerAddress& serverAddress) = 0;
  virtual bool setPlayerNum(const int16_t num) = 0;
  virtual bool setPrime(const int32_t prime) = 0;
  virtual bool sendDeckShares(const std::vector<int32_t> & deckShares) = 0;
  virtual bool drawHand(const int16_t numCards) = 0;
  virtual int16_t startGame() = 0;
};

class InitializerIfFactory {
 public:
  typedef InitializerIf Handler;

  virtual ~InitializerIfFactory() {}

  virtual InitializerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(InitializerIf* /* handler */) = 0;
};

class InitializerIfSingletonFactory : virtual public InitializerIfFactory {
 public:
  InitializerIfSingletonFactory(const boost::shared_ptr<InitializerIf>& iface) : iface_(iface) {}
  virtual ~InitializerIfSingletonFactory() {}

  virtual InitializerIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(InitializerIf* /* handler */) {}

 protected:
  boost::shared_ptr<InitializerIf> iface_;
};

class InitializerNull : virtual public InitializerIf {
 public:
  virtual ~InitializerNull() {}
  bool connectToPlayer(const ServerAddress& /* serverAddress */) {
    bool _return = false;
    return _return;
  }
  bool setPlayerNum(const int16_t /* num */) {
    bool _return = false;
    return _return;
  }
  bool setPrime(const int32_t /* prime */) {
    bool _return = false;
    return _return;
  }
  bool sendDeckShares(const std::vector<int32_t> & /* deckShares */) {
    bool _return = false;
    return _return;
  }
  bool drawHand(const int16_t /* numCards */) {
    bool _return = false;
    return _return;
  }
  int16_t startGame() {
    int16_t _return = 0;
    return _return;
  }
};

typedef struct _Initializer_connectToPlayer_args__isset {
  _Initializer_connectToPlayer_args__isset() : serverAddress(false) {}
  bool serverAddress :1;
} _Initializer_connectToPlayer_args__isset;

class Initializer_connectToPlayer_args {
 public:

  Initializer_connectToPlayer_args(const Initializer_connectToPlayer_args&);
  Initializer_connectToPlayer_args& operator=(const Initializer_connectToPlayer_args&);
  Initializer_connectToPlayer_args() {
  }

  virtual ~Initializer_connectToPlayer_args() throw();
  ServerAddress serverAddress;

  _Initializer_connectToPlayer_args__isset __isset;

  void __set_serverAddress(const ServerAddress& val);

  bool operator == (const Initializer_connectToPlayer_args & rhs) const
  {
    if (!(serverAddress == rhs.serverAddress))
      return false;
    return true;
  }
  bool operator != (const Initializer_connectToPlayer_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_connectToPlayer_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Initializer_connectToPlayer_pargs {
 public:


  virtual ~Initializer_connectToPlayer_pargs() throw();
  const ServerAddress* serverAddress;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_connectToPlayer_result__isset {
  _Initializer_connectToPlayer_result__isset() : success(false) {}
  bool success :1;
} _Initializer_connectToPlayer_result__isset;

class Initializer_connectToPlayer_result {
 public:

  Initializer_connectToPlayer_result(const Initializer_connectToPlayer_result&);
  Initializer_connectToPlayer_result& operator=(const Initializer_connectToPlayer_result&);
  Initializer_connectToPlayer_result() : success(0) {
  }

  virtual ~Initializer_connectToPlayer_result() throw();
  bool success;

  _Initializer_connectToPlayer_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const Initializer_connectToPlayer_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Initializer_connectToPlayer_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_connectToPlayer_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_connectToPlayer_presult__isset {
  _Initializer_connectToPlayer_presult__isset() : success(false) {}
  bool success :1;
} _Initializer_connectToPlayer_presult__isset;

class Initializer_connectToPlayer_presult {
 public:


  virtual ~Initializer_connectToPlayer_presult() throw();
  bool* success;

  _Initializer_connectToPlayer_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Initializer_setPlayerNum_args__isset {
  _Initializer_setPlayerNum_args__isset() : num(false) {}
  bool num :1;
} _Initializer_setPlayerNum_args__isset;

class Initializer_setPlayerNum_args {
 public:

  Initializer_setPlayerNum_args(const Initializer_setPlayerNum_args&);
  Initializer_setPlayerNum_args& operator=(const Initializer_setPlayerNum_args&);
  Initializer_setPlayerNum_args() : num(0) {
  }

  virtual ~Initializer_setPlayerNum_args() throw();
  int16_t num;

  _Initializer_setPlayerNum_args__isset __isset;

  void __set_num(const int16_t val);

  bool operator == (const Initializer_setPlayerNum_args & rhs) const
  {
    if (!(num == rhs.num))
      return false;
    return true;
  }
  bool operator != (const Initializer_setPlayerNum_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_setPlayerNum_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Initializer_setPlayerNum_pargs {
 public:


  virtual ~Initializer_setPlayerNum_pargs() throw();
  const int16_t* num;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_setPlayerNum_result__isset {
  _Initializer_setPlayerNum_result__isset() : success(false) {}
  bool success :1;
} _Initializer_setPlayerNum_result__isset;

class Initializer_setPlayerNum_result {
 public:

  Initializer_setPlayerNum_result(const Initializer_setPlayerNum_result&);
  Initializer_setPlayerNum_result& operator=(const Initializer_setPlayerNum_result&);
  Initializer_setPlayerNum_result() : success(0) {
  }

  virtual ~Initializer_setPlayerNum_result() throw();
  bool success;

  _Initializer_setPlayerNum_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const Initializer_setPlayerNum_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Initializer_setPlayerNum_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_setPlayerNum_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_setPlayerNum_presult__isset {
  _Initializer_setPlayerNum_presult__isset() : success(false) {}
  bool success :1;
} _Initializer_setPlayerNum_presult__isset;

class Initializer_setPlayerNum_presult {
 public:


  virtual ~Initializer_setPlayerNum_presult() throw();
  bool* success;

  _Initializer_setPlayerNum_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Initializer_setPrime_args__isset {
  _Initializer_setPrime_args__isset() : prime(false) {}
  bool prime :1;
} _Initializer_setPrime_args__isset;

class Initializer_setPrime_args {
 public:

  Initializer_setPrime_args(const Initializer_setPrime_args&);
  Initializer_setPrime_args& operator=(const Initializer_setPrime_args&);
  Initializer_setPrime_args() : prime(0) {
  }

  virtual ~Initializer_setPrime_args() throw();
  int32_t prime;

  _Initializer_setPrime_args__isset __isset;

  void __set_prime(const int32_t val);

  bool operator == (const Initializer_setPrime_args & rhs) const
  {
    if (!(prime == rhs.prime))
      return false;
    return true;
  }
  bool operator != (const Initializer_setPrime_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_setPrime_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Initializer_setPrime_pargs {
 public:


  virtual ~Initializer_setPrime_pargs() throw();
  const int32_t* prime;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_setPrime_result__isset {
  _Initializer_setPrime_result__isset() : success(false) {}
  bool success :1;
} _Initializer_setPrime_result__isset;

class Initializer_setPrime_result {
 public:

  Initializer_setPrime_result(const Initializer_setPrime_result&);
  Initializer_setPrime_result& operator=(const Initializer_setPrime_result&);
  Initializer_setPrime_result() : success(0) {
  }

  virtual ~Initializer_setPrime_result() throw();
  bool success;

  _Initializer_setPrime_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const Initializer_setPrime_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Initializer_setPrime_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_setPrime_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_setPrime_presult__isset {
  _Initializer_setPrime_presult__isset() : success(false) {}
  bool success :1;
} _Initializer_setPrime_presult__isset;

class Initializer_setPrime_presult {
 public:


  virtual ~Initializer_setPrime_presult() throw();
  bool* success;

  _Initializer_setPrime_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Initializer_sendDeckShares_args__isset {
  _Initializer_sendDeckShares_args__isset() : deckShares(false) {}
  bool deckShares :1;
} _Initializer_sendDeckShares_args__isset;

class Initializer_sendDeckShares_args {
 public:

  Initializer_sendDeckShares_args(const Initializer_sendDeckShares_args&);
  Initializer_sendDeckShares_args& operator=(const Initializer_sendDeckShares_args&);
  Initializer_sendDeckShares_args() {
  }

  virtual ~Initializer_sendDeckShares_args() throw();
  std::vector<int32_t>  deckShares;

  _Initializer_sendDeckShares_args__isset __isset;

  void __set_deckShares(const std::vector<int32_t> & val);

  bool operator == (const Initializer_sendDeckShares_args & rhs) const
  {
    if (!(deckShares == rhs.deckShares))
      return false;
    return true;
  }
  bool operator != (const Initializer_sendDeckShares_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_sendDeckShares_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Initializer_sendDeckShares_pargs {
 public:


  virtual ~Initializer_sendDeckShares_pargs() throw();
  const std::vector<int32_t> * deckShares;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_sendDeckShares_result__isset {
  _Initializer_sendDeckShares_result__isset() : success(false) {}
  bool success :1;
} _Initializer_sendDeckShares_result__isset;

class Initializer_sendDeckShares_result {
 public:

  Initializer_sendDeckShares_result(const Initializer_sendDeckShares_result&);
  Initializer_sendDeckShares_result& operator=(const Initializer_sendDeckShares_result&);
  Initializer_sendDeckShares_result() : success(0) {
  }

  virtual ~Initializer_sendDeckShares_result() throw();
  bool success;

  _Initializer_sendDeckShares_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const Initializer_sendDeckShares_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Initializer_sendDeckShares_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_sendDeckShares_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_sendDeckShares_presult__isset {
  _Initializer_sendDeckShares_presult__isset() : success(false) {}
  bool success :1;
} _Initializer_sendDeckShares_presult__isset;

class Initializer_sendDeckShares_presult {
 public:


  virtual ~Initializer_sendDeckShares_presult() throw();
  bool* success;

  _Initializer_sendDeckShares_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _Initializer_drawHand_args__isset {
  _Initializer_drawHand_args__isset() : numCards(false) {}
  bool numCards :1;
} _Initializer_drawHand_args__isset;

class Initializer_drawHand_args {
 public:

  Initializer_drawHand_args(const Initializer_drawHand_args&);
  Initializer_drawHand_args& operator=(const Initializer_drawHand_args&);
  Initializer_drawHand_args() : numCards(0) {
  }

  virtual ~Initializer_drawHand_args() throw();
  int16_t numCards;

  _Initializer_drawHand_args__isset __isset;

  void __set_numCards(const int16_t val);

  bool operator == (const Initializer_drawHand_args & rhs) const
  {
    if (!(numCards == rhs.numCards))
      return false;
    return true;
  }
  bool operator != (const Initializer_drawHand_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_drawHand_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Initializer_drawHand_pargs {
 public:


  virtual ~Initializer_drawHand_pargs() throw();
  const int16_t* numCards;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_drawHand_result__isset {
  _Initializer_drawHand_result__isset() : success(false) {}
  bool success :1;
} _Initializer_drawHand_result__isset;

class Initializer_drawHand_result {
 public:

  Initializer_drawHand_result(const Initializer_drawHand_result&);
  Initializer_drawHand_result& operator=(const Initializer_drawHand_result&);
  Initializer_drawHand_result() : success(0) {
  }

  virtual ~Initializer_drawHand_result() throw();
  bool success;

  _Initializer_drawHand_result__isset __isset;

  void __set_success(const bool val);

  bool operator == (const Initializer_drawHand_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Initializer_drawHand_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_drawHand_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_drawHand_presult__isset {
  _Initializer_drawHand_presult__isset() : success(false) {}
  bool success :1;
} _Initializer_drawHand_presult__isset;

class Initializer_drawHand_presult {
 public:


  virtual ~Initializer_drawHand_presult() throw();
  bool* success;

  _Initializer_drawHand_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Initializer_startGame_args {
 public:

  Initializer_startGame_args(const Initializer_startGame_args&);
  Initializer_startGame_args& operator=(const Initializer_startGame_args&);
  Initializer_startGame_args() {
  }

  virtual ~Initializer_startGame_args() throw();

  bool operator == (const Initializer_startGame_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const Initializer_startGame_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_startGame_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Initializer_startGame_pargs {
 public:


  virtual ~Initializer_startGame_pargs() throw();

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_startGame_result__isset {
  _Initializer_startGame_result__isset() : success(false) {}
  bool success :1;
} _Initializer_startGame_result__isset;

class Initializer_startGame_result {
 public:

  Initializer_startGame_result(const Initializer_startGame_result&);
  Initializer_startGame_result& operator=(const Initializer_startGame_result&);
  Initializer_startGame_result() : success(0) {
  }

  virtual ~Initializer_startGame_result() throw();
  int16_t success;

  _Initializer_startGame_result__isset __isset;

  void __set_success(const int16_t val);

  bool operator == (const Initializer_startGame_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Initializer_startGame_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Initializer_startGame_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Initializer_startGame_presult__isset {
  _Initializer_startGame_presult__isset() : success(false) {}
  bool success :1;
} _Initializer_startGame_presult__isset;

class Initializer_startGame_presult {
 public:


  virtual ~Initializer_startGame_presult() throw();
  int16_t* success;

  _Initializer_startGame_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class InitializerClient : virtual public InitializerIf {
 public:
  InitializerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  InitializerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool connectToPlayer(const ServerAddress& serverAddress);
  void send_connectToPlayer(const ServerAddress& serverAddress);
  bool recv_connectToPlayer();
  bool setPlayerNum(const int16_t num);
  void send_setPlayerNum(const int16_t num);
  bool recv_setPlayerNum();
  bool setPrime(const int32_t prime);
  void send_setPrime(const int32_t prime);
  bool recv_setPrime();
  bool sendDeckShares(const std::vector<int32_t> & deckShares);
  void send_sendDeckShares(const std::vector<int32_t> & deckShares);
  bool recv_sendDeckShares();
  bool drawHand(const int16_t numCards);
  void send_drawHand(const int16_t numCards);
  bool recv_drawHand();
  int16_t startGame();
  void send_startGame();
  int16_t recv_startGame();
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class InitializerProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<InitializerIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (InitializerProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_connectToPlayer(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_setPlayerNum(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_setPrime(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_sendDeckShares(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_drawHand(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_startGame(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  InitializerProcessor(boost::shared_ptr<InitializerIf> iface) :
    iface_(iface) {
    processMap_["connectToPlayer"] = &InitializerProcessor::process_connectToPlayer;
    processMap_["setPlayerNum"] = &InitializerProcessor::process_setPlayerNum;
    processMap_["setPrime"] = &InitializerProcessor::process_setPrime;
    processMap_["sendDeckShares"] = &InitializerProcessor::process_sendDeckShares;
    processMap_["drawHand"] = &InitializerProcessor::process_drawHand;
    processMap_["startGame"] = &InitializerProcessor::process_startGame;
  }

  virtual ~InitializerProcessor() {}
};

class InitializerProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  InitializerProcessorFactory(const ::boost::shared_ptr< InitializerIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< InitializerIfFactory > handlerFactory_;
};

class InitializerMultiface : virtual public InitializerIf {
 public:
  InitializerMultiface(std::vector<boost::shared_ptr<InitializerIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~InitializerMultiface() {}
 protected:
  std::vector<boost::shared_ptr<InitializerIf> > ifaces_;
  InitializerMultiface() {}
  void add(boost::shared_ptr<InitializerIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  bool connectToPlayer(const ServerAddress& serverAddress) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->connectToPlayer(serverAddress);
    }
    return ifaces_[i]->connectToPlayer(serverAddress);
  }

  bool setPlayerNum(const int16_t num) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->setPlayerNum(num);
    }
    return ifaces_[i]->setPlayerNum(num);
  }

  bool setPrime(const int32_t prime) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->setPrime(prime);
    }
    return ifaces_[i]->setPrime(prime);
  }

  bool sendDeckShares(const std::vector<int32_t> & deckShares) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sendDeckShares(deckShares);
    }
    return ifaces_[i]->sendDeckShares(deckShares);
  }

  bool drawHand(const int16_t numCards) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->drawHand(numCards);
    }
    return ifaces_[i]->drawHand(numCards);
  }

  int16_t startGame() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->startGame();
    }
    return ifaces_[i]->startGame();
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class InitializerConcurrentClient : virtual public InitializerIf {
 public:
  InitializerConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  InitializerConcurrentClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  bool connectToPlayer(const ServerAddress& serverAddress);
  int32_t send_connectToPlayer(const ServerAddress& serverAddress);
  bool recv_connectToPlayer(const int32_t seqid);
  bool setPlayerNum(const int16_t num);
  int32_t send_setPlayerNum(const int16_t num);
  bool recv_setPlayerNum(const int32_t seqid);
  bool setPrime(const int32_t prime);
  int32_t send_setPrime(const int32_t prime);
  bool recv_setPrime(const int32_t seqid);
  bool sendDeckShares(const std::vector<int32_t> & deckShares);
  int32_t send_sendDeckShares(const std::vector<int32_t> & deckShares);
  bool recv_sendDeckShares(const int32_t seqid);
  bool drawHand(const int16_t numCards);
  int32_t send_drawHand(const int16_t numCards);
  bool recv_drawHand(const int32_t seqid);
  int16_t startGame();
  int32_t send_startGame();
  int16_t recv_startGame(const int32_t seqid);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _WIN32
  #pragma warning( pop )
#endif

} // namespace

#endif