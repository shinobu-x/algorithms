#include <algorithm>
#include <limits>
#include <vector>
#ifndef HUNGARIAN_HPP
#define HUNGARIAN_HPP
typedef int weight;
template <typename T>
using Matrix = std::vector<std::vector<weight>>;
template <typename T>
T Hungarian(Matrix<T>& matrix) {
  const T inf = std::numeric_limits<T>::max();
  const int n = (int)matrix.size();
  const int m = (int)matrix[0].size();
  std::vector<int> p(m);
  std::vector<int> w(m);
  std::vector<T> u(n, 0);
  std::vector<T> v(m, 0);
  std::vector<T> min;
  std::vector<bool> used;
  for (int i = 1; i < n; ++i) {
    p[0] = i;
    min.assign(m, inf);
    used.assign(m, false);
    int j0 = 0;
    while (p[j0] != 0) {
      int i0 = p[j0];
      int j1 = 0;
      used[j0] = true;
      T delta = inf;
      for (int j = 1; j < m; ++j) {
        if (used[j]) continue;
        T current = matrix[i0][j] - u[i0] - v[j];
        if (current < min[j]) min[j] = current, w[j] = j0;
        if (min[j] < delta) delta = min[j], j1 = j;
      }
      for (int j = 0; j < m; ++j)
        if (used[j]) u[p[j]] += delta, v[j] -= delta;
      j0 = j1;
    }
    do p[j0] = p[w[j0]], j0 = w[j0];
    while (j0 != 0);
  }
  return -v[0];
}
#endif
