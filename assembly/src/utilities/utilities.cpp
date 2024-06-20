#include "utilities.h"
#include <iomanip>
#include <iostream>
#include <memory>

void printBufferToConsole(Payload &payload) {
  std::cout << "Payload: \nSize: " << payload.size << " | ";

  for (int i = 0; i < payload.size; ++i) {
    std::cout << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(payload.data[i]);
  }

  std::cout << std::endl;
}