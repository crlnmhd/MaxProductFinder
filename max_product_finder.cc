#include "max_product_finder.h"

#include <iterator>
#include <optional>
#include <stdexcept>

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
  return {};
}
