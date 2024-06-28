#include "../blocks/connections_manager.h"
#include "./connections_manager.test.h"
#include <iostream>
#include <memory>

using namespace std;

int connect_managers_test() {
  auto m1 = shared_ptr<ConnectionsManager>(
      new ConnectionsManager({0xff, 0xcc, 0xff, 0xcc, 0xff, 0xcc}));

  auto m2 = shared_ptr<ConnectionsManager>(
      new ConnectionsManager({0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}));

  if (m1.get()->connect(m2)) {
    cout << "Failed at connecting" << endl;
    return 1;
  };

  if (m1.get()->connection_at(0).get()->macAddress != m2.get()->macAddress) {
    cout << "Failed at connection_at(0)" << endl;

    return 1;
  };

  auto res = m1.get()->has_connection(m2.get()->macAddress);

  auto is1ConnectedTo2 = m1.get()->has_connection(m2.get()->macAddress) == 0;

  if (!is1ConnectedTo2) {
    cout << "Failed at hasConnection" << endl;

    return 1;
  }

  if (m1.get()->connect_at_socket(m2, 3)) {
    cout << "Failed at connect_at_socket(m2, 3)" << endl;

    return 1;
  };

  if (m1.get()->connection_at(3).get()->macAddress != m2.get()->macAddress) {
    cout << "Failed at connection_at(3)" << endl;

    return 1;
  };

  if (m1.get()->disconnect_at_socket(3)) {
    cout << "Failed at disconnect_at_socket(3)" << endl;

    return 1;
  }

  if (m1.get()->connection_at(3) != nullptr) {
    cout << "Failed at connection_at(3) == nullptr" << endl;

    return 1;
  };

  if (m1.get()->disconnect(m2)) {
    cout << "Failed at disconnect" << endl;
  };

  if (m1.get()->has_connection(m2.get()->macAddress)) {
    cout << "Failed at has_connection" << endl;

    return 1;
  }

  return 0;
}

int ConnectionsManagerTest::main() {
  cout << "ConnectionsManager" << endl;

  auto connect_managers_test_result = connect_managers_test();

  cout << "\tconnect_managers_test: "
       << (connect_managers_test_result ? "fail" : "pass") << endl;

  cout << endl;

  return 0;
}