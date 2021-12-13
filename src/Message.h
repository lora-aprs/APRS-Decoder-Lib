#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <Arduino.h>
#include <list>

#include "MessageType.h"
#include "Path.h"

namespace aprs {

class Message {
public:
  explicit Message(MessageType type);
  virtual ~Message();

  String getSource() const;
  void   setSource(const String &source);

  String getDestination() const;
  void   setDestination(const String &destination);

  Path &getPath();
  void  setPath(const Path path);

  MessageType getType() const;

  virtual String toString() const;

private:
  String      _source;
  String      _destination;
  Path        _path;
  MessageType _type;
};

class NotKnownMessage : public Message {
public:
  NotKnownMessage();
  ~NotKnownMessage();

  String getText() const;
  void   setText(const String &text);

private:
  String _text;
};

} // namespace aprs

#endif
