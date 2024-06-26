#ifndef CONNECTIONS_MANAGER
#define CONNECTIONS_MANAGER

#include "../types.h"
#include <memory>

using namespace std;

static const int CONNECTIONS_POOL = 5;
static const bool VERBOSE = false;

class ConnectionsManager {
private:
  shared_ptr<ConnectionsManager> _connections[CONNECTIONS_POOL];

public:
  const MacAddress macAddress;
  ConnectionsManager(const MacAddress &mA);

  int connect(shared_ptr<ConnectionsManager> other);
  int connect_at_socket(shared_ptr<ConnectionsManager> other, int socket);

  int disconnect(shared_ptr<ConnectionsManager> other);
  int disconnect_at_socket(int socket);

  int has_connection(const MacAddress address);
  shared_ptr<const ConnectionsManager> connection_at(int socket);

  void print_connections();
};

#endif // CONNECTIONS_MANAGER
