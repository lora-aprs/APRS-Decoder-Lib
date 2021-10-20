#include "Position.h"
#include "MessageType.h"

namespace aprs {

Position::Position() : Message(MessageType::PositionWithoutTimestamp) {
}

Position::~Position() {
}

double Position::getLatitude() const {
  return _latitude;
}

void Position::setLatitude(const double latitude) {
  _latitude = latitude;
}

double Position::getLongitude() const {
  return _longitude;
}

void Position::setLongitude(const double longitude) {
  _longitude = longitude;
}

String Position::getText() const {
  return _text;
}

void Position::setText(const String &text) {
  _text = text;
}

void PositionFactory::generate(const String &textMsg, std::shared_ptr<Position> msg) {
}

String PositionFactory::generate(std::shared_ptr<Position> msg) {
  return "";
}

} // namespace aprs
