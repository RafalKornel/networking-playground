#include <memory>

#ifndef TYPES_HPP
#define TYPES_HPP

// Define DataType as a placeholder
using DataType = uint8_t *;
using Size = size_t;

struct Payload {
  Size size;
  DataType data;
};

// const size_t buffer_size = 1024;

// Interface for ILayer
class INetworkLayer {
public:
  virtual ~INetworkLayer() = default;
  virtual void send(Payload payload, Payload &out) = 0;
  virtual void receive(Payload payload, Payload &out) = 0;
};

// Interface for IComposer
class INetworkComposer {
public:
  virtual ~INetworkComposer() = default;
  virtual INetworkComposer &add(INetworkLayer* layer) = 0;
  virtual void propagateDown(Payload payload, Payload &out) = 0;
  virtual void propagateUp(Payload payload, Payload &out) = 0;
};

#endif // TYPES_HPP
