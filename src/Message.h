#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Header.h"
#include <Arduino.h>

namespace aprs {

class Message : public Header {
public:
  Message();
  ~Message();

  String getAddressee() const;
  void   setAddressee(const String &addressee);

  String getText() const;
  void   setText(const String &text);

  int  getId() const;
  void setId(const int id);

  bool isIdSet() const;

private:
  String _addressee;
  String _text;
  int    _id;
  bool   _idSet;
};

class MessageFactory {
public:
  static void   generate(const String &textMsg, std::shared_ptr<Message> msg);
  static String generate(std::shared_ptr<Message> msg);
};

} // namespace aprs

#endif
