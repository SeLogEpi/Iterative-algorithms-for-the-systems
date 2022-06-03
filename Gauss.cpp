#include "Gauss.h"



using namespace std;



int Check(Matrix &m) {
	int N = m.getRows();
	for (int k = 0; k < N; k++) {
		int i_max = k;
		double v_max = m(i_max, k);
		for (int i = k + 1; i < N; i++) {
			if (fabs(m(i, k)) > v_max) {
				v_max = m(i, k);
				i_max = i;
			}
		}
			if (!m(i_max, k)) {
				return k;
			}
			if (i_max != k && m(k,k) == 0) {
				m.SwapRows(i_max, k);
			}
		#pragma omp parallel for
			for (int i = k + 1; i < N; i++) {
				double d = m(i, k) / m(k, k);
				if (d != 0) {
					for (int j = k; j <= N; j++) {
						m(i, j) = m(i, j) - d * m(k, j);
					}
				}
			}
	}

	return -1;
}

void Solutions(Matrix M) {
	int N = M.getRows();
	Matrix X(N, 1, 0);
	
	for (int i = N - 1; i >= 0; i--) {
		X(i,0) = M(i, N);
		for (int j = i + 1; j < N; j++) {
			X(i, 0) -= M(i, j) * X(j, 0);
		}
		X(i, 0) = X(i, 0) / M(i, i);
	}

	std::cout << "Solutions for the system: \n";
	for (int i = 0; i < N; i++)
		std::cout << "X[" <<i + 1 << "] = " << X(i, 0) << "\n";

}

void Gauss(Matrix M) {
	int flag = Check(M);

	if (flag != -1) {
		std::cout << "Matrix is singular \n";
		return;

	}

	Solutions(M);
	

}
