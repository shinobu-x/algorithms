#include <algorithm>
#include <queue>
#include <vector>
#ifndef MAX_FLOW_HPP
#define MAX_FLOW_HPP
struct MaxFlow {
  std::size_t vertex;
  std::vector<std::vector<std::size_t>> graph, capacity, edge;
  std::vector<std::size_t> visited, distance;
  MaxFlow(std::size_t vertices) : vertex(vertices),
    graph(vertices, std::vector<std::size_t>(vertices)),
    capacity(vertices, std::vector<std::size_t>(vertices)),
    edge(vertices) {}
  void add_edge(std::size_t u, std::size_t v, std::size_t c) {
    graph[u][v] = capacity[u][v] = c;
    edge[u].push_back(v); edge[v].push_back(u);
  }
  auto bfs(std::size_t u, std::size_t v) -> int {
    distance.assign(vertex, 0); std::queue<int> queue;
    queue.push(u); distance[u] = 1;
    while (!queue.empty()) {
      int n = queue.front(); queue.pop();
      for (auto i : edge[n])
        if (!distance[i] && graph[n][i]) {
          distance[i] = distance[i] + 1; queue.push(i);
        }
    } return distance[v];
  }
  auto dfs (std::size_t n, std::size_t c, std::size_t t) -> int {
    if (n == t) return c;
    for (; visited[n] < edge[n].size(); ++visited[n]) {
      int v = edge[n][visited[n]];
      if (graph[n][v] && distance[v] > distance[n]) {
        int f = dfs(v, std::min(c, graph[n][v]), t);
        graph[n][v] -= f; graph[v][n] += f; if (f) return f;
      }
    }
    return 0;
  }
  auto max_flow(std::size_t s, std::size_t t) {
    if (s == t) return 0x3fffffff; // INF
    int f, r = 0;
    while (bfs(s, t)) {
      visited.assign(vertex, 0);
      while ((f = dfs(s, 0x3fffffff, t))) r += f;
    } return r;
  }
  auto flow(std::size_t f, std::size_t t) -> int {
    return capacity[f][t] - graph[f][t];
  }
  auto flow(std::size_t n) -> int {
    int r = 0;
    for (int v : edge[n]) r += std::abs(flow(n, v));
    return r;
  }
};
#endif
