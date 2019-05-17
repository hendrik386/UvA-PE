#include "Utility.hpp"

#include <cmath>
#include <iostream>

#include "Constants.hpp"

double Utility::clamp(const double& x) {
	return fmax(fmin(x, 1.0), 0.0);
}

void Utility::logInfo(const std::string& message) {
	std::cout << "\n" << message << std::flush;
}

void Utility::logDebug(const std::string& message) {
	if(DEBUG_INFO) {
		std::cout << "\n" << message << std::flush;
	}
}
