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
