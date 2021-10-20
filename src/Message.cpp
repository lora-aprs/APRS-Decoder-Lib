#include "Message.h"

namespace aprs {

Message::Message(MessageType type) : _type(type) {
}

Message::~Message() {
}

String Message::getSource() const {
  return _source;
}

void Message::setSource(const String &source) {
  _source = source;
}

String Message::getDestination() const {
  return _destination;
}

void Message::setDestination(const String &destination) {
  _destination = destination;
}

Path &Message::getPath() {
  return _path;
}

void Message::setPath(Path path) {
  _path = path;
}

MessageType Message::getType() const {
  return _type;
}

String Message::toString() const {
  return "Source: " + _source + ", Destination: " + _destination + ", Path: " + _path.toString() + ", Type: " + _type.toString(); // + ", " + toStringBody();
}

} // namespace aprs
