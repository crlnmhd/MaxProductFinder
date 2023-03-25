#include <optional>

#include "matrix_parser.h"

class MaxProductFinder {
 public:
  std::optional<int> max_product(const Matrix &matrix,
                                 std::size_t elements_in_order);

  std::vector<int> get_elements_in_direction(matrix::Point point,
                                             std::size_t num_elemns,
                                             matrix::Direction direction) const;

 private:
  std::optional<int> from_point(const matrix::Point &point,
                                const Matrix &matrix,
                                const std::size_t num_elemnets);
};
