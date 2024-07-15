#include "../blocks/ethernet.h"
#include "../blocks/parser.h"
#include "../utilities/utilities.h"
#include "./ethernet.test.h"
#include <iostream>

using namespace std;

int test_connect_disconnect() {

  auto printFrameLambda = [](EthernetDataLinkFrame frame) {
    std::cout << frame.destignation << frame.fcs << frame.payload
              << frame.source << frame.type << std::endl;
  };

  auto ethernet1 = shared_ptr<Ethernet>(
      new Ethernet({0xff, 0xaa, 0xbb, 0xcc, 0xdd, 0xee}, printFrameLambda));

  auto ethernet2 = shared_ptr<Ethernet>(
      new Ethernet({0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc}, printFrameLambda));

  ethernet1->connect(ethernet2);
  ethernet2->connect(ethernet1);

  auto isAConnectedToB =
      ethernet1->connectionsManager->has_connection(ethernet2) == 0;

  if (!isAConnectedToB) {
    return 1;
  }

  auto isBConnectedToA =
      ethernet2->connectionsManager->has_connection(ethernet1) == 0;

  if (!isBConnectedToA) {
    return 1;
  }

  return 0;
}

int test_send_receive() {
  EthernetDataLinkFrame received_frame;

  auto emptyLambda = [](EthernetDataLinkFrame frame) {};

  auto ethernet1 = shared_ptr<Ethernet>(
      new Ethernet({0xff, 0xaa, 0xbb, 0xcc, 0xdd, 0xee}, emptyLambda));

  auto ethernet2 = shared_ptr<Ethernet>(
      new Ethernet({0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc},
                   [&received_frame](EthernetDataLinkFrame frame) {
                     received_frame = frame;
                   }));

  ethernet1->connect(ethernet2);
  ethernet2->connect(ethernet1);

  EthernetDataLinkFrame expected_frame = {
      {0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc}, // Destination
      {0xff, 0xaa, 0xbb, 0xcc, 0xdd, 0xee}, // Source
      0x0800,                               // Type
      {
          0xcc,
          0xcc,
          0xcc,
          0xcc,
      },                       // Payload
      {0xdd, 0xdd, 0xdd, 0xdd} // FCS
  };

  auto payload = convertEthernetDataLinkFrameToPayload(expected_frame);

  ethernet1.get()->send(payload);

  if (EthernetTest::VERBOSE) {
    cout << "expected: " << endl;
    printEthernetDataLinkFrame(expected_frame);
    cout << "received: " << endl;
    printEthernetDataLinkFrame(received_frame);
  }

  if (!compareEthernetDataLinkFrame(expected_frame, received_frame)) {
    return 1;
  }

  return 0;
}

int EthernetTest::main() {
  cout << "Ethernet" << endl;

  auto result1 = test_connect_disconnect();
  cout << "\tconnect/disconnect: " << (result1 ? "fail" : "pass") << endl;

  auto result2 = test_send_receive();
  cout << "\tsend/receive: " << (result2 ? "fail" : "pass") << endl;

  if (result1 || result2) {
    return 1;
  }

  cout << endl;

  return 0;
}