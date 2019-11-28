#include "PCA_04.h"

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
	auto startWall = chrono::high_resolution_clock::now();
	int n = atoi(argv[1]);
	int numberOfThreads = atoi(argv[2]);

	if (numberOfThreads > n) {
		throw invalid_argument("Number of threads can't be greater as the number of total iterations!");
	}

	pthread_t threadIds[numberOfThreads];

	struct runnerStruct runnerData[numberOfThreads];
	auto startCompute = chrono::high_resolution_clock::now();
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
	auto endCompute = chrono::high_resolution_clock::now();
	double pi = 3.1415926535897;
	cout.precision(17);
	cout << "The result is " << result << endl;
	cout << "The exact value of pi is " << pi << endl;
	auto durationCompute = chrono::duration_cast<chrono::microseconds>(endCompute - startCompute).count();
	cout << "The approximation of Pi with " << n << " rectangles and " << numberOfThreads << " threads took " << durationCompute << " microseconds" << endl;
	auto endWall = chrono::high_resolution_clock::now();
	auto durationWall = chrono::duration_cast<chrono::microseconds>(endWall - startWall).count();
	cout << "The total execution time of the program is " << durationWall << " microseconds." << endl;
}