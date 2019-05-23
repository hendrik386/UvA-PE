#include <omp.h>
#include <sys/time.h>
#include <iostream>

#include "Universe.hpp"

int main() {
	// Initialize OpenMP
	// omp_set_num_threads(4);

	// Simulation settings
	const int steps = 50;
	const int renderInterval = 1;

	// Image settings
	const bool createImage = false;
	const int imageWidth = 1024;
	const int imageHeight = 1024;

	// Universe settings
	const int bodyCount = 1024 * 64;
	const double systemSize = 3.5;

	timeval before, after;

	// Perform the actual simulation
	Universe universe(bodyCount, systemSize);
	gettimeofday(&before, NULL);
	universe.simulate(steps, renderInterval, createImage, imageWidth, imageHeight);
	gettimeofday(&after, NULL);
	std::cout << "Time: " <<(double)(after.tv_sec - before.tv_sec) + (double)(after.tv_usec - before.tv_usec) / 1e6 << std::endl;

	return 0;
}
