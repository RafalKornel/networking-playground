#include <iostream>

#include "./connections_manager.test.h"
#include "./ethernet.test.h"
#include "./event_listener.test.h"
#include "./parser.test.h"

int main() {
  ParserTest::main();
  ConnectionsManagerTest::main();
  EthernetTest::main();
  EventListenerTest::main();

  return 0;
}