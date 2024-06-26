#include "../blocks/ethernet.h"
#include "../blocks/parser.h"
#include <iostream>
#include <memory>

using namespace std;

void printEthernetPhysicalFrame(const EthernetPhysicalFrame &frame) {
  // Print preamble
  std::cout << "Preamble: ";
  for (int i = 0; i < 7; ++i) {
    std::cout << std::hex << static_cast<int>(frame.preamble[i]) << " ";
  }
  std::cout << std::endl;

  // Print SFD (Start Frame Delimiter)
  std::cout << "SFD: " << std::hex << static_cast<int>(frame.sfd) << std::endl;

  // Print payload of DATA_LINK_FRAME_SIZE bytes
  std::cout << "Payload:" << std::endl;
  for (int i = 0; i < DATA_LINK_FRAME_SIZE; ++i) {
    std::cout << std::hex << static_cast<int>(frame.payload[i]) << " ";
    if ((i + 1) % 16 == 0) { // Print 16 bytes per line
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;

  // Print inter-packet gap (IPG)
  std::cout << "IPG: ";
  for (int i = 0; i < 12; ++i) {
    std::cout << std::hex << static_cast<int>(frame.ipg[i]) << " ";
  }
  std::cout << std::endl;
}

void test_parsePhysicalFrame() {
  EthernetPhysicalFrame frame = {
      {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa},
      1,
      {0xcc, 0xcc, 0xcc, 0xcc},
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
  };


  
  // std::unique_ptr<uint8_t[]> buffer(new
  // uint8_t[sizeof(EthernetPhysicalFrame)]);
  std::unique_ptr<uint8_t[]> buffer(new uint8_t[sizeof(EthernetPhysicalFrame)]);

  memcpy(buffer.get(), &frame, sizeof(EthernetPhysicalFrame));

  auto parsedFrame = parsePhysicalFrame(std::move(buffer));

  printEthernetPhysicalFrame(frame);

  cout << "Parsed: " << endl;

  printEthernetPhysicalFrame(parsedFrame);

  // cout << "Preamble: ";
  // for (int i = 0; i < sizeof(frame.preamble); i++) {
  //   cout << frame.preamble[i] << " | " << parsedFrame.preamble[i];
  // }
  // cout << endl;

  // cout << "sfd: " << frame.sfd << " | " << parsedFrame.sfd << endl;

  // cout << "payload: ";
  // for (int i = 0; i < sizeof(frame.payload); i++) {
  //   cout << frame.payload[i] << " | " << parsedFrame.payload[i];
  // }
  // cout << endl;

  // cout << "ipg: ";
  // for (int i = 0; i < sizeof(frame.ipg); i++) {
  //   cout << frame.ipg[i] << " | " << parsedFrame.ipg[i];
  // }
  // cout << endl;

  // cout << "Preamble: " << frame.preamble << " | " << sizeof(frame.preamble)
  //      << " | " << parsedFrame.preamble << " | " <<
  //      sizeof(parsedFrame.preamble)
  //      << endl;

  // cout << "sfd: " << frame.sfd << " | " << sizeof(frame.sfd) << " | "
  //      << parsedFrame.sfd << " | " << sizeof(parsedFrame.sfd) << endl;

  // cout << "payload: " << frame.payload << " | " << sizeof(frame.payload)
  //      << " | " << parsedFrame.payload << " | " <<
  //      sizeof(parsedFrame.payload)
  //      << endl;

  // cout << "ipg: " << frame.ipg << " | " << sizeof(frame.ipg) << " | "
  //      << parsedFrame.ipg << " | " << sizeof(parsedFrame.ipg) << endl;
}

int main() {
  test_parsePhysicalFrame();
  return 0;
}
