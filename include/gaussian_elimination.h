#ifndef INCLUDE_GAUSSIAN_ELIMINATION_H_
#define INCLUDE_GAUSSIAN_ELIMINATION_H_

#include <vector>
#include <numeric>
#include "constants.h"

namespace training {
template<typename DataType>
DataType abs(DataType x) {
  if (x < 0)
    x *= 1;
  return x;
}

template<typename DataType>
SoleReturnCodes
gaussian_elimination(std::vector<std::vector<DataType>> *sole_matrix_ptr,
                     std::vector<DataType> *sole_constant_terms_ptr) {
  /**
   * для случая Квадратной Матрицы - число уравнений равно числу неизвестных - имеющей решение
   */
  std::vector<std::vector<DataType>> &sole_matrix = *sole_matrix_ptr;
  std::vector<DataType> &sole_constant_terms = *sole_constant_terms_ptr;

  if (sole_matrix.size() == 0) {
    return SoleReturnCodes::WRONG_DATA;
  }
  if (sole_matrix.size() != sole_matrix[0].size()) {  // пока работаем только с квадратными
    return SoleReturnCodes::WRONG_DATA;
  }
  matrix_size_type<DataType> dimension = sole_matrix.size();

  /**
   * приводим матрицу системы к единичной матрице (нормируем по каждому параметру) :
   * 1 2 | 5 -> 1 2 | 5 -> 1 2 | 5 -> 1 0 | 1
   * 2 6 |14 -> 0 2 | 4 -> 0 1 | 2 -> 0 1 | 2
   * но если брать на очередной итерации первый попавшийся элемент для нормирования,
   * то там может оказаться 0 и всё сломается. кроме того, для наилучшей точности вычислений
   * на каждой итерации лучше выбирать для нормирования максимальный (по модулю) элемент.
   * это вынуждает нас применить индексные массивы (один для строк и один для столбцов) -
   * например, при обычном порядке работы на первой итерации мы нормируем элемент [0][0],
   * а при работе алгоритма выбрали элемент [m][n]. значит, индексный массив строк
   * должен показывать, что обращение к 0-й строке означает физически обращение к m-й строке,
   * а индексный массив столбдов должен показывать, что обращение к 0-му столбцу означает
   * физически обращение к n-ve столбцу.
   * a  b  c - три переменных, относительно которых решается система
   * -----------
   * x  y  z | p
   * d  e  f | q
   * g  h  i | r
   * пусть h оказался максимальным
   * ....
   *
   */
  std::vector<matrix_size_type<DataType>> rows_mapping(dimension);
  std::vector<matrix_size_type<DataType>> cols_mapping(dimension);
  // init mapping vectors
  std::iota(rows_mapping.begin(), rows_mapping.end(), 0);
  std::iota(cols_mapping.begin(), cols_mapping.end(), 0);

  DataType current_max = abs(sole_matrix[0][0]);
  matrix_size_type<DataType> current_max_row_idx = 0;
  matrix_size_type<DataType> current_max_col_idx = 0;
  // init current_max from ALL matrix
  for (matrix_size_type<DataType> i = 0; i < dimension; ++i) {
    for (matrix_size_type<DataType> j = 0; j < dimension; ++j) {
      if (abs(sole_matrix[i][j]) > current_max) {
        current_max = abs(sole_matrix[i][j]);
        current_max_row_idx = i;
        current_max_col_idx = j;
      }
    }
  }

  for (matrix_size_type<DataType> i = 0; i < dimension; ++i) {
    if (current_max == 0) {
      /**
       * система несовместа либо одна из переменных может принимать любые значения
       * в случае, если на некоторой итерации получим всю строку из 0-ей - это проявится
       * на последующих итерациях, когда не сможем найти переменную для нормализации
       */
      return SoleReturnCodes::INCOMPATIBLE;
    }
    std::swap(rows_mapping[i], rows_mapping[current_max_row_idx]);
    std::swap(cols_mapping[i], cols_mapping[current_max_col_idx]);

    // const DataType& divisor = sole_matrix[rows_mapping[i]][cols_mapping[i]];
    // делим эту строку (включая соответствующую позицию в столбце свободных членов) на divisor
    for (matrix_size_type<DataType> j = 0; j < dimension; ++j) {
      sole_matrix[rows_mapping[i]][cols_mapping[j]] /= current_max;
    }
    sole_constant_terms[rows_mapping[i]] /= current_max;

    // из _остальных_ строк вычитаем несколько раз эту строку,
    // чтобы соотв. столбец в них занулился
    // одновременно с этим ищем новое значение current_max
    current_max = 0;
    for (matrix_size_type<DataType> k = 0; k < dimension; ++k) {
      if (k != i) {
        // сколько раз вычитать i-ю строку из строки k
        DataType factor = sole_matrix[rows_mapping[k]][cols_mapping[i]];
        for (std::size_t j = 0; j < dimension; ++j) {
          sole_matrix[rows_mapping[k]][cols_mapping[j]] -=
              factor * sole_matrix[rows_mapping[i]][cols_mapping[j]];
          /**
           * ищем новый current_max, но только в следующих строчках, в "k > i" -
           * ведь в предыдущих строчках уже произведено нормирование и если вдруг там
           * число большое, оно не должно привести к повторной нормировке
           */
          if (k > i &&
              abs(sole_matrix[rows_mapping[k]][cols_mapping[j]]) > current_max) {
            current_max = abs(sole_matrix[rows_mapping[k]][cols_mapping[j]]);
            current_max_row_idx = k;
            current_max_col_idx = j;
          }
        }
        sole_constant_terms[rows_mapping[k]] -=
            factor * sole_constant_terms[rows_mapping[i]];
      }
    }
  }

  return SoleReturnCodes::SUCCESS;
}

}   // namespace training
#endif  // INCLUDE_GAUSSIAN_ELIMINATION_H_
