#if !defined(MATRIX_PARSER_H)
#define MATRIX_PARSER_H

#include <sstream>
#include <string>
#include <vector>

#include "matrix.h"

class MatrixParser {
 public:
  Matrix from_string(const std::string str) {
    std::vector<matrix::Row> result{};
    std::istringstream iss{str};
    std::string row{};
    while (std::getline(iss, row)) {
      result.emplace_back(this->parse_row(row));
    }
    return Matrix{result};
  }

 private:
  matrix::Row parse_row(const std::string str) {
    std::stringstream ss(str);
    matrix::Row result{};
    int elem{};
    while (ss >> elem) {
      result.emplace_back(elem);
    }
    return result;
  }
};

#endif  // MATRIX_PARSER_H
