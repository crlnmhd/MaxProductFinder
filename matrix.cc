#include "matrix.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <stdexcept>
Matrix::Matrix(std::vector<matrix::Row> vec) : data(vec) {
  if (!matrix_is_valid()) {
    throw std::invalid_argument(
        "Cloud not construct matrix. All rows must be of equal size");
  }
}

std::size_t Matrix::num_rows() const { return data.size(); }

std::size_t Matrix::num_elements() const {
  if (data.size() == 0) {
    return 0;
  } else {
    return data[0].size();
  }
}

std::optional<std::vector<int>> Matrix::get_elements_in_direction(
    matrix::Point position, std::size_t num_elements,
    matrix::Direction direction) const {
  std::vector<int> result;

  for (std::size_t i{0}; i < num_elements; ++i) {
    const auto new_pos{new_position(position, direction, i)};
    if (new_pos.has_value()) {
      const auto [column, row] = new_pos.value();
      result.emplace_back(data.at(row).at(column));
    }
  }

  if (result.size() == num_elements) {
    return result;
  } else {
    return {};
  }
}

std::optional<matrix::Point> Matrix::new_position(const matrix::Point &start,
                                                  matrix::Direction direction,
                                                  std::size_t num_steps) const {
  for (const std::size_t &num :
       {start.first, start.second, num_steps, data.size()}) {
    assert_convertable_to_int(num);
  }
  if (data.size() > 0) {
    assert_convertable_to_int(data[0].size());
  } else {
    return {};
  }

  const auto [relative_x, relative_y] = x_and_y_steps(direction);
  const int new_x{static_cast<int>(start.first) +
                  relative_x * static_cast<int>(num_steps)};
  const int new_y{static_cast<int>(start.second) +
                  relative_y * static_cast<int>(num_steps)};

  if (new_x >= 0 && new_y >= 0) {
    const matrix::Point result{static_cast<int>(new_x),
                               static_cast<int>(new_y)};
    if (result.first < data[0].size() && result.second < data.size()) {
      return result;
    }
  }
  return {};
}

std::pair<int, int> Matrix::x_and_y_steps(matrix::Direction direction) const {
  switch (direction) {
    case matrix::Direction::Right:
      return {1, 0};
    case matrix::Direction::DownAndRight:
      return {1, 1};
    case matrix::Direction::Down:
      return {0, 1};
    case matrix::Direction::DownAndLeft:
      return {-1, 1};
  }
  throw std::runtime_error("Unexpected direction");
}

bool Matrix::matrix_is_valid() const {
  for (const auto &row : data) {
    if (row.size() != data[0].size()) {
      return false;
    }
  }
  return true;
}
void Matrix::assert_convertable_to_int(const std::size_t number) const {
  if (number > std::numeric_limits<int>::max()) {
    throw std::invalid_argument(
        "Convertion error. Number too large to fit in int");
  }
}
