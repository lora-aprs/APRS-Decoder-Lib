#ifndef APRS_MESSAGE_TYPE_H_
#define APRS_MESSAGE_TYPE_H_

#include <Arduino.h>

class APRSMessageType
{
public:
	enum Value
	{
		PositionWithoutTimestamp,	// = and !
		PositionWithTimestamp,		// @ and /
		Status,						// >
		Query,						// ?
		Message,					// :
		Weather,					// _
		Telemetry,					// T
		// you can add more types ;)
		Error,
	};

	APRSMessageType() = default;
	// cppcheck-suppress noExplicitConstructor
	APRSMessageType(char type)
	{
		switch(type)
		{
		case '=':
		case '!':
			value = PositionWithoutTimestamp;
			break;
		case '@':
		case '/':
			value = PositionWithTimestamp;
			break;
		case '>':
			value = Status;
			break;
		case '?':
			value = Query;
			break;
		case ':':
			value = Message;
			break;
		case '_':
			value = Weather;
			break;
		case 'T':
			value = Telemetry;
			break;
		default:
			value = Error;
		}
	}
	// cppcheck-suppress noExplicitConstructor
	constexpr APRSMessageType(Value aType) : value(aType) { }
	constexpr bool operator==(APRSMessageType a) const { return value == a.value; }
	constexpr bool operator!=(APRSMessageType a) const { return value != a.value; }
	explicit operator bool() const { return value != Error; }

	String toString() const
	{
		switch (value)
		{
		case PositionWithoutTimestamp:
			return "Position Without Timestamp";
		case PositionWithTimestamp:
			return "Position With Timestamp";
		case Status:
			return "Status";
		case Query:
			return "Query";
		case Message:
			return "Message";
		case Weather:
			return "Weather";
		case Telemetry:
			return "Telemetry";
		default:
			return "Error";
		}
	}

private:
	Value value;
};



/*
APRSMessageTypes getAPRSMessageType(const char type_char) const;
String getAPRSMessageTypeName(const APRSMessageTypes type) const;

enum class APRSPositionTypes
{
	WithMessage,	// = and @
	NoMessage,		// ! and /
};*/

#endif
