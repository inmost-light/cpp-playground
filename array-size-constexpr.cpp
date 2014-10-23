#include <iostream>
using namespace std;

template <class T, std::size_t N>
constexpr auto array_size(const T(&)[N]) -> std::size_t {
  return N;
}

auto main() -> int {
  int a[123];

  cout << array_size(a) << endl;

  auto x = 123;
  switch (x) {
  case array_size(a): cout << "yes" << endl; break;
  default: cout << "nope" << endl; break;
  }
}
