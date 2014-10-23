#pragma once

#include <iostream>

struct ctor_test
{
  ctor_test()    : id {id_count++} { print("ctor"); }
  ctor_test(int) : id {id_count++} { print("ctor(int)"); }
    
  ctor_test(const ctor_test&) : id {id_count++} { print("copy"); }
  ctor_test(ctor_test&&)      : id {id_count++} { print("move"); }
    
  ~ctor_test() { print("dtor"); ++dtor_count; }

  ctor_test& operator=(const ctor_test&) { id = id_count++; print("copy assignment"); return *this; }
  ctor_test& operator=(ctor_test&&)      { print("move assignment"); return *this; }
    
  int id;
        
  static int dtor_count;
  static int id_count;
    
  static auto print_stats() -> void {
    std::cout << "[dtor] called " << dtor_count << " times" << std::endl;
  }

private:
  void print(const char* str) {
    std::cout << str << "  [" << id << "]" << std::endl;
  }
};

// should go to .cpp, but whatever
int ctor_test::id_count   = 0;
int ctor_test::dtor_count = 0;
