#include "../types.hpp"

using MacAddress = uint8_t[6];

class Ethernet : public INetworkLayer {
public:
  const MacAddress macAddress = {0, 0, 0, 0, 0, 0};

public:
  Ethernet(const MacAddress &mA)
      : macAddress{mA[0], mA[1], mA[2], mA[3], mA[4], mA[5]} {};

  void receive(Payload payload, Payload &out) override {

    out.size = payload.size + 1;

    DataType newData = (DataType)malloc(sizeof(uint8_t) * out.size);

    memcpy(newData, payload.data, payload.size);
    newData[out.size - 1] = 0x33;

    out.data = newData;
  }

  void send(Payload payload, Payload &out) override {
    out.size = payload.size + 1;

    DataType newData = (DataType)malloc(sizeof(uint8_t) * out.size);

    memcpy(newData, payload.data, payload.size);
    newData[out.size - 1] = 0x22;

    out.data = newData;
  }
};
