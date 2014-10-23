#include <iostream>
using namespace std;

auto f(int x) -> double {
  return x * 1.5;
}

using int_double_fptr = auto (*)(int) -> double;

auto ff() -> auto (*)(int) -> double {
  return f;
}

using deeper_fptr = auto (*)() -> auto (*)(int) -> double;

auto main() -> int {
  int_double_fptr ptr = f;
  cout << ptr(9) << endl;
  deeper_fptr wp = ff;
  cout << wp()(123) << endl;
}
