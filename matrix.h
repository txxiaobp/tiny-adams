#ifndef MATRIX_H
#define MATRIX_H

#include <vector>


#define EPS 1e-10

class Matrix;
typedef Matrix Vector;

typedef enum
{
    DIRECTION_HORIZONTAL,
    DIRECTION_VERTICAL,
    DIRECTION_MAX,
}Stack_Direction_E;


class Matrix
{
public:
    Matrix(int row = 3, int col = 1);
    Matrix(std::vector<double> vector, int row, int col);
    Matrix(std::vector<double> vector); //vector
    Matrix(std::vector<double> &vector, int size); // diag matrix
    Matrix(const Matrix& other);
    virtual ~Matrix();
	
    void showMatrix() const;
    void showSize() const;

    double& operator[](int posIndex);
    double operator[](int posIndex) const;
    void operator=(const Matrix& other);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator*(const double scaler);
    Matrix operator/(const Matrix& other);
    Matrix operator/(const double scaler);
    Matrix operator+(const Matrix& other);
    void operator+=(const Matrix& other);
    Matrix operator-(const Matrix& other);
    bool operator<(const Matrix &matrix) const;

    int getRow() const; //获取行数
    int getCol() const; //获取列数
    double getValue(int row, int col) const; // 获得数值
    void setValue(int row, int col, double value); // 赋值

    Matrix shrink(int startRow, int endRow, int startCol, int endCol) const;
    Matrix reverseMatrix(); // 计算逆矩阵
    Matrix transpose(); // 计算转置矩阵
    int getDetermine(); // 计算行列式
    int getRank(); // 计算矩阵的秩
    bool isFullRank() { return getRank() == col; }

    // 扩充矩阵
    void pushStack(const Matrix& other, Stack_Direction_E direction);

protected:
    bool isNearlyZero(int row, int col);
	int pickPivotRow(int startRow); // 获取某列上主元所在行号
    void reducedEchelon(); // 矩阵变换成行阶梯最简型

    /* 矩阵基本变换 */
    void rowMulByConst(int row, double factor); // 行乘标量
    void addRowToAnother(int dRow, int sRow, double factor); // 某行乘一标量加到另一行
    void swapTwoRow(int row1, int row2); // s交换两行

    void setValueReverse(int row, int col); //元素取相反数
    void setValueReciprocal(int row, int col); //元素取倒数

    // 截取矩阵
    Matrix getRows(int startRow, int endRow);
    Matrix getCols(int startCol, int endCol);

    void pushHorizontalStack(const Matrix& other);
    void pushVerticalStack(const Matrix& other);

protected:
    double** elem;
    int row;
    int col;
};

#endif

