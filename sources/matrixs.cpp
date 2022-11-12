#include "headers/matrixs.hpp"

namespace matrixs
{
    // Стандартная реализация перемножения матриц
    double multMatrixs(const Matrix& matrOne, const Matrix& matrTwo)
    {
        size_t mOne = matrOne.getRow();
        size_t mTwo = matrTwo.getRow();
        size_t nOne = matrOne.getCol();
        size_t nTwo = matrTwo.getCol();


        if (nOne != mTwo)
            throw std::logic_error{ "colM1 != rowM2" };


        Matrix newMatr(mOne, nTwo);
        double start{}, stop{};


        start = omp_get_wtime();

        for (int m1 = 0; m1 < mOne; ++m1)
            for (int n2 = 0; n2 < nTwo; ++n2)
                for (int n1m2 = 0; n1m2 < nOne; ++n1m2)
                    newMatr(m1, n2) += matrOne(m1, n1m2) * matrTwo(n1m2, n2);

        stop = omp_get_wtime();

        return stop - start;
    }




    // Параллельная реализация перемножения матриц
    double multMatrixsParallel(const Matrix& matrOne, const Matrix& matrTwo)
    {
        size_t mOne = matrOne.getRow();
        size_t mTwo = matrTwo.getRow();
        size_t nOne = matrOne.getCol();
        size_t nTwo = matrTwo.getCol();


        if (nOne != mTwo)
            throw std::logic_error{ "colM1 != rowM2" };


        Matrix newMatr(mOne, nTwo);
        double start{}, stop{};


        start = omp_get_wtime();

    #pragma omp parallel for shared(matrOne, matrTwo, newMatr)
        for (int m1 = 0; m1 < mOne; ++m1)
            for (int n2 = 0; n2 < nTwo; ++n2)
                for (int n1m2 = 0; n1m2 < nOne; ++n1m2)
                    newMatr(m1, n2) += matrOne(m1, n1m2) * matrTwo(n1m2, n2);

        stop = omp_get_wtime();

        return stop - start;
    }


    // Тестирование (сравнение стандартной и параллельной версий)
    void testMultMatrixs(uint32_t low, uint32_t up, uint16_t step)
    {
        // Создаем временный .txt файл, для сохранения результатов
        std::string path = "../../resultMatrixs.txt";
        std::ofstream fout;

        fout.open(path, std::fstream::out | std::fstream::app);


        for (uint32_t sizeMatr = low; sizeMatr <= up; sizeMatr += step)
        {
            // Размерность матриц на текущей итерации
            cout << "dimension of the matrix: " << sizeMatr << '\n';

             // Записываем размерность матриц в .txt для тестов
            fout << sizeMatr << ' ';

            Matrix matrOne(sizeMatr, sizeMatr);
            Matrix matrTwo(sizeMatr, sizeMatr);


            // Необходимо для генерации случайных чисел (алгоритм Вихрь Мерсенна)
            std::random_device rd;
            std::mt19937 mersenne(rd()); 
            int minValue = -1'000'000;
            int maxValue = 1'000'000;


            // Инициализируем матрицы случайными числами из диапазона [minValue, maxValue]
            cout << "generation matrixs..." << '\n';

            for (uint32_t i = 0; i < sizeMatr; ++i)
                for (uint32_t j = 0; j < sizeMatr; ++j)
                {
                    matrOne(i, j) = minValue + mersenne() % (maxValue - minValue + 1);
                    matrTwo(i, j) = minValue + mersenne() % (maxValue - minValue + 1);
                }


            // Начало тестирования
            cout << "TESTING\n";
            
            double resNoPar{}, resPar{};

            // Тест версии без параллелизма
            resNoPar = multMatrixs(matrOne, matrTwo);
            cout << "timer no parallel: " << resNoPar << " sec." << '\n';
            fout << resNoPar << ' ';


            // Тест версии с парарллелизмом
            resPar = multMatrixsParallel(matrOne, matrTwo);
            cout << "timer parallel: " << resPar << " sec." << '\n';
            fout << resPar << '\n';


            // Определение победителя
            cout << "winner: " << ((resPar < resNoPar) ? "parallel" :
            (resPar > resNoPar) ? "no par" : "par = no par") << "\n\n";
        }

        // Парсинг в exel

        fout.close();        
    }
    
} // namespace matrixs
