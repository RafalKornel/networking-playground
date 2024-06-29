#include "./blocks/connections_manager.cpp"
#include "./blocks/ethernet.h"

template class ConnectionsManager<Ethernet>;

// for testing purposes
template class ConnectionsManager<int>;