#include "max_product_finder.h"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <numeric>
#include <optional>
#include <stdexcept>
#include <vector>

#include "matrix_parser.h"

std::optional<int> MaxProductFinder::max_product(
    const Matrix &matrix, std::size_t elements_in_order) {
  if (elements_in_order == 0) {
    return {};
  }
  if (matrix.num_rows() > elements_in_order &&
      matrix.num_elements() < elements_in_order) {
    return {};
  }
  std::optional<int> result{};
  for (std::size_t x{0}; x < matrix.num_elements(); ++x) {
    for (std::size_t y{0}; y < matrix.num_rows(); ++y) {
      std::optional<int> max_from_point =
          from_point({x, y}, matrix, elements_in_order);
      if (max_from_point.has_value() && result.has_value()) {
        result = std::max(max_from_point.value(), result.value());
      } else if (max_from_point.has_value()) {
        result = max_from_point.value();
      }
    }
  }
  return result;
}

std::optional<int> MaxProductFinder::from_point(
    const matrix::Point &point, const Matrix &matrix,
    const std::size_t num_elements) {
  std::vector<int> candidates{};

  using matrix::Direction;

  for (const auto direction :
       {Direction::Right, Direction::Down, Direction::DownAndRight,
        Direction::DownAndLeft}) {
    const std::optional<std::vector<int>> elements =
        matrix.get_elements_in_direction(point, num_elements, direction);
    if (elements.has_value()) {
      candidates.emplace_back(std::accumulate(
          elements->cbegin(), elements->cend(), 1, std::multiplies<>{}));
    }
  }
  if (candidates.size() == 0) {
    return {};
  } else {
    return *std::max_element(candidates.cbegin(), candidates.cend());
  }
}
