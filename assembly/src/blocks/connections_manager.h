#ifndef CONNECTIONS_MANAGER
#define CONNECTIONS_MANAGER

#include "../types.h"
#include <functional>
#include <memory>

using namespace std;

static const int CONNECTIONS_POOL = 5;

template <typename TParent> class ConnectionsManager {

private:
  shared_ptr<ConnectionsManager> _connections[CONNECTIONS_POOL];

public:
  static const bool VERBOSE = false;
  const shared_ptr<TParent> parent;

  ConnectionsManager<TParent>(shared_ptr<TParent> parent);

  int connect(shared_ptr<ConnectionsManager<TParent>> other);
  int connect_at_socket(shared_ptr<ConnectionsManager<TParent>> other,
                        int socket);

  int disconnect(shared_ptr<ConnectionsManager<TParent>> other);
  int disconnect_at_socket(int socket);

  shared_ptr<TParent>
  get_connection(function<bool(shared_ptr<TParent>)> predicate) const;

  int has_connection(shared_ptr<TParent>) const;
  shared_ptr<TParent> connection_at(int socket) const;

  void print_connections();

  // tutaj powinienem dodać event listenery, tak że
  // kiedy podłączamy dwie encje ze sobą, to receive z *othet*
  // powinno zostać zarejestrowane, a następnie wywołane kiedy wleci paczka
};

#endif // CONNECTIONS_MANAGER
