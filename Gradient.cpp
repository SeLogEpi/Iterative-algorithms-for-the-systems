#include "Gradient.h"

void Grad(Matrix M) {
    int n = M.getRows();
    Matrix X(n, 1, 0);
    double alpha = {};
    int count = 0;
    while (count < 100) {
        Matrix temp_x = X;
        Matrix temp1 = M.scalarM(X);
#pragma omp parallel for
        for (int i = 0; i < n; i++) {
            temp1(i, 0) -= M(i, n);
        }
        Matrix temp2 = M.scalarM(temp1);
        alpha = (temp1.scalarV(temp1)) / (temp2.scalarV(temp1));
#pragma omp parallel for
        for (int i = 0; i < n; i++) {
            temp1(i, 0) *= alpha;
            temp_x(i, 0) -= temp1(i, 0);
        }
        double eps = 0;
        for (int k = 0; k < n; k++) {
            eps += fabs(temp_x(k, 0) - X(k, 0));
        }
        if (eps < 0.0001) break;
        X = temp_x;
        count++;
    }
    /*for (int i = 0; i < n; i++) {
        std::cout << "X[" << i + 1 << "] = " << X(i, 0) << "\n";
    }*/
}
