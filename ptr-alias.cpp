#include <iostream>
using namespace std;

template <class T>
using raw_ptr = T*;

auto main() -> int {
  auto ptr = raw_ptr<int>{};
  cout << ptr << endl;
}
