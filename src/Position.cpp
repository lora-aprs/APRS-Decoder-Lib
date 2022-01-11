#include "Position.h"
#include "MessageType.h"

#include <iomanip>
#include <sstream>

namespace aprs {

Position::Position() : Header(MessageType::PositionWithoutTimestamp), _tableId('/'), _code('-'), _latitude(0), _longitude(0), _speed(0), _course(0), _speedAndCourseSet(false), _altitude(0), _altitudeSet(false) {
}

Position::~Position() {
}

char Position::getTableId() const {
  return _tableId;
}

void Position::setTableId(const char tableId) {
  _tableId = tableId;
}

char Position::getCode() const {
  return _code;
}

void Position::setCode(const char code) {
  _code = code;
}

double Position::getLatitude() const {
  return _latitude;
}

void Position::setLatitude(const double latitude) {
  _latitude = std::max(-90.0, std::min(90.0, latitude));
}

double Position::getLongitude() const {
  return _longitude;
}

void Position::setLongitude(const double longitude) {
  _longitude = std::max(-180.0, std::min(180.0, longitude));
}

String Position::getText() const {
  return _text;
}

void Position::setText(const String &text) {
  _text = text;
}

unsigned int Position::getSpeed() const {
  return _speed;
}

unsigned int Position::getCourse() const {
  return _course;
}

void Position::setSpeedAndCourse(const unsigned int knots, const unsigned int degrees) {
  _speed  = std::max<unsigned int>(0, std::min<unsigned int>(999, knots));
  _course = std::max<unsigned int>(0, std::min<unsigned int>(360, degrees));
  if (_course == 0) {
    _course = 360;
  }
  _speedAndCourseSet = true;
}

bool Position::isSpeedAndCourseSet() const {
  return _speedAndCourseSet;
}

int Position::getAltitude() const {
  return _altitude;
}

void Position::setAltitude(const int feet) {
  _altitude    = std::max(-99999, std::min(999999, feet));
  _altitudeSet = true;
}

bool Position::isAltitudeSet() const {
  return _altitudeSet;
}

void PositionFactory::generate(const String &textMsg, std::shared_ptr<Position> msg) {
  String lat = textMsg.substring(0, 8);
  msg->setLatitude(NMEA2double(lat));

  msg->setTableId(textMsg[8]);

  String lon = textMsg.substring(9, 18);
  msg->setLongitude(NMEA2double(lon));

  msg->setCode(textMsg[18]);

  msg->setText(textMsg.substring(19));
}

String PositionFactory::generate(std::shared_ptr<Position> msg) {
  std::stringstream stream;
  stream << double2NMEALat(msg->getLatitude()).c_str();
  stream << msg->getTableId();
  stream << double2NMEALong(msg->getLongitude()).c_str();
  stream << msg->getCode();
  if (msg->isSpeedAndCourseSet()) {
    stream << std::setfill('0') << std::setw(3) << msg->getCourse();
    stream << "/";
    stream << std::setfill('0') << std::setw(3) << msg->getSpeed();
  }
  if (msg->isAltitudeSet()) {
    stream << "/A=" << std::internal << std::setfill('0') << std::setw(6) << msg->getAltitude();
  }
  stream << msg->getText().c_str();
  return String(stream.str().c_str());
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
