#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Matrix
{   
    public:
        int m;  // Number of rows
        int n;  // Number of columns
        vector<vector<int>> vals;  // Values of matrix
        Matrix (vector<vector<int>>);
        void printMatrix();
        void setVals(vector<vector<int>>);
};

Matrix::Matrix (vector<vector<int>> v)
{
    m = v.size();
    n = v[0].size();
    vals = v;
}

void Matrix::setVals(vector<vector<int>> v)
{
    vals = v;
}

void Matrix::printMatrix()
{
    for (int i = 0; i < vals.size(); i++)
    {
        for (int j = 0; j < vals[0].size(); j++)
        {
            cout << vals[i][j] << " ";
        }
        cout << endl;
    }
}

class LinearAlgebra
{
    public:
        Matrix add(Matrix, Matrix);
        Matrix multiply(Matrix, Matrix);
        Matrix strassen(Matrix, Matrix, int);
        Matrix gaussElim(Matrix);
};

Matrix LinearAlgebra::add(Matrix A, Matrix B)
{
    if (A.m != B.m || A.n != B.n)
    {
        throw "Dimensions of A and B not compatible for addition";
    }
    vector<vector<int>> v;
    for (int i = 0; i < A.m; i++) 
    {
        vector<int> row;
        for (int j = 0; j < A.n; j++) 
        {
            row.push_back(A.vals[i][j] + B.vals[i][j]);
        }
        v.push_back(row);
    }
    return Matrix (v);
}

Matrix LinearAlgebra::multiply(Matrix A, Matrix B)
{
    if (A.n != B.m)
    {
        throw "Dimensions of A and B not compatible for multiplication";
    }
    vector<vector<int>> v;
    for (int i = 0; i < A.m; i++)
    {
        vector<int> row;
        for (int j = 0; j < B.n; j++)
        {
            int val = 0;
            for (int k = 0; k < B.m; k++)
            {
                val += A.vals[i][k] * B.vals[k][j];
            }
            row.push_back(val);
        }
        v.push_back(row);
    }
    return Matrix (v);
}

// TODO
Matrix LinearAlgebra::strassen(Matrix A, Matrix B, int m)
{
    if (m <= 2)
    {
        vector<vector<int>> v = {
            { A.vals[0][0] * B.vals[0][0] + A.vals[0][1] * B.vals[1][0], A.vals[0][0] * B.vals[0][1] + A.vals[0][1] * B.vals[1][1] },
            { A.vals[1][0] * B.vals[0][0] + A.vals[1][1] * B.vals[1][0], A.vals[1][0] * B.vals[0][1] + A.vals[1][1] * B.vals[1][1] }
        };
        return Matrix (v);
    }

    m /= 2;
    vector<vector<int>> tmp = {{0}};
    return Matrix (tmp);
}

Matrix LinearAlgebra::gaussElim(Matrix A)
{
    int r = 0;  // Row of pivot
    int c = 0;  // Column of pivot

    while (r < A.m && c < A.n)
    {
        int pivot = r;
        while (pivot < A.m && A.vals[pivot][c] == 0)
        {
            pivot++;
        }

        if (pivot == A.m)
        {
            c++;
        }
        else
        {
            iter_swap(A.vals.begin() + r, A.vals.begin() + pivot);

            int fac = A.vals[r][c];  // We need to divide row by leading factor so that it becomes 1
            for (int i = c; i < A.n; i++)
            {
                A.vals[r][i] /= fac;
            }

            // Subtract the pivot row from the rows above (leading value times)
            for (int i = r+1; i < A.m; i++) 
            {
                int lead = A.vals[i][c];
                for (int j = c; j < A.n; j++)
                {
                    A.vals[i][j] -= A.vals[r][j] * lead;
                }
            }
            r++;
            c++;
        }
    }
    return A;
}

int main()
{
    vector<vector<int>> v1
    {
        {1,2,8},
        {3,4,3},
        {4,4,4}
    };
    Matrix A (v1);
    vector<vector<int>> v2
    {
        {5,6},
        {7,8}
    };
    Matrix B (v2);
    LinearAlgebra la;
    Matrix C = la.gaussElim(A);
    C.printMatrix();
    return 0;
}