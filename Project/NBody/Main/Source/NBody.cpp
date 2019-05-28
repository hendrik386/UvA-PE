#include <omp.h>
#include <sys/time.h>
#include <iostream>

#include "Universe.hpp"

int main(int argc, char *argv[]) {
	// std::cout << __GNUC__ << std::endl;

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
	int bodyCount = 0;
	const double systemSize = 3.5;

	timeval before, after;

	if (argc == 2) {
		bodyCount = std::atoi(argv[1]);
		Universe universe(bodyCount, systemSize);

		gettimeofday(&before, NULL);
		universe.simulate(steps, renderInterval, createImage, imageWidth, imageHeight);
		gettimeofday(&after, NULL);
	}
	else if (argc == 3) {
		bodyCount = std::atoi(argv[2]);
		Universe universe = Universe::loadFromCsvFile(argv[1], systemSize, bodyCount);

		gettimeofday(&before, NULL);
		universe.simulate(steps, renderInterval, createImage, imageWidth, imageHeight);
		gettimeofday(&after, NULL);
	}
	else
	{
		bodyCount = 1024 * 64;
		Universe universe(bodyCount, systemSize);

		gettimeofday(&before, NULL);
		universe.simulate(steps, renderInterval, createImage, imageWidth, imageHeight);
		gettimeofday(&after, NULL);
	}


	// Perform the actual simulation
	std::cout << "Time: " <<(double)(after.tv_sec - before.tv_sec) + (double)(after.tv_usec - before.tv_usec) / 1e6 << std::endl;

	return 0;
}
