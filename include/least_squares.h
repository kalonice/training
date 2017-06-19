#ifndef INCLUDE_LEAST_SQUARES_H_
#define INCLUDE_LEAST_SQUARES_H_

#include <vector>
#include <functional>
#include "constants.h"

namespace training {

// Matrix transformations
template<typename DataType>
void multiply_matrix_and_vector_on_transposed_matrix(
    const std::vector<std::vector<DataType>> &matrix,
    const std::vector<DataType> &vector,
    std::vector<std::vector<DataType>> *result_matrix_ptr,
    std::vector<DataType> *result_vector_ptr) {
  /**
   * from     A = y
   * to       A*T(A) = y*T(A)
   */
  std::vector<std::vector<DataType>> &result_matrix = *result_matrix_ptr;
  std::vector<DataType> &result_vector = *result_vector_ptr;

  auto rows = matrix.size();
  auto cols = matrix[0].size();

  auto i = rows;  // fake assignment - just for support types compare
  for (i = 0; i < rows; ++i) {
    auto j = rows;  // fake assignment - just for support types compare
    for (j = 0; j < rows; ++j) {
      auto k = cols;  // fake assignment - just for support types compare
      for (k = 0; k < cols; ++k) {
        result_matrix[i][j] += matrix[j][k] * matrix[i][k];
      }
    }
    auto k = cols;  // fake assignment - just for support types compare
    for (k = 0; k < cols; ++k) {
      result_vector[i] += vector[k] * matrix[i][k];
    }
  }
}

template<typename DataType>
LinSysReturnCodes least_squares(const std::vector<std::vector<DataType>> &parameters_matrix,
                              const std::vector<DataType> &answers,
                              std::vector<DataType> *result_ptr,
                              std::function<LinSysReturnCodes(
                                  std::vector<std::vector<DataType>> *,
                                  std::vector<DataType> *)> linsys_solver) {
  std::vector<DataType> *result = result_ptr;
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
  matrix_size_type<DataType> rows = parameters_matrix.size();
  // LinSys, linsys = System of linear equations = СЛАУ = Система Линейных Алгебраических Уравнений
  std::vector<std::vector<DataType>> linsys_matrix(rows, std::vector<DataType>(rows));
  std::vector<DataType> linsys_constant_terms(rows);
  multiply_matrix_and_vector_on_transposed_matrix(parameters_matrix,
                                                  answers,
                                                  &linsys_matrix,
                                                  &linsys_constant_terms);

  LinSysReturnCodes result_code = linsys_solver(&linsys_matrix, &linsys_constant_terms);
  if (result_code == LinSysReturnCodes::SUCCESS) {
    *result = std::move(linsys_constant_terms);   // std::move чтоб без копирования
  }

  return result_code;
}

}   // namespace training

#endif  // INCLUDE_LEAST_SQUARES_H_
