#include "Utility.hpp"

#include <cmath>
#include <iostream>

#include "Constants.hpp"
#include "Vector3.hpp"

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

Vector3D Utility::astronomicalUnitsToMeters(const Vector3D& astronomicalUnits) {
	return astronomicalUnits * astronomicalUnitInMeters;
}

double Utility::astronomicalUnitsToMeters(const double& astronomicalUnits) {
	return astronomicalUnits * astronomicalUnitInMeters;
}

Vector3D Utility::metersToAstronomicalUnits(const Vector3D& meters) {
	return meters / astronomicalUnitInMeters;
}

double Utility::metersToAstronomicalUnits(const double& meters) {
	return meters / astronomicalUnitInMeters;
}
