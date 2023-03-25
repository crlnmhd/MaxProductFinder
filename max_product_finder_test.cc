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

}  // namespace
