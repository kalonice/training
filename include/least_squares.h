#ifndef INCLUDE_LEAST_SQUARES_H_
#define INCLUDE_LEAST_SQUARES_H_

#include <vector>
#include <functional>

// Matrix transformations
template <typename DataType>
void Multiply_Matrix_and_Vector_on_Transposed_Matrix(
        const std::vector<std::vector<DataType>>& matrix,
        const std::vector<DataType>& vector,
        std::vector<std::vector<DataType>>* result_matrix_ptr,
        std::vector<DataType>* result_vector_ptr) {
    /**
     * from     A = y
     * to       A*T(A) = y*T(A)
     */
    std::vector<std::vector<DataType>>& result_matrix = *result_matrix_ptr;
    std::vector<DataType>& result_vector = *result_vector_ptr;

    std::size_t rows = matrix.size();
    std::size_t cols = matrix[0].size();

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < rows; ++j) {
            for (std::size_t k = 0; k < cols; ++k) {
                result_matrix[i][j] += matrix[j][k] * matrix[i][k];
            }
        }
        for (std::size_t k = 0; k < cols; ++k) {
            result_vector[i] += vector[k] * matrix[i][k];
        }
    }
}


template <typename DataType>
int least_squares(const std::vector<std::vector<DataType>>& parameters_matrix,
                  const std::vector<DataType>& answers,
                  std::vector<DataType>* result_ptr,
                  std::function<int(std::vector<std::vector<DataType>>*,
                                    std::vector<DataType>*)> sole_solver) {
    std::vector<DataType>* result = result_ptr;
    /**
     * parameters_matrix - матрица восстанавливаемых параметров.
     *      т.е. снаружи подсчитаны не производные,
     *      а коэффициэнты при параметрах в зависимости от значений Xi
     *      строки здесь - параметры функции, столбцы - зависимость от Xi
     *      в рещультате у нас некая матрица A
     * answers - одна строка из Yi
     */

    /**
     * приводим "параметры" и "ответы" к системе линейных уравнений и решаем эту систему
     * если исходные "параметры" - матрица A, а "ответы" - вектор "y",
     * то система имеет вид :
     * A*T(A) = y*T(A)
     * где T(A) - транспонированная матрица A - мы не будем её отдельно хранить,
     * а будем обращаться к A, хитря с индексами
     */
    std::size_t rows = parameters_matrix.size();
    // sole = System of linear equations = СЛАУ = Система Линейных Алгебраических Уравнений
    std::vector<std::vector<DataType>> sole_matrix(rows, std::vector<DataType>(rows));
    std::vector<DataType> sole_constant_terms(rows);
    Multiply_Matrix_and_Vector_on_Transposed_Matrix(parameters_matrix,
                                                    answers,
                                                    &sole_matrix,
                                                    &sole_constant_terms);


    int result_code = sole_solver(&sole_matrix, &sole_constant_terms);
    if (result_code == 0) {
        *result = sole_constant_terms;
    }

    return result_code;
}


#endif  // INCLUDE_LEAST_SQUARES_H_
