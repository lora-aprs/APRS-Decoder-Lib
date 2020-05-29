#include "APRSMessage.h"

APRSMessage::APRSMessage()
	: _body(new APRSBody())
{
}

APRSMessage::APRSMessage(APRSMessage & other_msg)
	: _source(other_msg.getSource()), _destination(other_msg.getDestination()), _path(other_msg.getPath()), _body(new APRSBody())
{
	_body->setData(other_msg.getAPRSBody()->getData());
}

APRSMessage & APRSMessage::operator=(APRSMessage & other_msg)
{
	if(this != &other_msg)
	{
		_source = other_msg.getSource();
		_destination = other_msg.getDestination();
		_path = other_msg.getPath();
		_body->setData(other_msg.getAPRSBody()->getData());
	}
	return *this;
}

APRSMessage::~APRSMessage()
{
	delete _body;
}

String APRSMessage::getSource() const
{
	return _source;
}

void APRSMessage::setSource(const String & source)
{
	_source = source;
}

String APRSMessage::getDestination() const
{
	return _destination;
}

void APRSMessage::setDestination(const String & destination)
{
	_destination = destination;
}

String APRSMessage::getPath() const
{
	return _path;
}

void APRSMessage::setPath(const String & path)
{
	_path = path;
}

APRSBody * const APRSMessage::getAPRSBody()
{
	return _body;
}

bool APRSMessage::decode(const String & message)
{
	int pos_src = message.indexOf('>');
	_source = message.substring(0, pos_src);
	int pos_dest = message.indexOf(',');
	_destination = message.substring(pos_src+1, pos_dest);
	int pos_path = message.indexOf(':');
	_path = message.substring(pos_dest+1, pos_path);
	_body->decode(message.substring(pos_path+1));
	return true;
}

String APRSMessage::encode() const
{
	String msg;
	msg = _source + ">" + _destination;
	if(!_path.isEmpty())
	{
		msg = msg + "," + _path;
	}
	msg = msg  + ":" + _body->encode() + "\n";
	return msg;
}

String APRSMessage::toString() const
{
	return "Source: " + _source + ", Destination: " + _destination + ", Path: " + _path + ", " + _body->toString();
}

/*
APRSMessageTypes APRSMessage::getAPRSMessageType(const String & message)
{
	int blub = message.indexOf(':');
	switch(message.charAt(blub + 1))
	{
		case '=':
		case '!':
			return APRSMessageTypes::PositionWithoutTimestamp;
		case '@':
		case '/':
			return APRSMessageTypes::PositionWithTimestamp;
		case '>':
			return APRSMessageTypes::Status;
		case '?':
			return APRSMessageTypes::Query;
		case ':':
			return APRSMessageTypes::Message;
		case '_':
			return APRSMessageTypes::Weather;
		case 'T':
			return APRSMessageTypes::Telemetry;
	}
	return APRSMessageTypes::Message;
}
*/


APRSBody::APRSBody()
{
}

APRSBody::~APRSBody()
{
}

String APRSBody::getData() const
{
	return _data;
}

void APRSBody::setData(const String & data)
{
	_data = data;
}

bool APRSBody::decode(const String & message)
{
	_data = message;
	return true;
}

String APRSBody::encode() const
{
	return _data;
}

String APRSBody::toString() const
{
	return "Data: " + _data;
}
