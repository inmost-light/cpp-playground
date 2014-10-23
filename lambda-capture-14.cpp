#include <iostream>
using namespace std;

auto main() -> int {
  auto x = 123;
  // can't do that?
  auto l = [&x,
            y = x + 1 /*, z = y + 2 */] { return x + y; };
  cout << l() << endl;
}
