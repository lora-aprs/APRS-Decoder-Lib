#include "Factory.h"

namespace aprs {

std::shared_ptr<Header> Factory::generate(const String &textMsg) {
  if (getType(textMsg) == MessageType::PositionWithoutTimestamp) {
    std::shared_ptr<Position> msg  = std::make_shared<Position>();
    String                    body = Factory::generateHeader(textMsg, msg);
    Factory::generate(body, msg);
    return msg;
  }
  if (getType(textMsg) == MessageType::Message) {
    std::shared_ptr<Message> msg  = std::make_shared<Message>();
    String                   body = Factory::generateHeader(textMsg, msg);
    Factory::generate(body, msg);
    return msg;
  }
  std::shared_ptr<NotKnownMessage> msg  = std::make_shared<NotKnownMessage>();
  String                           body = Factory::generateHeader(textMsg, msg);
  msg->setText(body);
  return msg;
}

String Factory::generate(std::shared_ptr<Position> msg) {
  return Factory::generateHeader(msg) + PositionFactory::generate(msg);
}

String Factory::generate(std::shared_ptr<Message> msg) {
  return Factory::generateHeader(msg) + MessageFactory::generate(msg);
}

MessageType Factory::getType(const String &textMsg) {
  int pos_end_header = textMsg.indexOf(':');
  return MessageType(textMsg[pos_end_header + 1]);
}

String Factory::generateHeader(const String &textMsg, std::shared_ptr<Header> msg) {
  int pos_src = textMsg.indexOf('>');
  msg->setSource(textMsg.substring(0, pos_src));

  int pos_dest = textMsg.indexOf(',');
  int pos_path = textMsg.indexOf(':');
  if (pos_dest != -1 && pos_dest < pos_path) {
    msg->setPath(PathFactory::generate(textMsg.substring(pos_dest + 1, pos_path)));
    msg->setDestination(textMsg.substring(pos_src + 1, pos_dest));
  } else {
    msg->setDestination(textMsg.substring(pos_src + 1, pos_path));
  }
  return textMsg.substring(pos_path + 2);
}

String Factory::generateHeader(std::shared_ptr<Header> msg) {
  return msg->getSource() + ">" + msg->getDestination() + msg->getPath().toAPRSString() + ":" + msg->getType().toIdentifier();
}

void Factory::generate(const String &textMsg, std::shared_ptr<Position> msg) {
  PositionFactory::generate(textMsg, msg);
}

void Factory::generate(const String &textMsg, std::shared_ptr<Message> msg) {
  MessageFactory::generate(textMsg, msg);
}

} // namespace aprs
