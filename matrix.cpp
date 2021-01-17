#include "matrix.h"

#include <cassert>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>


Matrix::Matrix(int row, int col)
    : row(row)
    , col(col)
{
	assert(row > 0 && col > 0); 
    elem = new double*[row];

    for (int r = 0; r < row; r++)
	{
        elem[r] = new double[col];
	}
}

Matrix::Matrix(const Matrix& other)
{
	row = other.row;
	col = other.col;
    elem = new double*[row];

    for (int r = 0; r < row; r++)
    {
        elem[r] = new double[col];
        memcpy(elem[r], other.elem[r], sizeof(double) * col);
	}
}

// 生成对角矩阵
Matrix::Matrix(double* digArr, int size)
{
	assert(NULL != digArr && size > 0);
	row = col = size;
    elem = new double*[row];

	for (int i = 0; i < row; i++)
	{
        elem[i] = new double[col];
        elem[i][i] = digArr[i];
	}
}

Matrix::~Matrix()
{
    if (nullptr != elem)
	{
		for (int i = 0; i < row; i++)
		{
            if (nullptr != elem[i])
			{
                delete elem[i];
                elem[i] = nullptr;
			}
		}
        delete elem;
        elem = nullptr;
	}
}

/*
 * 属性：Private
 * row：行号
 * col：列号
 * 作用：判断矩阵中的某个元素是否近似为0
*/
bool Matrix::isNearlyZero(int row, int col)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

	return fabs(elem[row][col]) < EPS;
}

/*
 * 属性：Public
 * startRow：行号
 * 作用：获取某列主元所在行号
*/
int Matrix::pickPivotRow(int startRow)
{
	double tempValue = elem[startRow][startRow];
	int tempRow = startRow;
	for (int i = startRow + 1; i < row; i++)
	{
		if (fabs(elem[i][startRow]) - fabs(tempValue) > EPS)
		{
			tempValue = elem[i][startRow];
			tempRow = i;
		}
	}
	if (fabs(tempValue) < EPS)
	{
		return -1;
	}
	return tempRow;
}

int Matrix::getRow()
{
	return row;
}

int Matrix::getCol()
{
	return col;
}

void Matrix::setValue(int row, int col, double value)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

	elem[row][col] = value;
}


double Matrix::getValue(int row, int col)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

    return elem[row][col];
}

void Matrix::setValueReverse(int row, int col)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

	elem[row][col] = -1.0 * elem[row][col];
}

void Matrix::setValueReciprocal(int row, int col)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

	elem[row][col] = 1.0 / elem[row][col];
}

void Matrix::rowMulByConst(int row, double factor)
{
    assert (row >= 0 && row < this->row);

	for (int i = 0; i < col; i++)
	{
		elem[row][i] *= factor;
	}
}

void Matrix::addRowToAnother(int dRow, int sRow, double factor)
{
    assert (row >= 0 && row < this->row);

	for (int i = 0; i < col; i++)
	{
		elem[dRow][i] += factor * elem[sRow][i];
	}
}

void Matrix::swapTwoRow(int row1, int row2)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

    std::swap(elem[row1], elem[row2]);
}



int Matrix::reverseMatrix(Matrix** rMatrix)
{
	if (row != col)
	{
		return ERROR;
	}

	double* digArr = new double[row];
	for (int i = 0; i < row; i++)
	{
		digArr[i] = 1;
	}
	Matrix* retMatrix = new Matrix(digArr, row);
	Matrix tempMatrix(*this);

	for (int i = 0; i < row; i++)
	{
		int pivotRow = tempMatrix.pickPivotRow(i);
		if (-1 == pivotRow)
		{
			delete retMatrix;
			delete[] digArr;
			return ERROR;
		}

		tempMatrix.swapTwoRow(pivotRow, i);
		retMatrix->swapTwoRow(pivotRow, i);

        double pivot = tempMatrix.getValue(i, i);

		tempMatrix.rowMulByConst(i, 1.0 / pivot);
		retMatrix->rowMulByConst(i, 1.0 / pivot);

		for (int j = i + 1; j < row; j++)
		{
            double rowValue = tempMatrix.getValue(j, i);
			tempMatrix.addRowToAnother(j, i, -1.0 * rowValue);
			retMatrix->addRowToAnother(j, i, -1.0 * rowValue);
		}
	} // upper trianglur matrix now

	for (int i = row - 1; i > 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
            double rowValue = tempMatrix.getValue(j, i);
			tempMatrix.addRowToAnother(j, i, -1.0 * rowValue);
			retMatrix->addRowToAnother(j, i, -1.0 * rowValue);
		}
	}
	delete[] digArr;
	*rMatrix = retMatrix;

	return OK;
}

