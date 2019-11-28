#include "PCA.h"
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;


double approximatePi(int n) {
	double deltaX = 1.0 / n;
	double result = 0.0;
	double x, y;
	// only measure time for actual approximation
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < n; i++) {
		x = i * deltaX;
		y = sqrt(1.0 - pow(x, 2));
		result += y * deltaX;
	}
	result *= 4.0;
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "The approximation of Pi with " << n << " rectangles" << " took " << duration << " milliseconds" << endl;
	return result;
}


int main(int argc, char* argv[]) { 
	int n = atoi(argv[1]);
	double result = approximatePi(n);
	double pi = 3.1415926535897;
	cout.precision(17);
	cout << "The result is " << result << endl;
	cout << "The exact value of pi is " << pi << endl;
}
