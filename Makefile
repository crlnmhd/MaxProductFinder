CXX := g++
CXXFLAGS := -std=c++20 \
					 -Wall\
					 -Wextra \
					 -pedantic\
					 -Weffc++ \
					 -Wsuggest-attribute=const \
					 -fconcepts \
					 -Wsuggest-override \
					 -Werror=suggest-override \
					 -Werror=format-security \
					 -Wshadow \
					 -Wconversion\
					 -Wstrict-overflow \
					 -lgtest

CLASSES := max_product_finder.cc max_product_finder.cc matrix.cc
UNIT_TESTS := matrix_parser_test.cc max_product_finder_test.cc matrix_test.cc matrix_test.cc

assignment: $(CLASSES) assignment.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

tests: $(CLASSES) $(UNIT_TESTS) tests.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f assignment tests


