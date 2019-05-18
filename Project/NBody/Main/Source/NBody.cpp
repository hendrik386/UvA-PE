#include <omp.h>

#include "Universe.hpp"

int main() {
	// Initialize OpenMP
	omp_set_num_threads(4);

	// Simulation settings
	const int steps = 50;
	const int renderInterval = 1;

	// Image settings
	const bool createImage = true;
	const int imageWidth = 1024;
	const int imageHeight = 1024;

	// Universe settings
	const int bodyCount = 1024 * 64;
	const double systemSize = 3.5;

	// Perform the actual simulation
	Universe universe(bodyCount, systemSize);
	universe.simulate(steps, renderInterval, createImage, imageWidth, imageHeight);

	return 0;
}
