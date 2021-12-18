#ifndef FACTORY_H_
#define FACTORY_H_

#include <memory>

#include "Position.h"

namespace aprs {

class Factory {
public:
  static std::shared_ptr<Header> generate(const String &textMsg);
  static String                  generate(std::shared_ptr<Position> msg);

  static MessageType getType(const String &textMsg);

private:
  static String generateHeader(const String &textMsg, std::shared_ptr<Header> msg);
  static String generateHeader(std::shared_ptr<Header> msg);

  static void generate(const String &textMsg, std::shared_ptr<Position> msg);
};

} // namespace aprs

#endif
