#include "types.hpp"
#include "utilities/utilities.h"
#include <iostream>
#include <memory>
#include <vector>

class Composer : public INetworkComposer {
private:
  std::vector<INetworkLayer *> layers;

  static const int VERBOSE = 0;

public:
  Composer &add(INetworkLayer *layer) override {
    layers.push_back(layer);
    return *this;
  }

  void propagateDown(Payload payload, Payload &out) override {
    if (VERBOSE) {
      std::cout << "Propagading down data: " << std::endl;

      printBufferToConsole(payload);
    }

    Payload previousPayload = {payload.size, payload.data};
    Payload currentPayload = {payload.size, payload.data};

    for (int i = layers.size() - 1; i >= 0; i--) {
      layers[i]->send(previousPayload, currentPayload);

      if (currentPayload.data == nullptr)
        break;

      free(previousPayload.data);

      previousPayload.size = currentPayload.size;
      previousPayload.data = currentPayload.data;
    }

    out.data = currentPayload.data;
    out.size = currentPayload.size;
  }

  void propagateUp(Payload payload, Payload &out) override {
    if (VERBOSE) {
      std::cout << "Propagading up data: " << std::endl;

      printBufferToConsole(payload);
    }

    Payload previousPayload = {payload.size, payload.data};
    Payload currentPayload = {payload.size, payload.data};

    for (int i = 0; i < layers.size(); ++i) {
      layers[i]->receive(previousPayload, currentPayload);

      if (currentPayload.data == nullptr)
        break;

      free(previousPayload.data);

      previousPayload.size = currentPayload.size;
      previousPayload.data = currentPayload.data;
    }

    out.data = currentPayload.data;
    out.size = currentPayload.size;
  }
};
