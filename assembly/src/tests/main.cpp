#include <iostream>

#include "./connections_manager.test.h"
#include "./ethernet.test.h"
#include "./ethernet_physical_parser.test.h"
#include "./event_listener.test.h"

int main() {
  EthernetPhysicalParserTest::main();
  ConnectionsManagerTest::main();
  EthernetTest::main();
  EventListenerTest::main();

  return 0;
}