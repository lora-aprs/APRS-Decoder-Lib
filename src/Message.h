#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <Arduino.h>
#include <list>

#include "MessageType.h"
#include "Path.h"

namespace aprs {

class Message {
public:
  Message(MessageType type);
  virtual ~Message();

  String getSource() const;
  void   setSource(const String &source);

  String getDestination() const;
  void   setDestination(const String &destination);

  Path &getPath();
  void  setPath(Path path);

  MessageType getType() const;

  virtual String toString() const;

private:
  String      _source;
  String      _destination;
  Path        _path;
  MessageType _type;

  // virtual String toStringBody() const = 0;
};

} // namespace aprs

#endif
