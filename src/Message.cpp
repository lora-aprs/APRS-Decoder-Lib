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
  std::stringstream stream;
  stream << std::setw(9) << std::setfill(' ') << std::left << msg->getAddressee().c_str();
  stream << ':';
  stream << msg->getText().c_str();

  if (msg->isIdSet()) {
    stream << '{';
    stream << std::setw(3) << std::setfill('0') << std::right << msg->getId();
  }

  return String(stream.str().c_str());
}

} // namespace aprs
