#include <functional>
#include <utility>
#include <vector>
#ifndef MONOTONE_MINIMA
#define MONOTONE_MINIMA
template <typename T, typename C = std::less<T> >
struct MonotoneMinima {
  auto operator ()(int h, int w, const std::function<T(int, int)>& f,
      const C& compare = C()) -> std::vector<std::pair<int, T>> {
    std::vector<std::pair<int, T>> dp(h);
    std::function<void(int, int, int, int)> dfs = [&](int top, int bottom,
        int left, int right) {
          if (top > bottom) return;
          int mid = (top + bottom) / 2;
          T max; int min = -1;
          for (int i = left; i <= right; ++i) {
            T cost = f(mid, i);
            if (min == -1 || compare(cost, max)) {
              max = cost; min = i;
            }
          }
          dp[mid] = std::make_pair(min, max);
          dfs(top, mid - 1, left, min); dfs(mid + 1, bottom, min, right);
     };
  }
};
#endif
