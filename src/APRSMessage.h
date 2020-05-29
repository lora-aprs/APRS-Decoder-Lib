#ifndef APRS_HEADER_H_
#define APRS_HEADER_H_

#include <Arduino.h>

class APRSBody
{
public:
	APRSBody();
	virtual ~APRSBody();

	String getData() const;
	void setData(const String & data);

	virtual bool decode(const String & message);
	virtual String encode() const;
	virtual String toString() const;

private:
	String _data;
};

class APRSMessage
{
public:
	APRSMessage();
	APRSMessage(APRSMessage & other_msg);
	APRSMessage & operator=(APRSMessage & other_msg);
	virtual ~APRSMessage();

	String getSource() const;
	void setSource(const String & source);

	String getDestination() const;
	void setDestination(const String & destination);

	String getPath() const;
	void setPath(const String & path);

	APRSBody * const getAPRSBody();

	virtual bool decode(const String & message);
	virtual String encode() const;
	virtual String toString() const;

	/*
	enum class APRSMessageTypes
	{
		PositionWithoutTimestamp,	// = and !
		PositionWithTimestamp,		// @ and /
		Status,						// >
		Query,						// ?
		Message,					// :
		Weather,					// _
		Telemetry,					// T
		// you can add more types ;)
	};

	enum class APRSPositionTypes
	{
		WithMessage,	// = and @
		NoMessage,		// ! and /
	};*/

private:
	String _source;
	String _destination;
	String _path;
	APRSBody * const _body;
	//APRSMessageTypes _type;
};


#endif
