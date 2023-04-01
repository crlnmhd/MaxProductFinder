#include "max_product_finder.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace {

TEST(MaxProductFinder, DoesNotReturnValueForTooSmallMatrices) {
  MaxProductFinder max_product_finder;

  EXPECT_FALSE(max_product_finder.max_product(Matrix(), 1).has_value());
  EXPECT_FALSE(max_product_finder.max_product(Matrix(), 0).has_value());
  EXPECT_FALSE(max_product_finder.max_product(Matrix({{1, 2, 3}, {1, 2, 3}}), 4)
                   .has_value());
}

TEST(MaxProductFinder, FindsMaxProductInRowForOneRowMatrix) {
  MaxProductFinder max_product_finder;
  Matrix matrix{{{1, 2, 3, 4, 2}}};
  EXPECT_EQ(max_product_finder.max_product(matrix, 4), 2 * 3 * 4 * 2);
  EXPECT_EQ(max_product_finder.max_product(matrix, 3), 2 * 3 * 4);
  EXPECT_EQ(max_product_finder.max_product(matrix, 2), 3 * 4);
  EXPECT_EQ(max_product_finder.max_product(matrix, 1), 4);
}
TEST(MaxProductFinder, FindsMaxProductInMatrix) {
  MaxProductFinder max_product_finder;
  Matrix matrix{{{1, 2, 3, 0}, {1, 2, 3, 5}, {0, 1, 0, 99}}};
  EXPECT_EQ(max_product_finder.max_product(matrix, 4),
            1 * 2 * 3 * 5);  // middle row
  EXPECT_EQ(max_product_finder.max_product(matrix, 3),
            2 * 3 * 99);  // right diagonal
  EXPECT_EQ(max_product_finder.max_product(matrix, 2), 5 * 99);  // down
  EXPECT_EQ(max_product_finder.max_product(matrix, 1), 99);      // largest
}
TEST(MaxProductFinder, FindsMaxProductInLeftDiagonalOfMatrix) {
  MaxProductFinder max_product_finder;
  Matrix matrix{{{1, 2, 99, 0}, {1, 99, 3, 5}, {99, 1, 0, 99}}};
  EXPECT_EQ(max_product_finder.max_product(matrix, 3),
            99 * 99 * 99);  // left diagonal
}

}  // namespace
