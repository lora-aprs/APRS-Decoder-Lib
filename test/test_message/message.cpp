#include <Factory.h>
#include <unity.h>

void MessageIn1() {
  String                         msg = "AB1CDE-10>APRS::WU2Z     :Testing";
  std::shared_ptr<aprs::Message> mes = std::static_pointer_cast<aprs::Message>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(mes->getType() == aprs::MessageType::Message);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", mes->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", mes->getDestination().c_str());
  TEST_ASSERT_EQUAL_STRING("WU2Z", mes->getAddressee().c_str());
  TEST_ASSERT_EQUAL_STRING("Testing", mes->getText().c_str());
  TEST_ASSERT_EQUAL_INT(0, mes->getId());
  TEST_ASSERT_FALSE(mes->isIdSet());
}

void MessageIn2() {
  String                         msg = "AB1CDE-10>APRS::EMAIL    :msproul@ap.org Test email";
  std::shared_ptr<aprs::Message> mes = std::static_pointer_cast<aprs::Message>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(mes->getType() == aprs::MessageType::Message);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", mes->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", mes->getDestination().c_str());
  TEST_ASSERT_EQUAL_STRING("EMAIL", mes->getAddressee().c_str());
  TEST_ASSERT_EQUAL_STRING("msproul@ap.org Test email", mes->getText().c_str());
  TEST_ASSERT_EQUAL_INT(0, mes->getId());
  TEST_ASSERT_FALSE(mes->isIdSet());
}

void MessageIn3() {
  String                         msg = "AB1CDE-10>APRS::WU2Z     :Testing{003";
  std::shared_ptr<aprs::Message> mes = std::static_pointer_cast<aprs::Message>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(mes->getType() == aprs::MessageType::Message);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", mes->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", mes->getDestination().c_str());
  TEST_ASSERT_EQUAL_STRING("WU2Z", mes->getAddressee().c_str());
  TEST_ASSERT_EQUAL_STRING("Testing", mes->getText().c_str());
  TEST_ASSERT_EQUAL_INT(3, mes->getId());
  TEST_ASSERT_TRUE(mes->isIdSet());
}

void MessageOut1() {
  std::shared_ptr<aprs::Message> mes = std::make_shared<aprs::Message>();
  mes->setSource("AB1CDE-10");
  mes->setDestination("APRS");
  mes->setAddressee("WU2Z");
  mes->setText("Testing");
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10>APRS::WU2Z     :Testing", aprs::Factory::generate(mes).c_str());
}

void MessageOut2() {
  std::shared_ptr<aprs::Message> mes = std::make_shared<aprs::Message>();
  mes->setSource("AB1CDE-10");
  mes->setDestination("APRS");
  mes->setAddressee("EMAIL");
  mes->setText("msproul@ap.org Test email");
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10>APRS::EMAIL    :msproul@ap.org Test email", aprs::Factory::generate(mes).c_str());
}

void MessageOut3() {
  std::shared_ptr<aprs::Message> mes = std::make_shared<aprs::Message>();
  mes->setSource("AB1CDE-10");
  mes->setDestination("APRS");
  mes->setAddressee("WU2Z");
  mes->setText("Testing");
  mes->setId(3);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10>APRS::WU2Z     :Testing{003", aprs::Factory::generate(mes).c_str());
}

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  RUN_TEST(MessageIn1);
  RUN_TEST(MessageIn2);
  RUN_TEST(MessageIn3);
  RUN_TEST(MessageOut1);
  RUN_TEST(MessageOut2);
  RUN_TEST(MessageOut3);
  UNITY_END();
}

void loop() {
}
