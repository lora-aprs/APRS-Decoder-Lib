#ifndef MESSAGE_TYPE_H_
#define MESSAGE_TYPE_H_

#include <Arduino.h>

namespace aprs {
class MessageType {
public:
  enum Value : uint8_t {
    PositionWithoutTimestamp, // = and !
    // PositionWithTimestamp,    // @ and /
    // Status,                   // >
    // Query,                    // ?
    Message, // :
    // Weather,                  // _
    // Telemetry,                // T
    // CurrentMicEData,          // `
    // you can add more types ;)
    Error,
  };

  // cppcheck-suppress noExplicitConstructor
  MessageType(char type) {
    switch (type) {
    case '=':
    case '!':
      _value = PositionWithoutTimestamp;
      break;
    /*case '@':
    case '/':
      _value = PositionWithTimestamp;
      break;
    case '>':
      _value = Status;
      break;
    case '?':
      _value = Query;
      break;*/
    case ':':
      _value = Message;
      break;
    /*case '_':
      _value = Weather;
      break;
    case 'T':
      _value = Telemetry;
      break;
    case '`':
      _value = CurrentMicEData;
      break;*/
    default:
      _value = Error;
    }
  }
  // cppcheck-suppress noExplicitConstructor
  constexpr MessageType(Value aType) : _value(aType) {
  }

  constexpr bool operator==(MessageType a) const {
    return _value == a._value;
  }

  constexpr bool operator!=(MessageType a) const {
    return _value != a._value;
  }

  explicit operator bool() const {
    return _value != Error;
  }

  String toString() const {
    switch (_value) {
    case PositionWithoutTimestamp:
      return "Position Without Timestamp";
    /*case PositionWithTimestamp:
      return "Position With Timestamp";
    case Status:
      return "Status";
    case Query:
      return "Query";*/
    case Message:
      return "Message";
    /*case Weather:
      return "Weather";
    case Telemetry:
      return "Telemetry";
    case CurrentMicEData:
      return "Current Mic-E Data";*/
    default:
      return "Error";
    }
  }

  String toIdentifier() const {
    switch (_value) {
    case PositionWithoutTimestamp:
      return "=";
    /*case PositionWithTimestamp:
      return "@";
    case Status:
      return ">";
    case Query:
      return "?";*/
    case Message:
      return ":";
    /*case Weather:
      return "_";
    case Telemetry:
      return "T";
    case CurrentMicEData:
      return "`";*/
    default:
      return "E";
    }
  }

  Value getValue() const {
    return _value;
  }

private:
  Value _value;
};

} // namespace aprs

#endif
