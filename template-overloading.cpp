#include <iostream>
#include <vector>
using namespace std;

//------------------------------------------------------------------------------
auto plain_func(int)    -> void { cout << "plain(int)" << endl; }
auto plain_func(double) -> void { cout << "plain(double)" << endl; }

template <class T>
auto call_plain(T arg) -> void { plain_func(arg); }

auto plain_func(vector<int>) -> void { cout << "plain(v<int>)" << endl; }

//------------------------------------------------------------------------------
template <class T>
auto template_func(T)      -> void { cout << "base template func" << endl; }
template <>
auto template_func(int)    -> void { cout << "template func(int)" << endl; }
template <>
auto template_func(double) -> void { cout << "template func(double)" << endl; }

template <class T>
auto call_template(T arg) -> void { template_func(arg); }

// error: function template partial specialization
// 'template_func<std::vector<U> >' is not allowed
// template <class U>
// auto template_func<vector<U>>(vector<U>) -> void { cout <<
// "template func(v<U>)" << endl; }

template <class T>
auto template_func(vector<T>) -> void { cout << "template func(v<T>)" << endl; }

//------------------------------------------------------------------------------
template <class T>
struct wrapper {
  static auto func(T) -> void { cout << "base wrapper" << endl;; }
};

template <>
auto wrapper<int>::func(int)       -> void { cout << "wrapper(int)" << endl; }
template <>
auto wrapper<double>::func(double) -> void { cout << "wrapper(double)" << endl; }

template <class T>
auto call_template_wrapper(T t) -> void {
  wrapper<T>::func(t);
}

template <class T>
struct wrapper<vector<T>> {
  static auto func(vector<T>) -> void {
    cout << "wrapper(vector)" << endl;
  }
};

//------------------------------------------------------------------------------
auto main() -> int {
  auto v = vector<int> {1, 2, 3};

  cout << "Plain:" << endl;
  call_plain(1);
  call_plain(1.0);
  // error: no matching function for call to 'plain_func(std::vector<int>&)'
  // call_plain(v);
  cout << endl;

  cout << "Template functions:" << endl;
  call_template(1);
  call_template(1.0);
  call_template(v);
  cout << endl;

  cout << "Template wrapper:" << endl;
  call_template_wrapper(1);
  call_template_wrapper(1.0);
  call_template_wrapper(v);
  cout << endl;
}
