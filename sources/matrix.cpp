#include "headers/matrix.hpp"

Matrix::Matrix(size_t row, size_t col) : mRow{ row }, mCol{ col }, mCount{}
{
	if (mRow == 0 || mCol == 0)
		throw std::invalid_argument{ "there is zero in the passed arguments" };

	mCount = mRow * mCol;
	mMatr.resize(mCount);
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this == &other) return *this;

	mRow = other.mRow;
	mCol = other.mCol;
	mCount = other.mCount;
	mMatr = other.mMatr;

	return *this;
}

const int& Matrix::operator()(size_t i, size_t j) const
{
	if (i >= mRow || j >= mCol)
		throw std::out_of_range{ "going out of range" };

	return mMatr[i * mCol + j];
}

int& Matrix::operator () (size_t i, size_t j)
{
	if (i >= mRow || j >= mCol)
		throw std::out_of_range{ "going out of range" };

	size_t ind = i * mCol + j;

	return mMatr[i * mCol + j];
}
