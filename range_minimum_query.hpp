#include <algorithm>
#include <vector>

#ifndef RANGE_MINIMUM_QUERY_HPP
#define RANGE_MINIMUM_QUERY_HPP
typedef long long int ll;
struct RangeMinimumQuery {
  ll query(int left, int right, int a, int b, int k) {
    if (left <= b && a <= right) {
      int mid = (a + b) / 2;
      int left_value = query(left, right, a, mid, k * 2);
      int right_value = query(left, right, mid, b, k * 2 + 1);
      return std::min(left_value, right_value);
    } return 10e12;
  }
  std::vector<ll> segment_tree;
  std::size_t c;
  RangeMinimumQuery(std::size_t n) {
   c = 1;
   while (c < n) c <<= 1; segment_tree.assign(c * 2, 10e12);
  }
  void update(std::size_t position, ll value) {
    for (int i = c + position; i > 0; i /= 2) {
      segment_tree[i] = value;
      value = std::min(segment_tree[i], segment_tree[i^1]);
    }
  }
  ll get(std::size_t left, std::size_t right) {
    return query(left, right, 0, c, 1);
  }
  ll get(std::size_t position) {
    return segment_tree[c + position];
  }
};
#endif
