#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <experimental/optional>
using namespace std;

struct position {
  int x, y;
};
struct color {
  int r, g, b;
};

template <class T> struct id_helper;
#define COMPONENT_ID(C, N) template <> struct id_helper<C> { enum { value = N }; }

COMPONENT_ID(position, 0);
COMPONENT_ID(color,    1);

auto gen_id() -> int {
  static auto id = 0;
  return id++;
}

struct storage {
  virtual ~storage() = 0;
};

storage::~storage() {}

template <class T>
struct storage_impl : public storage {
  unordered_map<int, T> data;
};

struct database {
  unordered_map<int, unique_ptr<storage>> storages;

  template <class T>
  auto get() -> storage_impl<T>& {
    if (storages.find(id_helper<T>::value) == end(storages)) {
      storages.emplace(id_helper<T>::value, unique_ptr<storage>(new storage_impl<T>));
    }
    auto ptr = static_cast<storage_impl<T>*>(storages[id_helper<T>::value].get());
    return *ptr;
  }

  template <class T>
  auto get(int id) -> experimental::optional<T> {
    auto& s = get<T>();
    auto it = s.data.find(id);
    if (it != end(s.data)) {
      return it->second;
    } else {
      return {};
    }
  }

  template <class T>
  auto add(int id, T component) -> void {
    auto& s = get<T>();
    s.data.emplace(id, component);
  }
  
  struct setter {
    int obj;
    database& db;

    setter(int active_object, database& active_db) : obj {active_object}, db(active_db) {}
    template <class T>
    auto operator<<(T component) -> setter& {
      db.add(obj, component);
      return *this;
    }
  };

  auto use(int object) -> setter { return {object, *this}; }  
};

auto main() -> int {
  auto db = database {};
  auto obj = gen_id();
  auto obj2 = gen_id();

  auto c = color {1, 2, 3};
  auto p = position {320, 240};
  db.use(obj) << c << p;
  db.use(obj2) << p;

  auto co = db.get<color>(obj2);
  if (co) {
    cout << co->r << ' ' << co->g << ' ' << co->b << endl;
  } else {
    cout << obj2 << " has no color" << endl;
  }

  for (auto c : db.get<color>().data) {
    cout << c.first << ": "
         << c.second.r << ", "
         << c.second.g << ", "
         << c.second.b
         << endl;
  }
  for (auto p : db.get<position>().data) {
    cout << p.first << ": "
         << p.second.x << ", "
         << p.second.y
         << endl;
  }
}
