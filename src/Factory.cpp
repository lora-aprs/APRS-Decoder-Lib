#include "Factory.h"

namespace aprs {

std::shared_ptr<Message> Factory::generate(const String &textMsg) {
  if (getType(textMsg) == MessageType::PositionWithoutTimestamp) {
    std::shared_ptr<Position> msg  = std::make_shared<Position>();
    String                    body = Factory::generateHeader(textMsg, msg);
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

MessageType Factory::getType(const String &textMsg) {
  int pos_end_header = textMsg.indexOf(':');
  return MessageType(textMsg[pos_end_header + 1]);
}

String Factory::generateHeader(const String &textMsg, std::shared_ptr<Message> msg) {
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

String Factory::generateHeader(std::shared_ptr<Message> msg) {
  return "";
}

void Factory::generate(const String &textMsg, std::shared_ptr<Position> msg) {
  PositionFactory::generate(textMsg, msg);
}

} // namespace aprs
