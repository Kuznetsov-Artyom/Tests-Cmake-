#include "headers/vectors.hpp"

namespace vectors
{
    // Стандартная реализация сложения двух векторов
    double sumVectors(const vector<int>& vecOne, const vector<int>& vecTwo)
    {
        // Если размерность разная бросаем исключение
        if (vecOne.size() != vecTwo.size())
            throw std::logic_error{ "vectors of different dimensions" };

        size_t size = vecOne.size();
        vector<int> newVec(size);

        double start{}, stop{};

        start = omp_get_wtime();
        for (size_t i = 0; i < size; ++i) newVec[i] = vecOne[i] + vecTwo[i];
        stop = omp_get_wtime();

        return stop - start;
    }




    // Параллельная реализация сложения двух векторов
    double sumVectorsParallel(const vector<int>& vecOne, const vector<int>& vecTwo)
    {
        // Если размерность разная бросаем исключение
        if (vecOne.size() != vecTwo.size())
            throw std::logic_error{ "vectors of different dimensions" };

        size_t size = vecOne.size();
        vector<int> newVec(size);

        double start{}, stop{};

        start = omp_get_wtime();
    #pragma omp parallel for shared(vecOne, vecTwo, newVec, size)
        for (int i = 0; i < size; ++i) newVec[i] = vecOne[i] + vecTwo[i];
        stop = omp_get_wtime();

        return stop - start;
    }




    // Тестирование (сравнение стандартной и параллельной версий)
    void testSumVectors(uint32_t low, uint32_t up, uint16_t stepMul)
    {
        // Создаем временный .txt файл, для сохранения результатов
        std::string path = "../../resultVectors.txt";
        std::ofstream fout;

        fout.open(path, std::fstream::out | std::fstream::app);
        
        
        for (uint32_t sizeVec = low; sizeVec <= up; sizeVec *= stepMul)
        {
            // Размерность векторов на текущей итерации
            cout << "dimension of the vector: " << sizeVec << '\n';

            // Записываем размерность векторов в .txt для тестов
            fout << sizeVec << ' ';

            vector<int> vecOne(sizeVec);
            vector<int> vecTwo(sizeVec);


            // Необходимо для генерации случайных чисел (алгоритм Вихрь Мерсенна)
            std::random_device rd;
            std::mt19937 mersenne(rd()); 
            int minValue = -1'000'000;
            int maxValue = 1'000'000;


            // Инициализируем вектора случайными числами из диапазона [minValue, maxValue]
            cout << "generation vecOne..." << '\n';
            for(auto& elem : vecOne) elem = minValue + mersenne() % (maxValue - minValue + 1);

            cout << "generation vecTwo..." << '\n';
            for (auto& elem : vecTwo) elem = minValue + mersenne() % (maxValue - minValue + 1);


            // Начало тестирования
            cout << "TESTING\n";

            double resNoPar{}, resPar{};

            // Тест версии без параллелизма
            resNoPar = sumVectors(vecOne, vecTwo);
            cout << "timer no parallel: " << resNoPar << " sec." << '\n';
            fout << resNoPar << ' ';


            // Тест версии с парарллелизмом
            resPar = sumVectorsParallel(vecOne, vecTwo);
            cout << "timer parallel: " << resPar << " sec." << '\n';
            fout << resPar << '\n';


            // Определение победителя
            cout << "winner: " << ((resPar < resNoPar) ? "parallel" :
            (resPar > resNoPar) ? "no par" : "par = no par") << "\n\n";
        }

        // Закрываем файл после записи результатов
         fout.close();

        // Парсинг в exel

        // Удаление временных файлов

    }

} // namespace vectors