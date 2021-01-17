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


Matrix::Matrix(std::vector<double> &vector, int size)
{
    assert(size > 0);
    row = col = size;
    elem = new double*[row];

    for (int i = 0; i < row; i++)
    {
        elem[i] = new double[col];
        elem[i][i] = vector[i];
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

int Matrix::getRow() const
{
	return row;
}

int Matrix::getCol() const
{
	return col;
}

void Matrix::setValue(int row, int col, double value)
{
    assert ((row >= 0 && row < this->row) && (col >= 0 || col < this->col));

	elem[row][col] = value;
}


double Matrix::getValue(int row, int col) const
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

void Matrix::reducedEchelon()
{
    for (int i = 0; i < row; i++)
    {
        // 选取列主元所在的行
        int pivotRow = pickPivotRow(i);
        assert(pivotRow != -1);

        // 选取列主元所在的行与当前行交换
        swapTwoRow(pivotRow, i);

        // 选取列主元
        double pivot = getValue(i, i);

        // 列主元所在行除以列主元
        rowMulByConst(i, 1.0 / pivot);

        for (int j = i + 1; j < row; j++)
        {
            // 列主元以下的行变为0
            double rowValue = getValue(j, i);
            addRowToAnother(j, i, -1.0 * rowValue);
        }
    }

    // 现在是上三角矩阵

    for (int i = row - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            double rowValue = getValue(j, i);
            addRowToAnother(j, i, -1.0 * rowValue);
        }
    }
    // 现在是对角矩阵
}

Matrix Matrix::reverseMatrix()
{
    assert(row == col);
    std::vector<double> vector(row, 1.0);
    Matrix diagMatrix(vector, row);

    return this->operator/(diagMatrix);
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

Matrix Matrix::operator+(const Matrix& other)
{
    assert(row == other.row);
    assert(col == other.col);

    Matrix retMatrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
            double sum = getValue(i, j) + other.getValue(i, j);
            retMatrix.setValue(i, j, sum);
		}
	}

	return retMatrix;
}

Matrix Matrix::operator-(const Matrix& other)
{
    assert(row == other.row);
    assert(col == other.col);

    Matrix retMatrix(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            double sub = getValue(i, j) - other.getValue(i, j);
            retMatrix.setValue(i, j, sub);
        }
    }

    return retMatrix;
}

Matrix Matrix::operator*(const double scaler)
{
    Matrix retMatrix(row, col);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
            double mul = getValue(i, j) * scaler;
            retMatrix.setValue(i, j, mul);
		}
	}

	return retMatrix;
}

Matrix Matrix::operator*(const Matrix& other)
{
    assert(col == other.row);

    int retRow = row;
    int retCol = other.col;
    int tmpRow = col;
    Matrix retMatrix(retRow, retCol);

    for (int i = 0; i < retRow; i++)
	{
        for (int j = 0; j < retCol; j++)
		{
			double sum = 0;
            for (int k = 0; k < tmpRow; k++)
			{
                sum += getValue(i, k) * other.getValue(k, j);
			}
            retMatrix.setValue(i, j, sum);
		}
	}

	return retMatrix;
}

Matrix Matrix::operator/(const Matrix& other)
{
    Matrix retMatrix(*this);
    retMatrix.pushStack(other, DIRECTION_HORIZONTAL);
    retMatrix.reducedEchelon();
    return retMatrix.getCols(col, retMatrix.col);
}

Matrix Matrix::operator/(const double scaler)
{
    assert(fabs(scaler - 0.0) > EPS);
    return this->operator*(1.0 / scaler);
}

void Matrix::operator=(const Matrix& other)
{
    if (this == &other)
    {
        return;
    }

    this->~Matrix();

    row = other.row;
    col = other.col;
    elem = new double*[row];

    for (int r = 0; r < row; r++)
    {
        elem[r] = new double[col];
        memcpy(elem[r], other.elem[r], sizeof(double) * col);
    }
}

bool Matrix::operator!=(const Matrix& other)
{
	return !(*this == other);
}

bool Matrix::operator==(const Matrix& other)
{
    if (this == &other)
    {
        return true;
    }

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

Matrix Matrix::getRows(int startRow, int endRow)
{
    assert(startRow < endRow && endRow <= row);
    Matrix retMatrix(endRow - startRow, col);
    for (int r = startRow; r < endRow; r++)
    {
        memcpy(retMatrix.elem[r - startRow], elem[r], sizeof(double) * retMatrix.col);
    }
    return retMatrix;
}

Matrix Matrix::getCols(int startCol, int endCol)
{
    assert(startCol < endCol && endCol <= col);
    Matrix retMatrix(row, endCol - startCol);
    for (int r = 0; r < row; r++)
    {
        memcpy(retMatrix.elem[r], elem[r] + startCol, sizeof(double) * retMatrix.col);
    }
    return retMatrix;
}

void Matrix::pushStack(const Matrix& other, Stack_Direction_E direction)
{
    switch (direction)
    {
    case DIRECTION_HORIZONTAL:
        pushHorizontalStack(other);
        break;
    case DIRECTION_VERTICAL:
        pushVerticalStack(other);
        break;
    default:
        break;
    }
}

void Matrix::pushHorizontalStack(const Matrix& other)
{
    assert(row == other.row);

    for (int r = 0; r < row; r++)
    {
        double *tmp = new double[col];
        memcpy(tmp, elem[r], sizeof(double) * col);
        memcpy(tmp + col, other.elem[r], sizeof(double) * other.col);

        std::swap(elem[r], tmp);
        delete []tmp;
        tmp = nullptr;
    }
    col += other.col;
}

void Matrix::pushVerticalStack(const Matrix& other)
{
    assert(col == other.col);

    double **tmp = new double*[row + other.row];

    for (int r = 0; r < row; r++)
    {
        memcpy(tmp[r], elem[r], sizeof(double) * col);
    }
    for (int r = 0; r < other.row; r++)
    {
        memcpy(tmp[row + r], other.elem[r], sizeof(double) * col);
    }
    std::swap(tmp, elem);


    for (int r = 0; r < row; r++)
    {
        if (tmp[r])
        {
            delete []tmp[r];
            tmp[r] = nullptr;
        }
    }
    delete []tmp;
    tmp = nullptr;

    row += other.row;
}



