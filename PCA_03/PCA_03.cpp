#include "PCA_03.h"
using namespace std;

typedef vector<vector<double> > Grid;

Grid generateGrid(int n) {
	Grid grid;
	for (int i = 0; i < n; i++) {
		grid.push_back(vector<double>(n, 0.0));
	}
	return grid;
}

void setCircleWithValue(Grid &grid, double value, int diameter) {
	if (diameter > grid.size()) {
		throw invalid_argument("diameter can't be larger than the size of the grid");
	}
	int startX = floor((grid.size() - diameter) / 2) + floor(diameter / 2);
	int startY = floor(grid.size() / 2);
	int r = floor(diameter / 2);


	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (((i - startX) * (i - startX) + (j - startY) * (j - startY)) <= r * r) {
				grid[i][j] = value;
			}
		}
	}
}


void relaxationInPoint(Grid &grid, int i, int j) {
	const double phi = 6.0 / 25.0;
	// if neighbours are not part of the grid anymore, initialize with 0
	double gridIBefore = i == 0.0 ? 0.0 : grid[i - 1][j];
	double gridJBefore = j == 0.0 ? 0.0 : grid[i][j - 1];
	double gridIAfter = i == grid.size() - 1 ? 0 : grid[i + 1][j];
	double gridJAfter = j == grid.size() - 1 ? 0 : grid[i][j + 1];
	grid[i][j] = grid[i][j] + phi * ((-4) * grid[i][j] + gridIAfter + gridIBefore + gridJAfter + gridJBefore);
}

void relaxationInGrid(Grid &grid) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			relaxationInPoint(grid, i, j);
		}
	}
}

void printGrid(Grid &grid) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			printf("%.17g ", grid[i][j]);
		}
		printf("\n");
	}
}



int main(int argc, char *argv[])
{
	auto startWall = chrono::high_resolution_clock::now();
	int n = atoi(argv[1]);
	Grid grid = generateGrid(n);
	int diameter = atoi(argv[2]);
	int value = stod(argv[3]);
	setCircleWithValue(grid, value, diameter);
	auto startCompute = chrono::high_resolution_clock::now();
	int amountIterations = 1000;
	for (int i = 0; i < amountIterations; i++) {
		relaxationInGrid(grid);
	}
	// printGrid(grid);
	auto endCompute = chrono::high_resolution_clock::now();
	auto durationCompute = chrono::duration_cast<chrono::duration<double> >(endCompute - startCompute);
	auto endWall = chrono::high_resolution_clock::now();
	auto durationWall = chrono::duration_cast<chrono::duration<double> >(endWall - startWall);
	cout << "The relaxation of a " << n << " x " << n << " grid with " << amountIterations << " iterations took " << durationCompute.count() << " seconds";
	cout << "The total execution time of the program is " << durationWall.count() << " seconds";
}
