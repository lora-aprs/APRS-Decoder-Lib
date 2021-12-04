#ifndef POSITION_H_
#define POSITION_H_

#include "Message.h"
#include <Arduino.h>

namespace aprs {

class Position : public Message {
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
  static double NMEA2double(const String &nmea);
};

} // namespace aprs

#endif
