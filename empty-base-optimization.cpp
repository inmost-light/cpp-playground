// http://talesofcpp.fusionfenix.com/post-18/episode-ten-when-size-does-matter

#include <iostream>
using namespace std;

struct empty_base {};
struct omg  : private empty_base {};
struct test : private empty_base { omg o; };

template <class> struct empty_base_t {};
struct omg_t  : private empty_base_t<omg_t>  {};
struct test_t : private empty_base_t<test_t> { omg_t o; };

auto main() -> int {
  cout << sizeof(omg)   << ' ' << sizeof(test)   << endl
       << sizeof(omg_t) << ' ' << sizeof(test_t) << endl;
}
 
    
