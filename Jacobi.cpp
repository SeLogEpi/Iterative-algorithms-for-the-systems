#include "Jacobi.h"
#define Limit 100


bool check(Matrix m) {
	int check_count = 0;
	int matrix_size = m.getRows();
#pragma omp parallel 
	{
		#pragma omp for schedule (guided, 1)
		for (int i = 0; i < matrix_size; i++) {
			double row_sum = 0;
			for (int j = 0; j < matrix_size; j++) {
				if (j != i) row_sum += fabs(m(i,j));
			}

			if (fabs(m(i, i)) >= row_sum) {
			#pragma omp atomic 
				check_count++;
			}
		}
	}
	return check_count == matrix_size;

}


void Jacobi(Matrix matrix, double eps) {
	if (!check(matrix)) {
		std::cout << "Matrix is not diagonal dominant!";
		return;
		}
	int matrix_size = matrix.getRows();
	Matrix X(matrix_size, 1, 0);
	Matrix last_iteration(matrix_size, 1, 0);

	for (int i = 0; i < Limit; i++) {
		last_iteration = X;

#pragma omp parallel for schedule(dynamic, 1)
		for (int j = 0; j < matrix_size; j++) {
			double value = 0;
			for (int k = 0; k < matrix_size; k++) {
				if (j != k) {
					value += matrix(j, k) * X(k, 0);
				}
			}
			X(j, 0) = (matrix(j, matrix_size) - value) / matrix(j, j);
		}

		int stopping_count = 0;
#pragma omp parallel for schedule(dynamic,1)
		for (int s = 0; s < matrix_size; s++) {
			if (fabs(last_iteration(s, 0) - X(s, 0)) <= eps) {
#pragma omp atomic
				stopping_count++;
			}
		}

		if (stopping_count == matrix_size) break;
	}
	/*for (int k = 0; k < matrix_size; k++) {
		std::cout << "X[" << k + 1 << "] = " << X(k, 0) << "\n";
	}*/

}
