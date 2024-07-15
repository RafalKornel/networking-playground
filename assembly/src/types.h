#include <memory>

#ifndef TYPES_HPP
#define TYPES_HPP

using namespace std;

using DataType = uint8_t;
using Size = size_t;
using MacAddress = uint8_t[6];

struct Payload {
  Size size;
  shared_ptr<DataType> data;
};

// const size_t buffer_size = 1024;

// Interface for ILayer
class INetworkLayer {
public:
  virtual ~INetworkLayer() = default;
  virtual int send(Payload payload, Payload &out) = 0;
  virtual int receive(Payload payload, Payload &out) = 0;
};

// Interface for IComposer
class INetworkComposer {
public:
  virtual ~INetworkComposer() = default;
  virtual INetworkComposer &add(INetworkLayer *layer) = 0;
  virtual int propagateDown(Payload payload, Payload &out) = 0;
  virtual int propagateUp(Payload payload, Payload &out) = 0;
};

#endif // TYPES_HPP
