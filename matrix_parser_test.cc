#include "matrix_parser.h"

#include <gtest/gtest.h>

#include <numbers>

namespace {
TEST(MatrixParserTest, TestParsesInt) {
  MatrixParser matrix_parser;
  const Matrix expcted_matrix{{{42}}};
  EXPECT_EQ(matrix_parser.from_string("42"), expcted_matrix);
}
TEST(MatrixParserTest, TestParsesSingleLineIntoSingleLineMatrix) {
  MatrixParser matrix_parser;
  const Matrix expcted_matrix{{{0, 1, 2, 3}}};
  EXPECT_EQ(matrix_parser.from_string("00 01 02 03"), expcted_matrix);
}
TEST(MatrixParserTest, TestParsesTo2DMatrixWhenStringHasNewline) {
  MatrixParser matrix_parser;
  const Matrix expcted_matrix{{{0, 1, 2, 3}, {4, 5, 6, 7}}};
  EXPECT_EQ(matrix_parser.from_string("00 01 02 03\n04 05 06 07\n"),
            expcted_matrix);
}
}  // namespace
