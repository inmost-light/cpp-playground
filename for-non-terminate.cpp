#include <iostream>

int main() {
  // g++ -O2: warning: iteration 3u invokes undefined behavior
  // [-Waggressive-loop-optimizations]
  for (int i = 0; i < 4; ++i)
    std::cout << i << ":\t" << i*1000000000 << std::endl;
}
