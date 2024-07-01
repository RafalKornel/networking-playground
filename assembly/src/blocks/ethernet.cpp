#include "ethernet.h"
#include "../types.h"
#include "../utilities/utilities.h"
#include "./connections_manager.h"
#include "./parser.h"
#include <bitset>
#include <iostream>
#include <memory>

using namespace std;

Ethernet::Ethernet(const MacAddress &mA)
    : macAddress{mA[0], mA[1], mA[2], mA[3], mA[4], mA[5]},
      connectionsManager(shared_ptr<ConnectionsManager<Ethernet>>(
          new ConnectionsManager<Ethernet>(shared_ptr<Ethernet>(this)))) {}

int Ethernet::receive_listener(Payload payload, Payload &out) {
  auto frame = parseDataLinkFrame(payload);

  // should this `out` parameter be changed?

  return 0;
}

// 1) parse payload into data link frame
// 2) parse physical frame
// 3) send raw bytes to destignation
int Ethernet::send(Payload payload, Payload &out) {
  auto frame = parseDataLinkFrame(payload);

  auto lambdaPredicate = [&frame](shared_ptr<Ethernet> e) {
    auto found =
        memcmp(e.get()->macAddress, frame.destignation, sizeof(MacAddress));

    return found == 1;
  };

  auto connection = connectionsManager.get()->get_connection(lambdaPredicate);

  if (connection.get() == nullptr) {
    return 1;
  }

  cout << connection.get() << endl;

  cout << printMacAddress(connection.get()->macAddress) << endl;

  auto bits_count = sizeof(frame) * 8;

  for (int i = 0; i < bits_count; i++) {
    // we should dispatch `send_bit` event here
  }

  return 0;
}

int Ethernet::connect(shared_ptr<Ethernet> other) {
  return connectionsManager.get()->connect(
      shared_ptr<ConnectionsManager<Ethernet>>(
          other.get()->connectionsManager));
}

int Ethernet::disconnect(shared_ptr<Ethernet> other) {
  return connectionsManager.get()->disconnect(
      shared_ptr<ConnectionsManager<Ethernet>>(
          other.get()->connectionsManager));
}

bool Ethernet::operator<(const Ethernet &other) const {
  return memcmp(macAddress, other.macAddress, sizeof(MacAddress)) < 0;
}

int Ethernet::receive_bit_listener(bool bit_value) {
  // register bit in the buffer

  buffer <<= 1;
  buffer |= bit_value;

  // check if we should start recording frame data

  bool isPreambleAndSFD =
      (buffer.to_ullong() & PREAMBLE_WITH_SFD.to_ullong()) ==
      PREAMBLE_WITH_SFD.to_ullong();

  if (isPreambleAndSFD) {
    buffer.reset();
    return 0;
  }

  // check if we should conjure a package

  bitset<ETHERNET_BUFFER_SIZE> interpacket_gap_mask;
  interpacket_gap_mask.set();
  interpacket_gap_mask >>= (INTERPACKET_GAP_LENGTH);

  if ((buffer & interpacket_gap_mask) == 0) {
    buffer >>= (INTERPACKET_GAP_LENGTH);

    buffer <<= ETHERNET_BUFFER_SIZE - DATA_LINK_FRAME_SIZE * 8;

    auto data = shared_ptr<DataType>(new uint8_t[DATA_LINK_FRAME_SIZE]);

    auto d = buffer.to_ullong();

    memcpy(data.get(), &d, DATA_LINK_FRAME_SIZE);

    Payload payload;
    payload.data = data;
    payload.size = DATA_LINK_FRAME_SIZE;

    // here we dispatch event to `receive_listener`
    // or call it directly?
  }

  return 0;
}

int Ethernet::send_bit(bool signal, const MacAddress &mA) const {
  // here we should dispatch event to `receive_bit_listener`
  return 0;
}
