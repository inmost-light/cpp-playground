#include <iostream>
#include <map>
#include <memory>
#include <cassert>
using namespace std;

struct msgBase {
  virtual auto msgType() const -> int = 0;
};

struct msgType1 : public msgBase {
  auto msgType() const -> int override { return 1; }
};

struct msgType2 : public msgBase {
  auto msgType() const -> int override { return 2; }
};

void process(const msgType1&) {
  cout << "msg1" << endl;
}
void process(const msgType2&) {
  cout << "msg2" << endl;
}

struct dispatcher_base {
  virtual auto process(const msgBase&) const -> void = 0;
};
    
template <class T>
struct dispatcher_impl : dispatcher_base {
  auto process(const msgBase& b) const -> void override {
    ::process(static_cast<const T&>(b));
  }
};

auto g_table = map<int, std::unique_ptr<dispatcher_base>>{};

template <class T>
auto register_msg() -> void {
  g_table[T{}.msgType()].reset(new dispatcher_impl<T>{});
}

auto process(const msgBase& b) -> void {
  assert(g_table.find(b.msgType()) != g_table.end());
  g_table[b.msgType()]->process(b);
}

auto main() -> int {
  register_msg<msgType1>();
  register_msg<msgType2>();
    
  auto msg1 = msgType1 {};
  auto msg2 = msgType2 {};
  
  msgBase& b1 = msg1;
  msgBase& b2 = msg2;
  process(b1);
  process(b2);
}
