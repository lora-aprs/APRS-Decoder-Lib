#include <Factory.h>
#include <unity.h>

void PositionFactory_NMEA2double() {
  TEST_ASSERT_EQUAL_DOUBLE(12.56866666666666666667, aprs::PositionFactory::NMEA2double("1234.12N"));
  TEST_ASSERT_EQUAL_DOUBLE(123.752, aprs::PositionFactory::NMEA2double("12345.12E"));
  TEST_ASSERT_EQUAL_DOUBLE(12.752, aprs::PositionFactory::NMEA2double("01245.12E"));
  TEST_ASSERT_EQUAL_DOUBLE(-12.56866666666666666667, aprs::PositionFactory::NMEA2double("1234.12S"));
  TEST_ASSERT_EQUAL_DOUBLE(-123.752, aprs::PositionFactory::NMEA2double("12345.12W"));
  TEST_ASSERT_EQUAL_DOUBLE(-12.752, aprs::PositionFactory::NMEA2double("01245.12W"));
  TEST_ASSERT_EQUAL_DOUBLE(0, aprs::PositionFactory::NMEA2double("1234.12"));
  TEST_ASSERT_EQUAL_DOUBLE(0, aprs::PositionFactory::NMEA2double("12345.12"));
}

void PositionFactory_double2NMEA() {
  TEST_ASSERT_EQUAL_STRING("1234.12N", aprs::PositionFactory::double2NMEALat(12.56866666666666666667).c_str());
  TEST_ASSERT_EQUAL_STRING("12345.12E", aprs::PositionFactory::double2NMEALong(123.752).c_str());
  TEST_ASSERT_EQUAL_STRING("01245.12E", aprs::PositionFactory::double2NMEALong(12.752).c_str());
  TEST_ASSERT_EQUAL_STRING("1234.12S", aprs::PositionFactory::double2NMEALat(-12.56866666666666666667).c_str());
  TEST_ASSERT_EQUAL_STRING("12345.12W", aprs::PositionFactory::double2NMEALong(-123.752).c_str());
  TEST_ASSERT_EQUAL_STRING("01245.12W", aprs::PositionFactory::double2NMEALong(-12.752).c_str());
  TEST_ASSERT_EQUAL_STRING("", aprs::PositionFactory::double2NMEALat(91).c_str());
  TEST_ASSERT_EQUAL_STRING("", aprs::PositionFactory::double2NMEALat(-91).c_str());
  TEST_ASSERT_EQUAL_STRING("", aprs::PositionFactory::double2NMEALong(181).c_str());
  TEST_ASSERT_EQUAL_STRING("", aprs::PositionFactory::double2NMEALong(-181).c_str());
}

void FactoryNotKnown() {
  String                                 msg = "AB1CDE-10>APRS:AABCDE";
  std::shared_ptr<aprs::NotKnownMessage> pos = std::static_pointer_cast<aprs::NotKnownMessage>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(pos->getType() == aprs::MessageType::Error);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  TEST_ASSERT_EQUAL_STRING("ABCDE", pos->getText().c_str());
}

void FactoryPositionIn1() {
  String                          msg = "AB1CDE-10>APRS:=1234.12N/12345.12E-QTH von AB1CDE";
  std::shared_ptr<aprs::Position> pos = std::static_pointer_cast<aprs::Position>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(pos->getType() == aprs::MessageType::PositionWithoutTimestamp);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  TEST_ASSERT_EQUAL_DOUBLE(12.56866666666666666667, pos->getLatitude());
  TEST_ASSERT_EQUAL_DOUBLE(123.752, pos->getLongitude());
  TEST_ASSERT_EQUAL_STRING("QTH von AB1CDE", pos->getText().c_str());
}

void FactoryPositionIn2() {
  String                          msg = "AB1CDE-10>APRS,AB1CDE:=1234.12N/12345.12E-QTH von AB1CDE";
  std::shared_ptr<aprs::Position> pos = std::static_pointer_cast<aprs::Position>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(pos->getType() == aprs::MessageType::PositionWithoutTimestamp);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  for (auto &path : pos->getPath().get()) {
    TEST_ASSERT_EQUAL_STRING("AB1CDE", path->getName().c_str());
  }
  TEST_ASSERT_EQUAL_DOUBLE(12.56866666666666666667, pos->getLatitude());
  TEST_ASSERT_EQUAL_DOUBLE(123.752, pos->getLongitude());
  TEST_ASSERT_EQUAL_STRING("QTH von AB1CDE", pos->getText().c_str());
}

void FactoryPositionOut1() {
  std::shared_ptr<aprs::Position> pos = std::make_shared<aprs::Position>();
  pos->setSource("AB1CDE-10");
  pos->setDestination("APRS");
  pos->setLatitude(12.56866666666666666667);
  pos->setLongitude(123.752);
  pos->setText("QTH von AB1CDE");
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10>APRS:=1234.12N/12345.12E-QTH von AB1CDE", aprs::Factory::generate(pos).c_str());
}

void FactoryPositionOut2() {
  std::shared_ptr<aprs::Position> pos = std::make_shared<aprs::Position>();
  pos->setSource("AB1CDE-10");
  pos->setDestination("APRS");
  aprs::Path                          path;
  std::shared_ptr<aprs::IPathElement> test1 = std::make_shared<aprs::BasicPathElement>("AB1CDE");
  path.add(test1);
  pos->setPath(path);
  pos->setLatitude(12.56866666666666666667);
  pos->setLongitude(123.752);
  pos->setText("QTH von AB1CDE");
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10>APRS,AB1CDE:=1234.12N/12345.12E-QTH von AB1CDE", aprs::Factory::generate(pos).c_str());
}

void FactoryPositionOut3() {
  std::shared_ptr<aprs::Position> pos = std::make_shared<aprs::Position>();
  pos->setSource("AB1CDE-10");
  pos->setDestination("APRS");
  aprs::Path                          path;
  std::shared_ptr<aprs::IPathElement> test1 = std::make_shared<aprs::BasicPathElement>("AB1CDE");
  std::shared_ptr<aprs::IPathElement> test2 = std::make_shared<aprs::BasicPathElement>("CD2EGF", true);
  path.add(test1);
  path.add(test2);
  pos->setPath(path);
  pos->setLatitude(12.56866666666666666667);
  pos->setLongitude(123.752);
  pos->setText("QTH von AB1CDE");
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10>APRS,AB1CDE,CD2EGF*:=1234.12N/12345.12E-QTH von AB1CDE", aprs::Factory::generate(pos).c_str());
}

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  RUN_TEST(PositionFactory_NMEA2double);
  RUN_TEST(PositionFactory_double2NMEA);
  RUN_TEST(FactoryNotKnown);
  RUN_TEST(FactoryPositionIn1);
  RUN_TEST(FactoryPositionIn2);
  RUN_TEST(FactoryPositionOut1);
  RUN_TEST(FactoryPositionOut2);
  RUN_TEST(FactoryPositionOut3);
  UNITY_END();
}

void loop() {
}
