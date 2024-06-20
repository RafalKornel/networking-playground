#include "blocks/ethernet.cpp"
#include "composer.cpp"
#include "utilities/utilities.h"
#include <iostream>

// EMSCRIPTEN_KEEPALIVE
void test() {
  auto ethernet1 = new Ethernet({0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc});
  auto ethernet2 = new Ethernet({0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc});

  auto composer = new Composer();

  composer->add(ethernet1);
  composer->add(ethernet2);

  size_t payloadSize = 3;

  DataType data = (DataType)malloc(sizeof(uint8_t) * payloadSize);
  data[0] = 0xaa;
  data[1] = 0xbb;
  data[2] = 0xcc;

  Payload payload = {payloadSize, data};
  Payload result = {0, nullptr};

  printBufferToConsole(payload);

  composer->propagateDown(payload, result);

  printBufferToConsole(result);

  composer->propagateUp(result, payload);

  printBufferToConsole(payload);

  delete composer;
  delete ethernet1;
  delete ethernet2;
}

int main() {
  test();

  return 0;
}

// EMSCRIPTEN_BINDINGS(my_function_example) { function("test", &test); }