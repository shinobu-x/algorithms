#include <vector>
#include "euler_tour.hpp"
#include "binary_indexed_tree.hpp"

#ifndef COUNT_ON_EULER_TOUR_HPP
#define COUNT_ON_EULER_TOUR_HPP
template <typename T, typename U>
class CountOnEulerTour : public EulerTour<T> {
private:
  BinaryIndexedTree<U> _counts;
  std::size_t vertex_size;
  void _reset() {
    _counts = BinaryIndexedTree<U>(EulerTour<T>::size());
  }
  void _update(int index, U value, std::vector<bool>& is_already) {
    if (is_already[EulerTour<T>::operator[](index)]) {
      return;
    }
    is_already[EulerTour<T>::operator[](index)] = true;
    _counts.update(index, value);
  }
public:
  explicit CountOnEulerTour(UnWeightedGraph<T>& graph,
      std::size_t vertex_size) :
    EulerTour<T>(graph, vertex_size), _counts(2 * vertex_size),
    vertex_size(vertex_size) {}
  void init_previous_order_counts(U base) {
    std::vector<bool> is_already(vertex_size, false);
      for (int index = 0; index < EulerTour<T>::size(); ++index) {
        update(index, base, is_already);
      }
  }
  void init_following_order_counts(U base) {
    std::vector<bool> is_already(vertex_size, false);
    for (int index = EulerTour<T>::size() - 1; index >= 0; --index) {
      update(index, base, is_already);
    }
  }
  void reset_previous_order_counts(U base) {
    reset();
    init_previous_order_counts(base);
  }
  void reset_following_order_counts(U base) {
    reset();
    init_following_order_counts(base);
  }
  void reset() {
    _reset();
  }
  void update(int partial_tree_root, U value) {
    _counts.update(EulerTour<T>::index_of(partial_tree_root).first, value);
  }
  U query(std::pair<int, int> index) {
    return _counts.query(index.first, index.second);
  }
  U query(int partial_tree_root) {
    std::pair<int, int> index = EulerTour<T>::index_of(partial_tree_root);
    return _counts.query(index.first, index.second);
  }
};
#endif
