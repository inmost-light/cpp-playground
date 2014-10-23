#include <random>
#include <iostream>
using namespace std;
 
auto main() -> int {
  random_device rd;
  auto gen = mt19937 {0u};
  auto dis = uniform_int_distribution<>{1, 6};
 
  for (auto i = 0; i < 10; ++i) {
    cout << dis(gen) << ' ';
  }
  cout << endl;
}
