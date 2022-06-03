#pragma once
#ifndef CLASSMATRIX_H
#define CLASSMATRIX_H


#include <omp.h>
#include <thread>
#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::tuple;
class Matrix {
private:
    int n;
    int m;
    vector<vector<double> > m_matrix;
public:

    Matrix(int, int, double);
    ~Matrix();

    Matrix operator=(const Matrix&);

    double& operator()(const int&, const int&);
    void Print() const;
    void SwapRows(int i, int j);
    void SwapColumn(int i, int j);
    int getRows() const;
    Matrix scalarM(Matrix x);
    double scalarV(Matrix A);
    

};

#endif