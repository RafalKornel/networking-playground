#include "utilities.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream> // For std::stringstream
#include <string>

using namespace std;

void printBufferToConsole(Payload &payload) {
  cout << "Payload: \nSize: " << payload.size << " | ";

  for (int i = 0; i < payload.size; ++i) {
    auto a = payload.data;
    cout << hex << setw(2) << setfill('0') << (payload.data.get()[i]);
  }

  cout << endl;
}

string printMacAddress(const MacAddress address) {
  std::stringstream ss;

  ss << hex << setfill('0');

  for (int i = 0; i < 6; ++i) {
    ss << setw(2) << static_cast<int>(address[i]);
    if (i < 5)
      ss << ":";
  }
  ss << dec;

  return ss.str();
}
