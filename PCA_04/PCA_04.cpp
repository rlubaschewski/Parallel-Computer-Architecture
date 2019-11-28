#include "PCA_04.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <pthread.h>

using namespace std;

struct runnerStruct {
	int n;
	int start;
	int end;
};

double result = 0.0;
pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER;

// thread function to generate partial sums of pi approximation
void* approximatePiRunner(void* arg) {
	struct runnerStruct *arg_struct = (struct runnerStruct*)arg;
	double deltaX = 1.0 / arg_struct -> n;
	double x, y, partialResult = 0.0;
	for (int i = arg_struct -> start; i <= arg_struct -> end; i++) {
		x = i * deltaX;
		y = sqrt(1.0 - pow(x, 2));
		partialResult += y * deltaX;
	}
	// start critical section
	pthread_mutex_lock(&locker);
	result += partialResult;
	// end critical section
	pthread_mutex_unlock(&locker);
	pthread_exit(0);
}


int main(int argc, char* argv[]) {
	int n = 1000000;
	int numberOfThreads = 32;

	pthread_t threadIds[numberOfThreads];

	struct runnerStruct runnerData[numberOfThreads];
	auto start = chrono::high_resolution_clock::now();
	// spawn all threads
	for (int i = 0; i < numberOfThreads; i++) {
		runnerData[i].start = i * (n / numberOfThreads);
		runnerData[i].end  = (i + 1) * (n / numberOfThreads) - 1;
		runnerData[i].n = n;

		pthread_attr_t threadAtrribute;
		pthread_attr_init(&threadAtrribute);
		pthread_create(&threadIds[i], &threadAtrribute, approximatePiRunner, &runnerData[i]);
	}
	// wait for threads to complete
	for (int i = 0; i < numberOfThreads; i++) {
		pthread_join(threadIds[i], NULL);
	}
	result *= 4.0;
	auto end = chrono::high_resolution_clock::now();
	double pi = 3.1415926535897;
	cout.precision(17);
	cout << "The result is " << result << endl;
	cout << "The exact value of pi is " << pi << endl;
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
	cout << "The approximation of Pi with " << n << " rectangles and " << numberOfThreads << " threads " << " took " << duration << " microseconds" << endl;
}