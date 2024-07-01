#include "./ethernet_physical_parser.test.h"
#include "../blocks/ethernet.h"
#include "../blocks/parser.h"
#include "../types.h"
#include <iostream>
#include <memory>

using namespace std;

void printEthernetPhysicalFrame(const EthernetPhysicalFrame &frame) {
  // Print preamble
  cout << "Preamble: ";
  for (int i = 0; i < 7; ++i) {
    cout << hex << static_cast<int>(frame.preamble[i]) << " ";
  }
  cout << endl;

  // Print SFD (Start Frame Delimiter)
  cout << "SFD: " << hex << static_cast<int>(frame.sfd) << endl;

  // Print payload of DATA_LINK_FRAME_SIZE bytes
  cout << "Payload:" << endl;
  for (int i = 0; i < DATA_LINK_FRAME_SIZE; ++i) {
    cout << hex << static_cast<int>(frame.payload[i]) << " ";
    if ((i + 1) % 16 == 0) { // Print 16 bytes per line
      cout << endl;
    }
  }
  cout << endl;

  // Print inter-packet gap (IPG)
  cout << "IPG: ";
  for (int i = 0; i < 12; ++i) {
    cout << hex << static_cast<int>(frame.ipg[i]) << " ";
  }
  cout << endl;
}

int test_parsePhysicalFrame() {
  EthernetPhysicalFrame frame = {
      {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa},
      1,
      {0xcc, 0xcc, 0xcc, 0xcc},
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
  };

  // unique_ptr<uint8_t> buffer(new uint8_t[sizeof(EthernetPhysicalFrame)]);
  auto frame_size = sizeof(EthernetPhysicalFrame);

  auto buffer = shared_ptr<DataType>((DataType *)malloc(frame_size));

  memcpy(buffer.get(), &frame, frame_size);

  Payload payload = {frame_size, buffer};

  auto parsedFrame = parsePhysicalFrame(payload);

  auto result = memcmp(&frame, &parsedFrame, sizeof(EthernetDataLinkFrame));

  if (EthernetPhysicalParserTest::VERBOSE) {
    printEthernetPhysicalFrame(frame);

    cout << "Parsed: " << endl;

    printEthernetPhysicalFrame(parsedFrame);
  }

  return result;
}

int EthernetPhysicalParserTest::main() {
  cout << "Ethernet physical parser" << endl;

  auto result = test_parsePhysicalFrame();

  cout << "\tparsePhysicalFrame: " << (result ? "fail" : "pass") << endl;

  if (result) {
    return 1;
  }

  cout << endl;

  return 0;
}
