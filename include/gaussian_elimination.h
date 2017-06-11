#ifndef TRAINING_GAUSSIAN_ELIMINATION_H
#define TRAINING_GAUSSIAN_ELIMINATION_H

#include <vector>

template<typename DataType>
int gaussian_elimination(std::vector<std::vector<DataType>>& sole_matrix,
                         std::vector<DataType>& sole_constant_terms) {
    /**
     * для случая Квадратной Матрицы - число уравнений равно числу неизвестных - имеющей решение
     */
    std::size_t dimension = sole_matrix.size();

    // приводим к матрицу системы к единичной матрице
    for (std::size_t i = 0; i < dimension; ++i) {
        DataType divisor = sole_matrix[i][i];
        // делим эту строку (включая соответствующую позицию в столбце свободных членов) на divisor
        for (std::size_t j = 0; j < dimension; ++j) {
            sole_matrix[i][j] /= divisor;
        }
        sole_constant_terms[i] /= divisor;

        // из _остальных_ строк вычитаем несколько раз эту строку, чтобы соотв. столбез в них занулился
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

#endif //TRAINING_GAUSSIAN_ELIMINATION_H
