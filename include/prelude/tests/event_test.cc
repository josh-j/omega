#define BOOST_TEST_MAIN
#define BOOST_TEST_BUILD_INFO
#define BOOST_TEST_LOG_LEVEL all
#define BOOST_TEST_SHOW_PROGRESS yes
#define BOOST_TEST_MODULE event_test
#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "prelude/event.h"

using namespace std;

uint32_t g_num_event_calls = 0;

class TestClass {
public:
  PRELUDE_IMPLEMENT_EVENT(void(), EventTestStaticAssert);
  PRELUDE_IMPLEMENT_EVENT(bool(const std::string& str), EventTestStr);
  pre::Event<int(int a, int b, int c)> EventTestInts;


  void test_static_assert() {

  }

  bool test_str(const std::string& str) {
    std::vector<bool> results = event_manager_.CallSubscribersGetResults<bool, EventTestStr>(str);
    for (auto it : results) {
      cout << it << "\n";
    }
    return str.empty();
  }

  int test_ints(int a, int b, int c) {
    std::vector<int> results = EventTestInts.CallSubscribersGetResults(a, b, c);
    for (auto it : results) {
      cout << it << "\n";
    }
    return a + b + c;
  }

  pre::EventManager event_manager_;
};

bool whatWasSaid(const std::string& str) {
  ++g_num_event_calls;
  BOOST_REQUIRE_EQUAL(str, "hello world!");
  return false;
}

int whatWasAdded(int a, int b, int c) {
  ++g_num_event_calls;
  BOOST_REQUIRE_EQUAL(a, 1);
  BOOST_REQUIRE_EQUAL(b, 2);
  BOOST_REQUIRE_EQUAL(c, 3);
  return 100;
}

class TestTestClass {
 public:
  void Init(TestClass* tc) {
    tc->event_manager_.SubscribeMethod(TestClass::EventTestStr(), this,  &TestTestClass::whatWasSaid);
    tc->EventTestInts.SubscribeMethod(this, &TestTestClass::whatWasAdded);
    tc->test_str("This is TestTestClass, I have taken over!");
    tc->test_ints(9, 18, 27);
  }

  bool whatWasSaid(const std::string& str) {
    ++g_num_event_calls;
    BOOST_REQUIRE_EQUAL(str, "This is TestTestClass, I have taken over!");
    return false;
  }

  int whatWasAdded(int a, int b, int c) {
    ++g_num_event_calls;
    BOOST_REQUIRE_EQUAL(a, 9);
    BOOST_REQUIRE_EQUAL(b, 18);
    BOOST_REQUIRE_EQUAL(c, 27);
    return 500;
  }
};


BOOST_AUTO_TEST_CASE(TypicalUsage) {
  TestClass tc;
  tc.event_manager_.SubscribeFunction(TestClass::EventTestStr(), whatWasSaid);
  tc.EventTestInts.SubscribeFunction(whatWasAdded);
  tc.test_str("hello world!");
  tc.test_ints(1, 2, 3);

  tc.event_manager_.Dispose();
  tc.EventTestInts.Dispose();

  TestTestClass tcc;
  tcc.Init(&tc);

  BOOST_REQUIRE_EQUAL(g_num_event_calls, 4u);
}
