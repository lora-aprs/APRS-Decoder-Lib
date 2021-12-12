#include "Position.h"
#include "MessageType.h"

#include <iomanip>
#include <sstream>

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
  String lat = textMsg.substring(0, 8);
  msg->setLatitude(NMEA2double(lat));

  String lon = textMsg.substring(9, 18);
  msg->setLongitude(NMEA2double(lon));

  msg->setText(textMsg.substring(19));
}

String PositionFactory::generate(std::shared_ptr<Position> msg) {
  return "";
}

double PositionFactory::NMEA2double(const String &nmea) {
  if (nmea.length() != 8 && nmea.length() != 9) {
    return 0.0;
  }
  char direction = toupper(nmea[nmea.length() - 1]);
  if (direction != 'N' && direction != 'E' && direction != 'S' && direction != 'W') {
    return 0.0;
  }

  double _nmea = nmea.substring(0, nmea.length() - 1).toDouble();
  _nmea /= 100;
  int degrees = int(_nmea);
  _nmea -= degrees;
  _nmea *= 100;
  _nmea /= 60;
  _nmea += degrees;

  if (direction == 'S' || direction == 'W') {
    _nmea *= -1.0;
  }

  return _nmea;
}

const String PositionFactory::double2NMEALat(const double coordinate) {
  if (coordinate > 90.0 || coordinate < -90.0) {
    return String();
  }

  String coords = double2NMEA(coordinate, 2);

  if (coordinate > 0.0) {
    coords += 'N';
  } else {
    coords += 'S';
  }
  return coords;
}

const String PositionFactory::double2NMEALong(const double coordinate) {
  if (coordinate > 180.0 || coordinate < -180.0) {
    return String();
  }

  String coords = double2NMEA(coordinate, 3);

  if (coordinate > 0.0) {
    coords += 'E';
  } else {
    coords += 'W';
  }
  return coords;
}

const String PositionFactory::double2NMEA(const double coordinate, const int w) {
  double c     = fabs(coordinate);
  double after = c - std::floor(c);
  after *= 60;

  std::stringstream stream;
  stream << std::setfill('0') << std::setw(w) << std::floor(c);
  stream.precision(2);
  stream << std::setw(2) << std::fixed << after;

  return String(stream.str().c_str());
}

} // namespace aprs
