#include <utility>
#include <vector>
#include "unweighted_graph.hpp"

#ifndef EULER_TOUR_HPP
#define EULER_TOUR_HPP
template <typename T>
class EulerTour {
private:
  std::vector<int> data, in, out;
  std::size_t data_size;
  UnWeightedGraph<T>& graph;
  void dfs(int current_vertex, int previous_vertex, int& reference_count) {
    in[current_vertex] = reference_count;
    data[++reference_count] = current_vertex;
    for (auto following_vertex : graph[current_vertex]) {
      if (following_vertex == previous_vertex) {
        continue;
      }
      dfs(following_vertex, current_vertex, reference_count);
      data[++reference_count] = current_vertex;
    }
  }
public:
  explicit EulerTour(UnWeightedGraph<T>& graph, std::size_t data_size) :
    graph(graph), data(2 * data_size), in(data_size), out(data_size),
    data_size(0) {}
  void build(int start = 0) {
    int reference_count = 0;
    dfs(start, -1, reference_count);
    data_size = reference_count;
  }
  std::pair<int, int> index_of(const int vertex) {
    return {in[vertex], out[vertex]};
  }
  int previous_order(const int vertex) {
    return in[vertex];
  }
  int following_order(const int vertex) {
    return out[vertex] - 1;
  }
  const int& operator[] (const int index) const {
    return data[index];
  }
  std::size_t size() const noexcept {
    return data_size;
  }
};
#endif
