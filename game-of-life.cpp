#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

template <class T> struct TP;

struct world {
  enum class cell { alive, dead };
  int size;
  bool gg = false;
  vector<cell> prev_cells;
  vector<cell> cells;

  world(int world_size) : size {world_size} {
    for (auto i = 0; i < size * size; ++i) {
      cells.push_back(rand() % 2 ? cell::alive : cell::dead);
    }
    prev_cells = cells;
  }

  auto alive_neighbours_count(int idx) const -> int {
    const auto x = idx % size;
    const auto y = idx / size;
    
    auto neighbours = array<pair<int, int>, 8> {
      {
        {-1, -1}, {0, -1}, {1, -1},
        {-1,  0},          {1,  0},
        {-1,  1}, {0,  1}, {1,  1}
      }
    };
    
    auto alive_count = 0;
    for (auto p : neighbours) {
      auto nx = x + p.first;
      auto ny = y + p.second;
      if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
        auto i = nx + ny * size;
        if (i >= 0 && i < int(prev_cells.size()) && prev_cells[i] == cell::alive) {
          ++alive_count;
        }
      }
    }
    return alive_count;
  }
  
  auto update() -> void {
    for (auto i = cells.size() - cells.size(); i < cells.size(); ++i) {
      auto count = alive_neighbours_count(i);
      auto& c = cells[i];
      if (c == cell::alive && (count < 2 || count > 3)) {
        c = cell::dead;
      } else if (count == 3) {
        c = cell::alive;
      }
    }
    if (cells == prev_cells) {
      gg = true;
    }
    prev_cells = cells;
  }

  auto draw() const -> void {
    for (auto i = 0; i < size; ++i) {
      for (auto j = 0; j < size; ++j) {
        auto c = cells[i * size + j];
        cout << (c == cell::dead ? '.' : '@');
      }
      cout << endl;
    }
  }
};

auto main() -> int {
  srand(time(nullptr));
  auto world_size = 4;
  cout << "Enter world size: ";
  cin >> world_size;

  auto w = world {world_size};
  auto clear_str = string(world_size * world_size + world_size, '\b');

  w.draw();
  auto ticks = 0;
  while (!w.gg) {
    this_thread::sleep_for(chrono::milliseconds {200});
    cout << clear_str;
    w.update();
    ++ticks;
    w.draw();
  }
  cout << endl;
  w.draw();
  cout << endl;
  cout << "ticks: " << ticks << endl;
}
