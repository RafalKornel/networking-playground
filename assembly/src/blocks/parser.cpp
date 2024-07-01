#include "../types.h"
#include "ethernet.h"
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
  frame.type = *(payload.data.get() + 12);
  memcpy(frame.payload, payload.data.get() + 14, ETHERNET_MIN_BUFFER_SIZE);
  memcpy(frame.fcs, payload.data.get() + sizeof(EthernetDataLinkFrame) - 4, 4);

  return frame;
}
