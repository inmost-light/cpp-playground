#include "ctor-test.hpp"
#include <unordered_map>
#include <string>
#include <map>
using namespace std;

namespace util {
  namespace map {    
    template <class Table, class Key, class... ValueArgs>
    auto insert(Table& t, Key&& k, ValueArgs&&... value_args) -> void {
      t.emplace(std::piecewise_construct,
                std::forward_as_tuple(std::forward<Key>(k)),
                std::forward_as_tuple(std::forward<ValueArgs>(value_args)...));
    }
  } // namespace map
} // namespace util

auto main() -> int {
  {
    auto table = unordered_map<string, ctor_test>{};
    cout << "[k] = v" << endl;
    table["omg"] = ctor_test{};

    cout << endl << "emplace" << endl;
    table.emplace("wat", ctor_test{});
        
    cout << endl << "emplace picewise_construct" << endl;
    table.emplace(std::piecewise_construct, forward_as_tuple("key"), forward_as_tuple());
        
    cout << endl << "utils::map::insert" << endl;
    util::map::insert(table, "test");
        
    cout << endl << "premade objects" << endl;
    auto t1 = ctor_test{};
    auto t2 = ctor_test{};
        
    cout << endl << "utils::map::insert exisiting object" << endl;
    util::map::insert(table, "hello", move(t1));
        
    cout << endl << "emplace existing object" << endl;
    table.emplace("world", move(t2));
        
    cout << endl;
  }

  cout << endl;
  ctor_test::print_stats();
}
