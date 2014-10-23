#include <vector>

struct test {
  int x;
  int y;
};

auto main() -> int {
  auto v = std::vector<test>{};
  // error
  v.emplace_back(1, 2);
}
