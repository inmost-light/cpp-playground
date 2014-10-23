#include <iostream>
#include "Eigen/LU"
using namespace std;

auto main() -> int {
  auto m = Eigen::Matrix3f{};
  m << 1,0,0,
    0,5,0,
    0,0,9;

  cout << m.inverse() << endl
       << endl
       << m * m.inverse() << endl;
}
