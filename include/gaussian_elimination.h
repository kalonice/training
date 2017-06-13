#ifndef INCLUDE_GAUSSIAN_ELIMINATION_H_
#define INCLUDE_GAUSSIAN_ELIMINATION_H_

#include <vector>

template<typename DataType>
int gaussian_elimination(std::vector<std::vector<DataType>>* sole_matrix_ptr,
                         std::vector<DataType>* sole_constant_terms_ptr) {
    std::vector<std::vector<DataType>>& sole_matrix = *sole_matrix_ptr;
    std::vector<DataType>& sole_constant_terms = *sole_constant_terms_ptr;
    /**
     * для случая Квадратной Матрицы - число уравнений равно числу неизвестных - имеющей решение
     */
    if (sole_matrix.size() == 0) {
        return 1;
    }
    if (sole_matrix.size() != sole_matrix[0].size()) {
        return 1;
    }
    std::size_t dimension = sole_matrix.size();

    // приводим к матрицу системы к единичной матрице
    for (std::size_t i = 0; i < dimension; ++i) {
         const DataType& divisor = sole_matrix[i][i];
        // делим эту строку (включая соответствующую позицию в столбце свободных членов) на divisor
        for (std::size_t j = 0; j < i; ++j) {
            sole_matrix[i][j] /= divisor;
        }
        // сам i-й элемент "разделим" позже, ведь иначе запортим ссылку
        for (std::size_t j = i + 1; j < dimension; ++j) {
            sole_matrix[i][j] /= divisor;
        }
        sole_constant_terms[i] /= divisor;
        sole_matrix[i][i] = 1;

        // из _остальных_ строк вычитаем несколько раз эту строку,
        // чтобы соотв. столбез в них занулился
        for (std::size_t k = 0; k < dimension; ++k) {
            if (k != i) {
                DataType factor = sole_matrix[k][i];  // сколько раз вычитать i-ю строку из строки k
                for (std::size_t j = 0; j < dimension; ++j) {
                    sole_matrix[k][j] -= factor * sole_matrix[i][j];
                }
                sole_constant_terms[k] -= factor * sole_constant_terms[i];
            }
        }
    }

    return 0;
}

#endif  // INCLUDE_GAUSSIAN_ELIMINATION_H_
