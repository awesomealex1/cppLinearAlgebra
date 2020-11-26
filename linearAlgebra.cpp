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
        Matrix (vector<vector<int>>);
        vector<vector<int>> vals();
        void printMatrix();
        void setVals(vector<vector<int>>);
};

Matrix::Matrix (vector<vector<int>> v)
{
    n = v.size();
    m = v[0].size();
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
        Matrix multiply(Matrix, Matrix);
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
    return Matrix (v);
}

Matrix LinearAlgebra::multiply(Matrix A, Matrix B)
{
    if (A.ncols() != B.nrows())
    {
        throw "Dimensions of A and B not compatible for multiplication";
    }
    vector<vector<int>> v;
    for (int i = 0; i < A.nrows(); i++)
    {
        vector<int> row;
        for (int j = 0; j < B.ncols(); j++)
        {
            int val = 0;
            for (int k = 0; k < B.nrows(); k++)
            {
                val += A.vals()[i][k] * B.vals()[k][j];
            }
            row.push_back(val);
        }
        v.push_back(row);
    }
    return Matrix (v);
}

int main()
{
    vector<vector<int>> v1
    {
        {1,2},
        {3,4}
    };
    Matrix A (v1);
    vector<vector<int>> v2
    {
        {5,6},
        {7,8}
    };
    Matrix B (v2);
    LinearAlgebra la;
    Matrix C = la.multiply(A, B);
    C.printMatrix();
    return 0;
}