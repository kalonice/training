#include <least_squares.h>
#include <math.h>
#include <vector>
#include "gtest/gtest.h"
#include "./gaussian_elimination.h"

const double PRECISION_FOR_DOUBLES = 0.00000001;

TEST(SmokeTest, manually_precalculated_examples___ax_b) {
    // f = a*x + b
    std::vector<std::vector<double>> parameters_matrix = {{1, 2, 3, 4, 5, 6},
                                                          {1, 1, 1, 1, 1, 1}};
    std::vector<double> answers = {2, 3, 1, 5, 4, 8};
    std::vector<double> result;
    training::LinSysReturnCodes result_code = training::least_squares<double>(parameters_matrix, answers,
                                            &result, training::gaussian_elimination<double>);
    std::vector<double> result_expected = {1.057142857, 0.1333333333};
    EXPECT_EQ(training::LinSysReturnCodes::SUCCESS, result_code);
    EXPECT_EQ(result_expected.size(), result.size());
    for (std::vector<double>::size_type i = 0; i < result_expected.size(); ++i) {
        EXPECT_NEAR(result_expected[i], result[i], PRECISION_FOR_DOUBLES)
                            << "Vectors x and y differ at index " << i;
    }
}

TEST(SmokeTest, manually_precalculated_examples___asinx_b_cx) {
    // f = a*sin(x) + b + c*x
    std::vector<std::vector<double>> parameters_matrix = {
            {sin(1), sin(2), sin(3), sin(4), sin(5), sin(6)},
            {1, 1, 1, 1, 1, 1},
            {1, 2, 3, 4, 5, 6}};
    std::vector<double> answers = {2, 3, 1, 5, 4, 8};
    std::vector<double> result;
    training::LinSysReturnCodes result_code = training::least_squares<double>(parameters_matrix, answers,
                                            &result, training::gaussian_elimination<double>);
    std::vector<double> result_expected = {1.44954558, -1.596689209, 1.55856221};
    EXPECT_EQ(training::LinSysReturnCodes::SUCCESS, result_code);
    EXPECT_EQ(result_expected.size(), result.size());
    for (std::vector<double>::size_type i = 0; i < result_expected.size(); ++i) {
        EXPECT_NEAR(result_expected[i], result[i], PRECISION_FOR_DOUBLES)
                            << "Vectors x and y differ at index " << i;
    }
}

TEST(SmokeTest, manually_precalculated_examples___ax_bxx_cxxx) {
    // f = a*x + b*x^2 + c*x^3
    std::vector<std::vector<double>> parameters_matrix = {
            {1, 2, 3, 4, 5, 6},
            {1*1, 2*2, 3*3, 4*4, 5*5, 6*6},
            {1*1*1, 2*2*2, 3*3*3, 4*4*4, 5*5*5, 6*6*6}};
    std::vector<double> answers = {2, 3, 1, 5, 4, 8};
    std::vector<double> result;
    training::LinSysReturnCodes result_code = training::least_squares<double>(parameters_matrix, answers,
                                        &result, training::gaussian_elimination<double>);
    std::vector<double> result_expected = {2.567256817, -0.8968253968, 0.1146723647};
    EXPECT_EQ(training::LinSysReturnCodes::SUCCESS, result_code);
    EXPECT_EQ(result_expected.size(), result.size());
    for (std::vector<double>::size_type i = 0; i < result_expected.size(); ++i) {
        EXPECT_NEAR(result_expected[i], result[i], PRECISION_FOR_DOUBLES)
                            << "Vectors x and y differ at index " << i;
    }
}
