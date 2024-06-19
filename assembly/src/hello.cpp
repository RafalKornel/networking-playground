#include <emscripten/bind.h>

using namespace emscripten;

class PingPong {
private:
  int count;

public:
  PingPong() { this->count = 0; }

  // Method to simulate a ping
  void Ping() { count++; }

  // Method to simulate a pong
  void Pong() { count++; }

  int getResult() const { return this->count; }
};

int add(int a, int b) { return a + b; }

EMSCRIPTEN_BINDINGS(my_function_example) {
  function("add", &add);

  class_<PingPong>("PingPong")
      .constructor()
      .function("Ping", &PingPong::Ping)
      .function("Pong", &PingPong::Pong)
      .property("getResult", &PingPong::getResult);
}
