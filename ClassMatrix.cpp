#include "ClassMatrix.h"
using namespace std;

Matrix::Matrix(int rowSize, int colSize, double initial) {
    n = rowSize;
    m = colSize;
    m_matrix.resize(rowSize);
    for (int i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(colSize, initial);
    }
}


Matrix::~Matrix() {

}

Matrix Matrix :: operator=(const Matrix& B) {
    n = B.n;
    m = B.m;
    m_matrix.resize(n);
    for (int i = 0; i < n; i++) {
        m_matrix[i].resize(m);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            m_matrix[i][j] = B.m_matrix[i][j];
        }
    }
    
    return *this;
}

double& Matrix::operator()(const int& rowNo, const int& colNo)
{
    return this->m_matrix[rowNo][colNo];
}

int Matrix::getRows() const
{
    return this->n;
}


void Matrix::Print() const
{
    cout << "Matrix: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << m_matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void Matrix::SwapRows(int i, int j) {
#pragma omp parallel for
    for (int k = 0; k <= n; k++)
    {
        double temp = m_matrix[i][k];
        m_matrix[i][k] = m_matrix[j][k];
        m_matrix[j][k] = temp;
    }
}

void Matrix::SwapColumn(int i, int j) {
#pragma omp parallel for
    for (int k = 0; k < n; k++) 
    {
        double temp = m_matrix[k][i];
        m_matrix[k][i] = m_matrix[k][j];
        m_matrix[k][j] = temp;
    }
}

Matrix Matrix::scalarM(Matrix x) {
    Matrix temp(n, 1, 0);
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp(i,0) += m_matrix[i][j] * x(j, 0);
        }
            
    }
    return temp;
}
double Matrix::scalarV(Matrix A) {;
    double temp = 0;

    for (int i = 0; i < n; i++) {
        temp += m_matrix[i][0]*A.m_matrix[i][0];
    }
    return temp;
}