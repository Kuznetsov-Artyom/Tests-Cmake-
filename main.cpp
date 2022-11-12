#include <iostream>
#include "headers/vectors.hpp"
#include "headers/matrixs.hpp"







int main(int argc, char* argv[])
{
    std::cout << "+-+-+-+-+-+-+-+ VECTORS +-+-+-+-+-+-+-+\n";
    vectors::testSumVectors();

    std::cout << "+-+-+-+-+-+-+-+ MATRIXS +-+-+-+-+-+-+-+\n";
    matrixs::testMultMatrixs();


    return 0;
}