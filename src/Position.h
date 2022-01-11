#ifndef POSITION_H_
#define POSITION_H_

#include "Header.h"
#include <Arduino.h>

namespace aprs {

class Position : public Header {
public:
  Position();
  ~Position();

  char getTableId() const;
  void setTableId(const char tableId);

  char getCode() const;
  void setCode(const char code);

  double getLatitude() const;
  void   setLatitude(const double latitude);

  double getLongitude() const;
  void   setLongitude(const double longitude);

  String getText() const;
  void   setText(const String &text);

  unsigned int getSpeed() const;
  unsigned int getCourse() const;
  void         setSpeedAndCourse(const unsigned int knots, const unsigned int degrees);
  bool         isSpeedAndCourseSet() const;

  int  getAltitude() const;
  void setAltitude(const int feet);
  bool isAltitudeSet() const;

private:
  char         _tableId;
  char         _code;
  double       _latitude;
  double       _longitude;
  String       _text;
  unsigned int _speed;
  unsigned int _course;
  bool         _speedAndCourseSet;
  int          _altitude;
  bool         _altitudeSet;
};

class PositionFactory {
public:
  static void   generate(const String &textMsg, std::shared_ptr<Position> msg);
  static String generate(std::shared_ptr<Position> msg);

#ifndef UNIT_TEST
private:
#endif
  static double       NMEA2double(const String &nmea);
  static const String double2NMEA(const double coordinate, const int w);
  static const String double2NMEALat(const double coordinate);
  static const String double2NMEALong(const double coordinate);
};

} // namespace aprs

#endif
