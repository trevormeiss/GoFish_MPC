/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "gofish_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace gofish {


ServerAddress::~ServerAddress() throw() {
}


void ServerAddress::__set_port(const int16_t val) {
  this->port = val;
}

void ServerAddress::__set_hostname(const std::string& val) {
  this->hostname = val;
}

uint32_t ServerAddress::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->port);
          this->__isset.port = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->hostname);
          this->__isset.hostname = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ServerAddress::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ServerAddress");

  xfer += oprot->writeFieldBegin("port", ::apache::thrift::protocol::T_I16, 1);
  xfer += oprot->writeI16(this->port);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("hostname", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->hostname);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ServerAddress &a, ServerAddress &b) {
  using ::std::swap;
  swap(a.port, b.port);
  swap(a.hostname, b.hostname);
  swap(a.__isset, b.__isset);
}

ServerAddress::ServerAddress(const ServerAddress& other0) {
  port = other0.port;
  hostname = other0.hostname;
  __isset = other0.__isset;
}
ServerAddress& ServerAddress::operator=(const ServerAddress& other1) {
  port = other1.port;
  hostname = other1.hostname;
  __isset = other1.__isset;
  return *this;
}
void ServerAddress::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ServerAddress(";
  out << "port=" << to_string(port);
  out << ", " << "hostname=" << to_string(hostname);
  out << ")";
}


State::~State() throw() {
}


void State::__set_numCards(const int16_t val) {
  this->numCards = val;
}

void State::__set_numBooks(const int16_t val) {
  this->numBooks = val;
}

uint32_t State::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->numCards);
          this->__isset.numCards = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->numBooks);
          this->__isset.numBooks = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t State::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("State");

  xfer += oprot->writeFieldBegin("numCards", ::apache::thrift::protocol::T_I16, 1);
  xfer += oprot->writeI16(this->numCards);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("numBooks", ::apache::thrift::protocol::T_I16, 2);
  xfer += oprot->writeI16(this->numBooks);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(State &a, State &b) {
  using ::std::swap;
  swap(a.numCards, b.numCards);
  swap(a.numBooks, b.numBooks);
  swap(a.__isset, b.__isset);
}

State::State(const State& other2) {
  numCards = other2.numCards;
  numBooks = other2.numBooks;
  __isset = other2.__isset;
}
State& State::operator=(const State& other3) {
  numCards = other3.numCards;
  numBooks = other3.numBooks;
  __isset = other3.__isset;
  return *this;
}
void State::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "State(";
  out << "numCards=" << to_string(numCards);
  out << ", " << "numBooks=" << to_string(numBooks);
  out << ")";
}


InvalidOperation::~InvalidOperation() throw() {
}


void InvalidOperation::__set_whatOp(const int32_t val) {
  this->whatOp = val;
}

void InvalidOperation::__set_why(const std::string& val) {
  this->why = val;
}

uint32_t InvalidOperation::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->whatOp);
          this->__isset.whatOp = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->why);
          this->__isset.why = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t InvalidOperation::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("InvalidOperation");

  xfer += oprot->writeFieldBegin("whatOp", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->whatOp);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("why", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->why);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(InvalidOperation &a, InvalidOperation &b) {
  using ::std::swap;
  swap(a.whatOp, b.whatOp);
  swap(a.why, b.why);
  swap(a.__isset, b.__isset);
}

InvalidOperation::InvalidOperation(const InvalidOperation& other4) : TException() {
  whatOp = other4.whatOp;
  why = other4.why;
  __isset = other4.__isset;
}
InvalidOperation& InvalidOperation::operator=(const InvalidOperation& other5) {
  whatOp = other5.whatOp;
  why = other5.why;
  __isset = other5.__isset;
  return *this;
}
void InvalidOperation::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "InvalidOperation(";
  out << "whatOp=" << to_string(whatOp);
  out << ", " << "why=" << to_string(why);
  out << ")";
}

const char* InvalidOperation::what() const throw() {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: InvalidOperation";
  }
}

} // namespace