#define ERROR 1
#define OK 0

#include <vector>


#define EPS 1e-4


typedef enum
{
    DIRECTION_HORIZONTAL,
    DIRECTION_VERTICAL,
    DIRECTION_MAX,
}Stack_Direction_E;


class Matrix
{
public:
    Matrix(int row = 3, int col = 3);
	Matrix(const Matrix& other);
    Matrix(std::vector<double> &vector, int size); // diag matrix
	~Matrix();
	
    void operator=(const Matrix& other);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix operator*(const double scaler);
    Matrix operator/(const Matrix& other);
    Matrix operator/(const double scaler);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);

    Matrix getRows(int startRow, int endRow);
    Matrix getCols(int startCol, int endCol);
    void pushStack(const Matrix& other, Stack_Direction_E direction);
    void pushHorizontalStack(const Matrix& other);
    void pushVerticalStack(const Matrix& other);

    int getRow() const; //获取行数
    int getCol() const; //获取列数
    void setValue(int row, int col, double value); // 赋值
    double getValue(int row, int col) const; // 获得数值
    void setValueReverse(int row, int col); //元素取相反数
    void setValueReciprocal(int row, int col); //元素取倒数

    void rowMulByConst(int row, double factor); // 行乘标量
    void addRowToAnother(int dRow, int sRow, double factor); // 某行乘一标量加到另一行
    void swapTwoRow(int row1, int row2); // s交换两行

	int getDetermine(double* det); // 计算行列式
    Matrix reverseMatrix(); // 计算逆矩阵
    void reducedEchelon();

    int getRank(); // 计算矩阵的秩

private:
    bool isNearlyZero(int row, int col);
	int pickPivotRow(int startRow); // 获取某列上主元所在行号

private:
    double** elem;
    int row;
    int col;
};

