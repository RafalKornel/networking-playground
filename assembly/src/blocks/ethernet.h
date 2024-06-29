#include "../types.h"
#include "./connections_manager.h"
#include <stdlib.h>

#ifndef ETHERNET_H
#define ETHERNET_H

const int ETHERNET_BUFFER_SIZE = 64;
const int DATA_LINK_HEADER_SIZE = 18;
const int DATA_LINK_FRAME_SIZE = ETHERNET_BUFFER_SIZE + DATA_LINK_HEADER_SIZE;
const int PHYSICAL_HEADER_SIZE = 20;
const int PHYSICAL_FRAME_SIZE = DATA_LINK_FRAME_SIZE + PHYSICAL_HEADER_SIZE;

struct EthernetDataLinkFrame {
  uint8_t destignation[6];
  uint8_t source[6];
  uint16_t type;
  uint8_t payload[ETHERNET_BUFFER_SIZE];
  uint8_t fcs[4];
};

struct EthernetPhysicalFrame {
  uint8_t preamble[7];
  uint8_t sfd;
  uint8_t payload[DATA_LINK_FRAME_SIZE];
  uint8_t ipg[12];
};

class Ethernet : public INetworkLayer {
public:
  Ethernet(const MacAddress &mA);

  const shared_ptr<ConnectionsManager<Ethernet>> connectionsManager;
  const MacAddress macAddress;

  int receive(Payload payload, Payload &out) override;
  int send(Payload payload, Payload &out) override;

  int connect(shared_ptr<Ethernet> other);
  int disconnect(shared_ptr<Ethernet> other);

  bool operator<(const Ethernet &other) const;
};

#endif