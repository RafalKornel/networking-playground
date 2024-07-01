#include "../blocks/connections_manager.h"
#include "./connections_manager.test.h"
#include <iostream>
#include <memory>

using namespace std;

int connect_managers_test() {
  auto parent1 = make_shared<int>(42);

  auto m1 =
      shared_ptr<ConnectionsManager<int>>(new ConnectionsManager<int>(parent1));

  auto parent2 = make_shared<int>(43);

  auto m2 =
      shared_ptr<ConnectionsManager<int>>(new ConnectionsManager<int>(parent2));

  if (m1.get()->connect(m2)) {
    cout << "Failed at connecting" << endl;
    return 1;
  };

  if (m1.get()->connection_at(0).get() != parent2.get()) {
    cout << "Failed at connection_at(0)" << endl;

    return 1;
  };

  if (m1.get()->connect_at_socket(m2, 3)) {
    cout << "Failed at connect_at_socket(m2, 3)" << endl;

    return 1;
  };

  if (m1.get()->connection_at(3).get() != parent2.get()) {
    cout << "Failed at connection_at(3)" << endl;

    return 1;
  };

  if (m1.get()->disconnect_at_socket(0)) {
    cout << "Failed at disconnect_at_socket(0)" << endl;

    return 1;
  }

  if (m1.get()->connection_at(0).get() != nullptr) {
    cout << "Failed at connection_at(3) == nullptr" << endl;

    return 1;
  };

  auto lambdaPredicate = [](shared_ptr<int> e) {
    if (e.get() == nullptr) {
      return false;
    }

    auto found = *e.get() == 43;

    return found == 1;
  };

  auto foundConnection = m1.get()->get_connection(lambdaPredicate);

  if (foundConnection.get() == nullptr) {
    cout << "Failed at get_connection (did not find)" << endl;

    return 1;
  }

  if (*(foundConnection.get()) != 43) {
    cout << "Failed at get_connection (wrong value)" << endl;

    return 1;
  }

  auto res = m1.get()->has_connection(m2.get()->parent);

  auto is1ConnectedTo2 = m1.get()->has_connection(m2.get()->parent) == 0;

  if (!is1ConnectedTo2) {
    cout << "Failed at hasConnection" << endl;

    return 1;
  }

  if (m1.get()->disconnect(m2)) {
    cout << "Failed at disconnect" << endl;
  };

  if (!m1.get()->has_connection(m2.get()->parent)) {
    cout << "Failed at has_connection" << endl;

    return 1;
  }

  // TODO: add test cases for get_connection

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