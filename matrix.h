#define ERROR 1
#define OK 0

#define EPS 1e-4

class Matrix
{
private:
	double** elem;
	int row;
	int col;

public:
    Matrix(int row = 3, int col = 3);
	Matrix(const Matrix& other);
	Matrix(double* digNum, int size);
	Matrix(int size);
	~Matrix();
	
	int getRow(); //获取行数
	int getCol(); //获取列数
    void setValue(int row, int col, double value); // 赋值
    double getValue(int row, int col); // 获得数值
    void setValueReverse(int row, int col); //元素取相反数
    void setValueReciprocal(int row, int col); //元素取倒数

    void rowMulByConst(int row, double factor); // 行乘标量
    void addRowToAnother(int dRow, int sRow, double factor); // 某行乘一标量加到另一行
    void swapTwoRow(int row1, int row2); // s交换两行
	int getDetermine(double* det); // 计算行列式
	int reverseMatrix(Matrix** rMatrix); // 计算逆矩阵
	bool operator==(const Matrix& other);
	bool operator!=(const Matrix& other);
	int getRank();

private:
    bool isNearlyZero(int row, int col);
	int pickPivotRow(int startRow); // 获取某列上主元所在行号
};

Matrix* matrixMul(Matrix& lMatrix, Matrix& rMatrix);
Matrix* matrixScalerMul(Matrix& matrix, double scaler);
Matrix* matrixAdd(Matrix& lMatrix, Matrix& rMatrix);
Matrix* matrixSub(Matrix& lMatrix, Matrix& rMatrix);
