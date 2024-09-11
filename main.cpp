#include <iostream>
#include <cassert>

#include "matrix.h"

#define MATRIX_SIZE 10

using namespace std;

void test() {
	Matrix<int, -1> matrix;
	assert(matrix.size() == 0); // все ячейки свободны
	auto a = matrix[0][0];
	assert(a == -1);
	assert(matrix.size() == 0);
	matrix[100][100] = 314;
	assert(matrix[100][100] == 314);
	assert(matrix.size() == 1);
	// выведется одна строка
	// 100100314
	for(auto c: matrix)
	{
		int x = c.first.first;
		int y = c.first.second;
		int v = c.second;
		//	std::tie(x, y, v) = c;
		std::cout << x << y << v << std::endl;
	}
}

void test2() {
	Matrix<int, 0> matrix;
	assert(matrix.size() == 0);
	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix[i][i] = i;
	}
	assert(matrix.size() == MATRIX_SIZE - 1);

	for (int i = 0; i < MATRIX_SIZE; ++i) {
		matrix[MATRIX_SIZE - i - 1][i] = i;
	}
	assert(matrix.size() == 2 * MATRIX_SIZE - 2);

	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {
			cout << matrix[i][j].value() << " ";
		}
		cout << endl;
	}
	cout << matrix.size() << endl;

	for (auto c: matrix) {
		int x = c.first.first;
		int y = c.first.second;
		int v = c.second;
		//	std::tie(x, y, v) = c;
		std::cout << "(" <<  x << ", " << y << ") = " << v << std::endl;
	}
	assert(matrix.size() == 18);
}

int main()
{
	test();
	test2();

	return 0;
}
