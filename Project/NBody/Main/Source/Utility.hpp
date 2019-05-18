#pragma once

#include <string>

class Vector3D;

namespace Utility {
	const double pi = 3.14159265358979323846;

	/**
	 * Meters in an AU.
	 */
	const double astronomicalUnitInMeters = 1.496e11;

	double clamp(const double& x);

	void logInfo(const std::string& message);

	void logDebug(const std::string& message);

	Vector3D astronomicalUnitsToMeters(const Vector3D& astronomicalUnits);

	double astronomicalUnitsToMeters(const double& astronomicalUnits);

	Vector3D metersToAstronomicalUnits(const Vector3D& meters);

	double metersToAstronomicalUnits(const double& meters);
}
