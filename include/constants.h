#ifndef INCLUDE_CONSTANTS_H_
#define INCLUDE_CONSTANTS_H_

#include <vector>

namespace training {

enum class LinSysReturnCodes {    // LinSys = System of linear equations
  SUCCESS,        // решение найдено
  WRONG_DATA,     // кривые входные данные
  INCOMPATIBLE    // несовместная система линейных уравнений
};

template<typename DataType>
using matrix_size_type = typename std::vector<std::vector<DataType>>::size_type;
}   // namespace training

#endif    // INCLUDE_CONSTANTS_H_
