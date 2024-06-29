#ifndef CONNECTIONS_MANAGER
#define CONNECTIONS_MANAGER

#include "../types.h"
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

  int has_connection(shared_ptr<TParent>) const;
  shared_ptr<TParent> connection_at(int socket) const;

  void print_connections();
};

#endif // CONNECTIONS_MANAGER
