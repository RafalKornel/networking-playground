#include "../types.h"
#include "ethernet.h"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

EthernetPhysicalFrame parsePhysicalFrame(Payload payload) {
  EthernetPhysicalFrame frame;

  memcpy(frame.preamble, payload.data.get(), 7);

  frame.sfd = *(payload.data.get() + 7);

  memcpy(frame.payload, payload.data.get() + 8, DATA_LINK_FRAME_SIZE);
  memcpy(frame.ipg, payload.data.get() + sizeof(EthernetPhysicalFrame) - 12,
         12);

  return frame;
}

EthernetDataLinkFrame parseDataLinkFrame(Payload payload) {
  EthernetDataLinkFrame frame;

  memcpy(frame.destignation, payload.data.get(), 6);
  memcpy(frame.source, payload.data.get() + 6, 6);
  frame.type = *(reinterpret_cast<uint16_t *>(payload.data.get() + 12));

  memcpy(frame.payload, payload.data.get() + 14, ETHERNET_MIN_BUFFER_SIZE);
  memcpy(frame.fcs, payload.data.get() + sizeof(EthernetDataLinkFrame) - 4, 4);

  return frame;
}

EthernetPhysicalFrame
createPhysicalFrame(const EthernetDataLinkFrame &dataLinkFrame) {
  EthernetPhysicalFrame physicalFrame;

  for (int i = 0; i < 7; ++i) {
    physicalFrame.preamble[i] = 0b10101010;
  }

  physicalFrame.sfd = 0b10101011;

  memcpy(physicalFrame.payload, &dataLinkFrame, sizeof(EthernetDataLinkFrame));

  for (int i = 0; i < 12; ++i) {
    physicalFrame.ipg[i] = 0b00011000;
  }

  return physicalFrame;
}

bool compareEthernetDataLinkFrame(const EthernetDataLinkFrame &frame1,
                                  const EthernetDataLinkFrame &frame2) {
  return (std::memcmp(frame1.destignation, frame2.destignation, 6) == 0) &&
         (std::memcmp(frame1.source, frame2.source, 6) == 0) &&
         (frame1.type == frame2.type) &&
         (std::memcmp(frame1.payload, frame2.payload,
                      ETHERNET_MIN_BUFFER_SIZE) == 0) &&
         (std::memcmp(frame1.fcs, frame2.fcs, 4) == 0);
}

bool compareEthernetPhysicalFrame(const EthernetPhysicalFrame &frame1,
                                  const EthernetPhysicalFrame &frame2) {
  return (std::memcmp(frame1.preamble, frame2.preamble, 7) == 0) &&
         (frame1.sfd == frame2.sfd) &&
         (std::memcmp(frame1.payload, frame2.payload, DATA_LINK_FRAME_SIZE) ==
          0) &&
         (std::memcmp(frame1.ipg, frame2.ipg, 12) == 0);
}

Payload convertEthernetDataLinkFrameToPayload(EthernetDataLinkFrame frame) {
  auto buffer =
      shared_ptr<DataType>((DataType *)malloc(sizeof(EthernetDataLinkFrame)));
  memcpy(buffer.get(), &frame, sizeof(EthernetDataLinkFrame));
  Payload payload = {sizeof(EthernetDataLinkFrame), buffer};

  return payload;
}

void printEthernetDataLinkFrame(const EthernetDataLinkFrame &frame) {
  cout << "Ethernet Data Link Frame:\n";

  cout << "  Destination: ";
  for (int i = 0; i < 6; ++i) {
    cout << hex << setw(2) << setfill('0')
         << static_cast<int>(frame.destignation[i]);
    if (i < 5)
      cout << ":";
  }
  cout << dec << "\n";

  cout << "  Source: ";
  for (int i = 0; i < 6; ++i) {
    cout << hex << setw(2) << setfill('0') << static_cast<int>(frame.source[i]);
    if (i < 5)
      cout << ":";
  }
  cout << dec << "\n";

  cout << "  Type: 0x" << hex << setw(4) << setfill('0') << frame.type << dec
       << "\n";

  cout << "  Payload: ";
  for (int i = 0; i < ETHERNET_MIN_BUFFER_SIZE; ++i) {
    cout << hex << setw(2) << setfill('0')
         << static_cast<int>(frame.payload[i]);
    if (i < ETHERNET_MIN_BUFFER_SIZE - 1)
      cout << " ";
  }
  cout << dec << "\n";

  cout << "  FCS: ";
  for (int i = 0; i < 4; ++i) {
    cout << hex << setw(2) << setfill('0') << static_cast<int>(frame.fcs[i]);
    if (i < 3)
      cout << " ";
  }
  cout << dec << "\n";
}

void printEthernetPhysicalFrame(const EthernetPhysicalFrame &frame) {
  cout << "Ethernet Physical Frame:\n";

  cout << "  Preamble: ";
  for (int i = 0; i < 7; ++i) {
    cout << hex << setw(2) << setfill('0')
         << static_cast<int>(frame.preamble[i]);
    if (i < 6)
      cout << ":";
  }
  cout << dec << "\n";

  cout << "  SFD: " << hex << setw(2) << setfill('0')
       << static_cast<int>(frame.sfd) << dec << "\n";

  cout << "  Payload: ";
  for (int i = 0; i < DATA_LINK_FRAME_SIZE; ++i) {
    cout << hex << setw(2) << setfill('0')
         << static_cast<int>(frame.payload[i]);
    if (i < DATA_LINK_FRAME_SIZE - 1)
      cout << " ";
  }
  cout << dec << "\n";

  cout << "  IPG: ";
  for (int i = 0; i < 12; ++i) {
    cout << hex << setw(2) << setfill('0') << static_cast<int>(frame.ipg[i]);
    if (i < 11)
      cout << " ";
  }
  cout << dec << "\n";
}
