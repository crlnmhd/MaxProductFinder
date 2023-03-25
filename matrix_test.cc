#include "matrix.h"

#include <gtest/gtest.h>

#include <stdexcept>

#include "gtest/gtest.h"

namespace {
TEST(MatrixTest, TestGetElementsFromTheOrigin) {
  Matrix matrix{{{1, 2, 3, 4}, {5, 6, 7, 8}}};

  std::vector<int> three_to_the_right{1, 2, 3};
  std::vector<int> two_down{1, 5};
  std::vector<int> two_down_and_to_the_right{1, 6};

  matrix::Point origin{0, 0};
  EXPECT_EQ(
      matrix.get_elements_in_direction(origin, 3, matrix::Direction::Right)
          .value(),
      three_to_the_right);
  EXPECT_EQ(matrix.get_elements_in_direction(origin, 2, matrix::Direction::Down)
                .value(),
            two_down);
  EXPECT_EQ(
      matrix
          .get_elements_in_direction(origin, 2, matrix::Direction::DownAndRight)
          .value(),
      two_down_and_to_the_right);
}
TEST(MatrixTest, TestGetElementsFromPoint) {
  Matrix matrix{{{1, 2, 3, 4}, {5, 6, 7, 8}}};
  matrix::Point point{2, 1};

  std::vector<int> two_to_the_right{7, 8};
  std::vector<int> one_down{7};

  EXPECT_EQ(matrix.get_elements_in_direction(point, 2, matrix::Direction::Right)
                .value(),
            two_to_the_right);
  EXPECT_EQ(matrix.get_elements_in_direction(point, 1, matrix::Direction::Down)
                .value(),
            one_down);
}

TEST(MatrixTest, TestReturnsNulloptWhenOutOfBounds) {
  Matrix matrix({{1, 2, 3}, {4, 5, 6}});
  matrix::Point origin{0, 0};

  EXPECT_FALSE(
      matrix.get_elements_in_direction(origin, 4, matrix::Direction::Right));
  EXPECT_FALSE(
      matrix.get_elements_in_direction(origin, 4, matrix::Direction::Down));
  EXPECT_FALSE(matrix.get_elements_in_direction(
      origin, 4, matrix::Direction::DownAndRight));
};

TEST(MatrixTest, TestEqualityComparisonReturnsTrueForEqualMatrices) {
  Matrix matrix{{{0, 1, 2, 3}, {4, 5, 6, 7}}};
  Matrix equal_matrix{{{0, 1, 2, 3}, {4, 5, 6, 7}}};

  EXPECT_EQ(matrix, matrix);
  EXPECT_EQ(matrix, equal_matrix);
  EXPECT_EQ(Matrix{}, Matrix{});
}

TEST(MatrixTest, TestEqualityComparisonReturnsFalseForNonEqualMatrices) {
  Matrix matrix{{{0, 1, 2}, {3, 4, 5}}};

  Matrix last_element_differ{{{0, 1, 2}, {3, 4, 99}}};
  Matrix missing_last_row{{{0, 1, 2}}};
  Matrix extra_row{{{0, 1, 2}, {4, 5, 6}, {4, 5, 6}}};
  Matrix extra_elements_in_row{{{0, 1, 2, 3}, {3, 5, 4, 5}}};
  Matrix missing_elements_in_row{{{0, 1}, {3, 5}}};

  EXPECT_NE(matrix, last_element_differ);
  EXPECT_NE(matrix, missing_last_row);
  EXPECT_NE(matrix, extra_row);
  EXPECT_NE(matrix, extra_elements_in_row);
  EXPECT_NE(matrix, missing_elements_in_row);
}
TEST(MatrixTest, TestThrowsWhenMatrixDoesNotHaveEqualRowLengths) {
  EXPECT_THROW(Matrix({{1, 2, 3}, {4, 5}}), std::invalid_argument);
}

TEST(MatrixTest, TestNumRowsReturnsNumberOfRows) {
  EXPECT_EQ(Matrix({{1, 3}, {1, 2}, {1, 2}}).num_rows(), 3);
  EXPECT_EQ(Matrix().num_rows(), 0);
}
TEST(MatrixTest, TestNumElementsReturnsNumberOfElements) {
  EXPECT_EQ(Matrix({{1, 3, 2}, {4, 5, 6}}).num_rows(), 2);
  EXPECT_EQ(Matrix().num_rows(), 0);
}

}  // namespace
