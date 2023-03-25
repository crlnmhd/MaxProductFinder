#include <algorithm>
#include <cstddef>
#include <iterator>
#include <map>
#include <stdexcept>
#if !defined(MATRIX_H_)
#define MATRIX_H_

#include <vector>

namespace matrix {
using Row = std::vector<int>;

enum class Direction { Right, DownAndRight, Down };

using Point = std::pair<std::size_t, std::size_t>;
}  // namespace matrix

class Matrix {
 public:
  Matrix() = default;
  Matrix(std::vector<matrix::Row> vec) : data(vec) {
    if (!matrix_is_valid()) {
      throw std::invalid_argument(
          "Cloud not construct matrix. All rows must be of equal size");
    }
  }

  inline bool operator==(const Matrix &other) const {
    return std::equal(data.cbegin(), data.cend(), other.data.cbegin(),
                      other.data.cend());
  }

  std::vector<int> get_elemnents_in_direction(
      matrix::Point position, std::size_t num_elemns,
      matrix::Direction direction) const {
    const auto [x_increment, y_increment] = x_and_y_increment(direction);
    if (position.second + y_increment * num_elemns > data.size() ||
        position.first + x_increment * num_elemns > data[0].size()) {
      throw std::out_of_range(
          "Could not get elements from matrix. Out of range.");
    }
    std::vector<int> result;
    for (std::size_t i{0}; i < num_elemns; ++i) {
      const auto x{position.first + x_increment * i};
      const auto y{position.second + y_increment * i};
      result.emplace_back(data.at(y).at(x));
    }
    return result;
  }

 private:
  std::pair<std::size_t, std::size_t> x_and_y_increment(
      matrix::Direction direction) const {
    switch (direction) {
      case matrix::Direction::Right:
        return {1, 0};
      case matrix::Direction::DownAndRight:
        return {1, 1};
      case matrix::Direction::Down:
        return {0, 1};
    }
  }
  bool matrix_is_valid() {
    for (const auto &row : data) {
      if (row.size() != data[0].size()) {
        return false;
      }
    }
    return true;
  }

  std::vector<matrix::Row> data{};
};

#endif  // MATRIX_H_
