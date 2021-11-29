#include "Position.h"
#include "MessageType.h"

namespace aprs {

Position::Position() : Message(MessageType::PositionWithoutTimestamp), _latitude(0), _longitude(0) {
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
  String lat = textMsg.substring(0, 7);
  msg->setLatitude(NMEA2double(lat));

  String lon = textMsg.substring(9, 17);
  msg->setLongitude(NMEA2double(lon));

  msg->setText(textMsg.substring(19));
}

String PositionFactory::generate(std::shared_ptr<Position> msg) {
  return "";
}

double PositionFactory::NMEA2double(const String &nmea) {
  double _nmea = nmea.toDouble();
  _nmea /= 100;
  int degrees = int(_nmea);
  _nmea -= degrees;
  _nmea *= 100;
  _nmea /= 60;
  _nmea += degrees;
  return _nmea;
}

} // namespace aprs
