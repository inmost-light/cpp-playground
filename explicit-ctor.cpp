#include <iostream>
using namespace std;

struct impl1 { impl1(int) {} };
struct expl1 { explicit expl1(int) {} };

struct impl2 { impl2(int, int) {} };
struct expl2 { explicit expl2(int, int) {} };

auto fi1(impl1) -> void {}
auto fe1(expl1) -> void {}
auto fi2(impl2) -> void {}
auto fe2(expl2) -> void {}

auto main() -> int {
  fi1(123);
  // fe1(123);
  // fe1({123});
  fe1(expl1 {123});
  fi2({123, 123});
//  fe2({123,123});
}
