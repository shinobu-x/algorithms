#include <stack>
#include <utility>
#include <vector>

#ifndef UNION_FIND_UNDO_HPP
#define UNION_FIND_UNDO_HPP
struct UnionFindUndo {
  std::vector<int> data;
  std::stack<std::pair<int, int>> history;
  UnionFindUndo(int size) { data.assign(size, -1); }
  auto unite(int x, int y) -> bool {
    x = find(x), y = find(y);
    history.emplace(x, data[x]); history.emplace(y, data[y]);
    if (x != y) {
      if (data[x] < data[y]) std::swap(x, y);
      data[x] += data[y], data[y] = x; return true;
    } else return false;
  }
  auto find(int x) -> int {
    if (data[x] < 0) return x;
    return find(data[x]);
  }
  auto size(int x) -> int {
    return -data[find(x)];
  }
  void undo() {
    data[history.top().first] = history.top().second; history.pop();
  }
  void pop() { while (history.size()) history.pop(); }
  void reverse(int i) { while (history.size()) undo(); }
};
#endif
