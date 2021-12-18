#include <Factory.h>
#include <unity.h>

void FactoryNotKnown() {
  String                                 msg = "AB1CDE-10>APRS:AABCDE";
  std::shared_ptr<aprs::NotKnownMessage> pos = std::static_pointer_cast<aprs::NotKnownMessage>(aprs::Factory::generate(msg));
  TEST_ASSERT_TRUE(pos->getType() == aprs::MessageType::Error);
  TEST_ASSERT_EQUAL_STRING("AB1CDE-10", pos->getSource().c_str());
  TEST_ASSERT_EQUAL_STRING("APRS", pos->getDestination().c_str());
  TEST_ASSERT_EQUAL_STRING("ABCDE", pos->getText().c_str());
}

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  RUN_TEST(FactoryNotKnown);
  UNITY_END();
}

void loop() {
}
