#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

template <typename TPayload> class EventListener {
private:
  vector<function<void(TPayload)>> listeners;

public:
  void addEventHandler(function<void(TPayload payload)> handler);
  void dispatchEvent(TPayload payload);
};

template <typename TPayload>
void EventListener<TPayload>::addEventHandler(
    function<void(TPayload payload)> handler) {
  this->listeners.push_back(handler);
}

template <typename TPayload>
void EventListener<TPayload>::dispatchEvent(TPayload payload) {
  for (auto &handler : listeners) {
    handler(payload);
  }
}

struct Payload {
  int age;
};

int main() {
  auto manager = shared_ptr<EventListener<Payload>>(new EventListener<Payload>());

  auto firstPrinter = [](Payload payload) { cout << payload.age << endl; };

  auto name = "Rafal";

  auto secondPrinter = [&name](Payload payload) {
    cout << name << " " << payload.age << endl;
  };

  manager.get()->addEventHandler(firstPrinter);
  manager.get()->addEventHandler(secondPrinter);

  manager.get()->dispatchEvent({10});
  manager.get()->dispatchEvent({20});

  return 0;
}
