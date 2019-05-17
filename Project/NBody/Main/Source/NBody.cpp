#include <omp.h>

#include "Universe.hpp"

int main() {
	// Initialize OpenMP
	omp_set_num_threads(4);

	Universe universe(1024 * 64, 1024, 1024);
	universe.simulate();

	return 0;
}
