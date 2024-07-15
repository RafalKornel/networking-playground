#ifndef ETHERNET_H
#define ETHERNET_H

#include "../types.h"
#include "./connections_manager.h"
#include <bitset>

const int DATA_LINK_HEADER_SIZE = 18;
const int PHYSICAL_HEADER_SIZE = 20;

// const int DATA_LINK_MIN_PAYLOAD_SIZE = 46;
// const int DATA_LINK_MAX_PAYLOAD_SIZE = 1500;

// const int DATA_LINK_MIN_FRAME_SIZE =
//     DATA_LINK_HEADER_SIZE + DATA_LINK_MIN_PAYLOAD_SIZE;

// const int DATA_LINK_MAX_FRAME_SIZE =
//     DATA_LINK_HEADER_SIZE + DATA_LINK_MAX_PAYLOAD_SIZE;

// const int PHYSICAL_MIN_FRAME_SIZE =
//     PHYSICAL_HEADER_SIZE + DATA_LINK_MIN_FRAME_SIZE;
// const int PHYSICAL_MAX_FRAME_SIZE =
//     PHYSICAL_HEADER_SIZE + DATA_LINK_MAX_FRAME_SIZE;

const int ETHERNET_MIN_BUFFER_SIZE = 64;
const int ETHERNET_MAX_BUFFER_SIZE = 1522;

const int DATA_LINK_FRAME_SIZE =
    ETHERNET_MIN_BUFFER_SIZE + DATA_LINK_HEADER_SIZE;

const int PHYSICAL_FRAME_SIZE = DATA_LINK_FRAME_SIZE + PHYSICAL_HEADER_SIZE;

const int ETHERNET_BUFFER_SIZE = 1024;

static const bitset<64> PREAMBLE_WITH_SFD{"10101010"
                                          "10101010"
                                          "10101010"
                                          "10101010"
                                          "10101010"
                                          "10101010"
                                          "10101010"
                                          "10101011"};

static const int INTERPACKET_GAP_LENGTH = 12 * 8;

// THIS IS SOMEWHAT RANDOM, BECAUSE I DON'T KNOW HOW TO HANDLE END OF PACKET
// FOR NOW :)
static const bitset<INTERPACKET_GAP_LENGTH> END_OF_FRAME{"00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"
                                                         "00011000"};

struct EthernetDataLinkFrame {
  uint8_t destignation[6];
  uint8_t source[6];
  uint16_t type;
  uint8_t payload[ETHERNET_MIN_BUFFER_SIZE];
  uint8_t fcs[4];
};

struct EthernetPhysicalFrame {
  uint8_t preamble[7];
  uint8_t sfd;
  uint8_t payload[DATA_LINK_FRAME_SIZE];
  uint8_t ipg[12];
};

class Ethernet {
private:
  bitset<ETHERNET_BUFFER_SIZE> buffer;
  function<void(EthernetDataLinkFrame out_payload)> consume_callback;

public:
  Ethernet(const MacAddress &mA,
           function<void(EthernetDataLinkFrame out_payload)> consume_callback);

  const shared_ptr<ConnectionsManager<Ethernet>> connectionsManager;
  const MacAddress macAddress;

  int receive(Payload payload);
  int send(Payload payload);

  int connect(shared_ptr<Ethernet> other);
  int disconnect(shared_ptr<Ethernet> other);

  bool operator<(const Ethernet &other) const;

  int send_bit(bool signal, const MacAddress &mA) const;
  int receive_bit(bool signal);
};

#endif