#include <unity.h>
#include <APRS-Decoder.h>

void test1()
{
	String message = "OE5LFM-9>TXRT50,WIDE1-1,WIDE2-1,qAU,OE5XDO-10:`*(n!@,>/]\"3r}145.750MHz T123 -060Mandi=";
	APRSMessage msg;
	msg.decode(message);
	TEST_ASSERT_EQUAL_STRING("OE5LFM-9", msg.getSource().c_str());
	TEST_ASSERT_EQUAL_STRING("WIDE1-1,WIDE2-1,qAU,OE5XDO-10", msg.getPath().c_str());
	TEST_ASSERT_EQUAL_STRING("TXRT50", msg.getDestination().c_str());
	TEST_ASSERT_EQUAL_STRING("`*(n!@,>/]\"3r}145.750MHz T123 -060Mandi=", msg.getAPRSBody()->getData().c_str());
}

void test2()
{
	String message = "OE5ERN-9>APOTC1,WIDE1-1,WIDE2-2,qAR,OE5WWO:!/6&N;R*m\\> st/A=-00148 12.5V";
	APRSMessage msg;
	msg.decode(message);
	TEST_ASSERT_EQUAL_STRING("OE5ERN-9", msg.getSource().c_str());
	TEST_ASSERT_EQUAL_STRING("WIDE1-1,WIDE2-2,qAR,OE5WWO", msg.getPath().c_str());
	TEST_ASSERT_EQUAL_STRING("APOTC1", msg.getDestination().c_str());
	TEST_ASSERT_EQUAL_STRING("!/6&N;R*m\\> st/A=-00148 12.5V", msg.getAPRSBody()->getData().c_str());
}

void test3()
{
	String message = "OE3SZA-9>TX0P95,WIDE1-1,WIDE2-1,qAR,OE3XWJ-10:`*Hunf->/`\"7U}438.850MHz Toff -760_%";
	APRSMessage msg;
	msg.decode(message);
	TEST_ASSERT_EQUAL_STRING("OE3SZA-9", msg.getSource().c_str());
	TEST_ASSERT_EQUAL_STRING("WIDE1-1,WIDE2-1,qAR,OE3XWJ-10", msg.getPath().c_str());
	TEST_ASSERT_EQUAL_STRING("TX0P95", msg.getDestination().c_str());
	TEST_ASSERT_EQUAL_STRING("`*Hunf->/`\"7U}438.850MHz Toff -760_%", msg.getAPRSBody()->getData().c_str());
}

void test4()
{
	String message = "OE3MZC-9>APRS,qAS,OE3XOC-11:!/6,f)RPG%>G=QLoRa 18dBmW SNR=+10dB RSSI=-89db";
	APRSMessage msg;
	msg.decode(message);
	TEST_ASSERT_EQUAL_STRING("OE3MZC-9", msg.getSource().c_str());
	TEST_ASSERT_EQUAL_STRING("qAS,OE3XOC-11", msg.getPath().c_str());
	TEST_ASSERT_EQUAL_STRING("APRS", msg.getDestination().c_str());
	TEST_ASSERT_EQUAL_STRING("!/6,f)RPG%>G=QLoRa 18dBmW SNR=+10dB RSSI=-89db", msg.getAPRSBody()->getData().c_str());
}

#ifdef NATIVE
int main(int argc, char** argv)
#else
void setup()
#endif
{
	UNITY_BEGIN();
	RUN_TEST(test1);
	RUN_TEST(test2);
	RUN_TEST(test3);
	RUN_TEST(test4);
	UNITY_END();
}

void loop()
{
}
