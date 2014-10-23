#include <iostream>
using namespace std;

template <class F>
struct scope_guard {
  F f;
  scope_guard(F func) : f {func} {}
  ~scope_guard() { f(); }
};

template <class F>
auto make_scope_guard(F f) -> scope_guard<F> {
  return {f};
}

auto main() -> int {
  auto guard = make_scope_guard([] { cout << "hello" << endl; });
}
