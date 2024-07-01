#include "./composer.h"

Composer &Composer::add(INetworkLayer *layer) {
  layers.push_back(layer);
  return *this;
}

int Composer::propagateDown(Payload payload, Payload &out) {
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

    previousPayload.size = currentPayload.size;
    previousPayload.data = currentPayload.data;
  }

  out.data = currentPayload.data;
  out.size = currentPayload.size;

  return 0;
}

int Composer::propagateUp(Payload payload, Payload &out) {
  if (VERBOSE) {
    std::cout << "Propagading up data: " << std::endl;
    printBufferToConsole(payload);
  }

  Payload previousPayload = {payload.size, payload.data};
  Payload currentPayload = {payload.size, payload.data};

  for (int i = 0; i < layers.size(); ++i) {
    layers[i]->receive_listener(previousPayload, currentPayload);

    if (currentPayload.data == nullptr)
      break;

    previousPayload.size = currentPayload.size;
    previousPayload.data = currentPayload.data;
  }

  out.data = currentPayload.data;
  out.size = currentPayload.size;

  return 0;
}
