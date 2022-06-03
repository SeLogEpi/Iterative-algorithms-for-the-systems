#include "CG.h"


void CG(Matrix M, double tol) {
	int n = M.getRows(), k = 0;
	double alpha = {}, betta = {};
	Matrix X(n, 1, 0);
	Matrix b(n, 1, 0);
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		b(i, 0) = M(i, n);
	}
	 tol *= sqrt(b.scalarV(b));
	Matrix grad = M.scalarM(X);
#pragma omp parallel for
	for (int i = 0; i < n; i++) {
		grad(i, 0) = M(i, n) - grad(i, 0);
	}
	Matrix p = grad;
	double grad2 = sqrt(grad.scalarV(grad));
	//std::cout <<"grad2 = " <<  grad2 << " tol = "<< tol << "\n";
	while (grad2 >= tol && k < n) {
		Matrix Ap = M.scalarM(p);
		alpha = (pow(grad2,2) / (p.scalarV(Ap)));
#pragma omp parallel for
		for (int i = 0; i < n; i++) {
			X(i, 0) += alpha * p(i, 0);
			grad(i, 0) -= alpha * Ap(i, 0);
		}
		double grad2Old = grad2;
		grad2 = sqrt(grad.scalarV(grad));
		betta = pow(grad2, 2) / pow(grad2Old, 2);
#pragma omp parallel for
		for (int i = 0; i < n; i++) {
			p(i, 0) = grad(i, 0) + betta * p(i, 0);
		}
		k++;
	}
	//for (int i = 0; i < n; i++) {
	//	std::cout << "X[" << i + 1 << "] = " << X(i, 0) << "\n";
	//}
	

}