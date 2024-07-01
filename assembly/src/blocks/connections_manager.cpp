#include "./connections_manager.h"
#include "../types.h"
#include "../utilities/utilities.h"
#include "./ethernet.h"
#include "connections_manager.h"
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

template <typename TParent>
ConnectionsManager<TParent>::ConnectionsManager(shared_ptr<TParent> parent)
    : parent(parent) {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    _connections[i] = nullptr;
  }
};

template <typename TParent>
int ConnectionsManager<TParent>::connect(shared_ptr<ConnectionsManager> other) {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    if (_connections[i] == nullptr) {
      _connections[i] = other;

      if (VERBOSE) {
        cout << "Connecting: " << other.get() << " at socket: " << i << endl;
      }

      return 0;
    }
  }

  cout << "Max connections reached. Cannot add more." << endl;
  return 1;
};

template <typename TParent>
int ConnectionsManager<TParent>::connect_at_socket(
    shared_ptr<ConnectionsManager> other, int socket) {
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
      cout << "Overriding connection: " << current << endl;
    } else {
      cout << "Connecting: " << other.get() << " at socket: " << socket << endl;
    }
  }

  _connections[socket] = other;

  return 0;
}

template <typename TParent>
int ConnectionsManager<TParent>::disconnect_at_socket(int socket) {
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

template <typename TParent>
int ConnectionsManager<TParent>::disconnect(
    shared_ptr<ConnectionsManager> other) {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {

    if (_connections[i].get() == other.get()) {
      _connections[i] = nullptr;

      if (VERBOSE) {
        cout << "Disconnecting: " << other.get() << " from socket: " << i
             << endl;
      }

      return 0;
    }
  }

  if (VERBOSE) {
    cout << "Could not find connection. Is this entity connected?" << endl;
  }

  return 1;
};

template <typename TParent>
shared_ptr<TParent>
ConnectionsManager<TParent>::connection_at(int socket) const {
  if (socket >= CONNECTIONS_POOL) {
    if (VERBOSE) {
      cout << "Socket out of bounds. Provided: " << socket
           << ", max allowed: " << CONNECTIONS_POOL << endl;
    }

    return shared_ptr<TParent>(nullptr);
  }

  auto connection = _connections[socket];

  if (connection == nullptr || connection.get() == nullptr) {
    return shared_ptr<TParent>(nullptr);
  }

  if (VERBOSE) {
    cout << "Connection at socket " << socket << " : " << connection << endl;
  }

  return connection.get()->parent;
}

template <typename TParent>
int ConnectionsManager<TParent>::has_connection(
    shared_ptr<TParent> parent) const {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    auto currConnection = _connections[i].get();

    if (currConnection == nullptr) {
      continue;
    }

    auto currParent = currConnection->parent;

    if (currParent.get() == parent.get()) {
      return 0;
    }
  }

  return 1;
}

template <typename TParent>
shared_ptr<TParent> ConnectionsManager<TParent>::get_connection(
    function<bool(shared_ptr<TParent>)> predicate) const {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    auto currConnection = _connections[i].get();

    if (currConnection == nullptr) {
      continue;
    }

    shared_ptr<TParent> currParent = currConnection->parent;

    auto isResult = predicate(currParent);

    if (isResult) {
      return shared_ptr<TParent>(currParent);
    }
  }

  return shared_ptr<TParent>();
}

template <typename TParent>
void ConnectionsManager<TParent>::print_connections() {
  for (int i = 0; i < CONNECTIONS_POOL; i++) {
    auto curr = _connections[i];

    cout << i << '\t' << curr << '\t' << endl;
  }

  cout << endl;
}
