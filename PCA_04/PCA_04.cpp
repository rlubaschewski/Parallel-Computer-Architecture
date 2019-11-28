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
	double result;
};

// thread function to generate partial sums of pi approximation
void* approximatePiRunner(void* arg) {
	struct runnerStruct *arg_struct = (struct runnerStruct*)arg;
	double deltaX = 1.0 / arg_struct -> n;
	double x, y, result = 0.0;
	for (int i = arg_struct -> start; i <= arg_struct -> end; i++) {
		x = i * deltaX;
		y = sqrt(1.0 - pow(x, 2));
		result += y * deltaX;
	}
	arg_struct -> result = result;
	pthread_exit(0);
}


int main(int argc, char* argv[]) {
	int n = 1000;
	int numberOfThreads = 200;

	pthread_t threadIds[numberOfThreads];

	struct runnerStruct runnerData[numberOfThreads];

	for (int i = 0; i < numberOfThreads; i++) {
		runnerData[i].start = i * (n / numberOfThreads);
		cout << "start of thread " << i + 1 << " is " << runnerData[i].start << endl;
		runnerData[i].end  = (i + 1) * (n / numberOfThreads) - 1;
		cout << "end of thread " << i + 1 << " is " << runnerData[i].end << endl;
		runnerData[i].n = n;

		pthread_attr_t threadAtrribute;
		pthread_attr_init(&threadAtrribute);
		pthread_create(&threadIds[i], &threadAtrribute, approximatePiRunner, &runnerData[i]);
	}
	double result = 0.0;
	for (int i = 0; i < numberOfThreads; i++) {
		pthread_join(threadIds[i], NULL);
		result += runnerData[i].result;
	}
	result *= 4.0;
	double pi = 3.1415926535897;
	cout.precision(17);
	cout << "The result is " << result << endl;
	cout << "The exact value of pi is " << pi << endl;
}