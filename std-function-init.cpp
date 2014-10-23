#include <iostream>
#include <functional>
using namespace std;

template <class T>
struct test {
  T x ;
  function<T()> f = [=] { return x; };
};

auto main() -> int {
  auto t = test<int> {};
  cout << t.f() << endl;
}

// std-function-init.cpp: In instantiation of 'struct test<int>::<lambda()>':
// std-function-init.cpp:6:8:   required from here
// std-function-init.cpp:8:34: internal compiler error: in tsubst_copy, at cp/pt.c:12544
//    function<T()> f = [=] { return x; };
//                                   ^
// libbacktrace could not find executable to open
// Please submit a full bug report,
// with preprocessed source if appropriate.
// See <http://sourceforge.net/projects/mingw-w64> for instructions.
