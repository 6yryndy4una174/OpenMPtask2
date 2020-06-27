#include <iostream>
#include <vector>
#include <ctime>

#include <omp.h>

std::vector<std::vector<int>> generateMatrix(int N) {
	std::vector<std::vector<int>> matrix(N, std::vector<int>(N, 0));
	srand(time(0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			matrix[i][j] = rand();
		}
	}
	return matrix;
}

std::vector<std::vector<int>> mulMat(const std::vector<std::vector<int>>& m1, const std::vector<std::vector<int>>& m2) {
	std::vector<std::vector<int>> out(m1.size(), std::vector<int>(m1.size(), 0));
	for (int i = 0; i < m1.size(); ++i) {
		for (int j = 0; j < m1.size(); ++j) {
			for (int c = 0; c < m1.size(); ++c) {
				out[i][j] += m1[i][c] * m2[c][j];
			}
		}
	}
	return out;
}

std::vector<std::vector<int>> parallelMulMat(const std::vector<std::vector<int>>& m1, const std::vector<std::vector<int>>& m2, int num_threads) {
	std::vector<std::vector<int>> out(m1.size(), std::vector<int>(m1.size(), 0));
	omp_set_num_threads(num_threads);
#pragma omp parallel for
	for (int i = 0; i < m1.size(); ++i) {
		for (int j = 0; j < m1.size(); ++j) {
			for (int c = 0; c < m1.size(); ++c) {
				out[i][j] += m1[i][c] * m2[c][j];
			}
		}
	}
	return out;
}

int main()
{
	int N;
	std::cout << "Enter N: ";
	std::cin >> N;

	std::vector<std::vector<int>> m1 = generateMatrix(N);
	std::vector<std::vector<int>> m2 = generateMatrix(N);

	clock_t start = clock();
	mulMat(m1, m2);
	clock_t end = clock();
	std::cout << "Non parallel " << (end - start) << std::endl;

	start = clock();
	parallelMulMat(m1, m2, 4);
	end = clock();
	std::cout << "Parallel  4 threads " << (end - start) << std::endl;

	start = clock();
	parallelMulMat(m1, m2, 8);
	end = clock();
	std::cout << "Parallel  8 threads " << (end - start) << std::endl;

	start = clock();
	parallelMulMat(m1, m2, 16);
	end = clock();
	std::cout << "Parallel  16 threads " << (end - start) << std::endl;

	start = clock();
	parallelMulMat(m1, m2, 100);
	end = clock();
	std::cout << "Parallel  100 threads " << (end - start) << std::endl;

}