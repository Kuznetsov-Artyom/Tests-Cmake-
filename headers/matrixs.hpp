#ifndef MATRIXS_HPP
#define MATRIXS_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <omp.h>
#include <random>
#include <limits>
#include "matrix.hpp"
#include <fstream>


namespace matrixs
{
    using std::cout;

    // Стандартная реализация перемножения матриц
    double multMatrixs(const Matrix& matrOne, const Matrix& matrTwo);

    // Параллельная реализация перемножения матриц
    double multMatrixsParallel(const Matrix& matrOne, const Matrix& matrTwo);

    // Тестирование (сравнение стандартной и параллельной версий)
    void testMultMatrixs(uint32_t low = 10, uint32_t up = 1'010, uint16_t step = 200);

} // namespace matrixs




#endif // MATRIXS_HPP