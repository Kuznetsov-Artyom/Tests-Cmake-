#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <omp.h>
#include <random>
#include <limits>


namespace vectors
{
    using std::vector;
    using std::cout;

    // Стандартная реализация сложения двух векторов
    double sumVectors(const vector<int>& vecOne, const vector<int>& vecTwo);

    // Параллельная реализация сложения двух векторов
    double sumVectorsParallel(const vector<int>& vecOne, const vector<int>& vecTwo);

    // Тестирование (сравнение стандартной и параллельной версий)
    void testSumVectors(uint32_t low = 10, uint32_t up = 1'000'000'000, uint16_t stepMul = 10);
    
} // namespace vectors


#endif // VECTORS_HPP