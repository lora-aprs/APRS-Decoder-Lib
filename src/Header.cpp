#include "Header.h"

namespace aprs {

Header::Header(MessageType type) : _type(type) {
}

Header::~Header() {
}

String Header::getSource() const {
  return _source;
}

void Header::setSource(const String &source) {
  _source = source;
}

String Header::getDestination() const {
  return _destination;
}

void Header::setDestination(const String &destination) {
  _destination = destination;
}

Path &Header::getPath() {
  return _path;
}

void Header::setPath(const Path &path) {
  _path = path;
}

MessageType Header::getType() const {
  return _type;
}

String Header::toString() const {
  return "Source: " + _source + ", Destination: " + _destination + ", Path: " + _path.toString() + ", Type: " + _type.toString(); // + ", " + toStringBody();
}

NotKnownMessage::NotKnownMessage() : Header(MessageType::Error) {
}

NotKnownMessage::~NotKnownMessage() {
}

String NotKnownMessage::getText() const {
  return _text;
}

void NotKnownMessage::setText(const String &text) {
  _text = text;
}

} // namespace aprs
