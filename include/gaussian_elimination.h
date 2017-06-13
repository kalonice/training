#ifndef INCLUDE_GAUSSIAN_ELIMINATION_H_
#define INCLUDE_GAUSSIAN_ELIMINATION_H_

#include <vector>

template<typename DataType>
int gaussian_elimination(std::vector<std::vector<DataType>>* sole_matrix_ptr,
                         std::vector<DataType>* sole_constant_terms_ptr) {
    /**
     * для случая Квадратной Матрицы - число уравнений равно числу неизвестных - имеющей решение
     */
    std::vector<std::vector<DataType>>& sole_matrix = *sole_matrix_ptr;
    std::vector<DataType>& sole_constant_terms = *sole_constant_terms_ptr;

    if (sole_matrix.size() == 0) {
        return 1;
    }
    if (sole_matrix.size() != sole_matrix[0].size()) {  // пока работаем только с квадратными
        return 1;
    }
    std::size_t dimension = sole_matrix.size();

    /**
     * приводим матрицу системы к единичной матрице (нормируем по каждому параметру) :
     * 1 2 | 5 -> 1 2 | 5 -> 1 2 | 5 -> 1 0 | 1
     * 2 6 |14 -> 0 2 | 4 -> 0 1 | 2 -> 0 1 | 2
     * но если брать на очередной итерации первый попавшийся элемент для нормирования,
     * то там может оказаться 0 и всё сломается
     * поэтому - храним в отдельном set-е набор индексов, которые уже отнормировали,
     * ищем в столбце первый ненулевой элемент не из этого set-а и нормируем по нему
     */
    std::set<size_t> normalized;
    for (std::size_t i = 0; i < dimension; ++i) {
        bool flag;
        std::size_t normal_idx;
        for (std::size_t j = 0; j < dimension; ++j) {
            if (sole_matrix[j][i] != 0 && normalized.count(j) == 0) {
                flag = true;
                normal_idx = j;
                break;
            }
        }
        if (!flag) {
            return 2;       //
        }
        const DataType& divisor = sole_matrix[normal_idx][i];
        // делим эту строку (включая соответствующую позицию в столбце свободных членов) на divisor
        for (std::size_t j = 0; j < normal_idx; ++j) {
            sole_matrix[normal_idx][j] /= divisor;
        }
        // сам i-й элемент "разделим" позже, ведь иначе запортим ссылку
        for (std::size_t j = normal_idx + 1; j < dimension; ++j) {
            sole_matrix[normal_idx][j] /= divisor;
        }
        sole_constant_terms[normal_idx] /= divisor;
        sole_matrix[normal_idx][i] = 1;

        // из _остальных_ строк вычитаем несколько раз эту строку,
        // чтобы соотв. столбец в них занулился
        for (std::size_t k = 0; k < dimension; ++k) {
            if (k != normal_idx) {
                DataType factor = sole_matrix[k][i];  // сколько раз вычитать i-ю строку из строки k
                for (std::size_t j = 0; j < dimension; ++j) {
                    sole_matrix[k][j] -= factor * sole_matrix[normal_idx][j];
                }
                sole_constant_terms[k] -= factor * sole_constant_terms[normal_idx];
            }
        }

        normalized.insert(normal_idx);
    }

    return 0;
}

#endif  // INCLUDE_GAUSSIAN_ELIMINATION_H_
