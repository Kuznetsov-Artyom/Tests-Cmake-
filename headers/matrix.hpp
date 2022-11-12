#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <stdexcept>


class Matrix
{
private:
	std::vector<int> mMatr;
	size_t mRow;
	size_t mCol;
	size_t mCount;

public:
	Matrix(size_t row, size_t col);
	Matrix(const Matrix& other) : mRow{ other.mRow }, mCol{ other.mCol }, mCount{ other.mCount }
	{
		mMatr.resize(mCount);
	}

	size_t getRow() const noexcept { return mRow; }
	size_t getCol() const noexcept { return mCol; }
	size_t getCount() const noexcept { return mCount; }


	Matrix& operator = (const Matrix& other);
	int& operator () (size_t i, size_t j);
	const int& operator () (size_t i, size_t j) const;
	

};

#endif // MATRIX_HPP
