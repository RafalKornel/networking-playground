#include "ethernet.h"
#include "../types.h"
#include <iostream>

using namespace std;

// void exampleFrame() {
//   EthernetDataLinkFrame dataLinkFrame = {{0xaa, 0xbb, 0xcc, 0xdd, 0xee,
//   0xff},
//                                          {0x11, 0x22, 0x33, 0x44, 0x55,
//                                          0x66}, 0x0806, {5, 5, 5, 5}};

//   uint8_t payload[DATA_LINK_FRAME_SIZE];
//   memcpy(&dataLinkFrame, payload, DATA_LINK_FRAME_SIZE);

//   EthernetPhysicalFrame frame = {
//       {1, 2, 3, 4, 5, 6, 7},
//       1,
//       {4, 4, 4, 4},
//       {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
//   };

//   std::cout << "Size of frame: " << sizeof(frame) << std::endl;
//   std::cout << "Size of dataLinkFrame: " << sizeof(frame.payload) <<
//   std::endl;

//   std::cout << frame.preamble << frame.sfd <<
//   frame.payload.destignation_address
//             << frame.payload.source_address << frame.payload.type <<
//             std::endl;
// }




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
