#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
        int n;  // Number of rows
        int m;  // Number of columns
        vector<vector<int>> values;  // Values of matrix
    public:
        int nrows();
        int ncols();
        Matrix();
        Matrix (int, int, vector<vector<int>>);
        vector<vector<int>> vals();
        void printMatrix();
        void setVals(vector<vector<int>>);
};

Matrix::Matrix ()
{
    n = 0;
    m = 0;
}

Matrix::Matrix (int a, int b, vector<vector<int>> v)
{
    n = a;
    m = b;
    values = v;
}

int Matrix::nrows()
{
    return n;
}

int Matrix::ncols()
{
    return m;
}

vector<vector<int>> Matrix::vals()
{
    return values;
}

void Matrix::setVals(vector<vector<int>> v)
{
    values = v;
}

void Matrix::printMatrix()
{
    for (int i = 0; i < values.size(); i++)
    {
        for (int j = 0; j < values[0].size(); j++)
        {
            cout << values[i][j] << " ";
        }
        cout << endl;
    }
}

class LinearAlgebra
{
    public:
        Matrix add(Matrix, Matrix);
};

Matrix LinearAlgebra::add(Matrix A, Matrix B)
{
    if (A.nrows() != B.nrows() || A.ncols() != B.ncols())
    {
        throw "Dimensions of A and B not compatible for addition";
    }
    vector<vector<int>> v;
    for (int i = 0; i < A.nrows(); i++) 
    {
        vector<int> row;
        for (int j = 0; j < A.ncols(); j++) 
        {
            row.push_back(A.vals()[i][j] + B.vals()[i][j]);
        }
        v.push_back(row);
    }
    return Matrix (A.nrows(), A.ncols(), v);
}

int main()
{
    vector<vector<int>> v1
    {
        {1,2},
        {3,4}
    };
    Matrix A (2, 2, v1);
    vector<vector<int>> v2
    {
        {5,6},
        {7,8}
    };
    Matrix B (2, 2, v2);
    LinearAlgebra la;
    Matrix C = la.add(A, B);
    C.printMatrix();
    return 0;
}