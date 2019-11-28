#include "PCA_02.h"

using namespace std;

typedef vector<vector<double> > matrix;
typedef vector<double> vec;

double getRandomValue()
{
	return (double) rand() / RAND_MAX;
}

void matrixVectorMultiplyRowWise(matrix &A, vec &x, vec &y) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[0].size(); j++) {
			y[i] += A[i][j] * x[j];
		}
	}
}

void matrixVectorMultiplyColumnWise(matrix& A, vec& x, vec& y) {
	for (int j = 0; j < A[0].size(); j++) {
		for (int i = 0; i < A.size(); i++) {
			y[i] += A[i][j] * x[j];
		}
	}
}

void printVector(vec& y) {
	for (int i = 0; i < y.size(); i++) {
		printf("%f\n", y[i]);
	}
}

void printMatrix(matrix& A) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[0].size(); j++) {
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	string columnWiseStr = argv[3];
	bool columnWise = columnWiseStr == "columnWise";
	srand(time(NULL));
	matrix A(m, vec(m, 0.0));

	// fill matrix with random values
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = getRandomValue();
		}
	}
	vec x(m, 0.0);

	// fill vector with random values
	for (int i = 0; i < m; i++) {
		x[i] = getRandomValue();
	}

	// result vector
	vec y(m, 0.0);
	if (columnWise) {
		auto start = chrono::high_resolution_clock::now();
		matrixVectorMultiplyColumnWise(A, x, y);
		auto end = chrono::high_resolution_clock::now();
		cout << "Executing columnwise multiplication..." << endl;
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "The execution time of the multiplication with a " << m << " x " << n << " matrix took " << duration.count() << " microseconds.";
	}
	else {
		auto start = chrono::high_resolution_clock::now();
		matrixVectorMultiplyRowWise(A, x, y);
		auto end = chrono::high_resolution_clock::now();
		cout << "Executing rowwise multiplication..." << endl;
		auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
		cout << "The execution time of the multiplication with a " << m << " x " << n << " matrix took " << duration.count() << " microseconds.";
	}
	
	return 0;
}
