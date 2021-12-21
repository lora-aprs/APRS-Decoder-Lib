#include "Message.h"
#include "MessageType.h"

#include <iomanip>
#include <sstream>

namespace aprs {

Message::Message() : Header(MessageType::Message), _id(0), _idSet(false) {
}

Message::~Message() {
}

String Message::getAddressee() const {
  return _addressee;
}

void Message::setAddressee(const String &addressee) {
  _addressee = addressee;
}

String Message::getText() const {
  return _text;
}

void Message::setText(const String &text) {
  _text = text;
}

int Message::getId() const {
  return _id;
}

void Message::setId(const int id) {
  _id    = id;
  _idSet = true;
}

bool Message::isIdSet() const {
  return _idSet;
}

void MessageFactory::generate(const String &textMsg, std::shared_ptr<Message> msg) {
  String addressee = textMsg.substring(0, 9);
  addressee.trim();
  msg->setAddressee(addressee);

  String text = textMsg.substring(10, textMsg.length());

  int idx = text.lastIndexOf('{');
  if (text.length() - idx == 4) {
    msg->setId(text.substring(idx + 1).toInt());
    text = text.substring(0, idx);
  }
  msg->setText(text);
}

String MessageFactory::generate(std::shared_ptr<Message> msg) {
  String addressee = msg->getAddressee();
  for (int i = addressee.length(); i < 9; i++) {
    addressee += ' ';
  }
  String id_str;
  if (msg->isIdSet()) {
    id_str = "{";
    String id(msg->getId());
    for (int i = id.length(); i < 3; i++) {
      id = '0' + id;
    }
    id_str += id;
  }
  return addressee + ":" + msg->getText() + id_str;
}

} // namespace aprs
