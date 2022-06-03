#include <iostream>
#include "ClassMatrix.h"
#include "Gauss.h"
#include "GaussSeidel.h"
#include "Jacobi.h"
#include "Gradient.h"
#include "CG.h"
#include <cmath>
#include <ctime>

using namespace std;
int main() {
    srand(time(NULL));
    int n = 10000, flag = 0;
    double eps = 0.0001;
    Matrix M(n, n + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                M(i, j) = (double)(2*n);
            }
            else
                M(i, j) = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        M(i, n) = rand()%5001;
    }
    
    std :: cout << "size 10000*10000 \n";
    //JACOBI:
    clock_t start, end;
    start = clock();
    /*
    std::cout << "Jacobi, eps = 0.0001: \n";
    Jacobi (M,eps);
    std::cout << "\n" << "\n";
    end = clock();
    std::cout << "\n" << (double)(end - start) / (double)CLOCKS_PER_SEC << " sec" << "\n";

    std :: cout << "---------------------------------------- \n";

    std :: cout << "Gradient: steapest decent\n";
    start = clock();
    Grad(temp2);
    end = clock();
    
    std::cout << "\n" << (double)(end - start) / (double)CLOCKS_PER_SEC << " sec" << "\n";
    */
    std :: cout << "-------------------------------------- \n";
    std :: cout << "Gauss Seidel: \n";
    start = clock();
    GaussSeidel(M,eps);
    end = clock() - start;
    std :: cout << (double)end / (double)CLOCKS_PER_SEC << " sec\n";
/*
    std :: cout << "-------------------------------------- \n";
    std :: cout << "CGM: \n";
    start = clock();
    CG(temp,eps);
    end = clock() - start;
    std :: cout << (double)end / (double)CLOCKS_PER_SEC << " sec\n";*/
    
                
    return 0;
        
}