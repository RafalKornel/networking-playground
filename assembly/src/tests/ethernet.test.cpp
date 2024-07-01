#include "../blocks/ethernet.h"
#include "../utilities/utilities.h"
#include "./ethernet.test.h"
#include <iostream>

using namespace std;

int test_connect_disconnect() {
  auto ethernet1 =
      shared_ptr<Ethernet>(new Ethernet({0xff, 0xaa, 0xbb, 0xcc, 0xdd, 0xee}));

  auto ethernet2 =
      shared_ptr<Ethernet>(new Ethernet({0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc}));

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

  // TODO: write tests for sending / receiving
  {
    EthernetPhysicalFrame frame = {
        {0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc},
        1,
        {0xcc, 0xcc, 0xcc, 0xcc},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    };

    auto frame_size = sizeof(EthernetPhysicalFrame);

    auto buffer = shared_ptr<DataType>((DataType *)malloc(frame_size));

    memcpy(buffer.get(), &frame, frame_size);

    Payload payload = {frame_size, buffer};

    Payload out;

    ethernet1.get()->send(payload, out);
  }

  return 0;
}

int EthernetTest::main() {
  cout << "Ethernet" << endl;

  auto result = test_connect_disconnect();

  cout << "\tconnect/disconnect: " << (result ? "fail" : "pass") << endl;

  if (result) {
    return 1;
  }

  cout << endl;

  return 0;
}