int Matrix::getDetermine(double* det)
{
	if (row != col)
	{
		return ERROR;
	}

	Matrix tempMatrix(*this);
	*det = 1;

	for (int i = 0; i < row; i++)
	{
		int pivotRow = tempMatrix.pickPivotRow(i);
		if (-1 == pivotRow)
		{
			*det = 0;
			return OK;
		}

		if (pivotRow != i)
		{
			tempMatrix.swapTwoRow(pivotRow, i);
			*det = -*det;
		}

        double pivot = tempMatrix.getValue(i, i);
		*det *= pivot;

		double mulFactor = -1.0 / pivot;

		for (int j = i + 1; j < row; j++)
		{
            double rowValue = tempMatrix.getValue(j, i);
			tempMatrix.addRowToAnother(j, i, mulFactor * rowValue);
		}
	} // upper trianglur matrix now

	return OK;
}

int Matrix::getRank()
{
	int rank = 0;
	int r = std::min(row, col);
	Matrix tempMatrix = Matrix(*this);

	for (int i = 0; i < r; i++)
	{
		int pivotRow = tempMatrix.pickPivotRow(i);
		if (-1 == pivotRow) //该列无主元
		{
			continue;
		}
		rank++;

		tempMatrix.swapTwoRow(pivotRow, i);

        double pivot = tempMatrix.getValue(i, i);
		tempMatrix.rowMulByConst(i, 1 / pivot);

		for (int j = i + 1; j < row; j++)
		{
            double value = tempMatrix.getValue(j, i);
			double factor = -1.0 * value;
			tempMatrix.addRowToAnother(j, i, factor);
		}
	}

	return rank;
}

Matrix* matrixAdd(Matrix& lMatrix, Matrix& rMatrix)
{
	assert(lMatrix.getRow() == rMatrix.getRow());
	assert(lMatrix.getCol() == rMatrix.getCol());

	int row = lMatrix.getRow();
	int col = lMatrix.getCol();
	Matrix* retMatrix = new Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
            double lValue = lMatrix.getValue(i, j);
            double rValue = rMatrix.getValue(i, j);

			retMatrix->setValue(i, j, lValue + rValue);
		}
	}

	return retMatrix;
}

Matrix* matrixSub(Matrix& lMatrix, Matrix& rMatrix)
{
	assert(lMatrix.getRow() == rMatrix.getRow());
	assert(lMatrix.getCol() == rMatrix.getCol());

	int row = lMatrix.getRow();
	int col = lMatrix.getCol();
	Matrix* retMatrix = new Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
            double lValue = lMatrix.getValue(i, j);
            double rValue = rMatrix.getValue(i, j);

			retMatrix->setValue(i, j, lValue - rValue);
		}
	}

	return retMatrix;
}

Matrix* matrixScalerMul(Matrix& matrix, double scaler)
{
	int row = matrix.getRow();
	int col = matrix.getCol();
	Matrix* retMatrix = new Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
            double value = matrix.getValue(i, j);
			retMatrix->setValue(i, j, scaler * value);
		}
	}

	return retMatrix;
}

Matrix* matrixMul(Matrix& lMatrix, Matrix& rMatrix)
{
	assert(lMatrix.getCol() == rMatrix.getRow());

	int row = lMatrix.getRow();
	int col = rMatrix.getCol();
	int rowCol = lMatrix.getCol();
	Matrix* retMatrix = new Matrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			double sum = 0;
			for (int k = 0; k < rowCol; k++)
			{
                double lValue = lMatrix.getValue(i, k);
                double rValue = rMatrix.getValue(k, j);

				sum += lValue * rValue;
			}
			retMatrix->setValue(i, j, sum);
		}
	}

	return retMatrix;
}

bool Matrix::operator!=(const Matrix& other)
{
	return !(*this == other);
}

bool Matrix::operator==(const Matrix& other)
{
	if (this->row != other.row || this->col != other.col)
	{
		return false;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (fabs(elem[i][j] - other.elem[i][j]) > EPS)
			{
				return false;
			}
		}
	}

	return true;
}






