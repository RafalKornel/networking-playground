#include "./connections_manager.test.h"
#include "./ethernet.test.h"
#include "./ethernet_physical_parser.test.h"
#include <iostream>

int main() {
  EthernetPhysicalParserTest::main();
  ConnectionsManagerTest::main();
  EthernetTest::main();

  return 0;
}