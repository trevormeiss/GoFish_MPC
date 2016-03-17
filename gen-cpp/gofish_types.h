/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef gofish_TYPES_H
#define gofish_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace gofish {

class ServerAddress;

class State;

class InvalidOperation;

typedef struct _ServerAddress__isset {
  _ServerAddress__isset() : port(false), hostname(false) {}
  bool port :1;
  bool hostname :1;
} _ServerAddress__isset;

class ServerAddress {
 public:

  ServerAddress(const ServerAddress&);
  ServerAddress& operator=(const ServerAddress&);
  ServerAddress() : port(0), hostname() {
  }

  virtual ~ServerAddress() throw();
  int16_t port;
  std::string hostname;

  _ServerAddress__isset __isset;

  void __set_port(const int16_t val);

  void __set_hostname(const std::string& val);

  bool operator == (const ServerAddress & rhs) const
  {
    if (!(port == rhs.port))
      return false;
    if (!(hostname == rhs.hostname))
      return false;
    return true;
  }
  bool operator != (const ServerAddress &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ServerAddress &rhs) const {
    return this->hostname < rhs.hostname ||
           (this->hostname == rhs.hostname && this->port < rhs.port);
  }

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ServerAddress &a, ServerAddress &b);

inline std::ostream& operator<<(std::ostream& out, const ServerAddress& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _State__isset {
  _State__isset() : numCards(false), numBooks(false) {}
  bool numCards :1;
  bool numBooks :1;
} _State__isset;

class State {
 public:

  State(const State&);
  State& operator=(const State&);
  State() : numCards(0), numBooks(0) {
  }

  virtual ~State() throw();
  int16_t numCards;
  int16_t numBooks;

  _State__isset __isset;

  void __set_numCards(const int16_t val);

  void __set_numBooks(const int16_t val);

  bool operator == (const State & rhs) const
  {
    if (!(numCards == rhs.numCards))
      return false;
    if (!(numBooks == rhs.numBooks))
      return false;
    return true;
  }
  bool operator != (const State &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const State & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(State &a, State &b);

inline std::ostream& operator<<(std::ostream& out, const State& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _InvalidOperation__isset {
  _InvalidOperation__isset() : whatOp(false), why(false) {}
  bool whatOp :1;
  bool why :1;
} _InvalidOperation__isset;

class InvalidOperation : public ::apache::thrift::TException {
 public:

  InvalidOperation(const InvalidOperation&);
  InvalidOperation& operator=(const InvalidOperation&);
  InvalidOperation() : whatOp(0), why() {
  }

  virtual ~InvalidOperation() throw();
  int32_t whatOp;
  std::string why;

  _InvalidOperation__isset __isset;

  void __set_whatOp(const int32_t val);

  void __set_why(const std::string& val);

  bool operator == (const InvalidOperation & rhs) const
  {
    if (!(whatOp == rhs.whatOp))
      return false;
    if (!(why == rhs.why))
      return false;
    return true;
  }
  bool operator != (const InvalidOperation &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const InvalidOperation & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(InvalidOperation &a, InvalidOperation &b);

inline std::ostream& operator<<(std::ostream& out, const InvalidOperation& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif