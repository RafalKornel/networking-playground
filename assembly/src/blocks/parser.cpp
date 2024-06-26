#include "../types.h"
#include "ethernet.h"
#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

EthernetPhysicalFrame parsePhysicalFrame(unique_ptr<uint8_t[]> buffer) {
  EthernetPhysicalFrame frame;

  memcpy(frame.preamble, buffer.get(), 7);
  frame.sfd = *(buffer.get() + 7);
  memcpy(frame.payload, buffer.get() + 8, DATA_LINK_FRAME_SIZE);
  memcpy(frame.ipg, buffer.get() + sizeof(EthernetPhysicalFrame) - 12, 12);

  return frame;
}

EthernetDataLinkFrame parseDataLinkFrame(unique_ptr<uint8_t[]> buffer,
                                         int length) {
  EthernetDataLinkFrame frame;

  memcpy(frame.destignation, buffer.get(), 6);
  memcpy(frame.source, buffer.get() + 6, 6);
  frame.type = *(buffer.get() + 12);
  memcpy(frame.payload, buffer.get() + 14, ETHERNET_BUFFER_SIZE);
  memcpy(frame.fcs, buffer.get() + sizeof(EthernetDataLinkFrame) - 4, 4);

  return frame;
}
