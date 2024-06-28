#include "connections_manager.h"
#include "../types.h"
#include "../utilities/utilities.h"
#include <algorithm>
#include <iostream>

using namespace std;

ConnectionsManager::ConnectionsManager(const MacAddress &mA)
    : macAddress{mA[0], mA[1], mA[2], mA[3], mA[4], mA[5]} {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    _connections[i] = nullptr;
  }
};

int ConnectionsManager::connect(shared_ptr<ConnectionsManager> other) {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    if (_connections[i] == nullptr) {
      _connections[i] = other;

      if (VERBOSE) {
        cout << "Connecting: " << printMacAddress(other.get()->macAddress)
             << " at socket: " << i << endl;
      }

      return 0;
    }
  }

  cout << "Max connections reached. Cannot add more." << endl;
  return 1;
};

int ConnectionsManager::connect_at_socket(shared_ptr<ConnectionsManager> other,
                                          int socket) {
  if (socket >= CONNECTIONS_POOL) {
    if (VERBOSE) {
      cout << "Socket out of bounds. Provided: " << socket
           << ", max allowed: " << CONNECTIONS_POOL << endl;
    }
    return 1;
  }

  auto current = _connections[socket].get();

  if (VERBOSE) {

    if (current != nullptr) {
      cout << "Overriding connection with address: "
           << printMacAddress(current->macAddress) << endl;
    } else {
      cout << "Connecting: " << printMacAddress(other.get()->macAddress)
           << " at socket: " << socket << endl;
    }
  }

  _connections[socket] = other;

  return 0;
}

int ConnectionsManager::disconnect_at_socket(int socket) {
  if (socket >= CONNECTIONS_POOL) {
    if (VERBOSE) {
      cout << "Socket out of bounds. Provided: " << socket
           << ", max allowed: " << CONNECTIONS_POOL << endl;
    }
    return 1;
  }

  auto current = _connections[socket].get();

  if (current == nullptr) {
    if (VERBOSE) {
      cout << "No connection in provided socket." << endl;
    }

    return 1;
  }

  if (VERBOSE) {
    cout << "Disconnecting connection at socket: " << socket << endl;
  }

  _connections[socket] = nullptr;

  return 0;
}

int ConnectionsManager::disconnect(shared_ptr<ConnectionsManager> other) {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {

    if (_connections[i].get()->macAddress == other.get()->macAddress) {
      _connections[i] = nullptr;

      if (VERBOSE) {
        cout << "Disconnecting: " << printMacAddress(other.get()->macAddress)
             << " from socket: " << i << endl;
      }

      return 0;
    }
  }

  if (VERBOSE) {
    cout << "Could not find connection. Is this entity connected?" << endl;
  }

  return 1;
};

shared_ptr<const ConnectionsManager>
ConnectionsManager::connection_at(int socket) const {
  if (socket >= CONNECTIONS_POOL) {
    if (VERBOSE) {
      cout << "Socket out of bounds. Provided: " << socket
           << ", max allowed: " << CONNECTIONS_POOL << endl;
    }

    return shared_ptr<const ConnectionsManager>();
  }

  return _connections[socket];
}

int ConnectionsManager::has_connection(const MacAddress address) const {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    auto currAddress = _connections[i].get()->macAddress;

    if (memcmp(&currAddress, &address, sizeof(MacAddress))) {
      return 0;
    }
  }

  return 1;
}

void ConnectionsManager::print_connections() {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    auto curr = _connections[i].get();

    cout << i << '\t' << curr << '\t'
         << (curr != nullptr ? printMacAddress(curr->macAddress) : "") << endl;
  }

  cout << endl;
}
