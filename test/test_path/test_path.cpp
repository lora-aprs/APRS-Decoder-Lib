#include <APRS-Decoder.h>
#include <unity.h>

void test_PathElement() {
  aprs::PathElement elem("test1");
  TEST_ASSERT_EQUAL_STRING(elem.getName().c_str(), "test1");
  TEST_ASSERT_EQUAL(elem.getConsumed(), false);
  elem.setConsumed();
  TEST_ASSERT_EQUAL(elem.getConsumed(), true);
  elem.setConsumed(false);
  TEST_ASSERT_EQUAL(elem.getConsumed(), false);
}

void test_Path1() {
  aprs::Path path;
  path.add(aprs::PathElement("test1"));
  TEST_ASSERT_EQUAL(path.isExisting("test1"), true);
  TEST_ASSERT_EQUAL(path.isExisting("test11"), false);

  for (auto const &pathElement : path.get()) {
    TEST_ASSERT_EQUAL_STRING(pathElement.getName().c_str(), "test1");
    TEST_ASSERT_EQUAL(pathElement.getConsumed(), false);
  }

  path.setConsumed("test1");
  path.setConsumed("test11");
  for (auto const &pathElement : path.get()) {
    TEST_ASSERT_EQUAL(pathElement.getConsumed(), true);
  }
  TEST_ASSERT_EQUAL(path.isExisting("test1"), true);
  TEST_ASSERT_EQUAL(path.isExisting("test11"), true);
}

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  RUN_TEST(test_PathElement);
  RUN_TEST(test_Path1);
  UNITY_END();
}

void loop() {
}
