#include <vector>
#include "low_link.hpp"

#ifndef TWO_EDGE_CONNECTED_COMPONENT
#define TWO_EDGE_CONNECTED_COMPONENT
template <typename T>
struct TwoEdgeConnectedComponents : LowLink<T> {
  Graph<T> tree;
  std::vector<int> component; std::vector<std::vector<int>> group;
  explicit TwoEdgeConnectedComponents(int size) : LowLink<T>(size) {}
  auto operator[](const int& k) -> int {
    return component[k];
  }
  void dfs (int index, int parent, int& k) {
    if (parent >= 0 && this->ord[parent] >= this->low[index])
      component[index] = component[parent];
    else component[index] = ++k;
    for (auto& to : this->graph.graph[index])
      if (component[to] == -1) dfs(to, index, k);
  }
  void init() override {
    this->init();
    component.assign(this->graph.size(), -1); int k = 0;
    for (int i = 0; i < component.size(); ++i)
      if (component[i] == -1) dfs(i, -1, k);
    group.resize(k);
    for (int i = 0; i < (int)this->graph.size(); ++i)
      group[component[i]].emplace_back(i);
    tree = Graph<T>(k);
    for (auto& e : this->bridge)
      tree.add_edge(component[e.from], component[e.to], e.cost);
  }
};
#endif
