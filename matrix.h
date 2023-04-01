#if !defined(MATRIX_H_)
#define MATRIX_H_

#include <optional>
#include <vector>

namespace matrix {
using Row = std::vector<int>;

enum class Direction { Right, DownAndRight, Down, DownAndLeft };

using Point = std::pair<std::size_t, std::size_t>;
}  // namespace matrix

class Matrix {
 public:
  Matrix() = default;
  Matrix(std::vector<matrix::Row> vec);

  inline bool operator==(const Matrix &other) const {
    return std::equal(data.cbegin(), data.cend(), other.data.cbegin(),
                      other.data.cend());
  }
  std::size_t num_rows() const;

  std::size_t num_columns() const;

  std::optional<std::vector<int>> get_elements_in_direction(
      matrix::Point position, std::size_t num_columns,
      matrix::Direction direction) const;

 private:
  std::pair<int, int> x_and_y_steps(matrix::Direction direction) const;

  bool matrix_is_valid() const;

  void assert_convertable_to_int(const std::size_t number) const;

  std::optional<matrix::Point> new_position(const matrix::Point &start,
                                            matrix::Direction direction,
                                            std::size_t num_steps) const;

  std::vector<matrix::Row> data{};
};

#endif  // MATRIX_H_
