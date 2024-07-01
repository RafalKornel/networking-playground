#include "./event_listener.test.h"
#include "../utilities/event_listener.cpp"

#include <memory>

using namespace std;

int test_event_listener() {
  auto listener = shared_ptr<EventListener<int>>(new EventListener<int>());

  int value = 0;

  auto firstPrinter = [&value](int payload) { value += payload; };

  auto secondPrinter = [&value](int payload) { value += payload * 100; };

  listener.get()->addEventHandler(firstPrinter);
  listener.get()->addEventHandler(secondPrinter);

  listener.get()->dispatchEvent(10);

  if (value != 10 + 10 * 100) {
    cout << "Failed at dispatch event";

    return 1;
  }

  listener.get()->dispatchEvent(20);

  if (value != 1010 + 20 + 20 * 100) {
    cout << "Failed at dispatch event";

    return 1;
  }

  return 0;
}

int EventListenerTest::main() {
  cout << "Event listener" << endl;

  auto result = test_event_listener();

  cout << "\tevent listener: " << (result ? "fail" : "pass") << endl;

  if (result) {
    return 1;
  }

  cout << endl;
  return 0;
}