#include "PCA_04.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <pthread.h>

using namespace std;

double result = 0.0;

// thread function to generate partial sums of pi approximation
void* approximatePiRunner(void* arg) {
	int n = *(int*)arg;
	double deltaX = 1.0 / n;
	double x, y;
	for (int i = 0; i < n; i++) {
		x = i * deltaX;
		y = sqrt(1.0 - pow(x, 2));
		result += y * deltaX;
	}
	result *= 4.0;
	pthread_exit(0);
}


int main(int argc, char* argv[]) {
	int n = 100;
	int numberOfThreads = 1;

	pthread_t threadId;
	pthread_attr_t threadAtrribute;
	pthread_attr_init(&threadAtrribute);

	pthread_create(&threadId, &threadAtrribute, approximatePiRunner, &n);
	pthread_join(&threadId, NULL);

	double pi = 3.1415926535897;
	cout.precision(17);
	cout << "The result is " << result << endl;
	cout << "The exact value of pi is " << pi << endl;
}