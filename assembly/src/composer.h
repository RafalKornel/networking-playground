#ifndef COMPOSER_H
#define COMPOSER_H

#include "types.h"
#include "utilities/utilities.h"
#include <iostream>
#include <memory>
#include <vector>

class Composer : public INetworkComposer {
private:
  std::vector<INetworkLayer *> layers;

  static const int VERBOSE = 0;

public:
  Composer &add(INetworkLayer *layer) override;

  int propagateDown(Payload payload, Payload &out) override;

  int propagateUp(Payload payload, Payload &out) override;
};

#endif // COMPOSER_H
