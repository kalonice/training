#ifndef INCLUDE_GAUSSIAN_ELIMINATION_H_
#define INCLUDE_GAUSSIAN_ELIMINATION_H_

#include <vector>
#include <numeric>
#include <utility>
#include "./constants.h"

namespace training {
template<typename DataType>
DataType abs(DataType x) {    // в стандартных библиотеках не было шаблонизированного abs
  if (x < 0)
    return -x;
  else
    return x;
}

template<typename DataType>
LinSysReturnCodes
gaussian_elimination(std::vector<std::vector<DataType>> *linsys_matrix_ptr,
                     std::vector<DataType> *linsys_constant_terms_ptr) {
  /**
   * для случая Квадратной Матрицы - число уравнений равно числу неизвестных - имеющей решение
   */
  std::vector<std::vector<DataType>> &linsys_matrix = *linsys_matrix_ptr;
  std::vector<DataType> &linsys_constant_terms = *linsys_constant_terms_ptr;

  if (linsys_matrix.size() == 0) {
    return LinSysReturnCodes::WRONG_DATA;
  }
  if (linsys_matrix.size() != linsys_matrix[0].size()) {  // пока работаем только с квадратными
    return LinSysReturnCodes::WRONG_DATA;
  }
  matrix_size_type<DataType> dimension = linsys_matrix.size();

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
   * физически обращение к n-му столбцу.
   * a  b  c - три переменных, относительно которых решается система
   * -----------
   * x  y  z | p
   * d  e  f | q
   * g  h  i | r
   * пусть h оказался максимальным. а при обычном порядке мы вначале должны обрабатывать [0][0]
   * тогда индексный массив строк из {0,1,2} превратится в {2,1,0}, а столбцов - в {1,0,2}
   * и обращая/сь через них к [0][0] мы на самом деле обратимся к
   * [{2,1,0}.[0]][{1,0,2}.[0]] => [2][1]
   * и т.д.
   */
  std::vector<matrix_size_type<DataType>> rows_mapping(dimension);
  std::vector<matrix_size_type<DataType>> cols_mapping(dimension);
  // init mapping vectors
  std::iota(rows_mapping.begin(), rows_mapping.end(), 0);
  std::iota(cols_mapping.begin(), cols_mapping.end(), 0);

  DataType pivot = abs(linsys_matrix[0][0]);
  matrix_size_type<DataType> pivot_row_idx = 0;
  matrix_size_type<DataType> pivot_col_idx = 0;
  // init pivot across ALL matrix elements
  for (matrix_size_type<DataType> i = 0; i < dimension; ++i) {
    for (matrix_size_type<DataType> j = 0; j < dimension; ++j) {
      if (abs(linsys_matrix[i][j]) > pivot) {
        pivot = abs(linsys_matrix[i][j]);
        pivot_row_idx = i;
        pivot_col_idx = j;
      }
    }
  }

  for (matrix_size_type<DataType> i = 0; i < dimension; ++i) {
    if (pivot == 0) {
      /**
       * система несовместа либо одна из переменных может принимать любые значения
       * в случае, если на некоторой итерации получим всю строку из 0-ей - это проявится
       * на последующих итерациях, когда не сможем найти переменную для нормализации
       */
      return LinSysReturnCodes::INCOMPATIBLE;
    }
    std::swap(rows_mapping[i], rows_mapping[pivot_row_idx]);
    std::swap(cols_mapping[i], cols_mapping[pivot_col_idx]);

    // делим эту строку (включая соответствующую позицию в столбце свободных членов) на divisor
    for (matrix_size_type<DataType> j = 0; j < dimension; ++j) {
      linsys_matrix[rows_mapping[i]][cols_mapping[j]] /= pivot;
    }
    linsys_constant_terms[rows_mapping[i]] /= pivot;

    // из _остальных_ строк вычитаем несколько раз эту строку,
    // чтобы соотв. столбец в них занулился
    // одновременно с этим ищем новое значение pivot
    pivot = 0;
    for (matrix_size_type<DataType> k = 0; k < dimension; ++k) {
      if (k != i) {
        // сколько раз вычитать i-ю строку из строки k
        DataType factor = linsys_matrix[rows_mapping[k]][cols_mapping[i]];
        for (std::size_t j = 0; j < dimension; ++j) {
          linsys_matrix[rows_mapping[k]][cols_mapping[j]] -=
              factor * linsys_matrix[rows_mapping[i]][cols_mapping[j]];
          /**
           * ищем новый current_max, но только в следующих строчках, в "k > i" -
           * ведь в предыдущих строчках уже произведено нормирование и если вдруг там
           * число большое, оно не должно привести к повторной нормировке
           */
          if (k > i &&
              abs(linsys_matrix[rows_mapping[k]][cols_mapping[j]]) > pivot) {
            pivot = abs(linsys_matrix[rows_mapping[k]][cols_mapping[j]]);
            pivot_row_idx = k;
            pivot_col_idx = j;
          }
        }
        linsys_constant_terms[rows_mapping[k]] -=
            factor * linsys_constant_terms[rows_mapping[i]];
      }
    }
  }

  return LinSysReturnCodes::SUCCESS;
}

}   // namespace training
#endif  // INCLUDE_GAUSSIAN_ELIMINATION_H_
