#include <iostream>
#include <memory>
using namespace std;

struct base {
  virtual ~base() = 0;
};

base::~base()  {
  cout << "~base()" << endl;
}

struct derived : base {};

auto main() -> int {
//  auto d = make_unique<base>();
  auto d = make_unique<derived>();
}

    
