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
  Matrix(std::vector<matrix::Row> vec) : data(vec) { ; }

  inline bool operator==(const Matrix &other) const {
    return std::equal(this->data.cbegin(), this->data.cend(),
                      other.data.cbegin(), other.data.cend());
  }

  std::vector<int> get_elemnents_in_direction(
      matrix::Point position, std::size_t num_elemns,
      matrix::Direction direction) const {
    const auto [x_increment, y_increment] = x_and_y_increment(direction);
    if (position.second + y_increment * num_elemns > this->data.size() ||
        position.first + x_increment * num_elemns > this->data[0].size()) {
      throw std::out_of_range(
          "Could not get elements from matrix. Out of range.");
    }
    std::vector<int> result;
    for (std::size_t i{0}; i < num_elemns; ++i) {
      const auto x{position.first + x_increment * i};
      const auto y{position.second + y_increment * i};
      result.emplace_back(this->data.at(y).at(x));
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

  std::vector<matrix::Row> data{};
};

#endif  // MATRIX_H_
