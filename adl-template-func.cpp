#include <iostream>
using namespace std;

namespace ns_test {
  struct test {};

  template <class T>
  auto f(T) -> void {
    cout << "ns_test::f(T)" << endl;
  }
  template <int N, class T>
  auto g(T) -> void {
    cout << "ns_test::f<N>(T)" << endl;
  }
} // namespace ns_test

auto main() -> int {
  auto t = ns_test::test{};
  f(t);
  //g<123>(t);
  ns_test::g<123>(t);
}
