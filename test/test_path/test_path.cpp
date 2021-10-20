#include <Path.h>
#include <unity.h>

void test_BasicPathElement() {
  aprs::BasicPathElement elem("test1");
  TEST_ASSERT_EQUAL_STRING("test1", elem.getName().c_str());
  TEST_ASSERT_EQUAL(false, elem.getConsumed());
  elem.Consume();
  TEST_ASSERT_EQUAL(true, elem.getConsumed());
}

void test_BasicPathElement1() {
  aprs::Path                          path;
  std::shared_ptr<aprs::IPathElement> test1 = std::make_shared<aprs::BasicPathElement>("test1");
  std::shared_ptr<aprs::IPathElement> test2 = std::make_shared<aprs::BasicPathElement>("test2", true);
  path.add(test1);
  TEST_ASSERT_EQUAL(true, path.isExisting("test1"));
  TEST_ASSERT_EQUAL(false, path.isExisting("test11"));

  for (auto const pathElement : path.get()) {
    TEST_ASSERT_EQUAL_STRING("test1", pathElement->getName().c_str());
    TEST_ASSERT_EQUAL(false, pathElement->getConsumed());
  }

  path.setConsumed("test1");
  path.add(test2);
  for (auto const &pathElement : path.get()) {
    TEST_ASSERT_EQUAL(true, pathElement->getConsumed());
  }
  TEST_ASSERT_EQUAL(true, path.isExisting("test1"));
  TEST_ASSERT_EQUAL(true, path.isExisting("test2"));
}

void test_BasicPathElement2() {
  aprs::Path                          path;
  std::shared_ptr<aprs::IPathElement> test1 = std::make_shared<aprs::BasicPathElement>("test1");
  std::shared_ptr<aprs::IPathElement> test2 = std::make_shared<aprs::BasicPathElement>("test2");
  path.add(test1);
  path.add(test2);
  TEST_ASSERT_EQUAL_STRING("test1, test2", path.toString().c_str());
  path.setConsumed("test1");
  TEST_ASSERT_EQUAL_STRING("test1*, test2", path.toString().c_str());
}

void test_WidePathElement() {
  aprs::WidePathElement test1(3, 3);
  TEST_ASSERT_EQUAL(false, test1.getConsumed());
  TEST_ASSERT_EQUAL_STRING("WIDE3", test1.getName().c_str());
  TEST_ASSERT_EQUAL_STRING("WIDE3-3", test1.getPathName().c_str());

  test1.Consume();
  TEST_ASSERT_EQUAL(false, test1.getConsumed());
  TEST_ASSERT_EQUAL_STRING("WIDE3", test1.getName().c_str());
  TEST_ASSERT_EQUAL_STRING("WIDE3-2", test1.getPathName().c_str());

  test1.Consume();
  TEST_ASSERT_EQUAL(false, test1.getConsumed());
  TEST_ASSERT_EQUAL_STRING("WIDE3", test1.getName().c_str());
  TEST_ASSERT_EQUAL_STRING("WIDE3-1", test1.getPathName().c_str());

  test1.Consume();
  TEST_ASSERT_EQUAL(true, test1.getConsumed());
  TEST_ASSERT_EQUAL_STRING("WIDE3", test1.getName().c_str());
  TEST_ASSERT_EQUAL_STRING("WIDE3*", test1.getPathName().c_str());
}

void test_WidePathElement1() {
  aprs::Path                          path;
  std::shared_ptr<aprs::IPathElement> test1 = std::make_shared<aprs::BasicPathElement>("test1");
  std::shared_ptr<aprs::IPathElement> test2 = std::make_shared<aprs::BasicPathElement>("test2");
  std::shared_ptr<aprs::IPathElement> test3 = std::make_shared<aprs::WidePathElement>(3, 3);
  path.add(test1);
  path.add(test2);
  path.add(test3);
  TEST_ASSERT_EQUAL_STRING("test1, test2, WIDE3-3", path.toString().c_str());
  path.setConsumed("test1");
  TEST_ASSERT_EQUAL_STRING("test1*, test2, WIDE3-3", path.toString().c_str());
  path.setConsumed("WIDE3");
  TEST_ASSERT_EQUAL_STRING("test1*, test2, WIDE3-2", path.toString().c_str());
  path.setConsumed("WIDE3");
  path.setConsumed("WIDE3");
  TEST_ASSERT_EQUAL_STRING("test1*, test2, WIDE3*", path.toString().c_str());
}

void test_addNode() {
  aprs::Path                          path;
  std::shared_ptr<aprs::IPathElement> test1 = std::make_shared<aprs::BasicPathElement>("test1", true);
  std::shared_ptr<aprs::IPathElement> test2 = std::make_shared<aprs::BasicPathElement>("test2");
  std::shared_ptr<aprs::IPathElement> test3 = std::make_shared<aprs::BasicPathElement>("test3", true);
  path.addNode(test1);
  TEST_ASSERT_EQUAL_STRING("test1*", path.toString().c_str());
  path.add(test2);
  TEST_ASSERT_EQUAL_STRING("test1*, test2", path.toString().c_str());
  path.addNode(test3);
  TEST_ASSERT_EQUAL_STRING("test1*, test3*, test2", path.toString().c_str());
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
  RUN_TEST(test_addNode);
  UNITY_END();
}

void loop() {
}
