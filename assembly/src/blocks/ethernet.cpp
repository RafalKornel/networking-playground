#include "ethernet.h"
#include "../types.h"
#include "../utilities/utilities.h"
#include "./connections_manager.h"
#include "./parser.h"
#include <bitset>
#include <iostream>
#include <memory>

using namespace std;

Ethernet::Ethernet(
    const MacAddress &mA,
    function<void(EthernetDataLinkFrame out_payload)> consume_callback)
    : macAddress{mA[0], mA[1], mA[2], mA[3], mA[4], mA[5]},
      connectionsManager(shared_ptr<ConnectionsManager<Ethernet>>(
          new ConnectionsManager<Ethernet>(shared_ptr<Ethernet>(this)))),
      consume_callback(consume_callback) {}

int Ethernet::receive(Payload payload) {
  auto data_link_frame = parseDataLinkFrame(payload);

  consume_callback(data_link_frame);

  return 0;
}

// 1) parse payload into data link frame
// 2) parse physical frame
// 3) send raw bytes to destignation
int Ethernet::send(Payload payload) {
  auto data_link_frame = parseDataLinkFrame(payload);

  auto connection = connectionsManager.get()->get_connection(
      [&data_link_frame](shared_ptr<Ethernet> other) {
        auto found = memcmp(other.get()->macAddress,
                            data_link_frame.destignation, sizeof(MacAddress));

        return found == 0;
      });

  if (connection.get() == nullptr) {
    cout << "could not find connection" << endl;
    return 1;
  }

  auto physical_frame = createPhysicalFrame(data_link_frame);

  auto bits_count = sizeof(physical_frame);

  unsigned char *bufferPtr = (unsigned char *)&physical_frame;

  for (int i = 0; i < sizeof(physical_frame); i++) {
    auto byte = bufferPtr[i];

    for (int j = 7; j >= 0; j--) {

      bool bit = (byte >> j) & 1;

      connection.get()->receive_bit(bit);
    }
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

int Ethernet::receive_bit(bool bit_value) {
  buffer <<= 1;
  buffer |= bit_value;

  if (buffer.none()) {
    return 0;
  }

  bitset<64> last64Bits;

  for (int i = 0; i < 64; i++) {
    last64Bits[i] = buffer[i];
  }

  bool isPreambleAndSFD =
      (last64Bits.to_ullong() & PREAMBLE_WITH_SFD.to_ullong()) ==
      PREAMBLE_WITH_SFD.to_ullong();

  if (isPreambleAndSFD) {
    buffer.reset();
    return 0;
  }

  bitset<INTERPACKET_GAP_LENGTH> interpacket_gap;

  bool isEndOfFrame = true;

  for (int i = 0; i < INTERPACKET_GAP_LENGTH; i++) {
    if (buffer[i] != END_OF_FRAME[i]) {
      isEndOfFrame = false;
      break;
    }
  }

  if (isEndOfFrame) {

    buffer >>= (INTERPACKET_GAP_LENGTH);

    const size_t DATA_LINK_BITS_COUNT = sizeof(EthernetDataLinkFrame) * 8;

    bitset<DATA_LINK_BITS_COUNT> flipped;

    for (int i = 0; i < DATA_LINK_BITS_COUNT; i++) {
      flipped[i] = buffer[DATA_LINK_BITS_COUNT - i - 1];
    }

    auto data =
        shared_ptr<DataType>(new uint8_t[sizeof(EthernetDataLinkFrame)]);

    for (size_t i = 0; i < DATA_LINK_FRAME_SIZE; i++) {
      data.get()[i] = 0;

      u_char byte = 0b00000000;

      for (size_t j = 0; j < 8; j++) {
        byte <<= 1;
        byte |= flipped[i * 8 + j];
      }

      data.get()[i] = byte;
    }

    Payload payload;
    payload.data = data;
    payload.size = DATA_LINK_FRAME_SIZE;

    receive(payload);
  }

  return 0;
}
