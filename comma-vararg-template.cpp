#include <iostream>
using namespace std;

template <class T>
auto print(T t) -> void {
  cout << t << endl;
}

template <class... Args>
auto f(Args... args) -> void{
  using U = char[];
  U { (print(args), '0')..., '0' };
}

auto main() -> int {
  f(1, 2, 3, "hello", "world", 123.4);
}
