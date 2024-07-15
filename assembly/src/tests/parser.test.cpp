#include "./parser.test.h"
#include "../blocks/ethernet.h"
#include "../blocks/parser.h"
#include "../types.h"
#include <iostream>
#include <memory>

using namespace std;

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

  if (ParserTest::VERBOSE) {
    printEthernetPhysicalFrame(frame);

    cout << "Parsed: " << endl;

    printEthernetPhysicalFrame(parsedFrame);
  }

  return result;
}

int test_parseDataLinkFrame() {
  EthernetDataLinkFrame frame = {
      {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa}, // Destination
      {0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb}, // Source
      0x0800,                               // Type
      {0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
       0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
       0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
       0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc}, // Payload
      {0xdd, 0xdd, 0xdd, 0xdd}                          // FCS
  };

  auto frame_size = sizeof(EthernetDataLinkFrame);

  auto buffer = shared_ptr<uint8_t>(
      reinterpret_cast<uint8_t *>(malloc(frame_size)), free);

  memcpy(buffer.get(), &frame, frame_size);

  Payload payload = {frame_size, buffer};

  auto parsedFrame = parseDataLinkFrame(payload);

  auto result = memcmp(&frame, &parsedFrame, sizeof(EthernetDataLinkFrame));

  if (ParserTest::VERBOSE) {
    printEthernetDataLinkFrame(frame);

    cout << "Parsed: " << endl;

    printEthernetDataLinkFrame(parsedFrame);
  }

  return result;
}

int ParserTest::main() {
  cout << "Ethernet physical parser" << endl;

  auto result1 = test_parsePhysicalFrame();
  cout << "\tparsePhysicalFrame: " << (result1 ? "fail" : "pass") << endl;

  auto result2 = test_parseDataLinkFrame();
  cout << "\tparseDataLinkFrame: " << (result2 ? "fail" : "pass") << endl;

  if (result1 || result2) {
    return 1;
  }

  cout << endl;

  return 0;
}
