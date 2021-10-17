#include <Path.h>
#include <unity.h>

void test_BasicPathElement() {
  aprs::BasicPathElement elem("test1");
  TEST_ASSERT_EQUAL_STRING(elem.getName().c_str(), "test1");
  TEST_ASSERT_EQUAL(elem.getConsumed(), false);
  elem.Consume();
  TEST_ASSERT_EQUAL(elem.getConsumed(), true);
}

void test_BasicPathElement1() {
  aprs::Path             path;
  aprs::BasicPathElement test1("test1");
  aprs::BasicPathElement test2("test2", true);
  path.add(&test1);
  TEST_ASSERT_EQUAL(path.isExisting("test1"), true);
  TEST_ASSERT_EQUAL(path.isExisting("test11"), false);

  for (auto const pathElement : path.get()) {
    TEST_ASSERT_EQUAL_STRING(pathElement->getName().c_str(), "test1");
    TEST_ASSERT_EQUAL(pathElement->getConsumed(), false);
  }

  path.setConsumed("test1");
  path.add(&test2);
  for (auto const &pathElement : path.get()) {
    TEST_ASSERT_EQUAL(pathElement->getConsumed(), true);
  }
  TEST_ASSERT_EQUAL(path.isExisting("test1"), true);
  TEST_ASSERT_EQUAL(path.isExisting("test2"), true);
}

void test_BasicPathElement2() {
  aprs::Path             path;
  aprs::BasicPathElement test1("test1");
  aprs::BasicPathElement test2("test2");
  path.add(&test1);
  path.add(&test2);
  TEST_ASSERT_EQUAL_STRING(path.toString().c_str(), "test1, test2");
  path.setConsumed("test1");
  TEST_ASSERT_EQUAL_STRING(path.toString().c_str(), "test1*, test2");
}

void test_WidePathElement() {
  aprs::WidePathElement test1(3, 3);
  TEST_ASSERT_EQUAL(test1.getConsumed(), false);
  TEST_ASSERT_EQUAL_STRING(test1.getName().c_str(), "WIDE3");
  TEST_ASSERT_EQUAL_STRING(test1.getPathName().c_str(), "WIDE3-3");

  test1.Consume();
  TEST_ASSERT_EQUAL(test1.getConsumed(), false);
  TEST_ASSERT_EQUAL_STRING(test1.getName().c_str(), "WIDE3");
  TEST_ASSERT_EQUAL_STRING(test1.getPathName().c_str(), "WIDE3-2");

  test1.Consume();
  TEST_ASSERT_EQUAL(test1.getConsumed(), false);
  TEST_ASSERT_EQUAL_STRING(test1.getName().c_str(), "WIDE3");
  TEST_ASSERT_EQUAL_STRING(test1.getPathName().c_str(), "WIDE3-1");

  test1.Consume();
  TEST_ASSERT_EQUAL(test1.getConsumed(), true);
  TEST_ASSERT_EQUAL_STRING(test1.getName().c_str(), "WIDE3");
  TEST_ASSERT_EQUAL_STRING(test1.getPathName().c_str(), "WIDE3*");
}

void test_WidePathElement1() {
  aprs::Path             path;
  aprs::BasicPathElement test1("test1");
  aprs::BasicPathElement test2("test2");
  aprs::WidePathElement  test3(3, 3);
  path.add(&test1);
  path.add(&test2);
  path.add(&test3);
  TEST_ASSERT_EQUAL_STRING(path.toString().c_str(), "test1, test2, WIDE3-3");
  path.setConsumed("test1");
  TEST_ASSERT_EQUAL_STRING(path.toString().c_str(), "test1*, test2, WIDE3-3");
  path.setConsumed("WIDE3");
  TEST_ASSERT_EQUAL_STRING(path.toString().c_str(), "test1*, test2, WIDE3-2");
  path.setConsumed("WIDE3");
  path.setConsumed("WIDE3");
  TEST_ASSERT_EQUAL_STRING(path.toString().c_str(), "test1*, test2, WIDE3*");
}

#ifdef NATIVE
int main(int argc, char **argv)
#else
void setup()
#endif
{
  UNITY_BEGIN();
  RUN_TEST(test_BasicPathElement);
  RUN_TEST(test_BasicPathElement1);
  RUN_TEST(test_BasicPathElement2);
  RUN_TEST(test_WidePathElement);
  RUN_TEST(test_WidePathElement1);
  UNITY_END();
}

void loop() {
}
