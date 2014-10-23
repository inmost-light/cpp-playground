#include <iostream>
using namespace std;

auto main() -> int {
  auto print = [] (const auto& x) {
    cout << x << endl;
  };
  print(123);
  print("hello");
}
