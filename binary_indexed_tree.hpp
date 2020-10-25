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
  auto compute_counts(int index) -> T {
    T counts = 0;
    for (int current_index = index + 1; current_index > 0;
        current_index -= (current_index & -current_index)) {
      counts += data[current_index];
    }
    return counts;
  }
  auto get_counts() -> T {
    return compute_counts(data.size() - 1);
  }
  auto query(int left, int right) -> T {
    return compute_counts(right - 1) - compute_counts(left);
  }
};
#endif
