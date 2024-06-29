#include "ethernet.h"
#include "../types.h"
#include "./connections_manager.h"
#include <iostream>

using namespace std;

// template class ConnectionsManager<Ethernet>;

Ethernet::Ethernet(const MacAddress &mA)
    : macAddress{mA[0], mA[1], mA[2], mA[3], mA[4], mA[5]},
      connectionsManager(shared_ptr<ConnectionsManager<Ethernet>>(
          new ConnectionsManager<Ethernet>(shared_ptr<Ethernet>(this)))) {}

int Ethernet::receive(Payload payload, Payload &out) {
  out.size = payload.size + 1;

  DataType newData = (DataType)malloc(sizeof(uint8_t) * out.size);

  memcpy(newData, payload.data, payload.size);
  newData[out.size - 1] = 0x33;

  out.data = newData;

  return 0;
}

int Ethernet::send(Payload payload, Payload &out) {
  out.size = payload.size + 1;

  DataType newData = (DataType)malloc(sizeof(uint8_t) * out.size);

  memcpy(newData, payload.data, payload.size);
  newData[out.size - 1] = 0x22;

  out.data = newData;

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