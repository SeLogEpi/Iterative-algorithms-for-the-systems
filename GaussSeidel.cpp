#include "GaussSeidel.h"
#include "Jacobi.h"

#define Limit 100

	
	void GaussSeidel(Matrix m,double eps) {
		bool flag = check(m);
		double temp;
		int count = 0;
		if (!flag) {
			std::cout << "Matrix is not diagonal dominant! \n";
			return;

		}
		int n = m.getRows();
		int flag1 = 0;
		Matrix X(n, 1, 0);
		do {
			for (int i = 0; i < n; i++) {
				temp = X(i, 0);
				X(i, 0) = m(i, n);
				for (int j = 0; j < n; j++) {
					if (j == i)
						continue;
					X(i, 0) -= (m(i, j) * X(j, 0));
				}
				X(i, 0) = X(i, 0) / m(i, i);
				if (fabs(X(i, 0) - temp) <= eps)
					flag1++;
				std :: cout << "x" << i + 1 << "=" << X(i, 0) << " ";
			}
			count++;
			//std :: cout << "\n";
		} while (flag1 < n && count < Limit);
	}

