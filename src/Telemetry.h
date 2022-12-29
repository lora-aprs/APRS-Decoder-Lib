#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "Header.h"
#include <Arduino.h>

namespace aprs {

class Telemetry : public Header {
public:
  Telemetry();
  ~Telemetry();

private:
};

class TelemetryFactory {
public:
  static void   generate(const String &textMsg, std::shared_ptr<Telemetry> msg);
  static String generate(std::shared_ptr<Telemetry> msg);
};

} // namespace aprs

#endif
