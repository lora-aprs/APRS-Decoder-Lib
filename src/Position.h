#ifndef POSITION_H_
#define POSITION_H_

#include "Message.h"
#include <Arduino.h>

namespace aprs {

class Position : public Header {
public:
  Position();
  ~Position();

  double getLatitude() const;
  void   setLatitude(const double latitude);

  double getLongitude() const;
  void   setLongitude(const double longitude);

  String getText() const;
  void   setText(const String &text);

private:
  double _latitude;
  double _longitude;
  String _text;
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
