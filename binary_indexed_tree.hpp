#include <vector>

#ifndef BINARY_INDEXED_TREE_HPP
#define BINARY_INDEXED_TREE_HPP
template <typename T>
class BinaryIndexedTree {
private:
  std::vector<T> data;
public:
  explicit BinaryIndexedTree(int data_size) : data(data_size + 1, 0) {}
  void update(int index, T value) {
    for (int current_index = index + 1; current_index < data.size();
        current_index += (current_index & -current_index)) {
      data[current_index] += value;
    }
  }
  auto compute_sum(int index) -> T {
    T sum = 0;
    for (int current_index = index + 1; current_index > 0;
        current_index -= (current_index & -current_index)) {
      sum += data[current_index];
    }
    return sum;
  }
  auto get_sum() -> T {
    return compute_sum(data.size() - 1);
  }
  auto query(int left, int right) -> T {
    return compute_sum(right - 1) - compute_sum(left);
  }
};
#endif
