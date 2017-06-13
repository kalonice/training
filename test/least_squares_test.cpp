#include "gtest/gtest.h"
#include <least_squares.h>
#include "gaussian_elimination.h"

const int PRECISION_FOR_DOUBLES = 6;

TEST(Smoke_test, compare_with_manually_precalculated_examples) {
    std::vector<std::vector<double>> parameters_matrix = {{1, 2, 3, 4, 5, 6},
                                                          {1, 1, 1, 1, 1, 1}};
    std::vector<double> answers = {2, 3, 1, 5, 4, 8};
    std::vector<double> result;
    int result_code = least_squares<double>(parameters_matrix, answers,
                                            &result, gaussian_elimination<double>);
    std::vector<double> result_expected = {1.057142857, 0.1333333333};
    EXPECT_EQ(0, result_code);
    EXPECT_EQ(result_expected.size(), result.size());
    for (std::size_t i = 0; i < result_expected.size(); ++i) {
        EXPECT_NEAR(result_expected[i], result[i], PRECISION_FOR_DOUBLES)
                            << "Vectors x and y differ at index " << i;
    }
}
